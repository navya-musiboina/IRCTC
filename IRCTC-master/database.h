#ifndef DATABASE_H
#define DATABASE_H
#include<qmainwindow.h>
#include<iostream>
#include<cstring>
#include<string.h>
#include<cstdio>
class database
{
public:
    database();
    QString src;
    QString dst;
    QString train_no;
    QString arr_time;
    QString train_name;
    QString fare;
    QString availability;
};

#endif // DATABASE_H
