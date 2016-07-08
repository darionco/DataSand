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
        float FirstPosition[2];
        float SecondPosition[2];
        float FirstColor[3];
        float SecondColor[3];
    };
    std::vector<dataPoint> m_dataPoints;
    GSGThreadLock *m_lock;
    std::string m_file;

public:
    DSDataFormatter();
    ~DSDataFormatter();

    void loadCsvFile(std::string file);
    bool update();

    void *dataPoints();
    int dataLength();
};

#endif //DATASAND_DSDATAFORMATER_H
