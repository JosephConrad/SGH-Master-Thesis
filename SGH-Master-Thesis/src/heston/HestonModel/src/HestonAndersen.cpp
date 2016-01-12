#include <random>
#include <iostream>
#include "../header/HestonAndersen.h"

HestonAndersen::HestonAndersen(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        : Heston(option, kappa, theta, epsilon, rho) { }

void HestonAndersen::simulateVolPath(const std::vector<double> &volDraws,
                                     std::vector<double> &volPath) {
    auto size = volPath.size();
    double dt = option->T / static_cast<double>(size);

    std::vector<std::vector<double> > temp(size, {0.0, 0.0, 0.0, 0.0, 0.0});
    martingaleCorrectionCoeffs = temp;

    double discountFactor, normalRandom, uniformRandom;
    double m, eps2, psi, s2, a, b2, beta, p;

    discountFactor = exp(-kappa * dt);

    for (int i = 1; i < size; i++) {
        m = theta + (volPath[i - 1] - theta) * discountFactor;
        eps2 = pow(epsilon, 2);
        s2 = ((volPath[i - 1] * eps2 * discountFactor) / kappa) * (1 - discountFactor) +
             ((theta * eps2) / (2 * kappa)) * pow(1 - discountFactor, 2);
        psi = s2 / (m * m);

        if (psi <= PSI_CRITICAL) {
            b2 = 2 * pow(psi, -1) - 1 + sqrt(2 * pow(psi, -1) * (2 * pow(psi, -1) - 1));
            a = m / (1 + b2);
            normalRandom = normalDist(generator);
            volPath[i] = a * pow(sqrt(b2) + normalRandom, 2);
            martingaleCorrectionCoeffs[i - 1] = {psi, a, b2, 0.0, 0.0};
        } else {
            beta = 2 / (m * (psi + 1));
            p = (psi - 1) / (psi + 1);
            uniformRandom = uniformDist(generator);
            volPath[i] = modifiedExponentialInvertedCDF(uniformRandom, p, beta);
            martingaleCorrectionCoeffs[i - 1] = {psi, 0.0, 0.0, beta, p};
        }
    }
}

void HestonAndersen::simulateSpotPath(const std::vector<double> spotDraws,
                                      const std::vector<double> &volPath,
                                      std::vector<double> &spotPath) {
    auto size = spotDraws.size();
    double dt = option->T / static_cast<double>(size);

    double k0, k1, k2, k3, k4, gamma1, gamma2, A, B;

    gamma1 = 0.5;
    gamma2 = 0.5;

    k0 = -dt * (rho * kappa * theta) / (epsilon);
    k1 = gamma1 * dt * (((kappa * rho) / epsilon) - 0.5) - (rho / epsilon);
    k2 = gamma2 * dt * (((kappa * rho) / epsilon) - 0.5) + (rho / epsilon);
    k3 = gamma1 * dt * (1 - pow(rho, 2));
    k4 = gamma2 * dt * (1 - pow(rho, 2));

    A = k2 + 0.5 * k4;
    for (int i = 1; i < size; i++) {

        double normalRandom = normalDist(generator);

        B = (k1 + k3 / 2.0) * volPath[i - 1];
        double k0star = calcMartingaleCorrection(martingaleCorrectionCoeffs[i - 1], A, B);
        spotPath[i] = spotPath[i - 1] * exp(option->r * dt + k0star + k1 * volPath[i - 1] + k2 * volPath[i] +
                                            (sqrt(k3 * volPath[i - 1] + k4 * volPath[i]) * normalRandom));
    }
}

double HestonAndersen::modifiedExponentialInvertedCDF(double uniformRandom,
                                                      double p,
                                                      double beta) {
    return uniformRandom > p ? (pow(beta, -1) * log((1 - p) / (1 - uniformRandom))) : 0;
}

double HestonAndersen::calcMartingaleCorrection(std::vector<double> &coeffs,
                                                double A, double B) {
    double psi, a, b2, beta, p;
    psi = coeffs[0];
    a = coeffs[1];
    b2 = coeffs[2];
    beta = coeffs[3];
    p = coeffs[4];
    double x;

    if (psi <= PSI_CRITICAL) {
        x = -((A * b2 * a) / (1 - (2 * A * a))) + 0.5 * log(1 - (2 * A * a));
    } else {
        x = -log(p + (beta * (1 - p)) / (beta - A));
    }
    double ret = x - B;
    return ret;
}
