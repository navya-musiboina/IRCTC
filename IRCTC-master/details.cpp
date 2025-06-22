#include "details.h"
#include "ui_details.h"
#include<iostream>
#include<cstdio>
#include<cstring>
#include<fstream>
#include<QFile>
#include<QTextStream>
#include<QDebug>
#include<QDate>
#include<QDateTimeEdit>
#include<QMessageBox>
#include<QIODevice>

//it will print the details of confimed ticket

details::details(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::details)
{
    ui->setupUi(this);
    this->setWindowTitle("TICKET CONFIRMED!!!");
    QString filename="D:\\qt\\irctc3\\p-detail.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" exits...";
    }
    QString line;
    QString name,age,gender;
    int i=0;
    ui->label->setText(ui->label->text()+"\nS.No.\tName\tAge\tGender\n");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
    QTextStream stream(&file);
    while (!stream.atEnd()){
         line = stream.readLine();

           name = line.split(" ").at(0);
           age = line.split(" ").at(1);
           gender=line.split(" ").at(2);
            i++;
            ui->label->setText(ui->label->text()+"\n"+QString::number(i)+"\t"+name+"\t"+age+"\t"+gender);
        }
    }

    file.close();

    QString src,dst,date,arr_time,fare,avail,train_no,train_name,day;
   QString filename1="D:\\qt\\irctc3\\select.txt";
   QFile file1(filename1);
   if(!file1.exists()){
       qDebug() << "NO exist "<<filename1;
   }else{
       qDebug() << filename1<<" exits...";
   }
   QString line1;
   if (file1.open(QIODevice::ReadOnly | QIODevice::Text)){
   QTextStream stream1(&file1);
   while (!stream1.atEnd()){
        line1 = stream1.readLine();

          train_no= line1.split(" ").at(0);
          train_name= line1.split(" ").at(1);
          arr_time= line1.split(" ").at(2);
          avail= line1.split(" ").at(3);
          fare= line1.split(" ").at(4);
       }
   }
   file1.close();

   int f=fare.toInt();
   f=(i)*f;
   ui->label->setText(ui->label->text()+"\n\nFare Details:\nTicket Fare: "+QString ::number(f)+"\nService Charge: 22.90\ntotal Fare: "+QString :: number(f+22.9) );
}

details::~details()
{
    delete ui;
}

void details::on_pushButton_clicked()
{
    exit(0);
}
