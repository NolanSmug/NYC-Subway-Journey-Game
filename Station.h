//
// Created by Nolan Cyr on 1/31/24.
//

#ifndef M1OEP_NCYR1_STATION_H
#define M1OEP_NCYR1_STATION_H

#include <string>
#include <vector>
#include "Line.h"

using namespace std;

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
    Station(string id, string name, vector<LineName> transfers = {}, Borough borough = MANHATTAN);

    friend ostream& operator<<(ostream& str, Station station);

    string getId();
    void setId(string newId);

    string getName() const;
    void setName(string newName);

    vector<LineName> getTransfers();
    void addTransfers(LineName newTransfer);
    bool hasTransferLine(string input);

    Borough getBorough();
    void setBorough(Borough newBorough);

    string getTextForEnum(int enumVal);
};

#endif //M1OEP_NCYR1_STATION_H
