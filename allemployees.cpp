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


    m_dbhandler=new DatabaseHandler("data/payroll");

    connect(m_dbhandler,&DatabaseHandler::allemployeesloaded,
            this ,&allemployees::handleEmployeesLoaded);

    m_dbhandler->loadallEmployees();

}

allemployees::~allemployees()
{
    delete ui;
    delete m_dbhandler;
}


void allemployees::handleEmployeesLoaded(const QVector<employeeOutput> &employees,
                                         const QString &error){


    if(!m_layout||!m_layout->parent()){
        qCritical()<<"Layout is null!";
        return;
    }

    QLayoutItem *item;
    while((item=m_layout->takeAt(0))!=nullptr){
        QWidget *widget=item->widget();
        if(item->widget()){
            widget->setParent(nullptr);
            widget->deleteLater();
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
