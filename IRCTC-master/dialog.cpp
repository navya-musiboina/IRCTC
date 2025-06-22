#include "dialog.h"
#include "ui_dialog.h"
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
#include "database.h"
#include<QIODevice>
#include<QDate>
#include<QCalendarWidget>
#include<Queue>
using namespace std;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    this->setWindowTitle("WELCOME");
    flag=0;
    //the file code.txt contains all codes of cities
    //so two maps are created
    //1. map si contains city_name as key value
    //2. map is contains city_code as key value

    QString city_name,city_code;
    QString filename="D:\\qt\\irctc3\\code.txt";
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
           city_code = line.split(" ").at(0);
           city_name = line.split(" ").at(1);
           si[city_name]=city_code;
           is[city_code]=city_name;
        }
    }
    file.close();
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    QString src,dst,date1;
    QTextStream out(stdout);
     QDate date;
     int a,b,c;
    //source and destination and date of travelling are asked from user
    src=ui->lineEdit->text();
    dst=ui->lineEdit_2->text();
    date1=ui->dateEdit->text();

    //day is extracted from date selected from calender
     a= date1.split("/")[0].toInt();
     b= date1.split("/")[1].toInt();
     c= date1.split("/")[2].toInt();
    date.setDate(a,b,c);
    int day1=date.dayOfWeek();
    QString day=QDate::shortDayName(day1);
    int flag=0;

    //if fields are empty error is generated
    if(src=="" || dst =="")
    {
     QMessageBox::critical(this,tr("error"),tr("fields are empty"));
     flag=1;
    }

    //now search for the train for particular source to destination on choosen day
    if(flag==0)
    search(src,dst,day);
}

//to clear the fields
void Dialog::on_pushButton_2_clicked()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->dateEdit->clear();
}

void Dialog::on_pushButton_3_clicked()
{
    exit(0);
}

//sort the database of trains on the basis of source
void Dialog :: sort(database data[],int key)
{
    int i, j;
    database current;
    for(i = 1; i< key; i++)
    {
        current=data[i];
        for(j = i-1; j>=0; j--)
        {
            if((current.src).compare(data[j].src)<0)
            {
                data[j+1]=data[j];
            }
            else
                break;
        }
        data[j+1]=current;
    }
}

//efficiently search source and destination train in created database
int Dialog :: binary_search(database data[],QString src, QString dst,int key)
{
        int x,y;
        int mid;

        x = 0;
        y = key-1;

        while(x <= y)
        {
            mid = (x+y)/2;

            if(src.compare(data[mid].src)==0 && dst.compare(data[mid].dst)==0)
            {
                return mid;
            }
            else if(src.compare(data[mid].src)<0)
            {
                y = mid-1;
            }
            else if(src.compare(data[mid].src)>0)
            {
                x = mid +1;
            }
        }

        return -1;

}

//this function will the open the file temp.txt

void Dialog :: list_of_trains(QString src, QString dst, database data[], int key,QString day)
{
     QString date=ui->dateEdit->text();
    for(int i=0;i<key;i++)
    {
        if(data[i].src==src)
        {
            if(data[i].dst==dst)
            {
                QString filename="D:\\qt\\irctc3\\temp.txt";
                QFile file(filename);
                if(!file.exists()){
                    qDebug() << "NO exist "<<filename;
                }else{
                    qDebug() << filename<<" exits...";
                }
                QTextStream out(&file);
                file.open(QFile::ReadWrite | QFile::Append);
                out<<src<<" ";
                out<<dst<<" ";
                out<<date<<" ";
                out<<day<<" ";
                out<<data[i].train_no<<" ";
                out<<data[i].train_name<<" ";
                out<<data[i].fare<<" ";
                out<<data[i].availability<<" ";
                out<<data[i].arr_time<<"\n";

                file.close();
            }
        }
    }
}

int Dialog :: seq_search(database data[],QString src,QString dst,int key)
{
    for(int j=0;j<key;j++)
    {
        if(src==data[j].src)
        {
            if(dst==data[j].dst)
            {
                return j;
            }
        }
    }
    return -1;
}

