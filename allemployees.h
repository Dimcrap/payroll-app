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
    employeeOutput emptyInfobox();
    ~allemployees();
    void refreshEmployees();

public slots:
    void handleEmployeesLoaded(const QVector<employeeOutput> &employees,
                               const QString &error);
    void handleEmployeeDelete(QString empID);
private:
    Ui::allemployees *ui;
    QVBoxLayout *m_layout;
    std::shared_ptr <DatabaseHandler> m_dbhandler;
    void showEvent(QShowEvent *event)override;
    employeeinfobox * m_infobox;
};

#endif // ALLEMPLOYEES_H
