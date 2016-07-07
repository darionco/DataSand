//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSTASKSCHEDULER_H
#define DATASAND_DSTASKSCHEDULER_H

class DSDataFormatter;
class DSGraphics;

class DSTaskScheduler
{
    DSDataFormatter *m_dataFormatter;
    DSGraphics *m_graphics;

public:
    DSTaskScheduler(DSDataFormatter *dataFormatter, DSGraphics *graphics);
    ~DSTaskScheduler();

    DSDataFormatter *dataFormatter();
    DSGraphics *graphics();
};

#endif //DATASAND_DSTASKSCHEDULER_H
