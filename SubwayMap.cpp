//
// Created by Nolan Cyr on 2/1/24.
//
#include "sstream"
#include <fstream>
#include "vector"
#include "SubwayMap.h"

using namespace std;


void stringToLowerCase(string &string) {
    transform(string.begin(), string.end(), string.begin(), ::tolower);
}

string lineNameToCSV(LineName line) {
    if (line == NULL_TRAIN) {
        return "../csv/all_stations.csv";
    }

    string lineName = Line::getIDTextForEnum(line);
    string filePath = "../csv/" + lineName + "_stations.csv"; // standard file name pattern for each line
    stringToLowerCase(filePath); // ensure lowercase

    return filePath;
}

void SubwayMap::createStations(LineName line, vector<Station> &subwayStations) {
    string filePath = lineNameToCSV(line);

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
            if (!isspace(c)) { // Only process non-space characters
                if (c == 'S' && borough == "Bk") {
                    transfers.push_back(S_TRAIN_SHUTTLE);
                    break;
                }
                if (c == 'S' && borough == "Q") {
                    transfers.push_back(S_TRAIN_ROCKAWAY);
                    break;
                }
                if (c == 'f' || c == 'r') {
                    break;
                }
                else {
                    string lineStr(1, c);
                    LineName lineEnum = Line::stringToLineEnum(lineStr);
                    transfers.push_back(lineEnum);
                }
            }
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

void SubwayMap::updateStopsForLine(LineName line, vector<Station> &subwayStations) {
    createStations(line, subwayStations); // create the Station vector
}