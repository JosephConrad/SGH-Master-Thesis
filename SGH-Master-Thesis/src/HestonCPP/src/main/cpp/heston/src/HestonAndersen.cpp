#include <random>
#include <iostream>
#include "../header/HestonAndersen.h"

HestonAndersen::HestonAndersen(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        : HestonMC(option, kappa, theta, epsilon, rho) { }

void
HestonAndersen::simulateVolPath(const std::vector<double> &volDraws,
                                std::vector<double> &volPath) {

    auto size = volPath.size();
    double dt = option->T / static_cast<double>(size);

    std::vector<std::vector<double> >
            martingaleCorrection(size, {0.0, 0.0, 0.0, 0.0, 0.0});

    double discount, m, eps2, psi, s2, a, b2, beta, p;
    discount = exp(-kappa * dt);

    for (int i = 1; i < size; i++) {
        m = theta + (volPath[i - 1] - theta) * discount;
        eps2 = pow(eps, 2);
        s2 = ((volPath[i - 1] * eps2 * discount) / kappa) * (1 - discount) +
             ((theta * eps2) / (2 * kappa)) * pow(1 - discount, 2);
        psi = s2 / (m * m);

        if (psi <= PSI_CRITICAL) {
            b2 = 2 * pow(psi, -1) - 1 +
                 sqrt(2 * pow(psi, -1) * (2 * pow(psi, -1) - 1));
            a = m / (1 + b2);
            volPath[i] = a * pow(sqrt(b2) + normalDist(generator), 2);
            martingaleCorrection[i - 1] = {psi, a, b2, 0.0, 0.0};
        } else {
            beta = 2 / (m * (psi + 1));
            p = (psi - 1) / (psi + 1);
            volPath[i] = modifiedExpInvCDF(uniformDist(generator), p, beta);
            martingaleCorrection[i - 1] = {psi, 0.0, 0.0, beta, p};
        }
    }
}

void
HestonAndersen::simulateSpotPath(const std::vector<double> spotDraws,
                                 const std::vector<double> &volPath,
                                 std::vector<double> &spotPath) {
    auto size = spotDraws.size();
    double dt = option->T / static_cast<double>(size);

    double k0, k1, k2, k3, k4;

    k0 = -dt * (rho * kappa * theta) / (eps);
    k1 = GAMMA1 * dt * (((kappa * rho) / eps) - 0.5) - (rho / eps);
    k2 = GAMMA2 * dt * (((kappa * rho) / eps) - 0.5) + (rho / eps);
    k3 = GAMMA1 * dt * (1 - pow(rho, 2));
    k4 = GAMMA2 * dt * (1 - pow(rho, 2));

    for (int i = 1; i < size; i++) {
        double ds;
        ds = option->r * dt + k0 + k1 * volPath[i - 1] + k2 * volPath[i] +
             sqrt(k3 * volPath[i - 1] + k4 * volPath[i]) * spotDraws[i - 1];
        spotPath[i] = spotPath[i - 1] * exp(ds);
    }
}

double
HestonAndersen::modifiedExpInvCDF(double uniformRandom,
                                  double p,
                                  double beta) {
    return uniformRandom > p ?
           (pow(beta, -1) * log((1 - p) / (1 - uniformRandom))) : 0;
}

std::string HestonAndersen::getName() {
    return "HESTON ANDER";
}
