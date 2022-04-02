#include "randomnumber.h"

#include <QDebug>
#include <QMap>

RandomNumber::RandomNumber():
    useTime(0),
    createTime(QTime::currentTime()),
    randomEngine(std::default_random_engine(static_cast<unsigned int>(createTime.msec()))),
    distributionNormal(std::normal_distribution<double>(50, 16.67)),
    distributionUniform(std::uniform_int_distribution<int>(0,100))
{
    getRandomUniform();
}

RandomNumber::RandomNumber(int seed):
    useTime(0),
    createTime(QTime::currentTime()),
    randomEngine(std::default_random_engine(static_cast<unsigned int>(createTime.msec() + seed))),
    distributionNormal(std::normal_distribution<double>(50, 16.67)),
    distributionUniform(std::uniform_int_distribution<int>(0,100))
{
    getRandomUniform();
}

int RandomNumber::getRandomUniform(){
    useTime += 1;
    return distributionUniform(randomEngine);
}

double RandomNumber::getRandomNormal(){
    useTime += 1;
    double result = distributionNormal(randomEngine);

    if(result < 0 || result > 100) return distributionNormal(randomEngine);
    else return result;
}

void RandomNumber::test(){
    QMap<int, int> testMap;

    for(int i = 0; i < 50000; i ++)
        testMap[static_cast<int>(getRandomNormal())] += 1;

    for(auto i: testMap.keys())
        qDebug() << i << testMap.value(i);
}
