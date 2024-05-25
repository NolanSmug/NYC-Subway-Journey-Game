#ifndef NYC_SUBWAY_JOURNEY_GAME_TRAIN_H
#define NYC_SUBWAY_JOURNEY_GAME_TRAIN_H

#include <string>
#include <vector>
#include "Station.h"
#include "Line.h"
#include "SubwayMap.h"
#include <unordered_map>

using namespace std;

enum Direction {
    UPTOWN,
    DOWNTOWN,
    NULL_DIRECTION
};

extern unordered_map<LineName, pair<string, string> > lineDirections;
extern unordered_map<LineName, LineType> lineTypes;


class Train {
public:
    Train();
    Train(LineName lineName, Direction direction, vector<Station> scheduledStops, LineType lineType, int numCars);

    LineName getLine();
    void setLine(LineName newLineName);

    Direction getDirection();
    void reverseDirection();
    void setDirection(Direction newDirection);

    string getUptownLabel();
    string getDowntownLabel();

    void setUptownLabel(string newLabel);
    void setDowntownLabel(string newLabel);

    bool transferToLine(LineName newLine, Station currentStation);
    void updateScheduledStops(LineName &line);

    vector<Station> getScheduledStops();
    void addScheduledStop(Station newStop);
    void setScheduledStops(vector<Station> newScheduledStops);

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
    LineType lineType;
    Direction direction;
    string uptownLabel;
    string downtownLabel;
    vector<Station> scheduledStops;
    int currentStationIndex;
    int numCars; // not sure if this could be useful ever
};

#endif //NYC_SUBWAY_JOURNEY_GAME_TRAIN_H
