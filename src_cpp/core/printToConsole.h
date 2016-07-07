//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_PRINTTOCONSOLE_H
#define DATASAND_PRINTTOCONSOLE_H

#include <string>

class DataSandInstance;

void printToConsole(std::string message);
void setGlobalInstance(DataSandInstance *instance);

#endif //DATASAND_PRINTTOCONSOLE_H
