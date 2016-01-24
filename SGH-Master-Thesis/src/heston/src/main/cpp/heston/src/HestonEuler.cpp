#ifndef __HESTON_MC_CPP
#define __HESTON_MC_CPP

#include "../header/HestonEuler.h"

HestonEuler::HestonEuler(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        : HestonMC(option, kappa, theta, epsilon, rho) { }

void HestonEuler::simulateVolPath(const std::vector<double> &volDraws,
                                  std::vector<double> &volPath) {

    auto size = volDraws.size();
    double dt = option->T / static_cast<double>(size);

    for (int i = 1; i < size; i++) {
        double v_max = std::max(volPath[i - 1], 0.0);
        volPath[i] = volPath[i - 1] + kappa * (theta - v_max) * dt +
                     epsilon * sqrt(v_max * dt) * volDraws[i - 1];
    }
}

void HestonEuler::simulateSpotPath(const std::vector<double> spotDraws,
                                   const std::vector<double> &volPath,
                                   std::vector<double> &spotPath) {

    auto size = spotDraws.size();
    double dt = option->T / static_cast<double>(size);

    for (int i = 1; i < size; i++) {
        double v_max = std::max(volPath[i - 1], 0.0);
        spotPath[i] = spotPath[i - 1] + option->r * dt * spotPath[i - 1] +
                      sqrt(v_max * dt) * spotPath[i - 1] * spotDraws[i - 1];
    }
}

std::string HestonEuler::getName() {
    return "HESTON EULER";
}

#endif