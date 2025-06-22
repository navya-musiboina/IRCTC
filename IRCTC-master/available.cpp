#include "available.h"
#include "ui_available.h"
#include "dialog.h"
#include<QFile>
#include<QMessageBox>
#include<QDebug>
#include<QIODevice>

available::available(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::available)
{
    ui->setupUi(this);
    this->setWindowTitle("AVAILABILITY");

    QString date,day,src,dst;
     QString train_no,train_name,arr_time,avail,fare;
    QString filename="D:\\qt\\irctc3\\temp.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" exits...";
    }
    QString line;
    if (file.open(QFile::ReadWrite)){
    QTextStream stream(&file);
    int i=0;
    while (!stream.atEnd()){
         line = stream.readLine();
           src = line.split(" ").at(0);
           dst = line.split(" ").at(1);
           date=line.split(" ").at(2);
           day=line.split(" ").at(3);
           train_no=line.split(" ").at(4);
           train_name=line.split(" ").at(5);
           fare=line.split(" ").at(6);
           avail=line.split(" ").at(7);
           arr_time=line.split(" ").at(8);



           QTableWidgetItem *item0=new QTableWidgetItem(QString :: number(i+1));
          ui->tableWidget->setItem(i,0,item0);
           QTableWidgetItem *item=new QTableWidgetItem(train_no);
           ui->tableWidget->setItem(i,1,item);
            QTableWidgetItem *item2=new QTableWidgetItem(train_name);
           ui->tableWidget->setItem(i,2,item2);
           QTableWidgetItem *item3=new QTableWidgetItem(arr_time);
          ui->tableWidget->setItem(i,3,item3);
          QTableWidgetItem *item4=new QTableWidgetItem(avail);
         ui->tableWidget->setItem(i,4,item4);
         QTableWidgetItem *item5=new QTableWidgetItem(fare);
        ui->tableWidget->setItem(i,5,item5);
           i++;

        }
    }
    file.close();
}

available::~available()
{
    delete ui;
}

void available::on_pushButton_clicked()
{
   exit(0);
}

void available :: open_confirm()
{
    con=new confirm(this);
    con->show();
}

void available::on_pushButton_2_clicked()
{
    int flag=0;
    int sr=ui->lineEdit->text().toInt();
    QString str,train_no,train_name,arr_time,fare,avail;
    QTableWidgetItem* itm = ui->tableWidget->item( sr-1, 0 );
    if (itm)
    {
     str = itm->text();
      QTableWidgetItem* itm2 = ui->tableWidget->item( sr-1, 1 );
      train_no=itm2->text();
      QTableWidgetItem* itm3 = ui->tableWidget->item( sr-1, 2 );
      train_name=itm3->text();
      QTableWidgetItem* itm4 = ui->tableWidget->item( sr-1, 3 );
      arr_time=itm4->text();
      QTableWidgetItem* itm5 = ui->tableWidget->item( sr-1, 4 );
      avail=itm5->text();
      QTableWidgetItem* itm6 = ui->tableWidget->item( sr-1, 5 );
      fare=itm6->text();
    }
    else
    {
        QMessageBox::critical(this,tr("error"),tr("Invalid choice!"));
        flag=1;
    }
    qDebug()<<str;

    QString filename="D:\\qt\\irctc3\\select.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" exits...";
    }
    QTextStream out(&file);
    file.open((QIODevice::WriteOnly | QIODevice::Text));
    out<<train_no<<" ";
    out<<train_name<<" ";
    out<<arr_time<<" ";
    out<<avail<<" ";
    out<<fare<<" ";
    file.close();
    if(flag==0)
    {
         this->hide();
         open_confirm();
    }
}
