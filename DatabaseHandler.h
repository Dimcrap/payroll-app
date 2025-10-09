#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVector>
#include <QFile>
#include <QDir>
#include "userdata.h"


class DatabaseHandler:public QObject{

    Q_OBJECT
public:
    explicit DatabaseHandler(const QString &pathtodb,QObject *parent=nullptr);
    ~DatabaseHandler() ;
    bool isOpen() const;
    DatabaseHandler(const DatabaseHandler&) = delete;
    DatabaseHandler& operator=(const DatabaseHandler&) = delete;

    public slots:
    void loadallEmployees();
    void backupdb(const QString &backupFilePath);
    int adduserdata(const Userdata &userdatas);
    bool addusertaxes(taxdetails & usertax);

    signals:
    void allemployeesloaded(const QVector<employeeOutput> &employees,const QString &error="");
private:

    QSqlDatabase m_db;

};


struct Userdata;

#endif // DATABASEHANDLER_H
