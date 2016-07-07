//
// Created by Dario Segura on 2016-07-07.
//

#include "DSDataFormater.h"
#include "printToConsole.h"

#include "../GSGThreading/GSGThreadLock.h"
#include "../csv-parser/CSVparser.hpp"

DSDataFormatter::DSDataFormatter() {
    m_lock = new GSGThreadLock();
}

DSDataFormatter::~DSDataFormatter() {

}

void DSDataFormatter::loadCsvFile(std::string file) {
    m_file = file;

    std::string text = "Loaded CSV file size: ";
    printToConsole(text + std::to_string(m_file.size()));

    csv::Parser csvfile = csv::Parser(m_file, csv::ePURE);

    for (int i = 0; i < csvfile.rowCount(); i++) {
        dataPoint dp = {
            std::stof(csvfile[i]["Longitude"]),
            std::stof(csvfile[i]["Latitude"]),
            std::stof(csvfile[i]["Education"]),
            std::stof(csvfile[i]["Income"])
        };
        m_dataPoints.push_back(dp);
        if (i % 100 == 0){
            printToConsole("row #" + std::to_string(i + 1) + " point1: " + std::to_string(dp.x1) + ", " + std::to_string(dp.y2) + ", point2: " + std::to_string(dp.x2) + ", " + std::to_string(dp.y2));
        }
    }

}

bool DSDataFormatter::update() {
    /* print...? */
    printToConsole("DSDataFormatter Update()");

    /* check if we need to perform changes */
    if (true) { /* replace with condition */
        /* always lock before changing data */
        m_lock->lock();

        /* ------ make data changes here ----- */

        /* don't forget to unlock before returning */
        m_lock->unlock();

        /* return true if the data changed, false otherwise */
        return true;
    }

    /* return true if the data changed, false otherwise */
    return false;
}