//
// Created by Konrad Lisiecki on 21/02/16.
//

#include "config.h"

using boost::property_tree::ini_parser::read_ini;

Config::Config() {
    read_ini("config.ini", pt);
}

std::string Config::getCalibrationOutput() {
    return pt.get<std::string>("Calibration.input");
}