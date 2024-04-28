
#include "Challenge.h"

Challenge::Challenge() = default;

Challenge::Challenge(Station startStation, Station destinationStation, Difficulty difficulty) :
        startLine(NULL_TRAIN), // Set startLine to NULL_TRAIN by default
        startStation(startStation),
        destinationStation(destinationStation),
        difficulty(difficulty) {}


void Challenge::setStartLine(LineName newStartLine) {
    startLine = newStartLine;
}

LineName Challenge::getStartLine() {
    return startLine;
}


void Challenge::setStartStation(Station newStartStation) {
    startStation = newStartStation;
}

Station Challenge::getStartStation() {
    return startStation;
}


void Challenge::setDestinationStation(Station newDestinationStation) {
    destinationStation = newDestinationStation;
}

Station Challenge::getDestinationStation() {
    return destinationStation;
}


Difficulty Challenge::getDifficulty() {
    return difficulty;
}

void Challenge::setDifficulty(Difficulty newDifficulty) {
    difficulty = newDifficulty;
}

vector<Challenge> Challenge::getAllChallenges() {
    return allChallenges;
}


void Challenge::initializeAllChallenges() {
    const Station GRAND_CENTRAL_42                = Station::getStation("Grand Central-42 St","631");
    const Station BROOKLYN_BRIDGE_CITY_HALL       = Station::getStation("Brooklyn Bridge-City Hall","640");
    const Station W96TH_ST                        = Station::getStation("96 St", "120");
    const Station FLATBUSH_AVE_BROOKLYN_COLLEGE   = Station::getStation("Flatbush Av-Brooklyn College", "247");
    const Station E34TH_ST_PENN_STATION           = Station::getStation("34 St-Penn Station","A28");
    const Station WORLD_TRADE_CENTER              = Station::getStation("World Trade Center","E01");
    const Station METROPOLITAN_AVE                = Station::getStation("Metropolitan Av","G29");
    const Station COURT_SQ                        = Station::getStation("Court Sq","G22");
    const Station METS_WILLETS_POINT              = Station::getStation("Mets-Willets Point","702");
    const Station VAN_CORTLANDT_PARK_242ND_ST     = Station::getStation("Van Cortlandt Park-242 St","101");
    const Station ASTORIA_DITMARS_BLVD            = Station::getStation("Astoria-Ditmars Blvd","R01");
    const Station PRINCE_ST                       = Station::getStation("Prince St","R22");
    const Station E14TH_ST_UNION_SQ               = Station::getStation("14 St-Union Sq","635");
    const Station HOWARD_BEACH_JFK_AIRPORT        = Station::getStation("Howard Beach-JFK Airport", "H03");
    const Station W81ST_MUSEUM_OF_NATURAL_HISTORY = Station::getStation("81 St-Museum of Natural History", "A21");
    const Station DELANCEY_ST_ESSEX_ST            = Station::getStation("Delancey St-Essex St","M18");
    const Station MYRTLE_AVE                      = Station::getStation("Myrtle Av","M11");
    const Station NOSTRAND_AVE                    = Station::getStation("Nostrand Av","M28");
    const Station DYCKMAN_ST                      = Station::getStation("Dyckman St","A03");
    const Station PELHAM_BAY_PARK                 = Station::getStation("Pelham Bay Park","601");
    const Station CONEY_ISLAND_STILLWELL_AVE      = Station::getStation("Coney Island-Stillwell Av","D43");
    const Station GREENPOINT_AVE                  = Station::getStation("Greenpoint Av","G26");
    const Station FAR_ROCKAWAY_MOTT_AVE           = Station::getStation("Far Rockaway-Mott Av","H11");
    const Station JAMAICA_179TH_ST                = Station::getStation("Jamaica-179 St","F01");

    // Easy challenges
    allChallenges.emplace_back(GRAND_CENTRAL_42, BROOKLYN_BRIDGE_CITY_HALL, EASY);
    allChallenges.emplace_back(W96TH_ST, FLATBUSH_AVE_BROOKLYN_COLLEGE, EASY);
    allChallenges.emplace_back(E34TH_ST_PENN_STATION, WORLD_TRADE_CENTER, EASY);
    allChallenges.emplace_back(METROPOLITAN_AVE, COURT_SQ, EASY);
    allChallenges.emplace_back(GRAND_CENTRAL_42, METS_WILLETS_POINT, EASY);

    // Medium challenges
    allChallenges.emplace_back(VAN_CORTLANDT_PARK_242ND_ST, WORLD_TRADE_CENTER, MEDIUM);
    allChallenges.emplace_back(ASTORIA_DITMARS_BLVD, PRINCE_ST, MEDIUM);
    allChallenges.emplace_back(E14TH_ST_UNION_SQ, HOWARD_BEACH_JFK_AIRPORT, MEDIUM);
    allChallenges.emplace_back(W81ST_MUSEUM_OF_NATURAL_HISTORY, DELANCEY_ST_ESSEX_ST, MEDIUM);
    allChallenges.emplace_back(MYRTLE_AVE, NOSTRAND_AVE, MEDIUM);

    // Hard challenges
    allChallenges.emplace_back(COURT_SQ, DYCKMAN_ST, HARD);
    allChallenges.emplace_back(PELHAM_BAY_PARK, CONEY_ISLAND_STILLWELL_AVE, HARD);
    allChallenges.emplace_back(DYCKMAN_ST, GREENPOINT_AVE, HARD);
    allChallenges.emplace_back(FAR_ROCKAWAY_MOTT_AVE, JAMAICA_179TH_ST, HARD);
}

void Challenge::addNewChallenge(Challenge newChallenge) {
    allChallenges.emplace_back(newChallenge);
}

// overloaded cout operator
ostream& operator<<(ostream& str, Challenge challenge) {
    Station startStation = challenge.getStartStation();
    Station destiStation = challenge.getDestinationStation();

    int minStationNameWidth = 32;
    int minTransferLineWidth = 20;

    str << left << setw(minStationNameWidth) << startStation.getName();
    str << "  " << setw(minTransferLineWidth) << left << startStation.getTransferLinesString();

    str << setw(10) << left << "----->" << "   ";

    str << left << setw(minStationNameWidth) << destiStation.getName();
    str << "  " << setw(minTransferLineWidth) << left << destiStation.getTransferLinesString();

    return str;
}


