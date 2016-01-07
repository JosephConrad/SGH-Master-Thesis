#include <vector>
#include <stdlib.h>
#include <ostream>
#include <iostream>
#include "MCHeston.h"
#include "../statistics.h"
#include "../correlated_snd.h"
#include "../payoff.h"
#include "../option.h"
#include "../HestonModel/header/HestonEuler.h"
#include <fstream>
#include <sstream>

MCHeston::MCHeston() { };

MCHeston::~MCHeston() { };

double MCHeston::simulateHeston(std::vector<double> modelParams, std::vector<double> initParams, std::ofstream& outputFile) {

    unsigned num_sims = 10000;              // Number of simulated asset paths
    unsigned numIntervals = 1000;          // Number of intervals for the asset path to be sampled

    double initPrice = initParams[0];       // Initial spot price
    double strike = initParams[1];          // strike price
    double riskFreeRate = initParams[2];    // Risk-free rate
    double initVol = initParams[3];         // Initial volatility
    double timeToExpiry = initParams[4];    // One year until expiry

    double rho = modelParams[0];          // Correlation of asset and volatility
    double kappa = modelParams[1];          // Mean-reversion rate
    double theta = modelParams[2];          // Long run average volatility
    double sigma = modelParams[3];          // Volatiliry of volatility

    // Create the PayOff, Option and Heston objects
    PayOff *payOffCall = new PayOffCall(strike);
    Option *callOption = new Option(strike, riskFreeRate, timeToExpiry, payOffCall);
    HestonEuler hestonEuler(callOption, kappa, theta, sigma, rho);

    // Create the spot and vol initial normal and price paths
    std::vector<double> spot_draws(numIntervals, 0.0);  // Vector of initial spot normal draws
    std::vector<double> vol_draws(numIntervals, 0.0);   // Vector of initial correlated vol normal draws
    std::vector<double> spot_prices(numIntervals, initPrice);  // Vector of initial spot prices
    std::vector<double> vol_prices(numIntervals, initVol);   // Vector of initial vol prices

    int chartInterval = 300;
    double chartData[numIntervals][num_sims / chartInterval];


    // Monte Carlo options pricing
    double payoffSum = 0.0;
    int matlabIndex = 0;
    for (unsigned i = 0; i < num_sims; i++) {
        //std::cout << "Calculating path " << i + 1 << " of " << num_sims << std::endl;
        generate_normal_correlation_paths(rho, spot_draws, vol_draws);
        hestonEuler.simulateVolPath(vol_draws, vol_prices);
        hestonEuler.simulateSpotPath(spot_draws, vol_prices, spot_prices);

        if (i % chartInterval == 0) {
            for (auto j = 0; j < spot_prices.size(); ++j) {
                chartData[j][matlabIndex] = spot_prices[j];
            }
            matlabIndex++;
        }
        payoffSum += callOption->pay_off->operator()(spot_prices[numIntervals - 1]);
    }

    for (auto i = 0; i < numIntervals; ++i) {
        for (auto j = 0; j < num_sims / chartInterval; ++j) {
            (outputFile) << chartData[i][j] << ";";
        }
        (outputFile) << ";" << initPrice << std::endl;
    }

    double option_price = (payoffSum / static_cast<double>(num_sims)) * exp(-riskFreeRate * timeToExpiry);
    //std::cout << "Option Price: " << option_price << std::endl;

    // Free memory
    delete callOption;
    delete payOffCall;
    return option_price;
}

void MCHeston::generate_normal_correlation_paths(double rho,
                                                 std::vector<double> &spot_normals,
                                                 std::vector<double> &cor_normals) {
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
