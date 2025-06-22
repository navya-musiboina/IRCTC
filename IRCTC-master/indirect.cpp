#include "indirect.h"
#include "ui_indirect.h"
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

//it will open the window for showing indirect trains

indirect::indirect(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::indirect)
{
    ui->setupUi(this);
    show_train();
    this->setWindowTitle("SORRY!!!");
}

indirect::~indirect()
{
    delete ui;
}

void indirect::show_train()
{
    QString filename="D:\\qt\\irctc3\\extra.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" exits...";
    }
    QString line;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
    QTextStream stream(&file);
    int i=0;
     ui->label->setText(ui->label->text()+"source\t\tdest\t\ttrain_no\t\ttrain_name\t\tfare\n\n");
    while (!stream.atEnd()){
         line = stream.readLine();
         QString s=line.split(" ").at(0);
         if(s.compare("12345")==0)
         {
              ui->label->setText(ui->label->text()+QString :: number(i+1)+"\n\n");
              i++;
         }
         else
         {
         ui->label->setText(ui->label->text()+line.split(" ").at(0) +"\t\t");

         ui->label->setText(ui->label->text()+line.split(" ").at(1)+ "\t\t");
         ui->label->setText(ui->label->text()+line.split(" ").at(2)+"\t\t");
         ui->label->setText(ui->label->text()+line.split(" ").at(3)+"\t\t");
         ui->label->setText(ui->label->text()+line.split(" ").at(4)+"\n\n");
         }
        }
    }
    file.close();

}
