#include "GameStats.h"

GameStats::GameStats() = default;

GameStats::GameStats(int totalStationsVisited, int totalTransfers, set<LineName> linesVisited,
                     set<Borough> boroughsVisited) : totalStationsVisited(totalStationsVisited),
                                                               totalTransfers(totalTransfers),
                                                               linesVisited(linesVisited),
                                                               boroughsVisited(boroughsVisited) {};


void GameStats::incrementStationsVisited() {
    totalStationsVisited++;
}

int GameStats::getTotalStationsVisited(){
    return totalStationsVisited;
}


void GameStats::incrementTransfers() {
    totalTransfers++;
}

int GameStats::getTotalTransfers(){
    return totalTransfers;
}


void GameStats::addToLinesVisited(LineName lineName) {
    linesVisited.insert(lineName);
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

