//
// Created by Nolan Cyr on 1/25/24.
//
#ifndef TRAIN_H
#define TRAIN_H

#include <string>
#include <vector>
#include "Station.h"
#include "Line.h"
#include "SubwayMap.h"

using namespace std;
enum Direction {UPTOWN, DOWNTOWN};

static const char * DirectionEnumStrings[] = {
        "Bronx-Bound", "Manhattan-Bound", "Queens-Bound", "Brooklyn-Bound"
};

static unordered_map<LineName, pair<string, string>> lineDirections {
        {ONE_TRAIN, {"Downtown", "Uptown"}},
        {TWO_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {THREE_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {FOUR_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {FIVE_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {SIX_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {SEVEN_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {A_TRAIN, {"Downtown", "Uptown"}},
        {B_TRAIN, {"Manhattan-bound", "Brooklyn-bound"}},
        {C_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {D_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {E_TRAIN, {"Downtown", "Queens-bound"}},
        {F_TRAIN, {"Queens-bound", "Brooklyn-bound"}},
        {G_TRAIN, {"Church Av-bound", "Court Sq-bound"}},
        {J_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {L_TRAIN, {"Manhattan-bound", "Brooklyn-bound"}},
        {M_TRAIN, {"Queens-bound", "Brooklyn-bound"}},
        {N_TRAIN, {"Brooklyn-bound", "Queens-bound"}},
        {Q_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {R_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {W_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {Z_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {S_TRAIN, {"Times Sq-bound", "Grand Central-bound"}},
        {S_TRAIN_SHUTTLE, {"Franklin Av-bound", "Prospect Park-bound"}},
        {S_TRAIN_ROCKAWAY, {"Broad Channel-bound", "Rockaway Park-Beach 116 St-bound"}}
};


class Train {
public:
    Train();
    Train(LineName lineName, Direction direction, vector<Station> scheduledStops, bool express, int numCars);

    LineName getLine();
    void setLine(LineName newLineName);

    Direction getDirection();
    void setDirection(Direction newDirection);

    bool transferToLine(LineName newLine, Station currentStation);
    void updateScheduledStops(LineName &line);

    vector<Station> getScheduledStops();
    void addScheduledStop(Station newStop);

    Station getCurrentStation();
    Station getNextStation();
    int getCurrentStationIndex();

    void setCurrentStation(int stationIndex);   // overloaded
    void setCurrentStation(string stationName); // overloaded

    bool advanceStation();                  // overloaded
    bool advanceStation(int numStations);   // overloaded

    bool isExpress();
    void setExpress(bool isExpress);

    int getNumCars();
    void setNumCars(int newNumCars);

    static string getTextForDirectionEnum(Direction direction, LineName line);

private:
    LineName currentLine;
    Direction direction;
    vector<Station> scheduledStops;
    int currentStationIndex = 0;
    bool express;
    int numCars; // not sure if this could be useful ever
};

#endif
