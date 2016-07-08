//
// Created by Dario Segura on 2016-07-07.
//

#include "DSTaskScheduler.h"
#include "printToConsole.h"

#include "DSDataFormater.h"
#include "DSGraphics.h"

DSTaskScheduler::DSTaskScheduler(DSDataFormatter *dataFormatter, DSGraphics *graphics) : m_callbackFactory(this) {
    printToConsole("Initializing task scheduler...");

    m_dataLoaded = false;
    m_dataFormatter = dataFormatter;
    m_graphics = graphics;

    mainLoop(0);
}

DSTaskScheduler::~DSTaskScheduler() {
}

DSDataFormatter *DSTaskScheduler::dataFormatter() {
    return m_dataFormatter;
}

DSGraphics *DSTaskScheduler::graphics() {
    return m_graphics;
}

void DSTaskScheduler::mainLoop(int32_t) {

    if (!m_dataLoaded && m_dataFormatter->dataLength()) {
        m_graphics->loadData(m_dataFormatter->dataPoints(), m_dataFormatter->dataLength());
        m_dataLoaded = true;
    }

    m_graphics->render();

    m_graphics->context()->SwapBuffers(
            m_callbackFactory.NewCallback(&DSTaskScheduler::mainLoop)
    );
}

