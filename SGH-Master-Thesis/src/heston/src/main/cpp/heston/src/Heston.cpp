#include "../header/Heston.h"

Heston::Heston(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        :
        option(option),
        kappa(kappa),
        theta(theta),
        epsilon(epsilon),
        rho(rho)
{ }

Heston::~Heston() { }

double Heston::getRho() const {
    return rho;
}

void Heston::simulateVolPath(const std::vector<double> &volDraws, std::vector<double> &volPath) {

}

void Heston::simulateSpotPath(const std::vector<double> spotDraws, const std::vector<double> &volPath,
                              std::vector<double> &spotPath) {

}
