//
// Created by Konrad Lisiecki on 17/01/16.
//

#include <src/main/cpp/option/option.h>
#include <src/main/cpp/heston/header/HestonAndersen.h>
#include <src/main/cpp/heston/header/HestonAndersenMartingale.h>

HestonAndersenMartingale::HestonAndersenMartingale(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        : HestonAndersen(option, kappa, theta, epsilon, rho) { }


void HestonAndersenMartingale::
simulateSpotPath(const std::vector<double> spotDraws,
                 const std::vector<double> &volPath,
                 std::vector<double> &spotPath) {

    auto size = spotDraws.size();
    double dt = option->T / static_cast<double>(size);

    double k1, k2, k3, k4, A, B;

    k1 = GAMMA1 * dt * (((kappa * rho) / epsilon) - 0.5) - (rho / epsilon);
    k2 = GAMMA2 * dt * (((kappa * rho) / epsilon) - 0.5) + (rho / epsilon);
    k3 = GAMMA1 * dt * (1 - pow(rho, 2));
    k4 = GAMMA2 * dt * (1 - pow(rho, 2));

    A = k2 + 0.5 * k4;
    auto martingaleCorrection = calcMartingaleCorrection(martingaleCorrectionCoeffs, A);
    for (int i = 1; i < size; i++) {
        double normalRandom = normalDist(generator);

        B = (k1 + k3 / 2.0) * volPath[i - 1];
        double k0star = martingaleCorrection[i] - B;
        spotPath[i] = spotPath[i - 1] * exp(option->r * dt + k0star + k1 * volPath[i - 1] + k2 * volPath[i] +
                                            (sqrt(k3 * volPath[i - 1] + k4 * volPath[i]) * normalRandom));
    }
}

std::vector<double> HestonAndersenMartingale::
calcMartingaleCorrection(std::vector<std::vector<double>> martingaleCorrectionCoeffs,
                         double A) {
    double psi, a, b2, beta, p;
    std::vector<double> martingaleCorrection;
    for (auto coeffs: martingaleCorrectionCoeffs) {
        psi = coeffs[0];
        a = coeffs[1];
        b2 = coeffs[2];
        beta = coeffs[3];
        p = coeffs[4];
        double x;

        if (psi <= PSI_CRITICAL) {
            x = -((A * b2 * a) / (1 - (2 * A * a)))
                + 0.5 * log(1 - (2 * A * a));
        } else {
            x = -log(p + (beta * (1 - p)) / (beta - A));
        }
        martingaleCorrection.push_back(x);

    }
    return martingaleCorrection;
}
