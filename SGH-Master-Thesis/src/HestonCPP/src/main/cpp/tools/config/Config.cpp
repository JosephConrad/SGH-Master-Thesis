//
// Created by Konrad Lisiecki on 21/02/16.
//

#include "Config.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using boost::property_tree::ptree;
using boost::property_tree::ini_parser::read_ini;

Config::Config() {
    configFile_ = std::shared_ptr<ptree>(new ptree());
    read_ini("config.ini", *configFile_);
}

std::string Config::getSettings(std::string option)
{
    return configFile_->get<std::string>(option);
}