//if indirect path is found it will store the indirect path in extra.txt

void Dialog:: print_path(vector<int> &path,int key)
{
    QString filename="D:\\qt\\irctc3\\extra.txt";
    QFile file(filename);
    if(!file.exists()){
        qDebug() << "NO exist "<<filename;
    }else{
        qDebug() << filename<<" exits...";
    }
    QTextStream out(&file);
    file.open(QFile::ReadWrite | QFile::Append);

    QString src=QString::number(path[0]);
    src=is[src];
    qDebug()<<"hello\n";
    out<<"12345\n";
    for(unsigned int i=1;i<path.size();++i)
    {
        QString dst=QString::number(path[i]);
        dst=is[dst];
        flag=1;
       //int x= binary_search(data,src,dst,key);
        int x=seq_search(data,src,dst,key);
       out<<data[x].src<<" "<<data[x].dst<<" "<<data[x].train_no<<" "<<data[x].train_name<<" "<<data[x].fare<<"\n";
       src=dst;
    }
}

bool Dialog:: isadjacency_node_not_present_in_current_path(int node,vector<int> &path)
{
    for(unsigned int i=0;i<path.size();++i)
    {
        if(path[i]==node)
        return false;
    }
    return true;
}


//this function will search for indirect trains
//and it will only run when no direct trains are found
int Dialog:: findpaths(int source ,int target ,int key )
{
    path.push_back(source);
    q=queue<vector <int> >();
    q.push(path);

    while(!q.empty())
    {
        path=q.front();
        q.pop();
        int last_nodeof_path=path[path.size()-1];
        if(last_nodeof_path==target)
        {
            print_path(path,key);
        }

        for(unsigned int i=0;i<GRAPH[last_nodeof_path].size();++i)
        {
            if(isadjacency_node_not_present_in_current_path(GRAPH[last_nodeof_path][i],path))
            {
                vector<int>new_path(path.begin(),path.end());
                new_path.push_back(GRAPH[last_nodeof_path][i]);
                q.push(new_path);
            }
        }
    }
    return 1;
}

//function to clear the queue created
void Dialog:: clear(queue<vector<int> > &q)
{
    queue<vector<int> > empty;
    std::swap(q,empty);
}

