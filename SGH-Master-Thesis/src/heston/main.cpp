#include <src/main/cpp/payoff/payoff.h>
#include <src/main/cpp/option/option.h>
#include <src/main/cpp/heston/header/HestonEuler.h>
#include <src/main/cpp/heston/header/HestonAndersen.h>
#include <src/main/cpp/mc/MonteCarloSimulation.h>
#include <src/main/cpp/heston/header/HestonAndersenMartingale.h>
#include <src/main/cpp/heston/header/HestonExact.h>
#include <iostream>
#include <src/main/cpp/bs/MCBlackScholes.h>


int main(int argc, char **argv) {
//    double S_0 = 207.93;
//    double K = 205.0;
//    double r = 0.03;
//    double v_0 = 0.0395;
//    double T = 0.0356;
    double S_0 = 100.0;
    double K = 100.0;
    double r = 0.05;
    double v_0 = 0.09;
    double T = 5.0;
    PayOff *payOffCall = new PayOffCall(K);
    Option *option = new Option(K, r, T, S_0, v_0, payOffCall);

//    double rho = 0.4031;
//    double kappa = 40.5962;
//    double theta = 0.0098;
//    double epsilon = 0.0022;
    double rho = -0.30;
    double kappa = 2.00;
    double theta = 0.09;
    double epsilon = 1.00;
    HestonEuler *hestonEuler = new HestonEuler(option, kappa, theta, epsilon, rho);
    HestonAndersen *hestonAndersen = new HestonAndersen(option, kappa, theta, epsilon, rho);
    HestonAndersen *hestonAndersenMartingale = new HestonAndersenMartingale(option, kappa, theta, epsilon, rho);
    HestonExact *hestonExact = new HestonExact(option, kappa, theta, epsilon, rho);

    MonteCarloSimulation mc = MonteCarloSimulation();
    mc.simulate(hestonEuler, option);
    mc.simulate(hestonAndersen, option);
    mc.simulate(hestonAndersenMartingale, option);

    hestonExact->optionPrice(log(option->S_0), option->v_0, 0.0);


    double impliedVol = 0.1561; // Initial volatility
    MCBlackScholes *mcBlackScholes = new MCBlackScholes(T, K, S_0, impliedVol, r, 100000);
    std::cout << mcBlackScholes->simulate();

    // Free memory
    delete option;
    delete payOffCall;

    return 0;
}