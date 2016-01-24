#ifndef HESTON_HESTONMC_H
#define HESTON_HESTONMC_H

#include <src/main/cpp/heston/header/Heston.h>
#include <cmath>
#include <vector>
#include <random>
#include <src/main/cpp/option/option.h>

class HestonMC : public Heston {
protected:

    std::default_random_engine generator;
    std::normal_distribution<double> normalDist;
    std::uniform_real_distribution<double> uniformDist;

public:

    HestonMC(Option *option,
    double kappa,
    double theta,
    double epsilon,
    double rho);

    virtual void simulateVolPath(const std::vector<double> &volDraws,
                                 std::vector<double> &volPath);

    virtual void simulateSpotPath(const std::vector<double> spotDraws,
                                  const std::vector<double> &volPath,
                                  std::vector<double> &spotPath);

    virtual std::string getName();
};

#endif
