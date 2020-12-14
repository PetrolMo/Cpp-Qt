#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include <sys/time.h>
#include "QTime"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    setWindowIcon(QIcon("icon.png"));
    qRegisterMetaType<Sensor>("Sensor");
    ui->setupUi(this);
    this->btnList = ui->BG->buttons();
    foreach(auto item,btnList)
    {
        connect(item,&QRadioButton::toggled,this,[item,this] () {
            this->setBtn(item);
        });
    }

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setBtn(QAbstractButton *b){
    if(b->isChecked())
    {
        this->chosenList.append(b);
        this->sensorList.append(setXY(b->objectName()));
    }
    else{
        this->chosenList.removeOne(b);
        this->sensorList.removeOne(setXY(b->objectName()));
    }
    if(this->chosenList.empty()){
        ui->begin->setMarkdown(nullptr);
        ui->run->setMarkdown(nullptr);
    }
    else{
        ui->begin->setMarkdown(this->chosenList[0]->objectName());
        QString s;
        foreach(auto item, this->chosenList){
            s = s + " " + item->objectName();
        }
        ui->run->setMarkdown(s);
    }

}

void MainWindow::on_confirmButton_clicked()
{

    this->calculateList1 = ShortestDisList(this->sensorList);
    double d1 = TotalDis(this->calculateList1);
    int t1 = TotalTime(this->calculateList1);
    this->calculateList2 = ShortestTimeList(this->sensorList);
    int t2 = TotalTime(this->calculateList2);
    double d2 = TotalDis(this->calculateList2);
    QString Dis1 = QString::number(d1);
    QString Dis2 = QString::number(d2);
    QString Time1 = QString::number(t1);
    QString Time2 = QString::number(t2);
    QString showDis = showList(this->calculateList1);
    QString showTime = showList(this->calculateList2);
    ui->Dis1->setMarkdown(Dis1);
    ui->Dis2->setMarkdown(Dis2);
    ui->showDis->setMarkdown(showDis);
    ui->Time1->setMarkdown(Time1);
    ui->Time2->setMarkdown(Time2);
    ui->showTime->setMarkdown(showTime);
}
void MainWindow::setTime(float time){
    QString s = QString::number(time,'f',3);
    ui->showCalTime->setMarkdown(s);
}
