//
// Created by Konrad Lisiecki on 13/01/16.
//

#ifndef HESTON_MONTECARLOSIMULATION_H
#define HESTON_MONTECARLOSIMULATION_H


#include <src/main/cpp/heston/header/HestonEuler.h>

class MonteCarloSimulation {

public:
    void simulate(Heston* heston, Option* option);

    MonteCarloSimulation();
    virtual ~MonteCarloSimulation();
};


#endif //HESTON_MONTECARLOSIMULATION_H
