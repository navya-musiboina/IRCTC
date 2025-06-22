#ifndef CONFIRM_H
#define CONFIRM_H

#include <QDialog>
#include "debit.h"
namespace Ui {
class confirm;
}

class confirm : public QDialog
{
    Q_OBJECT

public:
    explicit confirm(QWidget *parent = 0);
    ~confirm();
    debit *deb;
    void payment_debit();
private slots:
  //  void on_radioButton_clicked();

    void on_pushButton_clicked();

    //void on_radioButton_2_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::confirm *ui;
};

#endif // CONFIRM_H
