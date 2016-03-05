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



void pprint(std::string str, double d, OutputAndConsole &outputStream) {
    outputStream << d << "\t";
}


void makeSimulation(Simulation &simulation, int &timeStep, OutputAndConsole &outputStream) {

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


    MonteCarloSimulation mc = MonteCarloSimulation(simulation.trials, timeStep);

    HestonEuler *hestonEuler =
            new HestonEuler(option, kappa, theta, epsilon, rho);
    double priceEuler = mc.simulate(hestonEuler, option);
    pprint(hestonEuler->getName(), priceEuler, outputStream);

//    HestonAndersen *hestonAndersen =
//            new HestonAndersen(option, kappa, theta, epsilon, rho);
//    double priceAndersen = mc.simulate(hestonAndersen, option);
//    pprint(hestonAndersen->getName(), priceAndersen, outputStream);
//
//    HestonAndersen *hestonAndersenMartingale =
//            new HestonAndersenMartingale(option, kappa, theta, epsilon, rho);
//    double priceMart = mc.simulate(hestonAndersenMartingale, option);
//    pprint(hestonAndersenMartingale->getName(), priceMart, outputStream);


    HestonExact *hestonExact =
            new HestonExact(option, kappa, theta, epsilon, rho);
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
//    delete hestonAndersen;
//    delete hestonAndersenMartingale;
    delete hestonEuler;
    delete hestonExact;
}


void testCases(std::vector<Simulation>& simulations,
               std::vector<int>& timeSteps) {

    OutputAndConsole output(Config::getInstance().getSettings("Simulation.output"));

    for (Simulation &simulation:simulations) {
        for (int &timeStep: timeSteps) {
            output << std::to_string(timeStep) << "\t";
            makeSimulation(simulation, timeStep, output);
            output << "\n";
        }
    }
}

int main(int argc, char **argv) {

    std::vector<Simulation> simulations;
    std::vector<int> timeSteps;
    JsonReader jsonReader;
    jsonReader.loadConfig("Simulation.input");
    jsonReader.processValuation(simulations);
    jsonReader.getTimeSteps(timeSteps);

    testCases(simulations, timeSteps);
//    calcVolatilitySmile(params, simulationTrials, timeSteps);

    return 0;
}