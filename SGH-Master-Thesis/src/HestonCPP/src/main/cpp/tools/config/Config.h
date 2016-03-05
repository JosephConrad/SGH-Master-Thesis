//
// Created by Konrad Lisiecki on 21/02/16.
//

#ifndef HESTON_CONFIG_H
#define HESTON_CONFIG_H

#include <string>
#include <functional>

namespace boost
{
    namespace property_tree
    {
        template < class Key, class Data, class KeyCompare >
        class basic_ptree;

        typedef basic_ptree< std::string, std::string, std::less<std::string> > ptree;
    }
}


class Config {

public:
    static Config &getInstance() {
        static Config instance;
        return instance;
    }

    std::string getSettings(std::string option);

private:
    std::shared_ptr<boost::property_tree::ptree> configFile_;

    Config();
    ~Config() {};

    Config(Config const &) = delete;

    void operator=(Config const &) = delete;
};


#endif //HESTON_CONFIG_H
