#include <random>
#include "../header/HestonAndersen.h"

HestonAndersen::HestonAndersen(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        : Heston(option, kappa, theta, epsilon, rho)
{ }

void HestonAndersen::simulateVolPath(const std::vector<double> &volDraws,
                                     std::vector<double> &volPath) {
    auto size = volDraws.size();
    double dt = option->T / static_cast<double>(size);

    double discountFactor, normalRandom, uniformRandom;
    double m, eps2, psi, s2, a, b2, beta, p;

    for (int i = 1; i < size; i++) {
        discountFactor = exp(-kappa * dt);
        m = theta + (volPath[i - 1] - theta) * discountFactor;
        eps2 = pow(epsilon, 2);
        s2 = (volPath[i - 1] * eps2 * discountFactor) / kappa * (1 - discountFactor) +
             ((theta * eps2) / (2 * kappa)) * pow(1 - discountFactor, 2);
        psi = s2 / m * m;

        if (psi <= PSI_CRITICAL) {
            b2 = 2 * pow(psi, -1) - 1 + sqrt(2 * pow(psi, -1) * (2 * pow(psi, -1) - 1));
            a = m / (1 + b2);
            normalRandom = normalDist(generator);
            volPath[i] = a * pow(sqrt(b2) + normalRandom, 2);
        } else {
            beta = 2 / (m * (psi + 1));
            p = (psi - 1) / (psi + 1);
            uniformRandom = uniformDist(generator);
            volPath[i] = modifiedExponentialInvertedCDF(uniformRandom, p, beta);
        }
    }
}

void HestonAndersen::simulateSpotPath(const std::vector<double> spotDraws,
                                      const std::vector<double> &volPath,
                                      std::vector<double> &spotPath) {
    auto size = spotDraws.size();
    double dt = option->T / static_cast<double>(size);

    for (int i = 1; i < size; i++) {
        double v_max = std::max(volPath[i - 1], 0.0);
        spotPath[i] = spotPath[i - 1] * exp((option->r - 0.5 * v_max) * dt +
                                            sqrt(v_max * dt) * spotDraws[i - 1]);
    }
}

double HestonAndersen::modifiedExponentialInvertedCDF(double uniformRandom,
                                                      double p,
                                                      double beta) {
    return uniformRandom > p ? (pow(beta, -1) * log((1 - p) / (1 - uniformRandom))) : 0;
}
