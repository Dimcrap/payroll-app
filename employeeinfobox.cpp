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
    QLabel *genderLabel =new  QLabel(employee.gender);
    QLabel *maritalLabel =new  QLabel(employee.marital);
    QLabel *birthLabel  =new   QLabel(employee.birthdate);
    QLabel *phoneLabel =new   QLabel(employee.phone);
    QLabel *positionLabel =new  QLabel(employee.pos);
    QLabel *hiredateLaber  =new   QLabel(employee.hiredate);
    QLabel *salarytypeLabel =new QLabel(employee.salarytype);
    QLabel *salaryLabel =new QLabel(QString::number(employee.salaryAmount));
    QLabel *taxLabel  =new  QLabel(employee.tax);



    QList<QLabel*> labels={genderLabel,maritalLabel,birthLabel
    ,phoneLabel ,positionLabel,   hiredateLaber ,   salarytypeLabel
                            , salaryLabel,      taxLabel
    };

    QPushButton *deletebtn=new QPushButton("Delete");
    deletebtn->setStyleSheet("padding:1px;max-width:100px;min-height:30px;min-width:80px");
    layout->addWidget(deletebtn);
    layout->setAlignment(deletebtn,Qt::AlignRight);
    layout->addRow("Gender:",genderLabel);
    layout->addRow("Marital Status:",maritalLabel);
    layout->addRow("Birth date:",birthLabel);
    layout->addRow("phone number:",phoneLabel);
    layout->addRow("Job position:",positionLabel);
    layout->addRow("Hire date:",hiredateLaber);
    layout->addRow("Salary form:",salarytypeLabel);
    layout->addRow("Salary anmount:",salaryLabel);
    layout->addRow("Tax amount: %",taxLabel);

    this->update();
    this->setLayout(layout);

}
