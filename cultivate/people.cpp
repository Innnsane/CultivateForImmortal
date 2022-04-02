#include "people.h"

#include <QDebug>
#include <QVector>
#include <QString>


Status::Status(double levelInput): level(levelInput){

    status.resize(int(AllStatusKey::END));
    talent.resize(int(AllStatusKey::END));
    personality.resize(int(PersonalityKey::END));

    for(int i = 0; i < int(AllStatusKey::END); i++){
        status[i] = 1;
        talent[i] = gameDataGlobal.getRandom().getRandomNormal();
    }

    for(int i = 0; i < int(PersonalityKey::END); i++)
        personality[i] = gameDataGlobal.getRandom().getRandomNormal();
}

Status::Status(double levelInput,
               QMap<int, double>& mapStatusInput,
               QMap<int, double>& mapTalentInput,
               QMap<int, double>& mapPersonalityInput): level(levelInput) {

    status.resize(int(AllStatusKey::END));
    talent.resize(int(AllStatusKey::END));
    personality.resize(int(PersonalityKey::END));

    for(int i = 0; i < int(AllStatusKey::END); i++){
        if(mapStatusInput.contains(i)) status[i] = mapStatusInput[i];
        else status[i] = 1;

        if(mapTalentInput.contains(i)) talent[i] = mapTalentInput[i];
        else talent[i] = gameDataGlobal.getRandom().getRandomNormal();
    }

    for(int i = 0; i < int(PersonalityKey::END); i++){
        if(mapPersonalityInput.contains(i)) personality[i] = mapPersonalityInput[i];
        else personality[i] = gameDataGlobal.getRandom().getRandomNormal();
    }

}

void Status::debugStatus(){
    qDebug() << "AllStatus";
    for(int i = 0; i < int(AllStatusKey::END); i++){
        qDebug() << gameDataGlobal.allStatusKeyName.value(i) << ": " << status[i];
    }

    qDebug() << "TalentStatus";
    for(int i = 0; i < int(AllStatusKey::END); i++){
        qDebug() << gameDataGlobal.allStatusKeyName.value(i) << ": " << talent[i];
    }

    qDebug() << "PersonalityStatus";
    for(int i = 0; i < int(PersonalityKey::END); i++){
        qDebug() << gameDataGlobal.allStatusKeyName.value(i) << ": " << personality[i];
    }
    qDebug() << endl;
}

QVector<double>& Status::getTalent(){
    return talent;
}

QVector<double>& Status::getPersonality(){
    return personality;
}

/*
* class People
*/
void People::remakeLearningChoice(){
    learningChoice.clear();
    if(talent[int(AllStatusKey::MAGIC)] > talent[int(AllStatusKey::STRENGTH)]) learningChoice[int(AllStatusKey::MAGIC)] = 0.5;
    else learningChoice[int(AllStatusKey::STRENGTH)] = 0.5;

    int habbit = 2; // MAGIC and STRENGTH is not include
    double mostTalented = 0;
    for(int i = 2; i < int(AllStatusKey::END); i++){
        if(talent[i] > mostTalented){
            habbit = i;
            mostTalented = talent[i];
        }
    }

    learningChoice[habbit] = 0.5;
}

void People::statusImprove(int statusId, double efficiency){
    double gain = pow(getTalent()[statusId] / 50, 2) * floor(level) * efficiency;
    status[statusId] += gain;
    qDebug() << status[statusId];
}

void People::locationChoose(){
    // chose learning at home or taking an adventure or something else
    int locationTemp = int(PeopleLocation::ATHOME);
    if(location.first && location.second > 0) locationTemp = location.first;
    else {
        double threshold = getPersonality()[int(PersonalityKey::RADICAL)];
        double dice = static_cast<double>(gameDataGlobal.getRandom().getRandomUniform());
        locationTemp = (dice < threshold) ? int(PeopleLocation::ATHOME) : int(PersonalityKey::RADICAL);
    }

    switch(PeopleLocation(locationTemp)){
        case PeopleLocation::ATHOME: learn();
            break;
        case PeopleLocation::ADVENTURE: adventure();
            break;
        default:
            break;
    }
}

void People::learn(double efficiency){
    // learningChoice has multi-keys, and its value is a 100-percent.
    for(auto statusKeyName: learningChoice.keys()){
        statusImprove(statusKeyName, efficiency * learningChoice.value(statusKeyName));
    }
}

void People::adventure(){
    // only status change for now.
    double base = gameDataGlobal.getRandom().getRandomNormal();
    double efficiency = pow((base - 10)/50, 2);

    int choice = gameDataGlobal.getRandom().getRandomUniform() % (int(AllStatusKey::END) - 1);

    statusImprove(choice, efficiency);
}

void People::upgradeJudge(){
    if(level >= 99.9){
        if(gameDataGlobal.getRandom().getRandomUniform() < 0.00001) level = 100;
    }
    else if(static_cast<int>(level * 10) % 10 >= 9){
        if(gameDataGlobal.getRandom().getRandomUniform() < (100 - level) / 100) level += 0.1;
    }
    else {
        if(gameDataGlobal.getRandom().getRandomUniform() < (100 - level) / 10) level += 0.1;
    }
}

void People::writePeopleHistory(int behaviorType, double number){
    history.push_back(QPair<int, double>(behaviorType, number));
}

PeopleArray peopleArrayGlobal = PeopleArray();

QVector<People>& PeopleArray::getPeopleArray(){
    return peopleArray;
}

void PeopleArray::peopleRecruitUniform(double level, int number){
    while(number--){
        peopleArray.push_back(People(level));
        peopleArray[peopleArray.size()-1].remakeLearningChoice();
    }
}


