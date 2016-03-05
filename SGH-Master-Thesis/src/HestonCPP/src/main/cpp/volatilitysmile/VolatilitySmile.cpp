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


VolatilitySmile::VolatilitySmile() { }


void VolatilitySmile::calcVolatilitySmile(std::vector<double> params,
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
    std::ifstream ifstream(Config::getInstance().getSettings("VolatilitySurface.input"));
    std::ofstream ofstream(Config::getInstance().getSettings("VolatilitySurface.output"));

    while (getline(ifstream, line)) {
        std::vector <std::string> params;
        boost::split(params, line, boost::is_any_of(";"), boost::token_compress_on);
        double K1 = std::stod(params[0]);
        double T1 = std::stod(params[2]);
        PayOff *payOffCall = new PayOffCall(K1);
        Option *option1 = new Option(K1, r, T1, S_0, v_0, payOffCall);

        HestonEuler *hestonEuler1 = new HestonEuler(option1, kappa, theta, epsilon, rho);
        double hestonPrice = mc.simulate(hestonEuler1, option1);

        ofstream << S_0 << ";" << K1 << ";" << r << ";" << T1 << ";" << hestonPrice << "\n";

        delete hestonEuler1;
        delete option1;
        //pprint("Heston Euler", hestonPrice, ofstream);
    }

    delete hestonEuler;
}
