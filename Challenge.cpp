
#include "Challenge.h"

Challenge::Challenge() = default;

Challenge::Challenge(LineName startLine, Station startStation, Station destinationStation, int difficulty) :
    startLine(startLine),
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


int Challenge::getDifficulty() {
    return difficulty;
}

void Challenge::setDifficulty(int newDifficulty) {
    difficulty = newDifficulty;
}


vector<Challenge> Challenge::getAllChallenges() {
    vector<Challenge> allChallenges;

    const Station GRAND_CENTRAL_42 = Station("631", "Grand Central-42 St", {FOUR_TRAIN, FIVE_TRAIN, SIX_TRAIN, SEVEN_TRAIN, S_TRAIN}, MANHATTAN);
    const Station BROOKLYN_BRIDGE_CITY_HALL = Station("640", "Brooklyn Bridge-City Hall", {FOUR_TRAIN,FIVE_TRAIN, SIX_TRAIN,J_TRAIN,Z_TRAIN}, MANHATTAN);
    const Station N96TH_ST = Station("120", "96th St", {ONE_TRAIN,TWO_TRAIN,THREE_TRAIN}, MANHATTAN);
    const Station FLATBUSH_AVE_BROOKLYN_COLLEGE = Station("D28", "Flatbush Ave-Brooklyn College", {TWO_TRAIN, FIVE_TRAIN}, BROOKLYN);
    const Station E34TH_ST_PENN_STATION = Station("D14", "34 St-Penn Station", {A_TRAIN, C_TRAIN, E_TRAIN}, MANHATTAN);
    const Station WORLD_TRADE_CENTER = Station("E14", "World Trade Center", {E_TRAIN}, MANHATTAN);
    const Station METROPOLITAN_AVE = Station("G16", "Metropolitan Ave", {G_TRAIN}, BROOKLYN);
    const Station COURT_SQ = Station("G22", "Court Sq", {G_TRAIN, SEVEN_TRAIN}, QUEENS);
    const Station METS_WILLETS_POINT = Station("F14", "Mets-Willets Point", {SEVEN_TRAIN}, QUEENS);
    const Station VAN_CORTLANDT_PARK_242ND_ST = Station("A01", "Van Cortlandt Park-242nd St", {ONE_TRAIN}, BRONX);
    const Station ASTORIA_DITMARS_BLVD = Station("N01", "Astoria-Ditmars Blvd", {N_TRAIN, W_TRAIN}, QUEENS);
    const Station PRINCE_ST = Station("R10", "Prince St", {N_TRAIN, R_TRAIN, W_TRAIN}, MANHATTAN);
    const Station E14TH_ST_UNION_SQ = Station("D17", "14 St-Union Sq", {FOUR_TRAIN, FIVE_TRAIN, SIX_TRAIN, L_TRAIN, N_TRAIN, Q_TRAIN, R_TRAIN}, MANHATTAN);
    const Station HOWARD_BEACH_JFK_AIRPORT = Station("A61", "Howard Beach-JFK Airport", {A_TRAIN}, QUEENS);
    const Station W81ST_MUSEUM_OF_NATURAL_HISTORY = Station("B02", "81 St-Museum of Natural History", {B_TRAIN, C_TRAIN}, MANHATTAN);
    const Station DELANCEY_ST_ESSEX_ST = Station("F16", "Delancey St-Essex St", {F_TRAIN, J_TRAIN, M_TRAIN, Z_TRAIN}, MANHATTAN);
    const Station MYRTLE_AVE = Station("M16", "Myrtle Av", {M_TRAIN}, BROOKLYN);
    const Station NOSTRAND_AVE = Station("M28", "Nostrand Av", {M_TRAIN}, BROOKLYN);
    const Station DYCKMAN_ST = Station("A01", "Dyckman St", {A_TRAIN}, MANHATTAN);
    const Station PELHAM_BAY_PARK = Station("D20", "Pelham Bay Park", {SIX_TRAIN}, BRONX);
    const Station CONEY_ISLAND_STILLWELL_AVE = Station("D42", "Coney Island-Stillwell Ave", {D_TRAIN, F_TRAIN, N_TRAIN, Q_TRAIN}, BROOKLYN);
    const Station GREENPOINT_AVE = Station("G24", "Greenpoint Av", {G_TRAIN, SEVEN_TRAIN}, BROOKLYN);
    const Station FAR_ROCKAWAY_MOTT_AVE = Station("H08", "Far Rockaway-Mott Av", {A_TRAIN}, QUEENS);
    const Station JAMAICA_179TH_ST = Station("F04", "Jamaica-179 St", {F_TRAIN}, QUEENS);

    // Easy challenges
    allChallenges.emplace_back(FOUR_TRAIN, GRAND_CENTRAL_42, BROOKLYN_BRIDGE_CITY_HALL, 1);
    allChallenges.emplace_back(TWO_TRAIN, N96TH_ST, FLATBUSH_AVE_BROOKLYN_COLLEGE, 1);
    allChallenges.emplace_back(E_TRAIN, E34TH_ST_PENN_STATION, WORLD_TRADE_CENTER, 1);
    allChallenges.emplace_back(G_TRAIN, METROPOLITAN_AVE, COURT_SQ, 1);
    allChallenges.emplace_back(SEVEN_TRAIN, GRAND_CENTRAL_42, METS_WILLETS_POINT, 1);

    // Medium challenges
    allChallenges.emplace_back(ONE_TRAIN, VAN_CORTLANDT_PARK_242ND_ST, WORLD_TRADE_CENTER, 2);
    allChallenges.emplace_back(N_TRAIN, ASTORIA_DITMARS_BLVD, PRINCE_ST, 2);
    allChallenges.emplace_back(FIVE_TRAIN, E14TH_ST_UNION_SQ, HOWARD_BEACH_JFK_AIRPORT, 2);
    allChallenges.emplace_back(B_TRAIN, W81ST_MUSEUM_OF_NATURAL_HISTORY, DELANCEY_ST_ESSEX_ST, 2);
    allChallenges.emplace_back(M_TRAIN, MYRTLE_AVE, NOSTRAND_AVE, 2);

    // Hard challenges
    allChallenges.emplace_back(G_TRAIN, COURT_SQ, DYCKMAN_ST, 3);
    allChallenges.emplace_back(SIX_TRAIN, PELHAM_BAY_PARK, CONEY_ISLAND_STILLWELL_AVE, 3);
    allChallenges.emplace_back(ONE_TRAIN, DYCKMAN_ST, GREENPOINT_AVE, 3);
    allChallenges.emplace_back(A_TRAIN, FAR_ROCKAWAY_MOTT_AVE, JAMAICA_179TH_ST, 3);

    return allChallenges;
}


