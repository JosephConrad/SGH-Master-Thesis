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
        : simTrials(simulationTrials),
          timeSteps(timeSteps) {
}

void corellatedNormalPaths(double rho,
                           std::vector<double> &spot_normals, std::vector<double> &cor_normals) {
    unsigned vals = spot_normals.size();

    StandardNormalDistribution snd;
    std::vector<double> snd_uniform_draws(vals, 0.0);

    for (int i = 0; i < snd_uniform_draws.size(); i++) {
        snd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    snd.random_draws(snd_uniform_draws, spot_normals);

    CorrelatedSND csnd(rho, &spot_normals);
    std::vector<double> csnd_uniform_draws(vals, 0.0);

    for (int i = 0; i < csnd_uniform_draws.size(); i++) {
        csnd_uniform_draws[i] = rand() / static_cast<double>(RAND_MAX);
    }

    csnd.random_draws(csnd_uniform_draws, cor_normals);
}


double MonteCarloSimulation::simulate(HestonMC *heston,
                                      Option *option) {
    double payoffSum = 0.0;

    std::vector<double> spotRandom(timeSteps, 0.0);
    std::vector<double> volRandom(timeSteps, 0.0);
    std::vector<double> spotPrices(timeSteps, option->S_0);
    std::vector<double> volPrices(timeSteps, option->v_0);

    double rho = heston->getRho();

    for (auto i = 0; i < simTrials; i++) {
        corellatedNormalPaths(rho, spotRandom, volRandom);
        heston->simulateVolPath(volRandom, volPrices);
        heston->simulateSpotPath(spotRandom, volPrices, spotPrices);
        double expiryPrice = spotPrices[timeSteps - 1];
        payoffSum += option->pay_off->operator()(expiryPrice);
    }

    double discount = option->getDiscountFactor();
    double payoffAvg = payoffSum / static_cast<double>(simTrials);

    double optionPrice = payoffAvg * discount;
    return optionPrice;
}

MonteCarloSimulation::MonteCarloSimulation() {
}

MonteCarloSimulation::~MonteCarloSimulation() {

}