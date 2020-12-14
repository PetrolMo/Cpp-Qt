#ifndef SENSOR_H
#define SENSOR_H
#include <QMainWindow>
#include <tuple>
#include <QMetaType>
typedef struct{
    int x;
    int y;
    std::string s;
}Sensor ;
Q_DECLARE_METATYPE(Sensor);//要调用Q_DECLARE_METATYPE，向QT声明这个结构体----***
bool operator== (const Sensor &a, const Sensor &b);
Sensor setXY(QString s);
double distance(Sensor a, Sensor b);
int itime(Sensor a, Sensor b);
Sensor ShortestDis(Sensor ps, QList<Sensor> pl);
QList<Sensor> ShortestDisList(QList<Sensor> a);//得到最短路径的list
double TotalDis(QList<Sensor> a); //计算最短距离
Sensor ShortestTime(Sensor ps, QList<Sensor> pl);
QList<Sensor> ShortestTimeList(QList<Sensor> a); //得到最短时间list
int TotalTime(QList<Sensor> a);//计算最短时间
QString showList(QList<Sensor> s);//展示所走路径
#endif // SENSOR_H

