#include "employeeinfobox.h"
#include <QLayout>
#include <QFormLayout>
#include <QLabel>

employeeinfobox::employeeinfobox(const employeeOutput &employee,QWidget *parent)
    :QGroupBox(parent)
{

    setTitle(employee.name+"(ID:"+employee.id+")");

    QFormLayout *layout=new QFormLayout(this);
    layout->setVerticalSpacing(8);
    QLabel *genderLabel     =new     QLabel(employee.gender);
    QLabel *maritalLabel    =new    QLabel(employee.marital);
    QLabel *birthLabel      =new      QLabel(employee.birthdate);
    QLabel *phoneLabel     =new      QLabel(employee.phone);
    QLabel *positionLabel   =new   QLabel(employee.pos);
    QLabel *hiredateLaber    =new   QLabel(employee.hiredate);
    QLabel *salarytypeLabel =new QLabel(employee.salarytype);
    QLabel *salaryLabel     =new     QLabel(employee.salaryAmount);
    QLabel *taxLabel        =new        QLabel(employee.tax);



    QList<QLabel> labels={genderLabel,maritalLabel,birthLabel
    ,phoneLabel ,positionLabel,   hiredateLaber ,   salarytypeLabel
                            , salaryLabel,      taxLabel       };

    layout->addRow("Gender:",genderLabel);
    layout->addRow("Marital Status:",maritalLabel);
    layout->addRow("Birth date:",birthLabel);
    layout->addRow("phone number:"phoneLabel);
    layout->addRow("Job position:",positionLabel);
    layout->addRow("Hire date:",hiredateLaber);
    layout->addRow("Salary form:",salarytypeLabel);
    layout->addRow("Salary anmount:"salaryLabel);
    layout->addRow("Tax amouny: %",taxLabel);





}
