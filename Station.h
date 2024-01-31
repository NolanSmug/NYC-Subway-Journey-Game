//
// Created by Nolan Cyr on 1/31/24.
//

#ifndef M1OEP_NCYR1_STATION_H
#define M1OEP_NCYR1_STATION_H

#include <string>
#include <vector>

using namespace std;

class Station {
private:
    string name;
    vector<string> transfers;

public:
    Station();
    Station(string name, vector<string> transfers = {});

    string getName();
    void setName(const string& newName);

    vector<string> getTransfers();
    void addTransfers(const string& newTransfer);
};

#endif //M1OEP_NCYR1_STATION_H

