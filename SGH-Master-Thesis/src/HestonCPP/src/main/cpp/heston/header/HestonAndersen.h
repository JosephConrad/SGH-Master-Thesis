#ifndef HESTON_HESTONANDERSEN_H
#define HESTON_HESTONANDERSEN_H

#include "HestonMC.h"

class HestonAndersen : public HestonMC {

protected:
    std::vector<std::vector<double> > martingaleCorrection; // pis, a, b2, beta
    double PSI_CRITICAL = 1.5;
    double GAMMA1 = 0.5;
    double GAMMA2 = 0.5;
    double a;

public:
    HestonAndersen(Option *option,
                   double kappa,
                   double theta,
                   double epsilon,
                   double rho);

    void simulateVolPath(const std::vector<double> &volDraws,
                         std::vector<double> &volPath);

    void simulateSpotPath(const std::vector<double> spotDraws,
                          const std::vector<double> &volPath,
                          std::vector<double> &spotPath);

    double modifiedExpInvCDF(double random, double p, double beta);

    double calcMartingaleCorr(std::vector<double> &vector,
                              double a, double d);

    std::string getName();
};


#endif
