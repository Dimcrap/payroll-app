#include "allemployees.h"
#include "ui_allemployees.h"

allemployees::allemployees(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::allemployees)
{
    ui->setupUi(this);
    setWindowTitle("All Employees");
}

allemployees::~allemployees()
{
    delete ui;
}
