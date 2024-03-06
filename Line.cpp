//
// Created by Nolan Cyr on 2/21/24.
//

#include "Line.h"
#include "random"

string Line::getTextForEnum(int enumVal) {
    return LineEnumStrings[enumVal];
}

string Line::getIDTextForEnum(int enumVal) {
    return LineEnumIDStrings[enumVal];
}

LineName Line::stringToLineEnum(string& lineStr) {
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
    if (lineStr == "S") return S_TRAIN;
    if (lineStr == "Sf") return S_TRAIN_SHUTTLE;
    if (lineStr == "Sr") return S_TRAIN_ROCKAWAY;
    if (lineStr == "Null_Train") return NULL_TRAIN;
    return NULL_TRAIN;
}

LineName Line::getRandomLine() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, TOTAL_NUM_LINES);

    int randomLineIndex = distribution(generator);
    LineName randomLine;
    randomLine = static_cast<LineName>(randomLineIndex);
    while (randomLine == NULL_TRAIN) {
        randomLineIndex = distribution(generator);
        randomLine = static_cast<LineName>(randomLineIndex);
    }

    return randomLine;
}
