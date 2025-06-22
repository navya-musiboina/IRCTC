#include "payment.h"
#include "ui_payment.h"
#include<QMessageBox>
#include<QDebug>

payment::payment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::payment)
{
    ui->setupUi(this);
    this->setWindowTitle("PAYMENT");
    //QPixmap pix("D:\\qt\\irctc3\\payment.jpg");
    //ui->label_2->setPixmap(pix);
}

payment::~payment()
{
    delete ui;
}

void payment::on_pushButton_2_clicked()
{
    exit(0);
}

void payment :: print_ticket()
{
    dl=new details(this);
    dl->show();
}


void payment::on_pushButton_clicked()
{
    //confirm the ticket
    //print ticket details
    qDebug()<<ui->lineEdit->text().toInt()<< ui->lineEdit_2->text().toInt() << ui->lineEdit_3->text().toInt();
    qDebug()<<(ui->lineEdit->text().toInt() && ui->lineEdit_2->text().toInt() && ui->lineEdit_3->text().toInt());

    if(ui->lineEdit->text().toInt()>=1000 && ui->lineEdit_2->text().toInt()>=10000000 && ui->lineEdit_3->text().toInt()>=100)
    {
        print_ticket();
        this->hide();
    }
    else
    {
        QMessageBox::critical(this,tr("error"),tr("fields are empty or Incorrect details"));

    }
}
