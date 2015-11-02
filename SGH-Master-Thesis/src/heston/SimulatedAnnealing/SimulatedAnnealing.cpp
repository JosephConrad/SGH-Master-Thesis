//
// Created by Konrad Lisiecki on 26/09/15.
//

#include <stdlib.h>
#include <math.h>
#include "SimulatedAnnealing.h"


SimulatedAnnealing::SimulatedAnnealing() {
    mcSimulation = new MonteCarloSimulation();
}

std::vector<double> SimulatedAnnealing::
calibration(std::vector<double> &bestHestonParams, int iterations, double coolingCoeff) {

    double bestHestonPrice = mcSimulation->simulateHeston(bestHestonParams, (__1::vector<double>()));
    double newHestonPrice;
    double temperature = 1.0;

    std::vector<double> newHestonParams;
    int k = 0;

    while (k < iterations) {
        newHestonParams = mutateParams(bestHestonParams);
        newHestonPrice = mcSimulation->simulateHeston(newHestonParams, (__1::vector<double>()));

        if (metropolisRule(bestHestonPrice, newHestonPrice, temperature)) {
            bestHestonParams = newHestonParams;
            bestHestonPrice = newHestonPrice;
        }

        temperature = coolingSchedule(temperature, coolingCoeff);
        k++;
    }
    return bestHestonParams;
}


double SimulatedAnnealing::coolingSchedule(double temperature, double coolingCoeff) {
    return coolingCoeff * temperature;
}


bool SimulatedAnnealing::metropolisRule(double bestSolution, double newSolution, double temperature) {
    if (newSolution < bestSolution)
        return true;
    return activationEnergyAchieved(bestSolution, newSolution, temperature);
}


bool SimulatedAnnealing::activationEnergyAchieved(double bestSol, double newSol, double temperature) {
    return calcEnergy(bestSol, newSol, temperature) > static_cast<double>(rand());
}


double SimulatedAnnealing::calcEnergy(double bestSol, double newSol, double temperature) {
    return exp((-1) * (bestSol - newSol) / temperature);
}

std::vector<double> SimulatedAnnealing::mutateParams(const std::vector<double> &hestonParams) {
    auto newHestonParams = hestonParams;
    int change = rand() % 4;
    double mutationParam = hestonParams[change];
    bool up = (rand() % 2);
    if (up) {
        mutationParam += 0.01;
    } else
    {
        mutationParam -= 0.01;
    }
    newHestonParams[change] = mutationParam;
    return newHestonParams;
}
