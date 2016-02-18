#pragma once

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
    PolarGenerator();
    ~PolarGenerator();

    PolarGenerator(PolarGenerator const &) = delete;

    void operator=(PolarGenerator const &) = delete;
};