//it will search for train in particular day file
//and store the found train city_codes in graph to be used
//for finding indirect trains
void Dialog :: search(QString src,QString dst, QString day)
{
   int key= readfile(day);
   sort(data,key);

   //int x= binary_search(data,src,dst,key);
   int x= seq_search(data,src,dst,key);
   if(x==-1)
   {
       GRAPH.resize(100);
       GRAPH.clear();
       if(day=="Mon")
       {
       QString filename="D:\\qt\\irctc3\\mon.txt";
       QFile file(filename);
       if(!file.exists()){
           qDebug() << "NO exist "<<filename;
       }else{
           qDebug() << filename<<" exits...";
       }
       QString line;

       int u,v;
       if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
       QTextStream stream(&file);
       while (!stream.atEnd()){
            line = stream.readLine();

              u= line.split(" ")[0].toInt();
              v= line.split(" ")[1].toInt();
              GRAPH[u].push_back(v);
           }
       }

       file.close();
       }

       else if(day=="Tue")
       {
       QString filename="D:\\qt\\irctc3\\tue.txt";
       QFile file(filename);
       if(!file.exists()){
           qDebug() << "NO exist "<<filename;
       }else{
           qDebug() << filename<<" exits...";
       }
       QString line;

       int u,v;
       if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
       QTextStream stream(&file);
       while (!stream.atEnd()){
            line = stream.readLine();

              u= line.split(" ")[0].toInt();
              v= line.split(" ")[1].toInt();
              GRAPH[u].push_back(v);
           }
       }

       file.close();
       }

       else if(day=="Wed")
       {
       QString filename="D:\\qt\\irctc3\\wed.txt";
       QFile file(filename);
       if(!file.exists()){
           qDebug() << "NO exist "<<filename;
       }else{
           qDebug() << filename<<" exits...";
       }
       QString line;
       int u,v;
       if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
       QTextStream stream(&file);
       while (!stream.atEnd()){
            line = stream.readLine();

              u= line.split(" ")[0].toInt();
              v= line.split(" ")[1].toInt();
              GRAPH[u].push_back(v);
           }
       }

       file.close();
       }

       else if(day=="Thu")
       {
       QString filename="D:\\qt\\irctc3\\thu.txt";
       QFile file(filename);
       if(!file.exists()){
           qDebug() << "NO exist "<<filename;
       }else{
           qDebug() << filename<<" exits...";
       }
       QString line;
       int u,v;
       if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
       QTextStream stream(&file);
       while (!stream.atEnd()){
            line = stream.readLine();

              u= line.split(" ")[0].toInt();
              v= line.split(" ")[1].toInt();
              GRAPH[u].push_back(v);
           }
       }

       file.close();
       }

       else if(day=="Fri")
       {
       QString filename="D:\\qt\\irctc3\\fri.txt";
       QFile file(filename);
       if(!file.exists()){
           qDebug() << "NO exist "<<filename;
       }else{
           qDebug() << filename<<" exits...";
       }
       QString line;
       int u,v;
       if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
       QTextStream stream(&file);
       while (!stream.atEnd()){
            line = stream.readLine();

              u= line.split(" ")[0].toInt();
              v= line.split(" ")[1].toInt();
              GRAPH[u].push_back(v);
           }
       }
       file.close();
       }

       else if(day=="Sun")
       {
       QString filename="D:\\qt\\irctc3\\sun.txt";
       QFile file(filename);
       if(!file.exists()){
           qDebug() << "NO exist "<<filename;
       }else{
           qDebug() << filename<<" exits...";
       }
       QString line;
       int u,v;
       if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
       QTextStream stream(&file);
       while (!stream.atEnd()){
            line = stream.readLine();

              u= line.split(" ")[0].toInt();
              v= line.split(" ")[1].toInt();
              GRAPH[u].push_back(v);

           }
       }

       file.close();
       }

       int source,target;
       source=si[src].toInt();
       target=si[dst].toInt();
       QString filename="D:\\qt\\irctc3\\extra.txt";
       QFile file(filename);
       if(!file.exists()){
           qDebug() << "NO exist "<<filename;
       }else{
           qDebug() << filename<<" exits...";
       }
       file.open(QIODevice::ReadWrite | QIODevice:: Truncate | QIODevice :: Text);
       file.close();
       flag=0;
       path.resize(0);
       path.clear();
       clear(q);
       q=queue<vector <int> > ();
       findpaths(source,target,key);
       qDebug()<<"path size"<<path.size();
       if(flag==1)
       {
           ind=new indirect(this);
           ind->show();
       }
       else
       {
           QMessageBox::critical(this,tr("error"),tr("Train not available"));
       }

  }

   else
   {
       QString filename="D:\\qt\\irctc3\\temp.txt";
       QFile file(filename);
       if(!file.exists()){
           qDebug() << "NO exist "<<filename;
       }
       else{
           qDebug() << filename<<" exits...";
       }

       file.open(QIODevice::ReadWrite | QIODevice:: Truncate | QIODevice :: Text);
       file.close();

       list_of_trains(src,dst,data,key,day);
       this->hide();
      open_available_trains();
   }

}

 void Dialog :: open_available_trains()
 {
     av=new available(this);
     av->show();
 }

 //read the specific file and store the data in database data[] to be used for further operations

