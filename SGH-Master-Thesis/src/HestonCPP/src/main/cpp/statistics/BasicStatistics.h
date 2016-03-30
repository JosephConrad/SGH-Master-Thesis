//
// Created by Konrad Lisiecki on 22/03/16.
//

#ifndef HESTON_BASICSTATISTICS_H
#define HESTON_BASICSTATISTICS_H


class BasicStatistics {
public:
    BasicStatistics(std::vector<double> data);

    double getMean();

    double getVariance();

    double getStdDev();

    double getStandardError();

    double bias(double exactValue);

    double rmsError(double exactValue);

private:
    std::vector<double> data;
    int size;
};

#endif //HESTON_BASICSTATISTICS_H
