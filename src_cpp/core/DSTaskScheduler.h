//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSTASKSCHEDULER_H
#define DATASAND_DSTASKSCHEDULER_H

class GSGThread;
class GSGThreadLock;
class DSDataFormatter;

class DSTaskScheduler
{
    GSGThread *m_dataFormatterThread;
    GSGThreadLock *m_dataFormatterLock;

public:
    DSTaskScheduler();
    ~DSTaskScheduler();
    DSDataFormatter *m_dataFormatter;
};

#endif //DATASAND_DSTASKSCHEDULER_H
