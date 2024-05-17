#include "GameStats.h"

GameStats::GameStats() = default;

GameStats::GameStats(int totalStationsVisited, int totalTransfers, vector<LineName> linesVisited,
                     vector<Borough> boroughsVisited) : totalStationsVisited(totalStationsVisited),
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
    linesVisited.push_back(lineName);
}

vector<LineName> GameStats::getLinesVisited() {
    return linesVisited;
}

void GameStats::addToBoroughsVisited(Borough borough) {
    boroughsVisited.push_back(borough);
}

vector<Borough> GameStats::getBoroughsVisited() {
    return boroughsVisited;
}


void GameStats::resetStats() {
    totalStationsVisited = 0;
    totalTransfers = 0;
}

