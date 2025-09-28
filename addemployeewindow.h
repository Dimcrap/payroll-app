#ifndef ADDEMPLOYEEWINDOW_H
#define ADDEMPLOYEEWINDOW_H

#include <QWidget>
#include <QMainWindow>

namespace Ui {
class addemployeewindow;
}

class addemployeewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit addemployeewindow(QWidget *parent = nullptr);
    ~addemployeewindow();

signals:
    void backToMain();


private:
    Ui::addemployeewindow *ui;

private slots:
    void onBackButtonClicked();
};

#endif // ADDEMPLOYEEWINDOW_H
