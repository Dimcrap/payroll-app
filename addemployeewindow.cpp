#include "addemployeewindow.h"
#include "ui_addemployeewindow.h"

addemployeewindow::addemployeewindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::addemployeewindow)
{
    ui->setupUi(this);
    setWindowTitle("Add New Employee");
}

addemployeewindow::~addemployeewindow()
{
    delete ui;
}
