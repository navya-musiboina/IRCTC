#include "debit.h"
#include "ui_debit.h"
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

//this window will just ask to select the bank you want to pay from
//then it will redirect to the payment window

debit::debit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::debit)
{
    ui->setupUi(this);
    checked=false;
    this->setWindowTitle("PAYMENT");
    QPixmap pix("D:\\qt\\irctc3\\card.jpg");
    ui->label->setPixmap(pix);
    QString src,dst,date,arr_time,fare,avail,train_no,train_name,day;
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

    QString filename2="D:\\qt\\irctc3\\temp.txt";
    QFile file2(filename2);
    if(!file2.exists()){
        qDebug() << "NO exist "<<filename2;
    }else{
        qDebug() << filename2<<" exits...";
    }
    QString line2;
    if (file2.open(QIODevice::ReadOnly | QIODevice::Text)){
    QTextStream stream2(&file2);
    while (!stream2.atEnd()){
         line2 = stream2.readLine();

           day= line2.split(" ").at(0);
           date= line2.split(" ").at(1);
           src= line2.split(" ").at(2);
           dst= line2.split(" ").at(3);

        }
    }
    file2.close();


    int f=fare.toInt();
    //journey details
    ui->label_7->setText("Journey Details\nTrain no./name :"+train_no+"/"+train_name+"\tJourney Date:"+day+", "+date+"\nFrom Station: "+src+"\t\t\tTo Station:"+dst);

    //passenger details
    QString name,age,gender,adhar;
    int i=1;
    QString filename1="D:\\qt\\irctc3\\p-detail.txt";
    QFile file1(filename1);
    if(!file1.exists()){
        qDebug() << "NO exist "<<filename1;
    }else{
        qDebug() << filename1<<" exits...";
    }
    QString line1;
    if (file1.open(QIODevice::ReadOnly | QIODevice::Text)){
    QTextStream stream1(&file1);
    ui->label_8->setText(ui->label_8->text()+"\nS.No.\tName\tAge\tGender\tAadhar no.\n");
    while (!stream1.atEnd()){
         line1 = stream1.readLine();

           name= line1.split(" ").at(0);
           age= line1.split(" ").at(1);
           gender= line1.split(" ").at(2);
           adhar= line1.split(" ").at(3);

          ui->label_8->setText(ui->label_8->text()+QString :: number(i)+"\t"+name+"\t"+age+"\t"+gender+"\t"+adhar+"\n");
           i++;
        }
    }
    file1.close();
    f=(i-1)*f;
    ui->label_9->setText("Fare Details:\nTicket Fare: "+QString ::number(f)+"\nService Charge: 22.90\ntotal Fare: "+QString :: number(f+22.9) );

}

debit::~debit()
{
    delete ui;
}

void debit::on_pushButton_clicked()
{
    exit(0);
}

void debit::on_radioButton_toggled()
{
    checked=true;
}

void debit :: call()
{
    pp=new payment(this);

    pp->show();
}


void debit::on_radioButton_2_toggled()
{
    checked=true;
}

 void debit :: on_pushButton_2_clicked()
 {
     if(checked==true)
     {
         this->hide();
         call();
     }
 }

void debit::on_radioButton_3_toggled()
{
    checked=true;
}

void debit::on_radioButton_4_toggled()
{
    checked=true;
}

void debit::on_radioButton_5_toggled()
{
    checked=true;
}

void debit::on_radioButton_6_toggled()
{
    checked=true;
}

void debit::on_radioButton_7_toggled()
{
    checked=true;
}

void debit::on_radioButton_8_toggled()
{
    checked=true;
}

void debit::on_radioButton_9_toggled()
{
    checked=true;
}

void debit::on_radioButton_10_toggled()
{
    checked=true;
}

void debit::on_radioButton_11_toggled()
{
    checked=true;
}
