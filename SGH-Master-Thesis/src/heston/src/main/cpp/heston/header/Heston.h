#ifndef HESTON_HESTON_H
#define HESTON_HESTON_H

#include <cmath>
#include <vector>
#include <random>
#include <src/main/cpp/option/option.h>

class Heston {
protected:
    Option *option;
    double kappa;
    double theta;
    double epsilon;
    double rho;

    std::default_random_engine generator;
    std::normal_distribution<double> normalDist;
    std::uniform_real_distribution<double> uniformDist;

public:

    Heston(Option *option,
           double kappa,
           double theta,
           double epsilon,
           double rho);

    virtual ~Heston();

    virtual void simulateVolPath(const std::vector<double> &volDraws,
                                 std::vector<double> &volPath) = 0;

    virtual void simulateSpotPath(const std::vector<double> spotDraws,
                                  const std::vector<double> &volPath,
                                  std::vector<double> &spotPath) = 0;
};

#endif
