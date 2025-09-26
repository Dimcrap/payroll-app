#ifndef ADDEMPLOYEEWINDOW_H
#define ADDEMPLOYEEWINDOW_H

#include <QWidget>

namespace Ui {
class addemployeewindow;
}

class addemployeewindow : public QWidget
{
    Q_OBJECT

public:
    explicit addemployeewindow(QWidget *parent = nullptr);
    ~addemployeewindow();

private:
    Ui::addemployeewindow *ui;
};

#endif // ADDEMPLOYEEWINDOW_H
