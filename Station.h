//
// Created by Nolan Cyr on 1/31/24.
//

#ifndef M1OEP_NCYR1_STATION_H
#define M1OEP_NCYR1_STATION_H

#include "Line.h"

enum Borough {
    MANHATTAN,
    BROOKLYN,
    QUEENS,
    BRONX,
    STATEN_ISLAND
};

static const char * BoroughEnumStrings[] = {"Manhattan", "Brooklyn", "Queens", "Bronx", "Staten Island" };

class Station {
private:
    string id;
    string name;
    vector<LineName> transfers;
    Borough borough;


public:
    Station();
    Station(string id, string name, vector<LineName> transfers, Borough borough);

    static vector<Station> allNycStations;
    static void initializeAllStations();

    friend ostream& operator<<(ostream& str, Station station);

    bool operator==(const Station &rhs) const;
    bool operator!=(const Station &rhs) const;

    string getId();
    void setId(string newId);

    string getName();
    void setName(string newName);

    vector<LineName> getTransfers();
    void addTransfers(LineName newTransfer);
    bool hasTransferLine(string input);
    bool hasTransferLine();
    string getTransferLinesString();

    vector<Station> getAllStations();

    Borough getBorough();
    void setBorough(Borough newBorough);

    static string getTextForEnum(int enumVal);

    static Station getStation(string stationID);
    static Station getRandomStation(vector<Station> &allStations);
};

#endif //M1OEP_NCYR1_STATION_H
