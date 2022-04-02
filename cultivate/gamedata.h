#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <QMap>
#include <QString>

#include "people.h"
#include "randomnumber.h"

enum class PeopleBehavior: int
    {GETIN, IMPROVE, UPGRADE, MISSIONSTART, MISSIONCOMPLISHED, DEAD, END};

enum class PeopleLocation: int
    {ATHOME, GRAVE, ADVENTURE, MISSION, BATTLEFIELD, END};

enum class BasicStatusKey: int
    {STRENGTH, MAGIC, END};

enum class AllStatusKey: int
    {STRENGTH, MAGIC, WEAPON, INSTRUMENT, CRAFT, CONSTRUCT, DRAWING, GARDEN, MEDICINE, DOLL, END};

enum class PersonalityKey: int
    {LOYALTY, RADICAL, END};


class GameData {
public:
    GameData();
    const QMap<int, QString> allStatusKeyName;
    const QMap<int, QString> basicStatusKeyName;
    const QMap<int, QString> personalityKeyName;

private:
    RandomNumber random;

public:
    RandomNumber& getRandom();
};

// global variable
extern GameData gameDataGlobal;

#endif // GAMEDATA_H
