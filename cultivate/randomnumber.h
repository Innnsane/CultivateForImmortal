#ifndef RANDOMNUMBER_H
#define RANDOMNUMBER_H
#include <random>
#include <QTime>

class RandomNumber
{

public:
    RandomNumber();
    int getRandomUniform();
    double getRandomNormal();
    void test();

private:
    int useTime;
    QTime createTime;
    std::default_random_engine randomEngine;
    std::normal_distribution<double> distributionNormal;
    std::uniform_int_distribution<int> distributionUniform;
};

#endif // RANDOMNUMBER_H
