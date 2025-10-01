#ifndef ADDEMPLOYEEWINDOW_H
#define ADDEMPLOYEEWINDOW_H

#include <QWidget>
#include <QMainWindow>
#include "DatabaseHandler.h"
#include <QList>
#include <QRadioButton>
#include <memory>

namespace Ui {
class addemployeewindow;
}

class addemployeewindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit addemployeewindow(QWidget *parent = nullptr);
    ~addemployeewindow();
    Userdata Userinputs();
    taxdetails Usertaxinput(int userid);

private:
    Ui::addemployeewindow *ui;
    QList<QRadioButton*> genders,marital
        ,positions,salaryTypes;
    std::unique_ptr <DatabaseHandler> m_dbhandler;

signals:
    void backToMain();


private slots:
    void onBackButtonClicked();
    void onEraseButtonClicked();

    void ;
};

#endif // ADDEMPLOYEEWINDOW_H
