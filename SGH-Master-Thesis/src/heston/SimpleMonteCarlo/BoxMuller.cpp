//
// Created by Konrad Lisiecki on 05/10/15.
//

#include <math.h>
#include "BoxMuller.h"


double BoxMuller::generateNormal() {
    double result;
    double x, y;
    double sizeSquared;

    do {
        x = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
        y = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
        sizeSquared = x * x + y * y;
    }
    while (sizeSquared >= 1.0);

    result = x * sqrt(-2 * log(sizeSquared) / sizeSquared);

    return result;
}
