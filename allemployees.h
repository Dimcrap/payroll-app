#ifndef ALLEMPLOYEES_H
#define ALLEMPLOYEES_H
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include "employeeinfobox.h"
#include "DatabaseHandler.h"
#include <memory>

namespace Ui {
class allemployees;
}

class allemployees : public QMainWindow
{
    Q_OBJECT

public:
    explicit allemployees(QWidget *parent = nullptr);
    void setDatabseHandler(std::shared_ptr <DatabaseHandler> handler);
    ~allemployees();
    void refreshEmployees();
public slots:
    void handleEmployeesLoaded(const QVector<employeeOutput> &employees,
                               const QString &error);
    //void handleEmployeeDelete();
private:
    Ui::allemployees *ui;
    QVBoxLayout *m_layout;
    std::shared_ptr <DatabaseHandler> m_dbhandler;
    void showEvent(QShowEvent *event)override;

};

#endif // ALLEMPLOYEES_H
