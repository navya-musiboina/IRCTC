#ifndef AVAILABLE_H
#define AVAILABLE_H

#include <QDialog>
#include "confirm.h"

namespace Ui {
class available;
}

class available : public QDialog
{
    Q_OBJECT

public:
    explicit available(QWidget *parent = 0);
    ~available();
    //void processText();
    confirm *con;
    void open_confirm();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

   private:
    Ui::available *ui;
};

#endif // AVAILABLE_H
