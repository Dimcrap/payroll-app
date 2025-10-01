#include "addemployeewindow.h"
#include "ui_addemployeewindow.h"



addemployeewindow::addemployeewindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::addemployeewindow)
{
    ui->setupUi(this);
    setWindowTitle("Add New Employee");
    m_dbhandler=std::make_unique<DatabaseHandler> ("data/payroll.db");
    setMinimumSize(700,380);
    setWindowFlag(Qt::Window);

    connect(ui->backToMain,&QPushButton::clicked,
    this,&addemployeewindow::onBackButtonClicked);
}

QList<QRadioButton*>genders={
    ui->maleB, ui->femaleB
};


QList<QRadioButton*>marital={
    ui->marriedB,
    ui->unmarriedB
};
QList<QRadioButton*>positions={
    ui->radioButton_5,ui->radioButton_6,
    ui->radioButton_7,ui->radioButton_8,
    ui->radioButton_9,ui->radioButton_10,
    ui->radioButton_11
};
QList<QRadioButton*>salaryTypes={
        weeklyB,monthlyB,projectB
};
void addemployeewindow::onBackButtonClicked(){


    emit backToMain();
}
addemployeewindow::~addemployeewindow()
{
    delete ui;
}
/*

struct taxdetails{
    int    employee_id ;
    double employer_cost;
    double socialsec ;
    double medicare ;

    taxdetails(const int &  id,const double emcost,
               const double & socialsecureity,const double & medcare):
        employee_id(id),employer_cost(emcost),socialsec(socialsecureity),
        medicare(medcare){}

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
};

 */
Userdata Userinputs(){



(radio->isChecked())
}
