#include "GameStats.h"

GameStats::GameStats() {
    totalStationsVisited = 0;
    totalTransfers = 0;
}


void GameStats::incrementStationsVisited() {
    totalStationsVisited++;
}

void GameStats::incrementTransfers() {
    totalTransfers++;
}


int GameStats::getTotalStationsVisited(){
    return totalStationsVisited;
}

int GameStats::getTotalTransfers(){
    return totalTransfers;
}


void GameStats::resetStats() {
    totalStationsVisited = 0;
    totalTransfers = 0;
}
