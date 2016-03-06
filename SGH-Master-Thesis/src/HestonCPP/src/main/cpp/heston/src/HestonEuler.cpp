#include <src/main/cpp/heston/header/HestonEuler.h>

HestonEuler::HestonEuler(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        : HestonMC(option, kappa, theta, epsilon, rho) { }

void
HestonEuler::simulateVolPath(const std::vector<double> &volDraws,
                             std::vector<double> &volPath) {

    auto size = volDraws.size();
    double dt = option->T / static_cast<double>(size);

    for (int i = 1; i < size; i++) {
        double v_max = std::max(volPath[i - 1], 0.0);
        volPath[i] = volPath[i - 1] + kappa * dt * (theta - v_max) +
                     eps * sqrt(v_max * dt) * volDraws[i - 1];
    }
}

void
HestonEuler::simulateSpotPath(const std::vector<double> spotDraws,
                              const std::vector<double> &volPath,
                              std::vector<double> &spotPath) {

    auto size = spotDraws.size();
    double dt = option->T / static_cast<double>(size);

    for (int i = 1; i < size; i++) {
        double v_max = std::max(volPath[i - 1], 0.0);
        spotPath[i] = spotPath[i - 1] *
                      exp((option->r - 0.5 * v_max) * dt) *
                      exp(sqrt(v_max * dt) * spotDraws[i - 1]);
    }
    }

std::string HestonEuler::getName() {
    return "HESTON EULER";
}