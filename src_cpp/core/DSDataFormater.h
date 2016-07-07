//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSDATAFORMATER_H
#define DATASAND_DSDATAFORMATER_H

#include <string>
#include <vector>

class GSGThreadLock;

class DSDataFormatter
{
    struct dataPoint {
        float x1;
        float y1;
        float x2;
        float y2;
        int flag;
    };
    std::vector<dataPoint> m_dataPoints;
    GSGThreadLock *m_lock;
    std::string m_file;

public:
    DSDataFormatter();
    ~DSDataFormatter();

    void loadCsvFile(std::string file);
    bool update();
};

#endif //DATASAND_DSDATAFORMATER_H
