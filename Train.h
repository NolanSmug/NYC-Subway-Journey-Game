//
// Created by Nolan Cyr on 1/25/24.
//
#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <vector>
#include "Train.h"

using namespace std;

class Train {
private:
    string lineName;
    vector<string> scheduledStops;
    bool express;
    int numCars;

public:
    Train();
    Train(string lineName, vector<string> scheduledStops, bool express, int numCars);

    string getLineName() const;
    void setLineName(const string& newLineName);

    vector<string> getScheduledStops() const;
    void addScheduledStops(const string& newStop);

    bool isExpress() const;
    void setExpress(bool isExpress);

    int getNumCars() const;
    void setNumCars(int newNumCars);
};

#endif

