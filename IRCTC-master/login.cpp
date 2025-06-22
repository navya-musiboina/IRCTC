#include "login.h"
#include "ui_login.h"
#include "dialog.h"
#include "ui_dialog.h"
#include<QMessageBox>
#include<QDebug>
#include<QFile>
#include<QTextStream>
#include<cstring>
#include<cstdio>
#include<string>
using namespace std;

login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    this->setWindowTitle("LOGIN");
    QPixmap pix("D:\\qt\\irctc3\\logo.jpg");
    ui->label_3->setPixmap(pix);
}

login::~login()
{
    delete ui;
}

void login::on_buttonBox_accepted()
{
    QString name,pass;
    name=ui->lineEdit->text();
    pass=ui->lineEdit_2->text();
    search(name,pass);
}

void login::on_buttonBox_rejected()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
}

void login::on_pushButton_clicked()
{
    exit(0);
}

QString login:: encrypted(QString pass)
{
    int n=pass.length();
    int i;
    std::string s=pass.toUtf8().constData();
    for(i=0;i<n;i++)
    {
        if(s[i]=='y')
            s[i]='a';
        if(s[i]=='Y')
            s[i]='A';
        if(s[i]=='z')
            s[i]='b';
        if(s[i]=='Z')
            s[i]='B';
        else
        s[i]=s[i]+2;
    }
    pass=QString ::fromStdString(s);
    return pass;
}

void login :: search(QString name,QString pass)
{
   readfile();
   int x=0;
   if(m.count(name))
   {
       qDebug()<<pass;
       pass=encrypted(pass);
       qDebug()<<pass;
       if(pass.compare(m[name])==0)
            x=1;
       else
           x=-1;

    }
        else
        {
            QMessageBox::critical(this,tr("error"),tr("Invalid username or password"));
        }

        if(x==-1)
        {
              QMessageBox::critical(this,tr("error"),tr("Invalid username or password"));
        }

        else if(x==1)
        {
              this->hide();
              opendisplay();
        }
}

void login :: readfile(){
    QString filename="D:\\qt\\irctc3\\user.txt";
    QFile file(filename);
    QString name,pass;
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" exits...";
    }
    QString line;
    int i=0;
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
    QTextStream stream(&file);
    while (!stream.atEnd()){
            line = stream.readLine();
            name=line.split(" ").at(0);
            pass=line.split(" ").at(1);
            m[name]=pass;
            i++;
        }
    }

    file.close();
}
