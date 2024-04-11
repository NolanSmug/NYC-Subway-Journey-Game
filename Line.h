//
// Created by Nolan Cyr on 2/21/24.
//

#ifndef LINE_H
#define LINE_H

#include <string>

using namespace std;

enum LineName {
    NULL_TRAIN,
    ONE_TRAIN, TWO_TRAIN, THREE_TRAIN,
    FOUR_TRAIN, FIVE_TRAIN, SIX_TRAIN, SEVEN_TRAIN,
    A_TRAIN, C_TRAIN, E_TRAIN,
    B_TRAIN, D_TRAIN, F_TRAIN, M_TRAIN,
    N_TRAIN, Q_TRAIN, R_TRAIN, W_TRAIN,
    J_TRAIN, Z_TRAIN,
    G_TRAIN,
    L_TRAIN,
    S_TRAIN, // Times Sq-42 St to Grand Central-42 St
    S_TRAIN_SHUTTLE, // Franklin Av Shuttle
    S_TRAIN_ROCKAWAY
};

enum LineType {
    NONE,
    EXPRESS,
    LOCAL
};

static const int TOTAL_NUM_LINES = 25;

static const char* LineEnumIDStrings[] = {
        "Null_Train",
        "One_Train", "Two_Train", "Three_Train",
        "Four_Train", "Five_Train", "Six_Train", "Seven_Train",
        "A_Train", "C_Train", "E_Train",
        "B_Train", "D_Train", "F_Train", "M_Train",
        "N_Train", "Q_Train", "R_Train", "W_Train",
        "J_Train", "Z_Train",
        "G_Train",
        "L_Train",
        "S_Train",
        "S_Train_Shuttle",
        "S_Train_Rockaway"
};

static const char * LineEnumStrings[] = {
        "Null_Train",
        "1", "2", "3",
        "4", "5", "6", "7",
        "A", "C", "E",
        "B", "D", "F", "M",
        "N", "Q", "R", "W",
        "J", "Z",
        "G",
        "L",
        "S",
        "Sf",
        "Sr"
};

static const char * LineTypeEnumStrings[] = {
        "",
        "Express",
        "Local"
};



class Line {
public:
    static string getTextForEnum(int enumVal);
    static string getIDTextForEnum(int enumVal);
    static string getLineTypeString(int enumVal);

    static LineName stringToLineEnum(string& lineStr);

    static LineName getRandomLine();
};

#endif // LINE_H
