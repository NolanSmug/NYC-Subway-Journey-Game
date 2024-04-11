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

enum Direction {
    UPTOWN,
    DOWNTOWN,
    NULL_DIRECTION
};


static unordered_map<LineName, pair<string, string>> lineDirections {
        {ONE_TRAIN, {"Downtown", "Uptown"}},
        {TWO_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {THREE_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {FOUR_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {FIVE_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {SIX_TRAIN, {"Brooklyn-Bridge-bound", "Bronx-bound"}},
        {SEVEN_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {A_TRAIN, {"Downtown", "Uptown"}},
        {B_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {C_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {D_TRAIN, {"Brooklyn-bound", "Bronx-bound"}},
        {E_TRAIN, {"Downtown", "Queens-bound"}},
        {F_TRAIN, {"Brooklyn-bound", "Queens-bound"}},
        {G_TRAIN, {"Church Av-bound", "Court Sq-bound"}},
        {J_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {L_TRAIN, {"Canarsie-Rockaway Pkwy-bound", "8 Av-bound"}},
        {M_TRAIN, {"Brooklyn-bound", "Queens-bound"}},
        {N_TRAIN, {"Brooklyn-bound", "Queens-bound"}},
        {Q_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {R_TRAIN, {"Brooklyn-bound", "Manhattan-bound"}},
        {W_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {Z_TRAIN, {"Manhattan-bound", "Queens-bound"}},
        {S_TRAIN, {"Times Sq-bound", "Grand Central-bound"}},
        {S_TRAIN_SHUTTLE, {"Franklin Av-bound", "Prospect Park-bound"}},
        {S_TRAIN_ROCKAWAY, {"Broad Channel-bound", "Rockaway Park-Beach 116 St-bound"}}
};

static std::unordered_map<LineName, LineType> lineTypes {
        {ONE_TRAIN,LOCAL},
        {TWO_TRAIN,EXPRESS},
        {THREE_TRAIN,EXPRESS},
        {FOUR_TRAIN,EXPRESS},
        {FIVE_TRAIN,EXPRESS},
        {SIX_TRAIN,LOCAL},
        {SEVEN_TRAIN,LOCAL},
        {A_TRAIN,EXPRESS},
        {B_TRAIN,EXPRESS},
        {C_TRAIN,LOCAL},
        {D_TRAIN,EXPRESS},
        {E_TRAIN,EXPRESS},
        {F_TRAIN,LOCAL},
        {G_TRAIN,LOCAL},
        {J_TRAIN,LOCAL},
        {L_TRAIN,LOCAL},
        {M_TRAIN,LOCAL},
        {N_TRAIN,EXPRESS},
        {Q_TRAIN,EXPRESS},
        {R_TRAIN,LOCAL},
        {W_TRAIN,LOCAL},
        {Z_TRAIN,LOCAL},
        {S_TRAIN,NONE},
        {S_TRAIN_SHUTTLE,NONE},
        {S_TRAIN_ROCKAWAY,NONE}
};

class Train {
public:
    Train();
    Train(LineName lineName, Direction direction, vector<Station> scheduledStops, LineType lineType, int numCars);

    LineName getLine();
    void setLine(LineName newLineName);

    Direction getDirection();
    void setDirection(Direction newDirection);

    string getUptownLabel();
    string getDowntownLabel();

    void setUptownLabel(string newLabel);
    void setDowntownLabel(string newLabel);

    bool transferToLine(LineName newLine, Station currentStation);
    void updateScheduledStops(LineName &line);

    vector<Station> getScheduledStops();
    void addScheduledStop(Station newStop);

    Station getCurrentStation();
    Station getNextStation();
    int getCurrentStationIndex();

    void setCurrentStation(int stationIndex);   // overloaded
    void setCurrentStation(string stationName); // overloaded
    void setCurrentStation(Station station);    // overloaded

    bool advanceStation();                  // overloaded
    bool advanceStation(int numStations);   // overloaded

    LineType setLineType();

    int getNumCars();
    void setNumCars(int newNumCars);

    static string getTextForDirectionEnum(Direction direction, LineName line);

private:
    LineName currentLine;
    Direction direction;
    string uptownLabel;
    string downtownLabel;
    vector<Station> scheduledStops;
    int currentStationIndex = 0;
    LineType lineType;
    int numCars; // not sure if this could be useful ever
};

#endif
