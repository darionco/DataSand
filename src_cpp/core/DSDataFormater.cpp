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

bool DSDataFormatter::loadCsvFile(std::string file) {
    m_file = file;

    std::string text = "Loaded CSV file size: ";
    printToConsole(text + std::to_string(m_file.size()));

    csv::Parser csvfile = csv::Parser(m_file, csv::ePURE);

    // print result
    printToConsole(csvfile.getHeaderElement(0));

    std::stringstream buffer;
    buffer << csvfile[0] << std::endl;
    printToConsole(buffer.str());

    std::stringstream buffer2;
    buffer2 << csvfile.rowCount() << std::endl;
    printToConsole(buffer2.str());

    std::stringstream buffer3;
    buffer3 << csvfile.columnCount() << std::endl;
    printToConsole(buffer3.str());

    return false;
}

bool DSDataFormatter::update() {
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