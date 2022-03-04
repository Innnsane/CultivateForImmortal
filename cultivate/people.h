#ifndef PEOPLE_H
#define PEOPLE_H
#include <QVector>
#include <QString>
#include <QMap>


#include "randomnumber.h"

typedef QMap<QString , double> MAP_STATUS;

class Status{
public:
    double level;
    MAP_STATUS mapStatus;

private:
    MAP_STATUS mapTalent;
    MAP_STATUS mapPersonality;

public:
    Status(){}
    Status(RandomNumber&);
    Status(RandomNumber&, double&);
    Status(RandomNumber&, double&, MAP_STATUS&, MAP_STATUS&, MAP_STATUS&);
    virtual ~Status();

    void debugStatus(void);

    MAP_STATUS& getMapTalent();
    MAP_STATUS& getMapPersonality();
};


class People: public Status{
public:
    QString name;
    double wealth;

private:
    QVector<QPair<int, double>> history;

public:
    People(): Status(){}
    People(RandomNumber &random): Status(random){}
    People(RandomNumber &random, double &levelInput): Status(random, levelInput){}
    People(RandomNumber &random, double &levelInput, MAP_STATUS &mapStatusInput, MAP_STATUS &mapTalentInput, MAP_STATUS &mapPersonalityInput):
        Status(random, levelInput, mapStatusInput, mapTalentInput, mapPersonalityInput){}
    virtual ~People();

    void upgradeNormal(RandomNumber&);
    void exerciseNormalChoice(RandomNumber &);
    void exerciseImprove(QString);
    void writePeopleHistory(int, double);

};

#endif // PEOPLE_H
