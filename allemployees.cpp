#include "allemployees.h"
#include "ui_allemployees.h"
#include <QScrollArea>
#include <QLayoutItem>



allemployees::allemployees(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::allemployees)
{
    ui->setupUi(this);
    setWindowTitle("All Employees");
    setMinimumSize(800,550);
    setWindowFlag(Qt::Window);


    QScrollArea *scrollArea=new QScrollArea(this);
    QWidget *scrollwidget=new QWidget();
    m_layout=new QVBoxLayout(scrollwidget);

    scrollArea->setWidget(scrollwidget);
    scrollArea->setWidgetResizable(true);

    setCentralWidget(scrollArea);

    //data baseperations
}

allemployees::~allemployees()
{
    delete ui;
}


void allemployees::handleEmployeesLoaded(const QVector<employeeOutput> &employees,
                                         const QString &error){
    QLayoutItem *item;
    while((item=m_layout(0))!=nullptr)
}
