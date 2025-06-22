#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "ui_dialog.h"
#include<QMessageBox>
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<cstring>
#include<cstdio>
#include<string>
#include<QDate>
#include<QPalette>
#include<QPixmap>
#include<QPainter>
#include<QDesktopServices>
#include<QUrl>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("WELCOME");
    QPixmap pix("D:\\qt\\irctc3\\rail.jpg");
    ui->label_2->setPixmap(pix);
    this->setStyleSheet(" background-image: url(D:/qt/irctc3/back.jpg);");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    this->hide();
    open_login();

}

void MainWindow :: open_signup()
{
    sign=new signup(this);
    sign->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    this->hide();
    open_signup();
}

void MainWindow::on_pushButton_3_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_4_clicked()
{
    QDesktopServices::openUrl(QUrl("https://www.irctc.co.in/eticketing/loginHome.jsf",QUrl::TolerantMode));
}
