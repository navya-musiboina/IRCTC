#ifndef DIALOG_H
#define DIALOG_H
#include<QMainWindow>
#include <fstream>
#include <QDialog>
#include "database.h"
#include<iostream>
#include<stdio.h>
#include "available.h"
#include<QTextEdit>
#include<QPushButton>
#include<QVBoxLayout>
#include<map>
#include<vector>
#include<utility>
#include<Queue>
using namespace std;
namespace Ui {
class Dialog;
}

#include "indirect.h"
class Dialog : public QDialog
{
    Q_OBJECT
    database data[1000];
    map<QString,QString> si;
    map<QString ,QString > is;
    vector<vector<int> >GRAPH;
    vector<int>path;
    queue<vector<int> >q;

public:
    void clear(queue<vector<int> > &q);
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    indirect *ind;
    int flag;
    void sort(database data[],int key);
    int  binary_search(database data[],QString user, QString pass,int key);
    void search(QString src,QString dst, QString day);
    int  readfile(QString day);
    available *av;
    void open_available_trains();
    int findpaths(int source ,int target,int key );
    void  list_of_trains(QString src, QString dst, database data[], int key,QString day);
    bool  isadjacency_node_not_present_in_current_path(int node,vector<int> &path);
    void print_path(vector<int> &path,int key);
    int seq_search(database data[],QString src,QString dst,int key);

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();




private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
