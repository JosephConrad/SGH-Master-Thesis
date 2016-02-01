#include <iostream>
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
                 const std::vector<double> &vol,
                 std::vector<double> &spotPath) {

    auto size = spotDraws.size();
    double dt = option->T / static_cast<double>(size);
    double r = option->r;

    double k1, k2, k3, k4, k0star, A, B;

    k1 = GAMMA1 * dt * (((kappa * rho) / eps) - 0.5) - (rho / eps);
    k2 = GAMMA2 * dt * (((kappa * rho) / eps) - 0.5) + (rho / eps);
    k3 = GAMMA1 * dt * (1 - pow(rho, 2));
    k4 = GAMMA2 * dt * (1 - pow(rho, 2));

    A = k2 + 0.5 * k4;

    for (int i = 1; i < size; i++) {
        B = (k1 + k3 / 2.0) * vol[i - 1];
        k0star = calcMartingaleCorr(martingaleCorrection[i - 1], A, B);

        double ds;
        ds = r * dt + k0star + k1 * vol[i - 1] + k2 * vol[i] +
             sqrt(k3 * vol[i - 1] + k4 * vol[i]) * spotDraws[i - 1];

        spotPath[i] = spotPath[i - 1] * exp(ds);
    }
}

double HestonAndersenMartingale::
calcMartingaleCorr(std::vector<double> &coeffs,
                   double A, double B) {
    double psi, a, b2, beta, p;
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
    return x - B;
}

std::string HestonAndersenMartingale::getName() {
    return "HESTON MART";
}
