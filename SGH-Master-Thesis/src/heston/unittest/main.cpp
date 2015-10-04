//
// Created by Konrad Lisiecki on 27/09/15.
//

#include <iostream>
#include "../SimulatedAnnealing/SimulatedAnnealing.h"

int main () {
    SimulatedAnnealing * simulatedAnnealing = new SimulatedAnnealing();
    auto testVector = std::vector<double> {10.0, 4.0, 5.0, 6.0};
    auto newTestVector = simulatedAnnealing->mutateParams(testVector);
    for (std::vector<double>::const_iterator i = newTestVector.begin(); i != newTestVector.end(); ++i)
        std::cout << *i << ' ' << std::endl;
}
