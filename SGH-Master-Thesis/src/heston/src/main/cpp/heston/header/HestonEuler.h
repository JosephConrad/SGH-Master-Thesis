#ifndef HESTON_HESTON_MC_H
#define HESTON_HESTON_MC_H

#include <cmath>
#include <vector>
#include "HestonMC.h"

class HestonEuler : public HestonMC {

public:
    HestonEuler(Option *option,
                double kappa,
                double theta,
                double epsilon,
                double rho);

    void simulateVolPath(const std::vector<double> &volDraws,
                         std::vector<double> &volPath);

    void simulateSpotPath(const std::vector<double> spotDraws,
                          const std::vector<double> &volPath,
                          std::vector<double> &spotPath);
};


#endif //HESTON_HESTON_MC_H
