//
// Created by Konrad Lisiecki on 26/09/15.
//

#ifndef HESTON_SIMULATEDANNEALING_H
#define HESTON_SIMULATEDANNEALING_H


#include <vector>
#include "../MonteCarlo/MCHeston.h"

class SimulatedAnnealing {

private:
    MonteCarloSimulation *mcSimulation;


public:
    SimulatedAnnealing();

    virtual std::vector<double> calibration(std::vector<double> &bestHestonParams, int iterations, double coolingCoeff);

    double calcEnergy(double bestSolution, double newSolution, double temperature);

    bool activationEnergyAchieved(double bestSolution, double newSolution, double temperature);

    bool metropolisRule(double bestSolution, double newSolution, double temperature);

    double coolingSchedule(double temperature, double coolingCoeff);

    std::vector<double> mutateParams(const std::vector<double> &vector);

};


#endif //HESTON_SIMULATEDANNEALING_H
