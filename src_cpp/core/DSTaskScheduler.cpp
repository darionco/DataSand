//
// Created by Dario Segura on 2016-07-07.
//

#include "DSTaskScheduler.h"
#include "printToConsole.h"

#include "../GSGThreading/GSGThread.h"
#include "../GSGThreading/GSGThreadLock.h"
#include "DSDataFormater.h"

DSTaskScheduler::DSTaskScheduler() {
    printToConsole("Initializing task scheduler...");

    m_dataFormatterLock = new GSGThreadLock();

    m_dataFormatter = new DSDataFormatter("some_file_name.csv", m_dataFormatterLock);
    m_dataFormatter->update();
}

DSTaskScheduler::~DSTaskScheduler() {
    delete m_dataFormatter;
}
