#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "dialog.h"
#include<cstring>
#include<utility>
#include<map>
using namespace std;
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT
    map <QString,QString> m;

public:
    explicit login(QWidget *parent = 0);
    ~login();
    QString encrypted(QString pass);
    void search(QString name,QString pass);
    Dialog *dia;
    void opendisplay()
    {

        dia=new Dialog(this);
        dia->show();
    }
    void readfile();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_clicked();

private:
    Ui::login *ui;
};

#endif // LOGIN_H
