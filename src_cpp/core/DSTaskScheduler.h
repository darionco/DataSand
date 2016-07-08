//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSTASKSCHEDULER_H
#define DATASAND_DSTASKSCHEDULER_H

#include "ppapi/utility/completion_callback_factory.h"

class DSDataFormatter;
class DSGraphics;

class DSTaskScheduler
{
    DSDataFormatter *m_dataFormatter;
    DSGraphics *m_graphics;

    pp::CompletionCallbackFactory<DSTaskScheduler> m_callbackFactory;

    bool m_dataLoaded;

public:
    DSTaskScheduler(DSDataFormatter *dataFormatter, DSGraphics *graphics);
    ~DSTaskScheduler();

    DSDataFormatter *dataFormatter();
    DSGraphics *graphics();

    void mainLoop(int32_t);
};

#endif //DATASAND_DSTASKSCHEDULER_H
