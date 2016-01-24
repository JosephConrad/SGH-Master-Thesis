//
// Created by Konrad Lisiecki on 17/01/16.
//

#ifndef HESTON_ANDERSENNORMAL_H
#define HESTON_ANDERSENNORMAL_H


#include <src/main/cpp/heston/header/HestonAndersen.h>

class HestonAndersenMartingale : public HestonAndersen {

    double calcMartingaleCorrection(std::vector<double> &vector, double A, double B);

    void simulateSpotPath(const std::vector<double> spotDraws, const std::vector<double> &volPath,
                          std::vector<double> &spotPath);

public:
    HestonAndersenMartingale(
            Option *option,
            double kappa,
            double theta,
            double epsilon,
            double rho);

    std::string getName();
};

#endif //HESTON_ANDERSENNORMAL_H
