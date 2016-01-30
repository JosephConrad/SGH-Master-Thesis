#include <src/main/cpp/heston/header/HestonMC.h>
#include <src/main/cpp/heston/header/Heston.h>


HestonMC::HestonMC(
        Option *option,
        double kappa,
        double theta,
        double epsilon,
        double rho)
        : Heston(option, kappa, theta, epsilon, rho) {
    generator.seed(0);
}

void HestonMC::simulateVolPath(const std::vector<double> &volDraws, std::vector<double> &volPath) {

}

void HestonMC::simulateSpotPath(const std::vector<double> spotDraws, const std::vector<double> &volPath,
                                std::vector<double> &spotPath) {

}

std::string HestonMC::getName() {
    return "HESTON MC";
}