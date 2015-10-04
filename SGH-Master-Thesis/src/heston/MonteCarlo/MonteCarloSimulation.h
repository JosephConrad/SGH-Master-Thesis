//
// Created by Konrad Lisiecki on 26/09/15.
//

#ifndef HESTON_MONTECARLOSIMULATION_H
#define HESTON_MONTECARLOSIMULATION_H


class MonteCarloSimulation {

public:
    MonteCarloSimulation();
    virtual ~MonteCarloSimulation();
    float simulateHeston(std::vector<double> params);

private:
    void generate_normal_correlation_paths(double rho, std::vector<double> &spot_normals,
                                           std::vector<double> &cor_normals);
};


#endif //HESTON_MONTECARLOSIMULATION_H
