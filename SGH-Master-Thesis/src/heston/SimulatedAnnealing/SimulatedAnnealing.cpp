//
// Created by Konrad Lisiecki on 26/09/15.
//

#include <jmorecfg.h>
#include <stdlib.h>
#include <math.h>
#include "SimulatedAnnealing.h"


SimulatedAnnealing::SimulatedAnnealing() {
    mcSimulation = new MonteCarloSimulation();
}

void SimulatedAnnealing::simulation(std::vector<double> &dist_draws) {

    float T = 1;
    float k = 0;
    int x = 3;
    int n1 = 4;
    int n2 = 3;
    while (k != n1) {
        int i = 0;
        while (i != n2) {
            i++;
            int z = mut(x);
            if (MetropolisRule(x, z, f, T)) {
                x = z;
            }
        }
        k = k + n2;
        T = a * T;

    }

}

int SimulatedAnnealing::mut(int x) {
    return 0;
}


boolean SimulatedAnnealing::MetropolisRule(float bestSolution, float newSolution, int temperature) {
    if (newSolution < bestSolution)
        return true;
    if (activationEnergyAchieved(bestSolution, newSolution, temperature))
        return true;
    return false;
}

bool SimulatedAnnealing::activationEnergyAchieved(float bestSolution, float newSolution, int temperature) {
    return calcEnergy(bestSolution, newSolution, temperature) > static_cast<double>(rand());
}

double SimulatedAnnealing::calcEnergy(float bestSolution, float newSolution, int temperature) {
    return exp((-1) * bestSolution - newSolution / temperature);
}

