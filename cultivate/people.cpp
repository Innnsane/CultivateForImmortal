#include "people.h"
#include "randomnumber.h"
#include "mainwindow.h"

#include <QDebug>
#include <QVector>
#include <QString>


Status::Status(RandomNumber &random): level(1){
    for(auto i: statusKeyName)
        mapStatus[i] = 1;
    for(auto i: talentKeyName)
        mapTalent[i] = random.getRandomNormal();
    for(auto i: personalityKeyName)
        mapPersonality[i] = random.getRandomNormal();
}

Status::Status(RandomNumber &random, double &levelInput): level(levelInput){
    for(auto i: talentKeyName)
        mapTalent[i] = random.getRandomNormal();
    for(auto i: personalityKeyName)
        mapPersonality[i] = random.getRandomNormal();

    for(auto i: statusKeyName){
        mapStatus[i] = 1;
    }
}

Status::Status(RandomNumber& random,
               double &levelInput,
               MAP_STATUS& mapStatusInput,
               MAP_STATUS& mapTalentInput,
               MAP_STATUS& mapPersonalityInput): level(levelInput){

    for(auto i: talentKeyName){
        if(mapTalentInput.contains(i)) mapTalent[i] = mapTalentInput[i];
        else mapTalent[i] = random.getRandomNormal();
    }

    for(auto i: personalityKeyName){
        if(mapPersonalityInput.contains(i)) mapPersonality[i] = mapPersonalityInput[i];
        else mapPersonality[i] = random.getRandomNormal();
    }

    for(auto i: statusKeyName){
        if(mapStatusInput.contains(i)) mapStatus[i] = mapStatusInput[i];
        else mapStatus[i] = 1;
    }

}

Status::~Status(){}
People::~People(){}

void Status::debugStatus(){
    for(auto i:statusKeyName){
        qDebug() << i << ": " << mapStatus.value(i);
    }
    for(auto i:talentKeyName){
        qDebug() << i << ": " << mapTalent.value(i);
    }
    for(auto i:personalityKeyName){
        qDebug() << i << ": " << mapPersonality.value(i);
    }
    qDebug() << endl;
}

MAP_STATUS& Status::getMapTalent(){
    return mapTalent;
}

MAP_STATUS& Status::getMapPersonality(){
    return mapPersonality;
}

void People::upgradeNormal(RandomNumber &random){
    if(level >= 99.9){
        if(random.getRandomUniform() < 0.00001) level = 100;
    }
    else if(static_cast<int>(level * 10) % 10 >= 9){
        if(random.getRandomUniform() < (100 - level) / 100) level += 0.1;
    }
    else {
        if(random.getRandomUniform() < (100 - level) / 10) level += 0.1;
    }
}

void People::exerciseNormalChoice(RandomNumber &random){
    QVector<QMap<QString, double>> maxTalent(2);
    MAP_STATUS mapTalentCopy;

    for(auto keyName: getMapTalent().keys())
        mapTalentCopy[keyName] = getMapTalent()[keyName];

    if(mapTalentCopy["strength"] > mapTalentCopy["magic"]){
        mapTalentCopy["strength"] *= 2;
        mapTalentCopy["weapon"] *= 2;
    } else {
        mapTalentCopy["magic"] *= 2;
        mapTalentCopy["instrument"] *= 2;
    }

    double totalBasicTalent = mapTalentCopy["strength"] + mapTalentCopy["magic"];
    double totalBasicStatus = mapStatus["strength"] + mapStatus["magic"];
    double strength = (mapTalentCopy["strength"]) / totalBasicTalent + mapStatus["strength"] / totalBasicStatus / 2;
    // double magic = (mapTalentCopy["magic"]) / totalBasicTalent + mapStatus["magic"] / totalBasicStatus / 2;

    for(auto keyName: talentKeyName){
        if(keyName == "strength" || keyName == "magic") continue;

        for(int order = 0; order < maxTalent.size(); order ++){
            double score = mapTalentCopy[keyName] *8 + mapStatus[keyName];
            if(maxTalent[order].isEmpty() || maxTalent[order].first() < score){
                maxTalent[order].clear();
                maxTalent[order][keyName] = score;
                break;
            }
        }
    }

    double totalOtherTalent = maxTalent[0].first() + maxTalent[1].first();
    double otherA = maxTalent[0].first() / totalOtherTalent;
    // double otherB = maxTalent[1].first() / totalOtherTalent;

    double dice = static_cast<double>(random.getRandomUniform()) /100;

    // qDebug() << maxTalent[0].firstKey() << " " << maxTalent[1].firstKey();
    // qDebug() << "dice:" << dice << " choice:" << strength << " " << magic << " " << otherA << " " << otherB;
    if(dice < 0.5 && dice < strength/2) exerciseImprove(QString::fromLocal8Bit("strength"));
    else if(dice < 0.5 && dice >= strength/2) exerciseImprove("magic");
    else if(dice < otherA) exerciseImprove(maxTalent[0].firstKey());
    else exerciseImprove(maxTalent[1].firstKey());

}

void People::exerciseImprove(QString exerciseKeyName){
    if(!mapStatus.contains(exerciseKeyName)) return;
    double talent = getMapTalent().value(exerciseKeyName);
    double status = mapStatus.value(exerciseKeyName);

    double baseAddition = (talent * talent / 2500) * (level / 10);
    double threshold = baseAddition * 36;
    double addition = baseAddition;

    if(baseAddition > threshold){
        addition = baseAddition * (status / threshold);
    }

    if(addition < 0.1){
        addition = 0.1;
    }

    mapStatus[exerciseKeyName] += addition;
}

void People::writePeopleHistory(int behaviorType, double number){
    history.push_back(QPair<int, double>(behaviorType, number));
}




