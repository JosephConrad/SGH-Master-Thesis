//
// Created by Konrad Lisiecki on 05/10/15.
//

#ifndef HESTON_BOXMULLER_H
#define HESTON_BOXMULLER_H


#include <stdlib.h>
#include <time.h>

class BoxMuller {
public:
    static BoxMuller &getInstance() {
        static BoxMuller instance;
        return instance;
    }

    double generateNormal();

private:
    BoxMuller() {
        srand(time(NULL));
    };

    BoxMuller(BoxMuller const &) = delete;

    void operator=(BoxMuller const &) = delete;
};


#endif //HESTON_BOXMULLER_H
