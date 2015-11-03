//
// Created by Konrad Lisiecki on 05/10/15.
//

#ifndef HESTON_BOXMULLER_H
#define HESTON_BOXMULLER_H


#include <stdlib.h>
#include <time.h>

class PolarGenerator {
public:
    static PolarGenerator &getInstance() {
        static PolarGenerator instance;
        return instance;
    }

    double genNorm();

private:
    PolarGenerator() {
        srand(time(NULL));
    };

    PolarGenerator(PolarGenerator const &) = delete;

    void operator=(PolarGenerator const &) = delete;
};


#endif //HESTON_BOXMULLER_H
