//
// Created by Konrad Lisiecki on 05/03/16.
//

#include "JsonReader.h"
#include <src/main/cpp/tools/config/Config.h>

#include <boost/property_tree/json_parser.hpp>

using boost::property_tree::ptree;
using boost::property_tree::read_json;

JsonReader::JsonReader() { }


void JsonReader::loadConfig(std::string configFilePath) {

    std::string jsonFile = Config::getInstance().getSettings(configFilePath);

    jsonTree_ = std::shared_ptr<ptree>(new ptree());
    read_json(jsonFile, *jsonTree_);
}


Simulation JsonReader::processOptionParams(const ptree::value_type &node) {

    return Simulation(
            node.second.get<double>("asset"),
            std::vector<double> {
                    node.second.get<double>("strikeLow"),
                    node.second.get<double>("strike"),
                    node.second.get<double>("strikeHigh"),
            },
            node.second.get<double>("riskFree"),
            node.second.get<double>("expiry"),
            node.second.get<double>("volatility"),
            node.second.get<double>("kappa"),
            node.second.get<double>("theta"),
            node.second.get<double>("eps"),
            node.second.get<double>("rho"),
            node.second.get<int>("trials"),
            node.second.get<double>("truePrice"),
            node.second.get<std::string>("description")
    );
}


void JsonReader::processValuation(std::vector<Simulation> &simulations) {

    for (ptree::value_type &simulation: jsonTree_->get_child("heston")) {
        simulations.push_back(processOptionParams(simulation));
    }
}

void JsonReader::getVector(std::vector<int> &timeSteps, std::string nodeName) {

    for (ptree::value_type &timeStep : jsonTree_->get_child(nodeName)) {
        timeSteps.push_back(std::stoi(timeStep.second.data()));
    }
}
