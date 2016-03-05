//
// Created by Konrad Lisiecki on 05/03/16.
//

#ifndef HESTON_VOLATILITYSMILE_H
#define HESTON_VOLATILITYSMILE_H


#include <vector>

class VolatilitySmile {

public:
    VolatilitySmile();

    ~VolatilitySmile();

    void calcVolatilitySmile(std::vector<double> params,
                             int simulationTrials,
                             int timeSteps);
};


#endif //HESTON_VOLATILITYSMILE_H
