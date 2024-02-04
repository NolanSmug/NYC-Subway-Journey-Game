//
// Created by Nolan Cyr on 2/1/24.
//
#include "sstream"
#include <fstream>
#include "vector"
#include "Station.h"
#include "SubwayMap.h"

using namespace std;

void SubwayMap::createAllStations(string filePath, vector<Station> &subwayStations) {
    ifstream inFile;
    inFile.open(filePath);

    string header; // read header (ignore)
    if (inFile) {
        getline(inFile, header);
    }

    // build variables
    string id, name, borough, transfersLine, emptyString;
    Borough boroughEnum;
    vector<string> transfers;
    char comma = ',';

    while (inFile && inFile.peek() != EOF) {
        // read id
        getline(inFile, id, comma);

        // read name
        getline(inFile, name, comma);

        // read transfers
        getline(inFile, transfersLine, comma);
        for (char c : transfersLine) {
            int check_if_char = isspace(c);
            string newTransfer = string(1, c);
            if (check_if_char == 0 && borough != "SI") { // only append the char if it's a non-space
                transfers.push_back(newTransfer);
            }
        }
        if (borough == "SI") {
            transfers.push_back("SIR");
        }

        // borough
        inFile >> borough;
        getline(inFile, emptyString);
        if (borough == "M") {
            boroughEnum = MANHATTAN;
        } else if (borough == "Bk") {
            boroughEnum = BROOKLYN;
        } else if (borough == "Bx") {
            boroughEnum = BRONX;
        } else if (borough == "Q") {
            boroughEnum = QUEENS;
        } else if (borough == "SI") {
            boroughEnum = STATEN_ISLAND;
        }

        Station newStation = Station(id, name, transfers, boroughEnum);
        subwayStations.push_back(newStation);

        transfers.clear(); // clear transfer vector before building the next station
    }

    inFile.close();
}