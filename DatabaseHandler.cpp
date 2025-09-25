#include "DatabaseHandler.h"
#include "userdata.h"
#include <QDebug>
#include <QSqlDriver>
#include <sqlite3.h>


DatabaseHandler::DatabaseHandler(const QString &pathtodb,QObject *parent):
    QObject(parent){

    m_db=QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("data/payroll.db");

    if(!m_db.open()){
        QString error=m_db.lastError().text();
        qCritical()<<"Failed to open databas:"<<error;

    }else{
        qDebug()<<"db opened successfully";
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


    QString connectionName ="backup_connection";

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
                sqlite3_backup_step(sqlitebackup,-1);
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

    db.rollback();

    qInfo()<<"Database backup successful:"<<backupFilePath;
    return;
}

bool DatabaseHandler::isOpen() const{
    return m_db.isOpen();
}

int DatabaseHandler::adduserdata(const Userdata &userdatas){
    QSqlQuery query;
    query.prepare("INSERT INTO employee (name,gender,marital_status,"
                  "pos,phone,salaryform,salary_amount,birth_date,hire_date)"
                  "VALUES (:sername,:gender,:pos,:phone,"
                  ":salaryform,:salary_amount,:birthdat,:hire_date)");

    query.bindValue(":name",userdatas.name);
    query.bindValue(":gender",userdatas.gender);
    query.bindValue(":marital_status",userdatas.maritalstatus);
    query.bindValue(":pos",postionTostring(userdatas.pos));
    query.bindValue("phone",userdatas.phone);
    query.bindValue(":salaryform",salarytypeTostring(userdatas.salaryform));
    query.bindValue(":salary_amount",userdatas.salary_amount);
    query.bindValue(":birthdate",userdatas.birthdate);
    query.bindValue(":hire_date",userdatas.hire_date);


        if(!query.exec()){
        //qCritical<<"Inserting data failed:"<<query.lastError().text();
        QString err=query.lastError().text();
        emit DatabaseHandler::employeeAdded(false,err);
        return -1;
        }

    emit DatabaseHandler::employeeAdded(true,"emplyee data added successfully");
    return query.lastInsertId().toInt();
    }

bool  DatabaseHandler::addusertaxes(taxdetails & usertax){
        QSqlQuery query;
        query.prepare("INSERT INTO tax(employee_id,emoployer_cost,"
                      "social,medicare)"
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

void DatabaseHandler::loadallEmployees(){
        QVector <employeeOutput>allusers;
        QSqlQuery query;

        QString sql="SELECT e.*,t.* FROM employee e"
            "INNER JOIN tax t ON e.ID=t.employee_id ";
        if(query.exec(sql)){
            emit allemployeesloaded(allusers);
            return;
        };

        while(query.next()){
            employeeOutput usrdata;


            usrdata.id=query.value("ID").toString();
            usrdata.name=query.value("name").toString();
            usrdata.gender=query.value("gender").toString();
            usrdata.marital=query.value("marital_status").toString();
            usrdata.pos=query.value("position").toString();
            usrdata.phone=query.value("phone").toString();
            usrdata.salarytype=query.value("salaryform").toString();
            usrdata.salaryAmount=query.value("salaryamount").toInt();//QString dollarString = QString("$%1").arg(alltaxes, 0, 'f', 2);
            QDate birthD=query.value("birth_date").toDate();
            usrdata.birthdate=birthD.toString("yyyy/MM/dd");
            QDate hireD=query.value("hire-dat").toDate();
            usrdata.hiredate=hireD.toString("yyyy/MM/dd");
            double emplyercost=query.value("employer_cost").isNull()?0.0:query.value("employer_cost").toDouble();
            double socialsec=query.value("social").isNull()?0.0:query.value("social").toDouble();
            double medicare=query.value("medicare").isNull()?0.0:query.value("medicare").toDouble();
            double taxes= emplyercost+socialsec+medicare;
            usrdata.tax="%"+QString::number(taxes);


            allusers.append(usrdata);
        }
        emit DatabaseHandler::allemployeesloaded(allusers,"employee list loaded successfully");
    }







