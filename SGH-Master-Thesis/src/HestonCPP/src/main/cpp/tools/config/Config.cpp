//
// Created by Konrad Lisiecki on 21/02/16.
//

#include "Config.h"

#include <boost/property_tree/ini_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <iostream>

using boost::property_tree::ptree;
using boost::property_tree::ini_parser::read_ini;
using boost::property_tree::ptree_error;

Config::Config() {
}


void Config::loadConfig(std::string configName) {
    try
    {
        configFile_ = std::shared_ptr<ptree>(new ptree());
        read_ini(configName, *configFile_);
    }
    catch(const ptree_error &e)
    {
        std::cout << e.what() << std::endl;
    }
}


std::string Config::getSettings(std::string option)
{
    return configFile_->get<std::string>(option);
}