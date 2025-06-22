#ifndef DEBIT_H
#define DEBIT_H

#include <QDialog>
#include "payment.h"

namespace Ui {
class debit;
}

class debit : public QDialog
{
    Q_OBJECT

public:
    explicit debit(QWidget *parent = 0);
    ~debit();
    payment *pp;
    void  call();

private slots:
    void on_pushButton_clicked();

    void on_radioButton_toggled();

    void on_pushButton_2_clicked();



    void on_radioButton_2_toggled();

    void on_radioButton_3_toggled();

    void on_radioButton_4_toggled();

    void on_radioButton_5_toggled();

    void on_radioButton_6_toggled();

    void on_radioButton_7_toggled();

    void on_radioButton_8_toggled();

    void on_radioButton_9_toggled();

    void on_radioButton_10_toggled();

    void on_radioButton_11_toggled();

private:
    bool checked;
    Ui::debit *ui;
};

#endif // DEBIT_H
