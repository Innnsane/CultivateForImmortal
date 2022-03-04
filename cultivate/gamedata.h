#ifndef GAMEDATA_H
#define GAMEDATA_H

#include "mainwindow.h"

const QVector<QString> statusBasicKeyName = {
    "strength", "magic"
};
const QVector<QString> statusKeyName = {
    "strength", "weapon", "magic", "instrument", "craft", "construct", "drawing", "garden", "medicine"
};
const QVector<QString> talentKeyName = {
    "strength", "weapon", "magic", "instrument", "craft", "construct", "drawing", "garden", "medicine"
};
const QVector<QString> personalityKeyName = {
    "loyalty", "radical"
};

enum class PeopleBehavior: int
    {GETIN, IMPROVE, UPGRADE, MISSIONSTART, MISSIONCOMPLISHED, DEAD};

class GameData
{
public:
    GameData();
    QVector<People> peopleArray;

    void peopleRecruit(double, int);

};

// global variable
extern GameData gameDataGlobal;

#endif // GAMEDATA_H
