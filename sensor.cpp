#include "sensor.h"
#include<math.h>
#include "QDebug"
using namespace std;
Sensor setXY(QString s){
    Sensor sensor;
    sensor.s = s.toStdString();
    string str = s.toStdString();
    switch (str[0]) {
    case 'A':
        sensor.y = 0;
        break;
    case 'B':
        sensor.y = 1;
        break;
    case 'C':
        sensor.y = 2;
        break;
    case 'D':
        sensor.y = 3;
        break;
    case 'E':
        sensor.y = 4;
        break;
    case 'F':
        sensor.y = 5;
        break;
    case 'G':
        sensor.y = 6;
        break;
    case 'H':
        sensor.y = 7;
        break;
    }
    s = s.remove(0,1);
    string str2 = s.toStdString();
    sensor.x = atoi(str2.c_str());
    return sensor;
}
bool operator== (const Sensor &a, const Sensor &b){
    return
       std::forward_as_tuple(a.x,
                             a.y,
                             a.s)
            ==
       std::forward_as_tuple(b.x,
                             b.y,
                             a.s);
}

double distance(Sensor a, Sensor b) //计算两传感器的距离
{
    int ix, iy;
    double ans;
    ix = fabs(a.x - b.x);
    iy = fabs(a.y - b.y);
    if (ix < iy)
        ans = (sqrt(2 * ix * ix) + iy - ix);
    else
        ans = (sqrt(2 * iy * iy) + ix - iy);
    ans = 100 * ans;
    return ans;
}
int itime(Sensor a, Sensor b)//计算两传感器的传递时间
{
    int ans;
    int jx, jy;
    jx = fabs(a.x - b.x);
    jy = fabs(a.y - b.y);
    if (jx < jy)
        ans = jy;
    else
        ans = jx;
    ans = ans * 100;
    return ans;
}

Sensor ShortestDis(Sensor ps, QList<Sensor> pl) //从未遍历的list中找到距离当前节点的最近节点
{
    Sensor ans1;
    if(pl.size() == 1){
        ans1 = pl[0];
    }else{
        double k = 0;
        double dis = distance(ps,pl[0]);
        int len = pl.size();
        for (int i = 0; i < len ; i++)
        {
            k = distance(ps,pl[i]);
            if(k <= dis){
                dis = k;
                ans1 = pl[i];
            }
        }
    }

    return ans1;

}
Sensor ShortestTime(Sensor ps, QList<Sensor> pl) //从未遍历的list中找到某一节点使之传递到当前节点时间最短
{
    Sensor ans2;
    if(pl.size() == 1){
        ans2 = pl[0];
    }
    else{
        int k = 0;
        int stime = itime(ps,pl[0]);
        int len = pl.size();
        for (int i = 0; i < len; i++)
        {
            k = itime(ps,pl[i]);
            if(k <= stime)
            {
                stime = k;
                ans2 = pl[i];
            }
        }
    }

    return ans2;
}

QList<Sensor> ShortestDisList(QList<Sensor> a)//得到最短路径的list
{
    QList<Sensor> ans3;
    Sensor cu = a[0];
    ans3.append(cu);
    a.removeOne(cu);
    int len = a.size();
    for(int i = 0 ; i < len;i++){
        cu = ShortestDis(cu,a);
        ans3.append(cu);
        a.removeOne(cu);
    }
    return ans3;
}
QList<Sensor> ShortestTimeList(QList<Sensor> a) //得到最短时间list
{
    QList<Sensor> ans4;
    Sensor cur = a[0];
    ans4.append(cur);
    a.removeOne(cur);
    int len = a.size();
    for(int i = 0; i < len;i++){
        cur = ShortestTime(cur,a);
        ans4.append(cur);
        a.removeOne(cur);
    }
    return ans4;
}

double TotalDis(QList<Sensor> a)//计算最短距离
{
    double ans5 = 0;
    for (int i = 0; i < a.size()-1; i++)
    {
        ans5 = ans5 + distance(a[i],a[i+1]);
    }
    return ans5;
}
int TotalTime(QList<Sensor> a)//计算最短时间
{
    int ans6 = 0;
    for (int i = 0; i < a.size() - 1; i++)
    {
        ans6 = ans6 + itime(a[i],a[i+1]);
    }
    return ans6;
}

QString showList(QList<Sensor> s)    //展示所走路径
{
    QString ans7;
    int len = s.size();
    for(int i = 0 ; i < len; i++){
        if(i == 0){
            ans7 = QString::fromStdString(s[i].s);
        }
        else {
            ans7 = ans7 + "->" +QString::fromStdString(s[i].s);
        }
    }
    return ans7;
}
