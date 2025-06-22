#ifndef SIGNUP_H
#define SIGNUP_H
#include "map"

#include <QDialog>
#include "login.h"
namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = 0);
    ~signup();
    login *log;
    void open_login();
    QString encrypted(QString pass);
    map<QString,QString> user;
private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_pushButton_clicked();

private:
    Ui::signup *ui;
    Dialog *di;
};

#endif // SIGNUP_H
