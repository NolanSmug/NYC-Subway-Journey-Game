//
// Created by Nolan Cyr on 1/31/24.
//

#ifndef M1OEP_NCYR1_STATION_H
#define M1OEP_NCYR1_STATION_H

#include <string>
#include <vector>

using namespace std;

enum Borough {
    MANHATTAN,
    BROOKLYN,
    QUEENS,
    BRONX,
    STATEN_ISLAND
};

class Station {
private:
    string id;
    string name;
    vector<string> transfers;
    Borough borough;

public:
    Station();
    Station(string id, string name, vector<string> transfers = {}, Borough borough = MANHATTAN);

    string getId();
    void setId(const string& newId);

    string getName();
    void setName(const string& newName);

    vector<string> getTransfers();
    void addTransfers(const string& newTransfer);

    Borough getBorough();  // Getter for borough
    void setBorough(Borough newBorough);  // Setter for borough
};

#endif //M1OEP_NCYR1_STATION_H


