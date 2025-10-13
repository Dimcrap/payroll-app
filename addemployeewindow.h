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
    void setDataBaseHandler(std::shared_ptr<DatabaseHandler> handler);
    Userdata Userinputs();
    void inputError(QString errormsg);
    void showEvent(QShowEvent *event) override;
private:

    Ui::addemployeewindow *ui;
    QList<QRadioButton*> genders,maritalsradios
        ,positions,salaryTypes;
    std::shared_ptr <DatabaseHandler> m_dbhandler;
    void cleanInputs();


signals:
    void backToMain();

private slots:
    void onBackButtonClicked();
    void onEraseButtonClicked();
    void onAddButtonClicked();

};

#endif // ADDEMPLOYEEWINDOW_H
