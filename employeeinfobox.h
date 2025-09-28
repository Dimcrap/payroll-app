#ifndef EMPLOYEEINFOBOX_H
#define EMPLOYEEINFOBOX_H
#include "userdata.h"
#include <QWidget>
#include <QGroupBox>


class employeeinfobox:public QGroupBox
{
    Q_OBJECT
public:
   explicit employeeinfobox(const employeeOutput &employee,QWidget *parent=nullptr);
};

#endif // EMPLOYEEINFOBOX_H
