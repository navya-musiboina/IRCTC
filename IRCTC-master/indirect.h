#ifndef INDIRECT_H
#define INDIRECT_H

#include <QDialog>

namespace Ui {
class indirect;
}

class indirect : public QDialog
{
    Q_OBJECT

public:
    explicit indirect(QWidget *parent = 0);
    void show_train();
    ~indirect();

private:
    Ui::indirect *ui;
};

#endif // INDIRECT_H
