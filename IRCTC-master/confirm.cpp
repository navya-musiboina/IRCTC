#include "confirm.h"
#include "ui_confirm.h"
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

confirm::confirm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::confirm)
{
    ui->setupUi(this);
    this->setWindowTitle("CONFIRMATION");

    //get the details of choosen src , dst, and date from file temp.txt

    QString src,dst,date,arr_time,fare,avail,train_no,train_name,day;
    QString filename1="D:\\qt\\irctc3\\temp.txt";
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

           day= line1.split(" ").at(0);
           date= line1.split(" ").at(1);
           src= line1.split(" ").at(2);
           dst= line1.split(" ").at(3);
        }
    }
    file1.close();

//get the details of selected train from file select.txt

    QString filename="D:\\qt\\irctc3\\select.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" exits...";
    }
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
    QTextStream stream(&file);
    while (!stream.atEnd()){
         line = stream.readLine();

           train_no= line.split(" ").at(0);
           train_name= line.split(" ").at(1);
           arr_time= line.split(" ").at(2);
           avail= line.split(" ").at(3);
           fare= line.split(" ").at(4);
        }
    }
    file.close();
//print the details on upper part of window

    ui->label->setText("Day of Travelling:"+day+", "+date+"\nsource: "+src+"\ndestination:"+dst+"\nTrain no. and name :"+train_no+", "+train_name+"\nArrival time: "+arr_time);
}

confirm::~confirm()
{
    delete ui;
}

void confirm :: payment_debit()
{
    deb=new debit(this);
    deb->show();
}

void confirm::on_pushButton_clicked()
{
    exit(0);
}

void confirm::on_pushButton_2_clicked()
{
    //write details from table to file
    //ask user to enter details of passenger

    QString name,age,adhar,gender;
    int i=0;
    QString filename="D:\\qt\\irctc3\\p-detail.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" exits...";
    }
    QTextStream out(&file);
    file.open((QIODevice::WriteOnly | QIODevice::Text));
    QTableWidgetItem* itm,*itm3,*itm4,*itm5;
     itm = ui->tableWidget->item( 0, 0 );
      itm3 = ui->tableWidget->item( 0, 1 );
     itm4 = ui->tableWidget->item( 0, 2 );
     qDebug()<<"items:: "<<itm->text()<<" "<<itm3->text()<<" "<<itm4->text();
    while (itm && itm3 && itm4)
    {

      name=itm->text();
      out<<name<<" ";

      age=itm3->text();
      out<<age<<" ";

      gender=itm4->text();
      out<<gender<<" ";
      qDebug()<<"items:: "<<name<<" "<<age<<" "<<gender;

      itm5 = ui->tableWidget->item( i, 3 );
      if(itm5){
        adhar=itm5->text();
        out<<adhar<<"\n";
      }

      //hello

       itm = ui->tableWidget->item( i+1, 0 );
       itm3 = ui->tableWidget->item( i+1, 1 );
       itm4 = ui->tableWidget->item( i+1, 2 );
       i++;
    }
     file.close();
     itm = ui->tableWidget->item( i-1, 0 );
     itm3 = ui->tableWidget->item( i-1, 1 );
     itm4 = ui->tableWidget->item( i-1, 2 );
     /*
    if(!itm || !itm3 || !itm4)
    {
        QMessageBox::critical(this,tr("error"),tr("fields are empty"));
    }


    else
    {
        this->hide();
        payment_debit();
    }
    */
     this->hide();
     payment_debit();
}
