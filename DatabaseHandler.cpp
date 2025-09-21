#include "DatabaseHandler.h"
#include <QDebug>

DatabaseHandler::DatabaseHandler(const QString &pathtodb,QObject *parent=nullptr):QObject(parent){

    m_db=QSqlDatabase::addDatabase("QSQLITE");
    m_db=setDatabaseName("data/payroll.db");

    if(!m_db.open()){
        QString error=m_db.lastError().text();
        //qCritical()<<"Failed to open databas:"<<error;
        emit databaseError(error);
    };/*else{
        qDebug("db opened successfully")
    };*/

}


bool DatabaseHandler::isOpen() const{
    return m_db.isOpen();
};

    void DatabaseHandler::addEmployee(const QString &name);
    void DatabaseHandler::loadallEmployees();
