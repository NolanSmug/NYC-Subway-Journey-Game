//
// Created by Nolan Cyr on 2/1/24.
//
#include "sstream"
#include <fstream>
#include "vector"
#include "SubwayMap.h"

using namespace std;

LineName stringToLineEnum(const string& lineStr) {
    if (lineStr == "1") return ONE_TRAIN;
    if (lineStr == "2") return TWO_TRAIN;
    if (lineStr == "3") return THREE_TRAIN;
    if (lineStr == "4") return FOUR_TRAIN;
    if (lineStr == "5") return FIVE_TRAIN;
    if (lineStr == "6") return SIX_TRAIN;
    if (lineStr == "7") return SEVEN_TRAIN;
    if (lineStr == "A") return A_TRAIN;
    if (lineStr == "C") return C_TRAIN;
    if (lineStr == "E") return E_TRAIN;
    if (lineStr == "B") return B_TRAIN;
    if (lineStr == "D") return D_TRAIN;
    if (lineStr == "F") return F_TRAIN;
    if (lineStr == "M") return M_TRAIN;
    if (lineStr == "N") return N_TRAIN;
    if (lineStr == "Q") return Q_TRAIN;
    if (lineStr == "R") return R_TRAIN;
    if (lineStr == "W") return W_TRAIN;
    if (lineStr == "J") return J_TRAIN;
    if (lineStr == "Z") return Z_TRAIN;
    if (lineStr == "G") return G_TRAIN;
    if (lineStr == "L") return L_TRAIN;
    return NULL_TRAIN; // Default value for unknown line strings
}


void SubwayMap::createAllStations(string filePath, vector<Station> &subwayStations) {
    ifstream inFile;
    inFile.open(filePath);

    subwayStations.clear(); // clear if passed in for a transfer

    string header; // read header (ignore)
    if (inFile) {
        getline(inFile, header);
    }

    // build variables
    string id, name, borough, transfersLine, emptyString;
    Borough boroughEnum;
    vector<LineName> transfers;
    char comma = ',';

    while (inFile && inFile.peek() != EOF) {
        // read id
        getline(inFile, id, comma);

        // read name
        getline(inFile, name, comma);

        // read transfers
        getline(inFile, transfersLine, comma);
        for (char c : transfersLine) {
            if (!isspace(c) && borough != "SI") { // Only process non-space characters
                string lineStr(1, c);
                LineName lineEnum = stringToLineEnum(lineStr);
                if (lineEnum != NULL_TRAIN) {
                    transfers.push_back(lineEnum);
                }
            }
        }
        if (borough == "SI") {
            transfers.push_back(NULL_TRAIN);
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

void stringToLowerCase(string &string) {
    transform(string.begin(), string.end(), string.begin(), ::tolower);
}

void SubwayMap::updateStopsForLine(LineName line, vector<Station> &subwayStations) {
    string lineName = Line::getTextForEnum(line);

    string filePath = "../csv/" + lineName + "_stations.csv"; // standard file name pattern for each line
    stringToLowerCase(filePath); // ensure lowercase

    createAllStations(filePath, subwayStations); // create the Station vector
}
