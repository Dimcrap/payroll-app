#ifndef USERDATA_H
#define USERDATA_H

#include <QString>
#include <QDate>


enum class salary_type{
    weekly=1,
    monthly=2,
    project=3,

};

salary_type intTosalarytype(int value);
int salarytypeToint(salary_type Stype);
QString salarytypeTostring(salary_type Stype);

enum class position{
    temprory=0,
    entry=1,
    mid=2,
    senior=3,
    leadership=4,
    executive=5,

    supportSpecialist=10,
};

position intToEmpPosition(int value);
int postiontoInt(position pos);
QString postionTostring(position pos);


struct taxdetails{
    int    employee_id ;
    double employer_cost;
    double socialsec ;
    double medicare ;

    taxdetails(const int &  id,const double emcost,
               const double & socialsecureity,const double & medcare):
        employee_id(id),employer_cost(emcost),socialsec(socialsecureity),
        medicare(medcare){}

    taxdetails():employee_id(-1),employer_cost(0.0),socialsec(0.0),
        medicare(0.0){}


};


struct Userdata{
    QString name;
    QString gender;
    QString maritalstatus;
    QDate birthdate;
    position pos;
    QString phone;
    salary_type salaryform;
    int salary_amount;
    QDate hire_date;

    Userdata(const QString &uname, const QString &ugender,const QString & umaritalstatus,QDate& ubirthdate,
             position &uposition,const QString &uphone,salary_type &usalaryform,int salaryamount,
             QDate &hiredate):name(uname),gender(ugender),maritalstatus(umaritalstatus),birthdate(ubirthdate),
        pos(uposition),phone(uphone),salaryform(usalaryform),salary_amount(salaryamount),hire_date(hiredate)
    {
    }
    Userdata():name(""),gender(""),maritalstatus(""),birthdate(QDate()),
        pos(static_cast<position>(0)),phone(""),salaryform(static_cast<salary_type>(1)),
        salary_amount(-1),hire_date(QDate())
    {

    }
};

struct employeeOutput{
    QString id;
    QString name;
    QString gender;
    QString marital;
    QString birthdate;
    QString pos;
    QString phone;
    QString salarytype;
    int salaryAmount;
    QString hiredate;
    QString tax;

};

#endif // USERDATA_H
