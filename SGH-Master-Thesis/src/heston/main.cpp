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

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


static boost::property_tree::ptree pt;

void makeSimulation(std::vector<double> params, int simulationTrials, int timeSteps) {

    double S_0 = params[0];
    double K = params[1];
    double r = params[2];
    double v_0 = params[3];
    double T = params[4];

//    double S_0 = 100.0;
//    double K = 100.0;
//    double r = 0.05;
//    double v_0 = 0.09;
//    double T = 5.0;
//
    double rho = params[5];
    double kappa = params[6];
    double theta = params[7];
    double epsilon = params[7];
//    double rho = -0.30;
//    double kappa = 2.00;
//    double theta = 0.09;
//    double epsilon = 1.00;
//    double impliedVol = 0.1561; // Initial volatility
//
//
    PayOff *payOffCall = new PayOffCall(K);
    Option *option = new Option(K, r, T, S_0, v_0, payOffCall);

    HestonEuler *hestonEuler = new HestonEuler(option, kappa, theta, epsilon, rho);
    HestonAndersen *hestonAndersen = new HestonAndersen(option, kappa, theta, epsilon, rho);
    HestonAndersen *hestonAndersenMartingale = new HestonAndersenMartingale(option, kappa, theta, epsilon, rho);
    HestonExact *hestonExact = new HestonExact(option, kappa, theta, epsilon, rho);

    MonteCarloSimulation mc = MonteCarloSimulation(simulationTrials, timeSteps);
    mc.simulate(hestonEuler, option);
    mc.simulate(hestonAndersen, option);
    mc.simulate(hestonAndersenMartingale, option);

    hestonExact->optionPrice(log(option->S_0), option->v_0, 0.0);

//    MCBlackScholes *mcBlackScholes = new MCBlackScholes(T, K, S_0, impliedVol, r, 100000);
//    std::cout << mcBlackScholes->simulate();

    delete option;
    delete payOffCall;
    delete hestonAndersen;
    delete hestonAndersenMartingale;
    delete hestonEuler;
    delete hestonExact;
}


void loadConfig(std::string filename) {
    boost::property_tree::read_json(filename, pt);
    return;
}

void processInput(const ptree &tree) {
    for (const ptree::value_type &node: tree.get_child("heston")) {
        std::vector<double> params{
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
        int simulationTrials = node.second.get<int>("trials");
        int timeSteps = node.second.get<int>("timeSteps");
        makeSimulation(params, simulationTrials, timeSteps);
    }
}


int main(int argc, char **argv) {
    std::ifstream ifs(argv[1]);
    std::string content((std::istreambuf_iterator<char>(ifs)),
                        (std::istreambuf_iterator<char>()));
    ptree json;
    std::istringstream is(content);
    loadConfig(argv[1]);
    processInput(pt);
}
