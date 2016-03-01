//
// Created by Konrad Lisiecki on 26/02/16.
//

#include "OutputAndConsole.h"


OutputAndConsole::OutputAndConsole(const std::string &fileName)
        : std::ofstream(fileName),
          fileName(fileName) { };