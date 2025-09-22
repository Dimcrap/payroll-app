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

void DatabaseHandler::backupdb(const QString &backupFilePath){

    QSqlDatabase db= QSqlDatabase::database();

    db.transaction()

        QSqlDriver *driver=db.driver();
    if(!driver){
        qCritical<<"faild to open driver";
        db.rollback();
        return false;
    };


    Qstring connectionName ="backup_connection";

    QSqlDatabase backup=QSqlDatabase::addDatabase("QSQLITE",connectionName);
    backup.setDatabaseName(backupFilePath);

    if(!backup.open()){
        qCritical<<"backup could't be opened";
        QSqlDatabase::removeDatabase(connectionName);
        db.rollback();
        return false;
    };

    QVariant handle=db.driver()->handle();
    QVariant backupHandle =backup.driver();

    if(handle.isValid()&&backup.isValid()&&
    qstrcmp(handle.typeName(),"sqlite3*")==0&&
    qstrcmp(backupHandl.typeName(),"sqlite3*")==0){
            sqlite3 * nativehandle=*static_cast<sqlite3 **>(handle.data());
            sqlite3 *backupnativeHandle=*static_cast<sqlite3 **>(backupHandle.data());

            sqlite3_backup *sqlitebackup=sqlite3_backup_init(backupnativeHandle,"main",nativehandle,"main");
            if(sqlitebackup){
                sqlite3_backup_step(backupnativeHandle,-1);
                sqlite3_backup_finish(backupnativeHandle);
            };
            int errcode=sqlite3_errcode(backupnativeHandle);
            if(errcode!=SQLITE_OK){
                qCritical<<"SQlite backup process faild:"<<
                    sqlite3_errmsg(backupnativeHandle);
                backup.close();
                QSqlDatabase::removeDatabase(connectionName);
                db.rollback();
                return false;
            }
            backup.close();

    }else{
        qCritical<<"Could not obtain native SQLite handles for backup.";
        backup.close();
        QSqlDatabase::removeDatabase(connectionName);
        db.rollback();
        return false;
    };
    QSqlDatabase::removeDatabase(connectionName);

    db.rollback();

    qinfo<<"Database backup successful:"<<backupFilePath;
    return true;
}






bool DatabaseHandler::isOpen() const{
    return m_db.isOpen();
};

    int DatabaseHandler::adduserdata(const Userdata &userdatas){
    QSqlQuery query;
    query.prepare("INSERT INTO employee (name ...)"
                  "VALUES (:username,)");

    query.bindValue(":name",userdatas.name);
    .
    .
    .

        if(!query.exec()){
        qCritical<<"Inserting data failed:"<<query.lastError().text();
        return -1;
        }

    return query.lastInsertId().toInt();
    }

    bool addusertaxes(int user_id){
        if(user_id==-1){
            really badshit happen
        }
    };
    void DatabaseHandler::addEmployee(const QString &name);
    void DatabaseHandler::loadallEmployees();
