//
// Created by Konrad Lisiecki on 21/02/16.
//

#include "Config.h"

using boost::property_tree::ini_parser::read_ini;

Config::Config() {
    read_ini("config.ini", pt);
}

std::string Config::getSettings(std::string option)
{
    return pt.get<std::string>(option);
}