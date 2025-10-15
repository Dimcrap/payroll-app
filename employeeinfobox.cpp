#include "employeeinfobox.h"
#include <QLayout>
#include <QFormLayout>
#include <QLabel>
#include <QPushButton>

employeeinfobox::employeeinfobox(const employeeOutput &employee,QWidget *parent)
    :QGroupBox(parent)
{

    setTitle(employee.name+"(ID:"+employee.id+")");
    QFont font = this->font();
    font.setPointSize(14);
    font.setBold(true);
    this->setFont(font);

    QFormLayout *layout=new QFormLayout(this);
    layout->setVerticalSpacing(8);

    this->setStyleSheet("QLabel {min-height:25px;font-size:14px;border-radius:6px}");

    QLabel *genderLabel =new  QLabel(employee.gender);
    QLabel *maritalLabel =new  QLabel(employee.marital);
    QLabel *birthLabel  =new   QLabel(employee.birthdate);
    QLabel *phoneLabel =new   QLabel(employee.phone);
    QLabel *positionLabel =new  QLabel(employee.pos);
    QLabel *hiredateLaber  =new   QLabel(employee.hiredate);
    QLabel *salarytypeLabel =new QLabel(employee.salarytype);
    QLabel *salaryLabel =new QLabel(QString::number(employee.salaryAmount));
    QLabel *taxLabel  =new  QLabel(employee.tax);

    bool ok;
    double salary=employee.salaryAmount;
    QString taxStr=employee.tax;
    taxStr.remove('%');
    taxStr=taxStr.trimmed();
    double tax=taxStr.toDouble(&ok);
    if (!ok) {
        qDebug() << "Error: Could not convert tax value:" << employee.tax;
        // Handle error - maybe use a default value
    }
    double taxMultiplier=(tax>1.0)?(tax/100.0):tax;
    double payresult= salary-(salary*taxMultiplier);
    QLabel *finalPay=new QLabel(QString::number(payresult));

    QPushButton *deletebtn=new QPushButton("Delete");
    deletebtn->setStyleSheet("padding:1px;max-width:100px;min-height:30px;min-width:80px");
    connect(deletebtn,&QPushButton::clicked,this,[this,employee](){
        qDebug()<<"Delete button clicked for employee:"<<employee.id;
        emit deleterequest(employee.id);
    });
    layout->addWidget(deletebtn);

    layout->setAlignment(deletebtn,Qt::AlignRight);
    layout->addRow("Gender:",genderLabel);
    layout->addRow("Marital Status:",maritalLabel);
    layout->addRow("Birth date:",birthLabel);
    layout->addRow("phone number:",phoneLabel);
    layout->addRow("Job position:",positionLabel);
    layout->addRow("Hire date:",hiredateLaber);
    layout->addRow("Salary form:",salarytypeLabel);
    layout->addRow("Salary amount:",salaryLabel);
    layout->addRow("Tax amount: %",taxLabel);
    layout->addRow("Pay:",finalPay);

    this->update();
    this->setLayout(layout);

}
