//
// Created by Konrad Lisiecki on 26/02/16.
//

#ifndef HESTON_OUTPUTANDCONSOLE_H
#define HESTON_OUTPUTANDCONSOLE_H

#include <string>
#include <iostream>
#include <fstream>

class OutputAndConsole : std::ofstream {
public:
    OutputAndConsole(const std::string &fileName);

    template<typename T>
    OutputAndConsole &operator<<(const T &var) {
        std::cout << var;
        static_cast<std::ofstream &>(*this) << var;
        return *this;
    };


private:
    const std::string fileName;
};

#endif //HESTON_OUTPUTANDCONSOLE_H
