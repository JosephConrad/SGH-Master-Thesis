#include <src/main/cpp/payoff/payoff.h>
#include <src/main/cpp/heston/header/HestonEuler.h>
#include <src/main/cpp/heston/header/HestonExact.h>
#include <iostream>
#include <boost/algorithm/string/split.hpp>
#include <fstream>
#include <map>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <src/main/cpp/heston/header/HestonAndersen.h>
#include <src/main/cpp/heston/header/HestonAndersenMartingale.h>
#include <src/main/cpp/mc/MonteCarloSimulation.h>
#include <src/main/cpp/bs/MCBlackScholes.h>
#include <src/main/cpp/bs/BlackScholesAnalytic.h>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/classification.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


//void processVolatilitySmile(char *string);
//
//void calcVolatilitySmile(std::vector<double> vector);

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

    double hestonPrice = mc.simulate(hestonEuler, option);
    std::ofstream outf("impVol.txt");
    outf << S_0 << ";" << K << ";" << r << ";" << T << ";" << hestonPrice << std::endl;
    //prepareImpliedVolatility


    double impliedVol = 0.2;
    // black scholes implied volatility important
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


boost::property_tree::ptree loadConfig(std::string filename) {
    static boost::property_tree::ptree pt;
    boost::property_tree::read_json(filename, pt);
    return pt;
}

void processValuation(char *fname, std::vector<double> &params, int &simulationTrials, int &timeSteps) {

    const ptree &jsonTree = loadConfig(fname);
//    std::ifstream ifs(fname);
//    std::string content((std::istreambuf_iterator<char>(ifs)),
//                        (std::istreambuf_iterator<char>()));
//    ptree json;
//    std::istringstream is(content);
    for (const ptree::value_type &node: jsonTree.get_child("heston")) {
        params = {
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
        simulationTrials = node.second.get<int>("trials");
        timeSteps = node.second.get<int>("timeSteps");
    }
}


int main(int argc, char **argv) {
    std::vector<double> params;
    int simulationTrials, timeSteps;
    processValuation(argv[1], params, simulationTrials, timeSteps);
    makeSimulation(params, simulationTrials, timeSteps);
}


//std::vector<double> processLine(std::string str) {
//    std::vector<std::string> vectorStr;
//    std::vector<double> vectorDouble;
//    boost::split(vectorStr, str, boost::is_any_of(";"), boost::token_compress_on);
//    std::transform(vectorStr.begin(),
//                   vectorStr.end(),
//                   std::back_inserter(vectorDouble),
//                   [](const int &p) { return static_cast<double>(p); });
//    return vectorDouble;
//}

void processVolatilitySmile(char *fname) {

    std::ifstream file(fname);
    std::string line;

    while (getline(file, line)) {
        std::vector<std::string> params;
        boost::split(params, line, boost::is_any_of(";"), boost::token_compress_on);
        std::vector<double> paramsDouble{
                std::stod(params[0]),
                std::stod(params[1]),
                std::stod(params[2])
        };
//        calcVolatilitySmile(paramsDouble);
    }

}

//void calcVolatilitySmile(std::vector<double> params, std::vector<double> params) {
//    // params (timeToExpiry, kappa, cena)
//    double S_0 = params[0];
//    double K = params[1];
//    double r = params[2];
//    double v_0 = params[3];
//    double T = params[4];
//    double rho = params[5];
//    double kappa = params[6];
//    double theta = params[7];
//    double epsilon = params[8];
//
//    PayOff *payOffCall = new PayOffCall(K);
//    Option *option = new Option(K, r, T, S_0, v_0, payOffCall);
//
//    HestonEuler *hestonEuler = new HestonEuler(option, kappa, theta, epsilon, rho);
//    MonteCarloSimulation mc = MonteCarloSimulation(simulationTrials, timeSteps);
//    mc.simulate(hestonEuler, option);
//}
