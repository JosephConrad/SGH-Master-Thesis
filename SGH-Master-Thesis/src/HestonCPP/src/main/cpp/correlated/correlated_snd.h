//
// Created by Konrad Lisiecki on 18/05/15.
//

#ifndef HESTON_CORELLATED_SND_H
#define HESTON_CORELLATED_SND_H


#include <src/main/cpp/statistics/StatisticalDistribution.h>

class CorrelatedSND : public StandardNormalDistribution {
protected:
    double rho;
    const std::vector<double> *uncorr_draws;

    // Modify an uncorrelated set of distribution draws to be correlated
    virtual void correlation_calc(std::vector<double> &dist_draws);

public:
    CorrelatedSND(const double _rho,
                  const std::vector<double> *_uncorr_draws);

    virtual ~CorrelatedSND();

    // Obtain a sequence of correlated random draws from another set of SND draws
    virtual void random_draws(const std::vector<double> &uniform_draws,
                              std::vector<double> &dist_draws);
};


#endif //HESTON_CORELLATED_SND_H
