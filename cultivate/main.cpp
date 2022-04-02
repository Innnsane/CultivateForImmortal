#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QVector>

void test(MainWindow&);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //test(w);
    return a.exec();
}

void test(MainWindow& w){
    RandomNumber *random = new RandomNumber();

    qDebug() << random->getRandomUniform();
    peopleArrayGlobal.peopleRecruitUniform(1, 3);
    w.displayPeopleStatus();
}
