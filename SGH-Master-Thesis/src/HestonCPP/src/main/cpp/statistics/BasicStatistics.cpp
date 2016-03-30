//
// Created by Konrad Lisiecki on 22/03/16.
//

#include <vector>
#include "BasicStatistics.h"
#include <cmath>


BasicStatistics::BasicStatistics(std::vector<double> dataParam) {
    data = dataParam;
    size = data.size();

}

double BasicStatistics::getMean() {
    double sum = 0.0;
    for (double a : data)
        sum += a;
    return sum / size;
}

double BasicStatistics::getVariance() {
    double mean = getMean();
    double temp = 0;
    for (double a :data)
        temp += (mean - a) * (mean - a);
    return temp / size;
}

double BasicStatistics::getStdDev() {
    return std::sqrt(getVariance());
}

double BasicStatistics::getStandardError() {
    return std::sqrt(getVariance()) / std::sqrt(size);
}

double BasicStatistics::bias(double exactValue) {
    return getMean() - exactValue;
}

double BasicStatistics::rmsError(double exactValue) {
    return std::sqrt(std::pow(bias(exactValue),2) + getVariance());
}