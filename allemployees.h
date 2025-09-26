#ifndef ALLEMPLOYEES_H
#define ALLEMPLOYEES_H
#include <QWidget>

#include <QWidget>

namespace Ui {
class allemployees;
}

class allemployees : public QWidget
{
    Q_OBJECT

public:
    explicit allemployees(QWidget *parent = nullptr);
    ~allemployees();

private:
    Ui::allemployees *ui;
};

#endif // ALLEMPLOYEES_H
