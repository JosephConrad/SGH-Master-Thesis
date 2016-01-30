#include <fstream>
#include <map>
#include <iostream>

#include <src/main/cpp/payoff/payoff.h>
#include <src/main/cpp/heston/header/HestonEuler.h>
#include <src/main/cpp/heston/header/HestonExact.h>
#include <src/main/cpp/heston/header/HestonAndersen.h>
#include <src/main/cpp/heston/header/HestonAndersenMartingale.h>
#include <src/main/cpp/mc/MonteCarloSimulation.h>
#include <src/main/cpp/bs/MCBlackScholes.h>
#include <src/main/cpp/bs/BlackScholesAnalytic.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/tokenizer.hpp>

void calcVolatilitySmile(char *string, std::vector<double> vector, int i, int i1);

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


void makeSimulation(std::vector<double> params, int simulationTrials, int timeSteps) {

    double S_0 = params[0];
    double K = params[1];
    double r = params[2];
    double v_0 = params[3];
    double T = params[4];
    double rho = params[5];
    double kappa = params[6];
    double theta = params[7];
    double epsilon = params[8];

    PayOff *payOffCall = new PayOffCall(K);
    Option *option = new Option(K, r, T, S_0, v_0, payOffCall);

    HestonEuler *hestonEuler = new HestonEuler(option, kappa, theta, epsilon, rho);
    HestonAndersen *hestonAndersen = new HestonAndersen(option, kappa, theta, epsilon, rho);
    HestonAndersen *hestonAndersenMartingale = new HestonAndersenMartingale(option, kappa, theta, epsilon, rho);
    HestonExact *hestonExact = new HestonExact(option, kappa, theta, epsilon, rho);

    MonteCarloSimulation mc = MonteCarloSimulation(simulationTrials, timeSteps);
    mc.simulate(hestonEuler, option);
    //mc.simulate(hestonAndersen, option);
    //mc.simulate(hestonAndersenMartingale, option);


    double impliedVol = 0.2;
    BlackScholesAnalytic *bsAnalytic = new BlackScholesAnalytic();
    MCBlackScholes *mcBlackScholes = new MCBlackScholes(T, K, S_0, impliedVol, r, 100000);
    std::cout << "BS SIMULATION:\t" << mcBlackScholes->simulate() << std::endl;
    double call = bsAnalytic->call_price(S_0, K, r, impliedVol, T);

    std::cout << "BS ANALYTIC:\t" << call << std::endl;
    std::cout << "IMPLIED VOL:\t" << bsAnalytic->impliedVolatility(S_0, T, call) << std::endl;

    delete option;
    delete payOffCall;
    delete hestonAndersen;
    delete hestonAndersenMartingale;
    delete hestonEuler;
    delete hestonExact;
}



void calcVolatilitySmile(char *fname, std::vector<double> params, int simulationTrials, int timeSteps) {
    double S_0 = params[0];
    double K = params[1];
    double r = params[2];
    double v_0 = params[3];
    double T = params[4];
    double rho = params[5];
    double kappa = params[6];
    double theta = params[7];
    double epsilon = params[8];

    PayOff *payOffCall = new PayOffCall(K);
    Option *option = new Option(K, r, T, S_0, v_0, payOffCall);

    HestonEuler *hestonEuler = new HestonEuler(option, kappa, theta, epsilon, rho);

    MonteCarloSimulation mc = MonteCarloSimulation(simulationTrials, timeSteps);
    mc.simulate(hestonEuler, option);

    std::string line;
    std::ifstream inputStream(fname);
    std::ofstream outputStream("impVol.txt");

    while (getline(inputStream, line)) {
        std::vector<std::string> params;
        boost::split(params, line, boost::is_any_of(";"), boost::token_compress_on);
        K = std::stod(params[0]);
//        double strike = std::stod(params[1]);
        T = std::stod(params[2]);
        option = new Option(K, r, T, S_0, v_0, payOffCall);

        double hestonPrice = mc.simulate(hestonEuler, option);
        outputStream << S_0 << ";" << K << ";" << r << ";" << T << ";" << hestonPrice << std::endl;
    }

    delete hestonEuler;
}



boost::property_tree::ptree loadConfig(std::string filename) {
    static boost::property_tree::ptree pt;
    boost::property_tree::read_json(filename, pt);
    return pt;
}

std::vector<double> processOptionParams(const ptree::value_type &node) {
    return {
            node.second.get<double>("asset"),
            node.second.get<double>("strike"),
            node.second.get<double>("riskFree"),
            node.second.get<double>("volatility"),
            node.second.get<double>("expiry"),
            node.second.get<double>("rho"),
            node.second.get<double>("kappa"),
            node.second.get<double>("theta"),
            node.second.get<double>("epsilon")
    };
}

void processValuation(char *fname, std::vector<double> &params, int &simulationTrials, int &timeSteps) {

    const ptree &jsonTree = loadConfig(fname);
    for (const ptree::value_type &node: jsonTree.get_child("heston")) {
        params = processOptionParams(node);
        simulationTrials = node.second.get<int>("trials");
        timeSteps = node.second.get<int>("timeSteps");
    }
}


int main(int argc, char **argv) {
    std::vector<double> params;
    int simulationTrials, timeSteps;
    processValuation(argv[1], params, simulationTrials, timeSteps);
    makeSimulation(params, simulationTrials, timeSteps);
    calcVolatilitySmile(argv[2], params, simulationTrials, timeSteps);
}