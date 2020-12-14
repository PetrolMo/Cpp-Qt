#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui_mainwindow.h"
#include "sensor.h"
#include <sys/time.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void setBtn(QAbstractButton* b);
    QList<Sensor> sensorList;
    QList<Sensor> calculateList1;
    QList<Sensor> calculateList2;
    void setTime(float time);
private slots:

    void on_confirmButton_clicked();

private:
    Ui::MainWindow *ui;
    QList<QAbstractButton*> btnList;
    QList<QAbstractButton*> chosenList;


};



#endif // MAINWINDOW_H
