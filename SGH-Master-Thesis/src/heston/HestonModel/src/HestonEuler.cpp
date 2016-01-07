//
// Created by Konrad Lisiecki on 18/05/15.
//
#ifndef __HESTON_MC_CPP
#define __HESTON_MC_CPP

#include "../header/HestonEuler.h"


HestonEuler::HestonEuler(Option *option, double kappa, double theta, double epsilon, double rho)
        : Heston(option, kappa, theta, epsilon, rho) { }


void HestonEuler::simulateVolPath(const std::vector<double> &volDraws,
                                  std::vector<double> &volPath) {

    size_t vec_size = volDraws.size();
    double dt = option->T / static_cast<double>(vec_size);

    for (int i = 1; i < vec_size; i++) {
        double v_max = std::max(volPath[i - 1], 0.0);
        volPath[i] = volPath[i - 1] + kappa * dt * (theta - v_max) +
                     epsilon * sqrt(v_max * dt) * volDraws[i - 1];
    }
}

void HestonEuler::simulateSpotPath(const std::vector<double> spotDraws,
                                   const std::vector<double> &volPath,
                                   std::vector<double> &spotPath) {

    size_t vec_size = spotDraws.size();
    double dt = option->T / static_cast<double>(vec_size);

    for (int i = 1; i < vec_size; i++) {
        double v_max = std::max(volPath[i - 1], 0.0);
        spotPath[i] = spotPath[i - 1] * exp((option->r - 0.5 * v_max) * dt +
                                              sqrt(v_max * dt) * spotDraws[i - 1]);
    }
}

#endif