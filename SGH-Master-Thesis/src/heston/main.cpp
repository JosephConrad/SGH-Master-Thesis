#include <src/main/cpp/payoff/payoff.h>
#include <src/main/cpp/option/option.h>
#include <src/main/cpp/heston/header/HestonEuler.h>
#include <src/main/cpp/heston/header/HestonAndersen.h>
#include <src/main/cpp/mc/MonteCarloSimulation.h>
#include <src/main/cpp/heston/header/HestonAndersenMartingale.h>


int main(int argc, char **argv) {

    double S_0 = 100.0;
    double K = 100.0;
    double r =  0.0319;
    double v_0 = 0.010201;
    double T = 1.00;
    PayOff *payOffCall = new PayOffCall(K);
    Option *option = new Option(K, r, T, S_0, v_0, payOffCall);

    double rho = -0.7;
    double kappa = 6.21;
    double theta = 0.019;
    double epsilon = 0.61;
    HestonEuler* hestonEuler = new HestonEuler(option, kappa, theta, epsilon, rho);
    HestonAndersen* hestonAndersen = new HestonAndersen(option, kappa, theta, epsilon, rho);
    HestonAndersen* hestonAndersenMartingale = new HestonAndersenMartingale(option, kappa, theta, epsilon, rho);

    MonteCarloSimulation mc = MonteCarloSimulation();

   // mc.simulate(hestonEuler, option);
    mc.simulate(hestonAndersen, option);
    mc.simulate(hestonAndersenMartingale, option);
    // Free memory
    delete option;
    delete payOffCall;

    return 0;
}