#include <fstream>
#include <map>
#include <iostream>

#include <src/main/cpp/payoff/payoff.h>
#include <src/main/cpp/heston/header/HestonEuler.h>
#include <src/main/cpp/heston/header/HestonExact.h>
#include <src/main/cpp/heston/header/HestonAndersen.h>
#include <src/main/cpp/heston/header/HestonAndersenMartingale.h>
#include <src/main/cpp/mc/MonteCarloSimulation.h>
#include <src/main/cpp/simulation/Simulation.h>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/tokenizer.hpp>


using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;

void calcVolatilitySmile(char *string, std::vector<double> vector, int i, int i1);

void pprint(std::string str, double d, std::ofstream& ofstream) {

    // << str << ":\t" << d << std::endl;
    ofstream << d << "\t";
}


void makeSimulation(Simulation &simulation, int &timeStep, std::ofstream& outputStream) {

    double S_0 = simulation.asset;
    double K = simulation.strike;
    double r = simulation.riskFree;
    double v_0 = simulation.volatility;
    double T = simulation.expiry;
    double rho = simulation.rho;
    double kappa = simulation.kappa;
    double theta = simulation.theta;
    double epsilon = simulation.eps;

    PayOff *payOffCall = new PayOffCall(K);
    Option *option = new Option(K, r, T, S_0, v_0, payOffCall);

    HestonEuler *hestonEuler =
            new HestonEuler(option, kappa, theta, epsilon, rho);
    HestonAndersen *hestonAndersen =
            new HestonAndersen(option, kappa, theta, epsilon, rho);
    HestonAndersen *hestonAndersenMartingale =
            new HestonAndersenMartingale(option, kappa, theta, epsilon, rho);
    HestonExact *hestonExact =
            new HestonExact(option, kappa, theta, epsilon, rho);

    MonteCarloSimulation mc = MonteCarloSimulation(simulation.trials, timeStep);

    double priceEuler = mc.simulate(hestonEuler, option);
    pprint(hestonEuler->getName(), priceEuler, outputStream);

    double priceAndersen = mc.simulate(hestonAndersen, option);
    pprint(hestonAndersen->getName(), priceAndersen, outputStream);

    double priceMart = mc.simulate(hestonAndersenMartingale, option);
    pprint(hestonAndersenMartingale->getName(), priceMart, outputStream);

    double priceExact = hestonExact->optionPrice(S_0, v_0, 0.0);
    pprint(hestonExact->getName(), priceExact, outputStream);


//    double impliedVol = 0.05;
//    // TODO obliczyc zmiennosc implikowana dla opcji o podanych parametrach
//    BlackScholesAnalytic *bsAnalytic = new BlackScholesAnalytic();
//    MCBlackScholes *mcBlackScholes = new MCBlackScholes(T, K, S_0, impliedVol, r, 100000);
//    pprint("BS SIMULATION", mcBlackScholes->simulate());
//
//    double call = bsAnalytic->call_price(S_0, K, r, impliedVol, T);
//    pprint("BS ANALYTIC", call);
//    pprint("IMPLIED VOL", bsAnalytic->impliedVolatility(S_0, T, call));

    delete option;
    delete payOffCall;
    delete hestonAndersen;
    delete hestonAndersenMartingale;
    delete hestonEuler;
    delete hestonExact;
}



void calcVolatilitySmile(char *fname,
                         std::vector<double> params,
                         int simulationTrials,
                         int timeSteps) {

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
    std::ofstream outputStream("../../output/hestonPrices.txt");

    while (getline(inputStream, line)) {
        std::vector<std::string> params;
        boost::split(params, line, boost::is_any_of(";"), boost::token_compress_on);
        double K1 = std::stod(params[0]);
        double T1 = std::stod(params[2]);
        PayOff *payOffCall = new PayOffCall(K1);
        Option *option1 = new Option(K1, r, T1, S_0, v_0, payOffCall);

        HestonEuler *hestonEuler1 = new HestonEuler(option1, kappa, theta, epsilon, rho);
        double hestonPrice = mc.simulate(hestonEuler1, option1);
        delete hestonEuler1;
        delete option1;
        //pprint("Heston Euler", hestonPrice, outputStream);
        outputStream << S_0 << ";" << K1 << ";" << r << ";" << T1 << ";" << hestonPrice << std::endl;
    }

    delete hestonEuler;
}


ptree loadConfig(std::string filename) {

    static ptree pt;
    read_json(filename, pt);

    return pt;
}


Simulation processOptionParams(const ptree::value_type &node) {

    return Simulation(
            node.second.get<double>("asset"),
            node.second.get<double>("strike"),
            node.second.get<double>("riskFree"),
            node.second.get<double>("expiry"),
            node.second.get<double>("volatility"),
            node.second.get<double>("kappa"),
            node.second.get<double>("theta"),
            node.second.get<double>("eps"),
            node.second.get<double>("rho"),
            node.second.get<int>("trials"),
            node.second.get<double>("truePrice"),
            "desc"
    );
}


void processValuation(char *fname,
                      std::vector<Simulation> &simulations) {

    const ptree &jsonTree = loadConfig(fname);

    for (const ptree::value_type &node: jsonTree.get_child("heston")) {
        simulations.push_back(processOptionParams(node));
    }
}

void testCases(std::vector<Simulation> simulations) {

    std::vector<int> timeSteps
            = {500, 250, 200, 150, 100, 50, 30, 10};
    std::ofstream outputStream("../../output/hestonSimulation.txt");


    for (Simulation &simulation:simulations) {
        for (int &timeStep: timeSteps) {
            outputStream << std::to_string(timeStep) << "\t";
            makeSimulation(simulation, timeStep, outputStream);
            outputStream << std::endl;
        }
    }
    outputStream.close();
}

int main(int argc, char **argv) {

    std::vector<Simulation> simulations;
    processValuation(argv[1], simulations);

    testCases(simulations);
    //calcVolatilitySmile(argv[2], params, simulationTrials, timeSteps);

    return 0;
}