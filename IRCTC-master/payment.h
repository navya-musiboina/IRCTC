#ifndef PAYMENT_H
#define PAYMENT_H
#include "details.h"

#include <QDialog>

namespace Ui {
class payment;
}

class payment : public QDialog
{
    Q_OBJECT

public:
    explicit payment(QWidget *parent = 0);
    ~payment();
    details *dl;
    void print_ticket();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::payment *ui;
};

#endif // PAYMENT_H
