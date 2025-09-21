#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
class DatabaseHandler:public QObject{

    Q_OBJECT
public:
    explicit DatabaseHandler(const QString &pathtodb,QObject *parent=nullptr);

    bool isOpen() const;

    public slots:
    void addEmployee(const QString &name);
    void loadallEmployees();

    signals:
    void employeeAdded(bool success,const QString &error="");
    void allemployeesloaded(const QList<QString> &employeelist,const QString &error="");
    void databaseError(const QString &errmsg);
private:

    QSqlDatabase m_db;
};

#endif // DATABASEHANDLER_H
