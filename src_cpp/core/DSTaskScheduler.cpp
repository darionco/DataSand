//
// Created by Dario Segura on 2016-07-07.
//

#include "DSTaskScheduler.h"
#include "printToConsole.h"

#include "DSDataFormater.h"
#include "DSGraphics.h"

DSTaskScheduler::DSTaskScheduler(DSDataFormatter *dataFormatter, DSGraphics *graphics) {
    printToConsole("Initializing task scheduler...");

    m_graphics = graphics;

    m_dataFormatter = dataFormatter;
    m_dataFormatter->update();
}

DSTaskScheduler::~DSTaskScheduler() {
}

DSDataFormatter *DSTaskScheduler::dataFormatter() {
    return m_dataFormatter;
}

DSGraphics *DSTaskScheduler::graphics() {
    return m_graphics;
}
