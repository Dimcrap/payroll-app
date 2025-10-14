#ifndef EMPLOYEEINFOBOX_H
#define EMPLOYEEINFOBOX_H
#include "DatabaseHandler.h"
#include <QWidget>
#include <QGroupBox>


class employeeinfobox:public QGroupBox
{
    Q_OBJECT
public:
   explicit employeeinfobox(const employeeOutput &employee,QWidget *parent=nullptr);

signals:
   void deleterequest(QString employe_id);
};

#endif // EMPLOYEEINFOBOX_H
