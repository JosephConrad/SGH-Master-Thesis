//
// Created by Konrad Lisiecki on 26/09/15.
//

#ifndef HESTON_SIMULATEDANNEALING_H
#define HESTON_SIMULATEDANNEALING_H


#include <vector>
#include <jmorecfg.h>
#include "../MonteCarlo/MonteCarloSimulation.h"

class SimulatedAnnealing {

private:
    float bestSolutionEnergy;
    MonteCarloSimulation *mcSimulation;


public:
    SimulatedAnnealing();

    virtual void simulation(std::vector<double> &dist_draws);

private:
    int mut(int x);

    double calcEnergy(float bestSolution, float newSolution, int temperature);

    bool activationEnergyAchieved(float bestSolution, float newSolution, int temperature);

    boolean MetropolisRule(float bestSolution, float newSolution, int temperature);
};


#endif //HESTON_SIMULATEDANNEALING_H
