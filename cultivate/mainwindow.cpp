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

    model->setColumnCount(int(AllStatusKey::END)+2);
    model->setHeaderData(0,Qt::Horizontal,QString::fromLocal8Bit("name"));
    model->setHeaderData(1,Qt::Horizontal,QString::fromLocal8Bit("level"));

    ui->PeopleDisplayTable->setModel(model);
    ui->PeopleDisplayTable->setColumnWidth(0,65);
    ui->PeopleDisplayTable->setColumnWidth(1,65);

    for(int i = 0; i < int(AllStatusKey::END); i++){
        model->setHeaderData(i+2,Qt::Horizontal, gameDataGlobal.allStatusKeyName[i]);
        ui->PeopleDisplayTable->setColumnWidth(i+2,65);
    }

    ui->PeopleDisplayTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

    auto arr = peopleArrayGlobal.getPeopleArray();
    for(int i = 0; i < arr.size(); i++)
    {
        model->setItem(i,0,new QStandardItem(arr[i].name));
        model->setItem(i,1,new QStandardItem(QString::number(arr[i].level)));

        for(int j = 0; j < int(AllStatusKey::END); j++){
            double a = arr[i].status[j];
            model->setItem(i,j+2,new QStandardItem(QString::number(static_cast<int>(a))));
        }
    }
}

void MainWindow::on_PeopleRecruitButton_clicked(){
    peopleArrayGlobal.peopleRecruitUniform(1, 1);
    displayPeopleStatus();
}

void MainWindow::on_NextPeriodButton_clicked(){
    QVector<People>& arr = peopleArrayGlobal.getPeopleArray();
    for(int i = 0; i < arr.size(); i++){
        arr[i].locationChoose();
        arr[i].debugStatus();
        // arr[i].upgradeNormal();
    }

    displayPeopleStatus();
}
