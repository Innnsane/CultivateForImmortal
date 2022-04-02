#include "gamedata.h"
#include "mainwindow.h"

GameData::GameData():
    allStatusKeyName({
        {int(AllStatusKey::STRENGTH),"STRENGTH"},
        {int(AllStatusKey::MAGIC),"MAGIC"},
        {int(AllStatusKey::WEAPON),"WEAPON"},
        {int(AllStatusKey::INSTRUMENT),"INSTRUMENT"},
        {int(AllStatusKey::CRAFT),"CRAFT"},
        {int(AllStatusKey::CONSTRUCT),"CONSTRUCT"},
        {int(AllStatusKey::DRAWING),"DRAWING"},
        {int(AllStatusKey::GARDEN),"GARDEN"},
        {int(AllStatusKey::MEDICINE),"MEDICINE"},
        {int(AllStatusKey::DOLL),"DOLL"},
    }),
    basicStatusKeyName({
        {int(BasicStatusKey::STRENGTH),"STRENGTH"},
        {int(BasicStatusKey::MAGIC),"MAGIC"},
    }),
    personalityKeyName({
        {int(PersonalityKey::LOYALTY),"LOYALTY"},
        {int(PersonalityKey::RADICAL),"RADICAL"},
    }){};

GameData gameDataGlobal = GameData();

RandomNumber& GameData::getRandom(){
    return random;
}
