#include "gamedata.h"
#include "mainwindow.h"

GameData::GameData(): peopleArray(QVector<People>()){}

GameData gameDataGlobal = GameData();

void GameData::peopleRecruit(double level, int number){
    RandomNumber *random = new RandomNumber();

    while(number--){
        peopleArray.push_back(People(*random, level));
    }
}
