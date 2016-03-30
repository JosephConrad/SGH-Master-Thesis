#ifndef HESTON_MONTECARLOSIMULATION_H
#define HESTON_MONTECARLOSIMULATION_H

#include <src/main/cpp/heston/header/HestonMC.h>
#include <src/main/cpp/statistics/BasicStatistics.h>

class MonteCarloSimulation {
private:

    int simTrials;
    int timeSteps;

public:

    MonteCarloSimulation(int simulationTrials,
                         int timeSteps);

    BasicStatistics simulate(HestonMC *heston, Option *option);

    MonteCarloSimulation();

    virtual ~MonteCarloSimulation();
};

#endif //HESTON_MONTECARLOSIMULATION_H
