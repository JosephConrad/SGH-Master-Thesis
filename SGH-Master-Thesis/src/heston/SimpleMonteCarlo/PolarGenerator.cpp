#include <math.h>
#include "PolarGenerator.h"

double PolarGenerator::genNorm() {
    double square;
    double a, b;

    do {
        a = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
        b = 2.0 * rand() / static_cast<double>(RAND_MAX) - 1;
        square = a * a + b * b;
    }
    while (square >= 1.0);

    return sqrt(-2 * log(square) / square) * a;
}