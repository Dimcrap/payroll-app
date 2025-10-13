#include "DatabaseHandler.h"
#include "userdata.h"
#include <QDebug>
#include <QSqlDriver>
#include <sqlite3.h>
#include <QCoreApplication>
#include <QFileInfo>
#include <QSettings>


DatabaseHandler::DatabaseHandler(const QString &pathtodb,QObject *parent):
    QObject(parent){


    qDebug()<<"available drivers:"<<QSqlDatabase::drivers();
    qDebug()<<"Database path:"<<pathtodb;

    QFileInfo dbFile(pathtodb);
    if (!dbFile.exists()) {
        qCritical() << "Database file does not exist:" << pathtodb;
        return;
    }

    if (!dbFile.isReadable()) {
        qCritical() << "Database file is not readable:" << pathtodb;
        return;
    }

    //qDebug() << "Database file exists, size:" << dbFile.size() << "bytes";

    QStringList connections = QSqlDatabase::connectionNames();

    for (const QString &connectionName : connections) {

        QSqlDatabase existingDb = QSqlDatabase::database(connectionName, false);
        if (existingDb.isValid() && existingDb.databaseName() == pathtodb) {
            qDebug() << "Found existing connection to same database:" << connectionName;

            if (existingDb.isOpen()) {

                QSqlQuery cleanupQuery(existingDb);
                cleanupQuery.finish();

                existingDb.close();
                qDebug() << "Closed existing connection:" << connectionName;
            }


            QSqlDatabase::removeDatabase(connectionName);
            qDebug() << "Removed existing connection:" << connectionName;
        }
    }


    QString uniqueName=QString("connection_%1").arg(quintptr(this));
    m_db=QSqlDatabase::addDatabase("QSQLITE",uniqueName);
    m_db.setDatabaseName(pathtodb);

    if(!m_db.open()){
        QString error=m_db.lastError().text();
        qCritical()<<"Failed to open databas:"<<error;

    }else{
        qDebug()<<"db opened successfully";

    }


    qDebug() << "=== DATABASE PATH DEBUG ===";

    // Get absolute path
    QFileInfo fileInfo(pathtodb);
    QString absolutePath = fileInfo.absoluteFilePath();
    qDebug() << "Requested path:" << pathtodb;
    qDebug() << "Absolute path:" << absolutePath;
    qDebug() << "File exists:" << QFile::exists(absolutePath);
    qDebug() << "File is writable:" << QFileInfo(absolutePath).isWritable();
    qDebug() << "Current directory:" << QDir::currentPath();


    QSqlQuery fileQuery(m_db);
    if(fileQuery.exec("PRAGMA database_list;")) {
        while(fileQuery.next()) {
            qDebug() << "Database file:" << fileQuery.value(2).toString();
        }
    }

    // Enable foreign keys
    QSqlQuery fkQuery(m_db);
    if(fkQuery.exec("PRAGMA foreign_keys = ON;")) {
        qDebug() << "Foreign keys enabled";
    } else {
        qCritical() << "Failed to enable foreign keys:" << fkQuery.lastError();
    }

    qDebug() << "=================================";

}

