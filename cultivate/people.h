#ifndef PEOPLE_H
#define PEOPLE_H
#include <QVector>
#include <QString>
#include <QPair>
#include <QMap>

#include "gamedata.h"

typedef QMap<QString, double> MAP_STATUS;

class Status{
public:
    double level;
    QVector<double> status;

protected:
    QVector<double> talent;
    QVector<double> personality;

public:
    Status(double level = 1.0);
    Status(double, QMap<int, double>&, QMap<int, double>&, QMap<int, double>&);

    void debugStatus(void);

    QVector<double>& getTalent();
    QVector<double>& getPersonality();
};

class People: public Status{
public:
    QString name;
    double wealth;

private:
    // recording behiviour history of people.
    QVector<QPair<int, double>> history;
    // think about that choice not change frequently, so save them.
    // <Choice, timeOccupied> (everyone should exercise basic status, maybe not much.)
    QMap<int, double> learningChoice;
    QPair<int, int> location;

public:
    People(): Status(){}
    People(double levelInput): Status(levelInput){}
    People(double levelInput, QMap<int, double> &mapStatusInput, QMap<int, double> &mapTalentInput, QMap<int, double> &mapPersonalityInput):
        Status(levelInput, mapStatusInput, mapTalentInput, mapPersonalityInput){}

    void locationChoose();
    void adventure();
    void learn(double efficiency = 1.0);
    void statusImprove(int, double efficiency = 1.0);
    void upgradeJudge();

    void remakeLearningChoice();
    void writePeopleHistory(int, double);
};

class PeopleArray{
private:
    QVector<People> peopleArray;

public:
    QVector<People>& getPeopleArray();
    void peopleRecruitUniform(double, int);
};

// global variable
extern PeopleArray peopleArrayGlobal;

#endif // PEOPLE_H
