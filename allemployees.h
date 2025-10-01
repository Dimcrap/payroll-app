#ifndef ALLEMPLOYEES_H
#define ALLEMPLOYEES_H
#include <QWidget>
#include <QMainWindow>
#include <QVBoxLayout>
#include "employeeinfobox.h"


namespace Ui {
class allemployees;
}

class allemployees : public QMainWindow
{
    Q_OBJECT

public:
    explicit allemployees(QWidget *parent = nullptr);
    ~allemployees();
public slots:
void handleEmployeesLoaded(const QVector<employeeOutput> &employees,
                               const QString &error);
private:
    Ui::allemployees *ui;
    QVBoxLayout *m_layout;
    DatabaseHandler *m_dbhandler;
};

#endif // ALLEMPLOYEES_H
