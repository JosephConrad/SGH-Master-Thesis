//
// Created by Konrad Lisiecki on 05/03/16.
//

#ifndef HESTON_JSONREADER_H
#define HESTON_JSONREADER_H

#include <src/main/cpp/simulation/Simulation.h>
#include <boost/property_tree/ptree.hpp>
#include <string>
#include <vector>

class JsonReader {

public:
    JsonReader();

    ~JsonReader() { };

    void processValuation(std::vector<Simulation> &simulations);
    void getTimeSteps(std::vector<int> &timeSteps);
    void loadConfig(std::string filename);


private:
    Simulation processOptionParams(const ptree::value_type &node);



    std::shared_ptr<boost::property_tree::ptree> jsonTree_;

    const int &getInt(const boost::use_default &aDefault);
};


#endif //HESTON_JSONREADER_H
