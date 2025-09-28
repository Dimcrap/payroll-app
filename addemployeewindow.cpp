#include "addemployeewindow.h"
#include "ui_addemployeewindow.h"


addemployeewindow::addemployeewindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::addemployeewindow)
{
    ui->setupUi(this);
    setWindowTitle("Add New Employee");

    setMinimumSize(700,280);
    setWindowFlag(Qt::Window);
    connect(ui->backToMain,&QPushButton::clicked,
this,&addemployeewindow::onBackButtonClicked);
}
void addemployeewindow::onBackButtonClicked(){


    emit backToMain();
}
addemployeewindow::~addemployeewindow()
{
    delete ui;
}
