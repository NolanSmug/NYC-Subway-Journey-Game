#include "GameStats.h"

GameStats::GameStats() = default;

GameStats::GameStats(int totalStationsVisited, int totalTransfers, set<LineName> linesVisited,
                     set<Borough> boroughsVisited) : totalStationsVisited(totalStationsVisited),
                                                               totalTransfers(totalTransfers),
                                                               linesVisited(linesVisited),
                                                               boroughsVisited(boroughsVisited) {};


void GameStats::incrementStationsVisited(Borough currentBorough) {
    boroughsVisited.insert(currentBorough);
    totalStationsVisited++;
}

void GameStats::incrementStationsVisited(int total) {
    totalStationsVisited += total;
}

int GameStats::getTotalStationsVisited(){
    return totalStationsVisited;
}

void GameStats::incrementTransfers() {
    totalTransfers++;
}

int GameStats::getTotalTransfers() {
    return totalTransfers;
}

void GameStats::addToLinesVisited(LineName lineName) {
    if (linesVisited.insert(lineName).second) {    // Line was successfully added to the set
        incrementTransfers();
    }
}

set<LineName> GameStats::getLinesVisited() {
    return linesVisited;
}

void GameStats::addToBoroughsVisited(Borough borough) {
    boroughsVisited.insert(borough);
}

set<Borough> GameStats::getBoroughsVisited() {
    return boroughsVisited;
}


void GameStats::resetStats() {
    totalStationsVisited = 0;
    totalTransfers = 0;
    linesVisited = {};
    boroughsVisited = {};
}

ostream& operator<<(ostream& os, GameStats stats) {
    set<LineName> linesVisited = stats.getLinesVisited();
    set<Borough> boroughsVisited = stats.getBoroughsVisited();

    os << "Total Stations Visited: " << stats.getTotalStationsVisited() << "\n"
       << "Total Lines Visited:    " << stats.getTotalTransfers() << "\n";

    os << "Lines Visited: ";
    for (set<LineName>::iterator it = linesVisited.begin(); it != linesVisited.end(); ++it) {
        os << Line::getTextForEnum(*it);
        if (next(it) != linesVisited.end()) {
            os << ",";
        }
    }

    os << "\nBoroughs Visited: ";
    for (set<Borough>::iterator it = boroughsVisited.begin(); it != boroughsVisited.end(); ++it) {
        os << Station::getTextForEnum(*it);
        if (next(it) != boroughsVisited.end()) {
            os << ",";
        }
    }

    return os;
}

