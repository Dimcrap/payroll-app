#include "allemployees.h"
#include "ui_allemployees.h"
#include <QScrollArea>
#include <QLayoutItem>
#include <memory>


allemployees::allemployees(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::allemployees)
{
    ui->setupUi(this);
    setWindowTitle("All Employees");
    setMinimumSize(800,550);
    setWindowFlag(Qt::Window);



    m_dbhandler=new DatabaseHandler("data/payroll");

    connect(m_dbhandler,&DatabaseHandler::allemployeesloaded,
            this ,&allemployees::handleEmployeesLoaded);
    if(!m_dbhandler){
        qDebug("couldn't set database connection");
    };

    m_dbhandler->loadallEmployees();
    QScrollArea *scrollArea=new QScrollArea(this);
    QWidget *scrollwidget=new QWidget();
    m_layout=new QVBoxLayout(scrollwidget);



    scrollArea->setWidget(scrollwidget);
    scrollArea->setWidgetResizable(true);

    setCentralWidget(scrollArea);

}

allemployees::~allemployees()
{
    delete ui;
}


void allemployees::handleEmployeesLoaded(const QVector<employeeOutput> &employees,
                                         const QString &error){
    QLayoutItem *item;
    while((item=m_layout->takeAt(0))!=nullptr){
        if(item->widget()){
            delete item->widget();
        }
        delete item;
    }


    if(!error.isEmpty()){
        qCritical()<<error;
        return;
    }

    for(const employeeOutput & emp:employees){
        employeeinfobox *infobox=new employeeinfobox(emp);
        m_layout->addWidget(infobox);
    }

    m_layout->addStretch();
}
