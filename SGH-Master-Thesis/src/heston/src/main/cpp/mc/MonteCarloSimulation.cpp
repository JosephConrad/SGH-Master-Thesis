//
// Created by Konrad Lisiecki on 13/01/16.
//

#include <src/main/cpp/statistics/statistics.h>
#include <src/main/cpp/correlated/correlated_snd.h>
#include <iostream>
#include "MonteCarloSimulation.h"



MonteCarloSimulation::MonteCarloSimulation(
        unsigned int simulationTrials,
        unsigned int timeSteps)
        : simulationTrials(simulationTrials),
          timeSteps(timeSteps) {
    srand(0);
}

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
    //srand(time(NULL));

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


void MonteCarloSimulation::simulate(HestonMC *heston, Option *option) {

    std::vector<double> spot_draws(timeSteps, 0.0);
    std::vector<double> vol_draws(timeSteps, 0.0);
    std::vector<double> spot_prices(timeSteps, option->S_0);
    std::vector<double> vol_prices(timeSteps, option->v_0);


    // Monte Carlo options pricing
    double payoff_sum = 0.0;
    for (unsigned i = 0; i < simulationTrials; i++) {
        generate_normal_correlation_paths(heston->getRho(), spot_draws, vol_draws);
        heston->simulateVolPath(vol_draws, vol_prices);
        heston->simulateSpotPath(spot_draws, vol_prices, spot_prices);
        payoff_sum += option->pay_off->operator()(spot_prices[timeSteps - 1]);
    }

    double discount = option->getDiscountFactor();
    double option_price = (payoff_sum / static_cast<double>(simulationTrials)) * discount;
    std::cout << heston->getName() << "\n\t Option Price:\t" << option_price << std::endl;


}

MonteCarloSimulation::MonteCarloSimulation() {
}

MonteCarloSimulation::~MonteCarloSimulation() {

}