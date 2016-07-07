//
// Created by Dario Segura on 2016-07-07.
//

#include "DSDataFormater.h"
#include "printToConsole.h"

#include "../GSGThreading/GSGThreadLock.h"
#include "../csv-parser/CSVparser.hpp"
#include <math.h>

DSDataFormatter::DSDataFormatter() {
    m_lock = new GSGThreadLock();
}

DSDataFormatter::~DSDataFormatter() {

}

void DSDataFormatter::loadCsvFile(std::string file) {
    m_file = file;

    csv::Parser csvfile = csv::Parser(m_file, csv::ePURE);
    // set x axis max to: 1000
    // each bucket width: 100 (80 capacity) 10 padding each side
    int MAX_X_AXIS = 1000;
    int NUM_BUCKETS = 10;
    int BUCKET_PADDING = 10;
    int bucketSize = MAX_X_AXIS / NUM_BUCKETS;
    int bucketCapacity = bucketSize - (BUCKET_PADDING * 2);
    float x2Max;
    float geoFactor = MAX_X_AXIS / 360;

    // buckets contains int that tells number of datapoints each bucket have
    std::vector<int> buckets (10, 0);
    float bucketColors[10][3] = {
        {244 ,67, 54},
        {255 ,87, 34},
        {255 ,152, 0},
        {255 ,193, 7},
        {255 ,235, 59},
        {205 ,220, 57},
        {139 ,195, 74},
        {76 ,175, 80},
        {0 ,150, 136},
        {0 ,188, 212}
    };
    
    // calculate max x2 value
    for (int i = 0; i < csvfile.rowCount(); i++) {
        float x2 = std::stof(csvfile[i]["Education"]);
        x2Max = std::max(x2Max, x2);
    }
    float histFactor = MAX_X_AXIS / x2Max;

    for (int i = 0; i < csvfile.rowCount(); i++) {
        float x1 = (std::stof(csvfile[i]["Longitude"]) + 180) * geoFactor;
        float y1 = (std::stof(csvfile[i]["Latitude"]) + 90) * geoFactor;
        float x2 = std::stof(csvfile[i]["Education"]) * histFactor;
        int x2BucketIndex = x2 / MAX_X_AXIS * NUM_BUCKETS;
        int x2BucketOffset = x2BucketIndex * (bucketSize);
        auto color = bucketColors[x2BucketIndex];

        float x2Final = x2BucketOffset + (buckets[x2BucketIndex] % bucketCapacity) + BUCKET_PADDING;
        float y2 = floor(buckets[x2BucketIndex]++ / bucketCapacity);

        dataPoint dp = {
            { x1, y1 },
            { x2Final, y2},
            {color[0], color[1], color[2]},
            {color[0], color[1], color[2]},
        };
        m_dataPoints.push_back(dp);
        if (i % 100 == 0){
            printToConsole("row #" + std::to_string(i + 1) + " color: " + std::to_string(dp.SecondColor[0]) + " point1: " + std::to_string(dp.FirstPosition[0]) + ", " + std::to_string(dp.FirstPosition[1]) + ", point2: " + std::to_string(dp.SecondPosition[0]) + ", " + std::to_string(dp.SecondPosition[1]));
        }
    }

}

bool DSDataFormatter::update() {
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