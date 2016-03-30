//
// Created by Konrad Lisiecki on 05/03/16.
//

#ifndef HESTON_VOLATILITYSMILE_H
#define HESTON_VOLATILITYSMILE_H


#include <vector>
#include <src/main/cpp/simulation/Simulation.h>

class VolatilitySmile {

public:
    VolatilitySmile();

    void calcVolatilitySmile(Simulation simulation,
                             int simulationTrials,
                             int timeSteps);
};


#endif //HESTON_VOLATILITYSMILE_H