DatabaseHandler::~DatabaseHandler() {
    if (m_db.isOpen()) {
        m_db.close();
        qDebug() << "Database connection closed:" << m_db.connectionName();
    }
}
void DatabaseHandler::backupdb(const QString &backupFilePath){

    QSqlDatabase db= QSqlDatabase::database();
    db.transaction();

        QSqlDriver *driver =db.driver();
    if(!driver){
        qCritical()<<"faild to open driver";
        db.rollback();
        return;
    };


    QString connectionName ="backup_connection_"+QString::number(QDateTime::currentSecsSinceEpoch());

    QSqlDatabase backup=QSqlDatabase::addDatabase("QSQLITE",connectionName);
    backup.setDatabaseName(backupFilePath);

    if(!backup.open()){
        qCritical()<<"backup could't be opened";
        QSqlDatabase::removeDatabase(connectionName);
        db.rollback();
        return;
    };

    QVariant handle=db.driver()->handle();
    QVariant backupHandle =backup.driver()->handle();

    if(handle.isValid()&&backup.isValid()&&
    qstrcmp(handle.typeName(),"sqlite3*")==0&&
    qstrcmp(backupHandle.typeName(),"sqlite3*")==0){
            sqlite3 * nativehandle=*static_cast<sqlite3 **>(handle.data());
            sqlite3 *backupnativeHandle=*static_cast<sqlite3 **>(backupHandle.data());

            sqlite3_backup *sqlitebackup=sqlite3_backup_init(backupnativeHandle,"main",nativehandle,"main");
            if(sqlitebackup){
                int rc;
                do {
                    rc=sqlite3_backup_step(sqlitebackup,100);
                    if(rc==SQLITE_OK||rc==SQLITE_BUSY||rc==SQLITE_LOCKED){
                        sqlite3_sleep(250);
                    }
                }while(rc==SQLITE_OK||rc==SQLITE_BUSY||rc==SQLITE_LOCKED);

                sqlite3_backup_finish(sqlitebackup);
            };
            int errcode=sqlite3_errcode(backupnativeHandle);
            if(errcode!=SQLITE_OK){
                qCritical()<<"SQlite backup process faild:"<<
                    sqlite3_errmsg(backupnativeHandle);
                backup.close();
                QSqlDatabase::removeDatabase(connectionName);
                db.rollback();
                return;
            }
            backup.close();

    }else{
        qCritical()<<"Could not obtain native SQLite handles for backup.";
        backup.close();
        QSqlDatabase::removeDatabase(connectionName);
        db.rollback();
        return;
    };
    QSqlDatabase::removeDatabase(connectionName);

    db.commit();

    qInfo()<<"Database backup successful:"<<backupFilePath;
    return;
}

bool DatabaseHandler::isOpen() const{
    return m_db.isOpen();
}

int DatabaseHandler::adduserdata(const Userdata &userdatas){
    QSqlQuery query(m_db);

    qDebug() << "=== User Data Debug ===";
    qDebug() << "Name:" << userdatas.name;
    qDebug() << "Gender:" << userdatas.gender;
    qDebug() << "Marital Status:" << userdatas.maritalstatus;
    qDebug() << "Position:" <<postionTostring( userdatas.pos);
    qDebug() << "Phone:" << userdatas.phone;
    qDebug() << "Salary Form:" << salarytypeTostring(userdatas.salaryform);
    qDebug() << "Salary Amount:" << userdatas.salary_amount;
    qDebug() << "Birthdate:" << userdatas.birthdate;
    qDebug() << "Hire Date:" << userdatas.hire_date;
    qDebug() << "=======================";


    qDebug() << "=== Before prepare ===";
    qDebug() << "Database open?" << m_db.isOpen();
    qDebug() << "Database valid?" << m_db.isValid();
    qDebug() << "Last error:" << m_db.lastError();


    query.prepare("INSERT INTO employee (name,gender,marital_status,"
                  "position,phone,salaryform,salaryamount,birth_date,hire_date) "
                  "VALUES (:username,:gender,:marital_status,:pos,:phone, "
                  ":salaryform,:salary_amount,:birthdate,:hire_date)");

    query.bindValue(":username",userdatas.name);
    query.bindValue(":gender",userdatas.gender);
    query.bindValue(":marital_status",userdatas.maritalstatus);
    query.bindValue(":pos",postionTostring(userdatas.pos));
    query.bindValue(":phone",userdatas.phone);
    query.bindValue(":salaryform",salarytypeTostring(userdatas.salaryform));
    query.bindValue(":salary_amount",userdatas.salary_amount);
    query.bindValue(":birthdate",userdatas.birthdate);
    query.bindValue(":hire_date",userdatas.hire_date);


    QSqlQuery checkTable(m_db);
    if(checkTable.exec("SELECT name FROM sqlite_master WHERE type='table' AND name='employee'")) {
        if(checkTable.next()) {
            qDebug() << "Table 'employee' exists";
        } else {
            qCritical() << "Table 'employee' does NOT exist!";
            return -1;
        }
    }
    /*
     * QSqlQuery schemaQuery(m_db);
    if(schemaQuery.exec("PRAGMA table_info(employee)")) {
        qDebug() << "Employee table schema:";
        while(schemaQuery.next()) {
            qDebug() << "Column:" << schemaQuery.value(1).toString()
            << "Type:" << schemaQuery.value(2).toString();
        }
    }
    */

        if(!query.exec()){
        qCritical()<<"Inserting user personal data failed:"<<query.lastError().text();
        QString err="error execution";
        qDebug()<<query.lastError().databaseText();
        return -1;
        }

        if(query.numRowsAffected()<=0){
            qWarning()<<"No rows affected by insert operation";
            return -1;
        }
        QSqlQuery verifyQuery(m_db);
        if(verifyQuery.exec("SELECT COUNT(*) FROM employee")) {
            if(verifyQuery.next()) {
                qDebug() << "Total employees in database after insert:" << verifyQuery.value(0).toInt();
            }
        }

        int lastId = query.lastInsertId().toInt();
        qDebug() << "Last insert ID:" << lastId;
        return lastId;
    return query.lastInsertId().toInt();

    }