int Dialog :: readfile(QString day){
    int size;
    qDebug()<<"readfile"<<day;
    if(day=="Mon")
    {
    QString filename="D:\\qt\\irctc3\\mon.txt";
    QFile file(filename);
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

           data[i].src = line.split(" ").at(0);
           data[i].dst = line.split(" ").at(1);
           data[i].src = is[data[i].src];
           data[i].dst = is[data[i].dst];
           data[i].train_no=line.split(" ").at(2);
           data[i].train_name=line.split(" ").at(3);
           data[i].arr_time=line.split(" ").at(4);
           data[i].availability=line.split(" ").at(5);
           data[i].fare=line.split(" ").at(6);
           i++;
           size=i;
        }
    }

    file.close();
    }

    else if(day=="Tue")
    {
    QString filename="D:\\qt\\irctc3\\tue.txt";
    QFile file(filename);
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

           data[i].src = line.split(" ").at(0);
           data[i].dst = line.split(" ").at(1);
           data[i].src = is[data[i].src];
           data[i].dst = is[data[i].dst];
           data[i].train_no=line.split(" ").at(2);
           data[i].train_name=line.split(" ").at(3);
           data[i].arr_time=line.split(" ").at(4);
           data[i].availability=line.split(" ").at(5);
           data[i].fare=line.split(" ").at(6);
           i++;
           size=i;
        }
    }

    file.close();
    }

    else if(day=="Wed")
    {
    QString filename="D:\\qt\\irctc3\\wed.txt";
    QFile file(filename);
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

           data[i].src = line.split(" ").at(0);
           data[i].dst = line.split(" ").at(1);
           data[i].src = is[data[i].src];
           data[i].dst = is[data[i].dst];
           data[i].train_no=line.split(" ").at(2);
           data[i].train_name=line.split(" ").at(3);
           data[i].arr_time=line.split(" ").at(4);
           data[i].availability=line.split(" ").at(5);
           data[i].fare=line.split(" ").at(6);
           i++;
           size=i;
        }
    }

    file.close();
    }

   else if(day=="Thu")
    {
    QString filename="D:\\qt\\irctc3\\thu.txt";
    QFile file(filename);
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

           data[i].src = line.split(" ").at(0);
           data[i].dst = line.split(" ").at(1);
           data[i].src = is[data[i].src];
           data[i].dst = is[data[i].dst];
           data[i].train_no=line.split(" ").at(2);
           data[i].train_name=line.split(" ").at(3);
           data[i].arr_time=line.split(" ").at(4);
           data[i].availability=line.split(" ").at(5);
           data[i].fare=line.split(" ").at(6);
           i++;
           size=i;
        }
    }

    file.close();
    }


   else if(day=="Fri")
    {
    QString filename="D:\\qt\\irctc3\\fri.txt";
    QFile file(filename);
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

           data[i].src = line.split(" ").at(0);
           data[i].dst = line.split(" ").at(1);
           data[i].src = is[data[i].src];
           data[i].dst = is[data[i].dst];
           data[i].train_no=line.split(" ").at(2);
           data[i].train_name=line.split(" ").at(3);
           data[i].arr_time=line.split(" ").at(4);
           data[i].availability=line.split(" ").at(5);
           data[i].fare=line.split(" ").at(6);
           i++;
           size=i;
        }
    }
    file.close();
    }

   else if(day=="Sat")
    {
    QString filename="D:\\qt\\irctc3\\sat.txt";
    QFile file(filename);
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

           data[i].src = line.split(" ").at(0);
           data[i].dst = line.split(" ").at(1);
           data[i].src = is[data[i].src];
           data[i].dst = is[data[i].dst];
           data[i].train_no=line.split(" ").at(2);
           data[i].train_name=line.split(" ").at(3);
           data[i].arr_time=line.split(" ").at(4);
           data[i].availability=line.split(" ").at(5);
           data[i].fare=line.split(" ").at(6);
           i++;
           size=i;
        }
    }

    file.close();
    }

    else if(day=="Sun")
    {
    QString filename="D:\\qt\\irctc3\\sun.txt";
    QFile file(filename);
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

           data[i].src = line.split(" ").at(0);
           data[i].dst = line.split(" ").at(1);
           data[i].src = is[data[i].src];
           data[i].dst = is[data[i].dst];
           data[i].train_no=line.split(" ").at(2);
           data[i].train_name=line.split(" ").at(3);
           data[i].arr_time=line.split(" ").at(4);
           data[i].availability=line.split(" ").at(5);
           data[i].fare=line.split(" ").at(6);
           i++;
           size=i;
        }
    }
    file.close();
    }
    else
    {
        qDebug()<<"wrong day entered";
    }
    return size;
}
