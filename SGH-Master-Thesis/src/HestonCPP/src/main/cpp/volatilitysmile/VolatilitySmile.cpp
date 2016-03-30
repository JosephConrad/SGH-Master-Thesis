//
// Created by Konrad Lisiecki on 05/03/16.
//

#include <src/main/cpp/payoff/payoff.h>
#include <src/main/cpp/heston/header/HestonEuler.h>
#include <src/main/cpp/mc/MonteCarloSimulation.h>
#include <src/main/cpp/tools/config/Config.h>
#include <fstream>
#include "VolatilitySmile.h"

#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include <src/main/cpp/tools/output/OutputAndConsole.h>


VolatilitySmile::VolatilitySmile() { }


void VolatilitySmile::calcVolatilitySmile(Simulation simulation,
                                          int simulationTrials,
                                          int timeSteps) {

    double S_0 = simulation.asset;
    double K = simulation.strikePrices[1];
    double r = simulation.riskFree;
    double v_0 = simulation.volatility;
    double T = simulation.expiry;
    double rho = simulation.rho;
    double kappa = simulation.kappa;
    double theta = simulation.theta;
    double epsilon = simulation.eps;

    MonteCarloSimulation mc = MonteCarloSimulation(simulationTrials, timeSteps);

    std::string line;
    std::ifstream ifstream(Config::getInstance().getSettings("VolatilitySurface.input"));
    OutputAndConsole ofstream(Config::getInstance().getSettings("VolatilitySurface.output"));

    while (getline(ifstream, line)) {
        std::vector <std::string> params;
        boost::split(params, line, boost::is_any_of(";"), boost::token_compress_on);
        double K1 = std::stod(params[0]);
        double T1 = std::stod(params[1]);
        PayOff *payOffCall = new PayOffCall(K1);
        Option *option1 = new Option(K1, r, T1, S_0, v_0, payOffCall);

        HestonEuler *hestonEuler1 = new HestonEuler(option1, kappa, theta, epsilon, rho);
        BasicStatistics bsEuler = mc.simulate(hestonEuler1, option1);

        ofstream << S_0 << ";" << K1 << ";" << r << ";" << T1 << ";" << bsEuler.getMean() << "\n";

        delete hestonEuler1;
        delete option1;
    }
}
