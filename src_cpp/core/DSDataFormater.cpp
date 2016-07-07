//
// Created by Dario Segura on 2016-07-07.
//

#include "DSDataFormater.h"
#include "printToConsole.h"

#include "../GSGThreading/GSGThreadLock.h"

DSDataFormatter::DSDataFormatter() {
    m_lock = new GSGThreadLock();
}

DSDataFormatter::~DSDataFormatter() {

}

bool DSDataFormatter::loadCsvFile(std::string file) {
    m_file = file;
    std::string text = "Loaded CSV file size: ";
    printToConsole(text + std::to_string(m_file.size()));
    return false;
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