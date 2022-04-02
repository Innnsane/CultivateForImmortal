#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QMap>

#include "randomnumber.h"
#include "gamedata.h"
#include "people.h"

/*
 * - GameData
 * - - RandomNumber
 *
 * - PeopleArray
 * - - People
 *
 */

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayPeopleStatus();

private slots:
    void on_PeopleRecruitButton_clicked();
    void on_NextPeriodButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
