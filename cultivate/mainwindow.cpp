#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::displayPeopleStatus(){
    QStandardItemModel *model = new QStandardItemModel();

    model->setColumnCount(statusKeyName.size()+2);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("name"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("level"));

    ui->PeopleDisplayTable->setModel(model);
    ui->PeopleDisplayTable->setColumnWidth(0,65);
    ui->PeopleDisplayTable->setColumnWidth(1,65);

    for(int i = 0; i < statusKeyName.size(); i++){
        model->setHeaderData(i+2,Qt::Horizontal,statusKeyName[i]);
        ui->PeopleDisplayTable->setColumnWidth(i+2,65);
    }

    ui->PeopleDisplayTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    for(int i = 0; i < gameDataGlobal.peopleArray.size(); i++)
    {
        model->setItem(i,0,new QStandardItem(gameDataGlobal.peopleArray[i].name));
        model->setItem(i,1,new QStandardItem(QString::number(gameDataGlobal.peopleArray[i].level)));

        for(int j = 0; j < statusKeyName.size(); j++){
            double a = gameDataGlobal.peopleArray[i].mapStatus.value(statusKeyName[j]);
            model->setItem(i,j+2,new QStandardItem(QString::number(static_cast<int>(a))));
        }
    }
}

void MainWindow::on_PeopleRecruitButton_clicked(){
    gameDataGlobal.peopleRecruit(1, 10);
    displayPeopleStatus();
}

void MainWindow::on_NextPeriodButton_clicked(){
    RandomNumber *random = new RandomNumber();

    for(int i = 0; i < gameDataGlobal.peopleArray.size(); i++){
        gameDataGlobal.peopleArray[i].exerciseNormalChoice(*random);
        gameDataGlobal.peopleArray[i].upgradeNormal(*random);
    }

    displayPeopleStatus();
}