bool  DatabaseHandler::addusertaxes(taxdetails & usertax){
        QSqlQuery query(m_db);
        query.prepare("INSERT INTO tax(employee_id,emoployer_cost,"
                      "social,medicare) "
                      "VALUES(:employee_id,:emoployer_cost,:social,:medicare)");

        query.bindValue(":employee_id",usertax.employee_id);
        query.bindValue(":emoployer_cost",usertax.employer_cost);
        query.bindValue(":social",usertax.socialsec);
        query.bindValue(":medicare",usertax.medicare);

        if(!query.exec()){
            qCritical()<<"couldn't register tax information:"<<query.lastError().text();
            return false;
        }



        return 1;
    }


bool DatabaseHandler::deleteEmployee(int Id)
{
    QSqlQuery query(m_db);
    QSettings settings;
    int deleteCount=settings.value("delete_counter",0).toInt();


    query.prepare( "DELETE FROME employee WHERE ID = :id ");
    query.bindValue(":id",Id);

    if(!query.exec()){
        qCritical()<<"Delete employe with id:"<<Id<<" faild\n"<<query.lastError().text();
        return false;
    }

    deleteCount++;

    if(deleteCount>=BACKUP_THRESHOLD){
        backupdb(generateBackupPath());
        settings.setValue("delete_counter",0);
        return true;
    }else{
        settings.setValue("delete_counter",deleteCount);
        return true;
    };

}

bool DatabaseHandler::openDatabase()
{
    if(!m_db.isOpen()){
        if(!m_db.open()){
            return false;
    }
    }
    QSqlQuery query(m_db);
    if(!query.exec()) {
        qCritical() << "Failed to enable foreign keys:" << query.lastError().text();
        return false;
    }
    return true;
}


QString DatabaseHandler::generateBackupPath()
{
    QString timestamp=QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss");
    return QString("data/backup_auto_%1.db").arg(timestamp);
}

void DatabaseHandler::loadallEmployees(){
     QVector <employeeOutput>allusers;
    QSqlQuery query(m_db);

        if(!m_db.isOpen()){
            emit allemployeesloaded(allusers,"Data base connection issue");
            return;
        }
        QString sql="SELECT e.*,t.* FROM employee e "
            "INNER JOIN tax t ON e.ID=t.employee_id;";

        qDebug() << "About to execute query:" << sql;

        bool success = query.exec(sql);
        qDebug() << "Query execution result:" << success;

        if(!success){
            qDebug() << "Query failed! Last error:" << query.lastError().text();
            emit allemployeesloaded(allusers,"Execution error!");
            return;
        } else {
            qDebug() << "Query executed successfully!";

            while(query.next()){
                employeeOutput usrdata;

                usrdata.id=query.value("ID").toString();
                usrdata.name=query.value("name").toString();
                usrdata.gender=query.value("gender").toString();
                usrdata.marital=query.value("marital_status").toString();
                usrdata.pos=query.value("position").toString();
                usrdata.phone=query.value("phone").toString();
                usrdata.salarytype=query.value("salaryform").toString();
                usrdata.salaryAmount=query.value("salaryamount").toInt();
                //QString dollarString = QString("$%1").arg(alltaxes, 0, 'f', 2);
                QDate birthD=query.value("birth_date").toDate();
                usrdata.birthdate=birthD.toString("yyyy/MM/dd");
                QDate hireD=query.value("hire_date").toDate();
                usrdata.hiredate=hireD.toString("yyyy/MM/dd");
                double emplyercost=query.value("emoployer_cost").isNull()?0.0:query.value("emoployer_cost").toDouble();
                double socialsec=query.value("social").isNull()?0.0:query.value("social").toDouble();
                double medicare=query.value("medicare").isNull()?0.0:query.value("medicare").toDouble();
                double taxes= emplyercost+socialsec+medicare;
                usrdata.tax="%"+QString::number(taxes);


                allusers.append(usrdata);
            }

            emit DatabaseHandler::allemployeesloaded(allusers);
        }



    }







