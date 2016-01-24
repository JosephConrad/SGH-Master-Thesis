//
// Created by Konrad Lisiecki on 13/01/16.
//

#ifndef HESTON_MONTECARLOSIMULATION_H
#define HESTON_MONTECARLOSIMULATION_H


#include <src/main/cpp/heston/header/HestonEuler.h>

class MonteCarloSimulation {
private:

    unsigned int simulationTrials;
    unsigned int timeSteps;

public:

    MonteCarloSimulation(unsigned int simulationTrials, unsigned int timeSteps);

    void simulate(HestonMC *heston, Option *option);

    MonteCarloSimulation();

    virtual ~MonteCarloSimulation();
};


#endif //HESTON_MONTECARLOSIMULATION_H
