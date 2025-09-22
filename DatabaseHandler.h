#ifndef DATABASEHANDLER_H
#define DATABASEHANDLER_H

#include <QObject>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>

enum class salary_type{
    weekly=1,
    monthly=2,
    project=3
};

enum class position{
    temprory=0,
    entry=1,
    mid=2,
    senior=3,
    leadership=4,
    executive=5,

    supportSpecialist=10,
};

struct Userdata{
    QString name;
    QString gender;
    QDate birthdate;
    position pos;
    int phone;
    salary_type salaryform;
    int salary_amount;
    QDate hire_date;

    Userdata(const QString &uname, const QString &ugender,QDate& ubirthdate,
             position &uposition,int &uphone,salary_type &usalaryform,int &salary_amount,
             QDate &hire_date):name(uname),ugender(gender),ubirthdate(birthdate),
        uposition(pos),uphone(phone),usalaryform(salaryform)
    {
    }
};

class DatabaseHandler:public QObject{

    Q_OBJECT
public:
    explicit DatabaseHandler(const QString &pathtodb,QObject *parent=nullptr);

    bool isOpen() const;

    public slots:
    void addEmployee(const QString &name);
    void loadallEmployees();
    void backupdb(const QString &backupFilePath);
    int adduserdata(const Userdata &userdatas);
    bool addusertaxes(int user_id);

    signals:
    void employeeAdded(bool success,const QString &error="");
    void allemployeesloaded(const QList<QString> &employeelist,
                            const QString &error="");
    void databaseError(const QString &errmsg);
private:

    QSqlDatabase m_db;
};


struct Userdata;

#endif // DATABASEHANDLER_H
