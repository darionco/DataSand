//
// Created by Dario Segura on 2016-07-07.
//

#ifndef DATASAND_DSDATAFORMATER_H
#define DATASAND_DSDATAFORMATER_H

#include <string>

class GSGThreadLock;

class DSDataFormatter
{
    GSGThreadLock *m_lock;
    std::string m_filename;
    std::string m_file;

public:
    DSDataFormatter(std::string filename, GSGThreadLock *lock);
    ~DSDataFormatter();

    bool loadCsvFile(std::string file);
    bool update();
};

#endif //DATASAND_DSDATAFORMATER_H
