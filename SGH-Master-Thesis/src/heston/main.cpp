#include <iostream>
#include <src/main/cpp/statistics/statistics.h>
#include <src/main/cpp/correlated/correlated_snd.h>
#include <src/main/cpp/payoff/payoff.h>
#include <src/main/cpp/option/option.h>
#include <src/main/cpp/heston/header/HestonEuler.h>
#include <src/main/cpp/heston/header/HestonAndersen.h>
#include <src/main/cpp/mc/MonteCarloSimulation.h>

void generate_normal_correlation_paths(double rho,
                                       std::vector<double> &spot_normals, std::vector<double> &cor_normals) {
    unsigned vals = spot_normals.size();

    // Create the Standard Normal Distribution and random draw vectors
    StandardNormalDistribution snd;
    std::vector<double> snd_uniform_draws(vals, 0.0);

    // Simple random number generation method based on RAND
    for (int i = 0; i < snd_uniform_draws.size(); i++) {
        snd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    // Create standard normal random draws
    snd.random_draws(snd_uniform_draws, spot_normals);

    // Create the correlated standard normal distribution
    CorrelatedSND csnd(rho, &spot_normals);
    std::vector<double> csnd_uniform_draws(vals, 0.0);

    // Uniform generation for the correlated SND
    for (int i = 0; i < csnd_uniform_draws.size(); i++) {
        csnd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    // Now create the -correlated- standard normal draw series
    csnd.random_draws(csnd_uniform_draws, cor_normals);
}

int main(int argc, char **argv) {
    // First we create the parameter list
    // Note that you could easily modify this code to input the parameters
    // either from the command line or via a file
    unsigned numSims = 10000;   // Number of simulated asset paths
    unsigned numInts = 1000;  // Number of intervals for the asset path to be sampled

    double S_0 = 100.0;    // Initial spot price
    double K = 100.0;      // Strike price
    double r =  0.0319;     // Risk-free rate
    double v_0 = 0.010201; // Initial volatility
    double T = 1.00;       // One year until expiry

    double rho = -0.7;     // Correlation of asset and volatility
    double kappa = 6.21;   // Mean-reversion rate
    double theta = 0.019;  // Long run average volatility
    double epsilon = 0.61;      // "Vol of vol"

    // Create the PayOff, Option and Heston objects
    PayOff *payOffCall = new PayOffCall(K);
    Option *option = new Option(K, r, T, payOffCall);
     
    HestonEuler hestonEuler(option, kappa, theta, epsilon, rho);
    HestonAndersen hestonAndersen(option, kappa, theta, epsilon, rho);

    // Create the spot and vol initial normal and price paths
    std::vector<double> spot_draws(numInts, 0.0);  // Vector of initial spot normal draws
    std::vector<double> vol_draws(numInts, 0.0);   // Vector of initial correlated vol normal draws
    std::vector<double> spot_prices(numInts, S_0);  // Vector of initial spot prices
    std::vector<double> vol_prices(numInts, v_0);   // Vector of initial vol prices

    // Monte Carlo options pricing
    double payoff_sum = 0.0;
    for (unsigned i = 0; i < numSims; i++) {
//        std::cout << "Calculating path " << i + 1 << " of " << numSims << std::endl;
        generate_normal_correlation_paths(rho, spot_draws, vol_draws);
        hestonEuler.simulateVolPath(vol_draws, vol_prices);
        hestonEuler.simulateSpotPath(spot_draws, vol_prices, spot_prices);
        payoff_sum += option->pay_off->operator()(spot_prices[numInts - 1]);
    }


    double option_price = (payoff_sum / static_cast<double>(numSims)) * exp(-r * T);
    std::cout << "Option Price: " << option_price << std::endl;


    payOffCall = new PayOffCall(K);
    option = new Option(K, r, T, payOffCall);
    payoff_sum = 0.0;

    for (unsigned i = 0; i < numSims; i++) {
//        std::cout << "Calculating path " << i + 1 << " of " << numSims << std::endl;
        hestonAndersen.simulateVolPath(vol_draws, vol_prices);
        hestonAndersen.simulateSpotPath(spot_draws, vol_prices, spot_prices);
        payoff_sum += option->pay_off->operator()(spot_prices[numInts - 1]);
    }

    option_price = (payoff_sum / static_cast<double>(numSims)) * exp(-r * T);
    std::cout << "Option Price: " << option_price << std::endl;

    // Free memory
    delete option;
    delete payOffCall;

    return 0;
}