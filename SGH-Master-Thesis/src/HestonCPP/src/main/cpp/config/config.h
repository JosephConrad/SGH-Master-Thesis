//
// Created by Konrad Lisiecki on 21/02/16.
//

#ifndef HESTON_CONFIG_H
#define HESTON_CONFIG_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>

using boost::property_tree::ptree;


class Config {

public:
    static Config &getInstance() {
        static Config instance;
        return instance;
    }

    std::string getCalibrationOutput();

private:
    ptree pt;

    Config();
    ~Config() {};

    Config(Config const &) = delete;

    void operator=(Config const &) = delete;
};


#endif //HESTON_CONFIG_H
