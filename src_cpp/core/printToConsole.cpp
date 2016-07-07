//
// Created by Dario Segura on 2016-07-07.
//

#include "printToConsole.h"
#include "../DataSand.h"

DataSandInstance *g_dataSandInstance = NULL;

void printToConsole(std::string message) {
    if (g_dataSandInstance) {
        g_dataSandInstance->printToConsole(message);
    }
}

void setGlobalInstance(DataSandInstance *instance) {
    g_dataSandInstance = instance;
}