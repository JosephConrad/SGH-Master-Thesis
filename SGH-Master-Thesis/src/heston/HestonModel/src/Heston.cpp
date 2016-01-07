//
// Created by Konrad Lisiecki on 06/01/16.
//

#include "../header/Heston.h"

Heston::Heston(Option *_pOption,
                         double _kappa, double _theta,
                         double _xi, double _rho) :
        pOption(_pOption), kappa(_kappa), theta(_theta), xi(_xi), rho(_rho) { }

Heston::~Heston() { }
