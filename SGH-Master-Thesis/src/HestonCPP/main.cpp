#include <src/main/cpp/payoff/payoff.h>
#include <src/main/cpp/heston/header/HestonEuler.h>
#include <src/main/cpp/heston/header/HestonExact.h>
#include <src/main/cpp/heston/header/HestonAndersen.h>
#include <src/main/cpp/heston/header/HestonAndersenMartingale.h>
#include <src/main/cpp/mc/MonteCarloSimulation.h>
#include <src/main/cpp/simulation/Simulation.h>
#include <src/main/cpp/tools/config/Config.h>
#include <src/main/cpp/tools/output/OutputAndConsole.h>

#include <boost/property_tree/json_parser.hpp>
#include <src/main/cpp/tools/json/JsonReader.h>
#include <src/main/cpp/heston/header/HestonExactLittleTrap.h>
#include <src/main/cpp/volatilitysmile/VolatilitySmile.h>

static const std::string DELIMITER = ";";

void pprint(double d, OutputAndConsole &outputStream) {
    outputStream << std::fixed;
    outputStream << std::setprecision(3);
    outputStream << d << "\t";
}

void printStatistics(BasicStatistics statistics,
                     double exactPrice,
                     OutputAndConsole &outputStream) {
    pprint(statistics.getMean(), outputStream);
    pprint(statistics.bias(exactPrice), outputStream);
    pprint(statistics.getStandardError(), outputStream);
}

void makeSimulation(Simulation &simulation, double &K, int &timeStep,
                    int &trials, OutputAndConsole &outputStream) {

    double S_0 = simulation.asset;
    double r = simulation.riskFree;
    double v_0 = simulation.volatility;
    double T = simulation.expiry;
    double rho = simulation.rho;
    double kappa = simulation.kappa;
    double theta = simulation.theta;
    double epsilon = simulation.eps;

    MonteCarloSimulation mc = MonteCarloSimulation(trials, timeStep);


    PayOff *payOffCall = new PayOffCall(K);
    Option *option = new Option(K, r, T, S_0, v_0, payOffCall);


    HestonExact *hestonExact =
            new HestonExact(option, kappa, theta, epsilon, rho);
    double priceExact = hestonExact->optionPrice(S_0, v_0, 0.0);

    HestonExactLittleTrap *hestonExactLittleTrap =
            new HestonExactLittleTrap(option, kappa, theta, epsilon, rho);
    double priceExactLittleTrap = hestonExactLittleTrap->optionPrice(S_0, v_0, 0.0);
    std::cout << priceExactLittleTrap << std::endl;
//    HestonMC *hestonEuler =
//            new HestonEuler(option, kappa, theta, epsilon, rho);
//    BasicStatistics bsEuler = mc.simulate(hestonEuler, option);
//
//    printStatistics(bsEuler, priceExactLittleTrap, outputStream);
//
//
//    HestonMC *hestonAndersen =
//            new HestonAndersen(option, kappa, theta, epsilon, rho);
//    BasicStatistics bsAndersen = mc.simulate(hestonAndersen, option);
//
//    printStatistics(bsAndersen, priceExactLittleTrap, outputStream);
//
//
//    HestonMC *hestonAndersenMartingale =
//            new HestonAndersenMartingale(option, kappa, theta, epsilon, rho);
//    BasicStatistics bsMartingale = mc.simulate(hestonAndersenMartingale, option);
//
//    printStatistics(bsMartingale, priceExactLittleTrap, outputStream);

    delete option;
    delete payOffCall;
//    delete hestonAndersen;
//    delete hestonAndersenMartingale;
//    delete hestonEuler;
    delete hestonExact;
    delete hestonExactLittleTrap;
}


void testCases(std::vector<Simulation> simulations, std::vector<int> timeSteps,
               std::vector<int> trials) {

    OutputAndConsole output(Config::getInstance().getSettings("Simulation.output"));

    for (Simulation &simulation:simulations) {
        output << "No\tN\t\tEUL\t\tBias\tSE\t\tAND\t\tBias\tSE\t\tMAR\t\tBias\tSE\t\tEXACT\n";
        for (double &K: simulation.strikePrices) {
            output << "\tK = " << std::to_string(K) << "\n";
            for (int i = 0; i < timeSteps.size(); ++i) {
                output << std::to_string(timeSteps[i]) << "\t";
                output << std::to_string(trials[i]) << "\t";
                makeSimulation(simulation, K, timeSteps[i], trials[i], output);
                output << "\n";
            }
        }
    }
}

int main(int argc, char **argv) {

    Config::getInstance().loadConfig(argv[1]);

    std::vector<Simulation> simulations;
    std::vector<int> timeSteps;
    std::vector<int> trials;
    JsonReader jsonReader;
    jsonReader.loadConfig("Simulation.input");
    jsonReader.processValuation(simulations);
    jsonReader.getVector(timeSteps, "timeSteps");
    jsonReader.getVector(trials, "trials");

    testCases(simulations, timeSteps, trials);
    VolatilitySmile volatilitySmile;
    volatilitySmile.calcVolatilitySmile(simulations[1], 30000, timeSteps[3]);

    return 0;
}