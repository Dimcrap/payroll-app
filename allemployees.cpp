#include "allemployees.h"
#include "ui_allemployees.h"
#include <QScrollArea>
#include <QLayoutItem>



allemployees::allemployees(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::allemployees)
    ,m_dbhandler(nullptr)
    ,m_infobox(new employeeinfobox(emptyInfobox()))
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

}

allemployees::~allemployees()
{
    delete ui;
}

void allemployees::refreshEmployees()
{

    if(m_dbhandler){
        m_dbhandler->loadallEmployees();
    }else{
        qWarning()<<"Could't refresh employees!";
    }

}

void allemployees::setDatabseHandler(std::shared_ptr <DatabaseHandler> handler){
    m_dbhandler=handler;

    if(m_dbhandler){
        connect(m_dbhandler.get(),&DatabaseHandler::allemployeesloaded,
                this ,&allemployees::handleEmployeesLoaded);
    }
    m_dbhandler->loadallEmployees();
}

employeeOutput allemployees::emptyInfobox()
{
    employeeOutput emptyForm;
    emptyForm.id="0";
    emptyForm.name="";
    emptyForm.gender="";
    emptyForm.marital=" ";
    emptyForm.pos=" ";
    emptyForm.phone=" ";
    emptyForm.salarytype=" ";
    emptyForm.salaryAmount=0;
    emptyForm.birthdate=" ";
    emptyForm.hiredate=" ";
    emptyForm.tax="%";

    return emptyForm;
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
        };
        delete item;
    }

    if(!error.isEmpty()){
        qCritical()<<error;
        return;
    }

    if(employees.empty()){

        m_infobox=new employeeinfobox(emptyInfobox());
        m_layout->addWidget(m_infobox);

        qInfo()<<"no employee founded";

    }else{

        for(const employeeOutput & emp:employees){
            m_infobox=new employeeinfobox(emp);
            connect(m_infobox,&employeeinfobox::deleterequest,this,&allemployees::handleEmployeeDelete);
            m_layout->addWidget(m_infobox);
        };
    };

    m_layout->addStretch();
}

void allemployees::handleEmployeeDelete(QString empID)
{
    bool confirm=m_dbhandler->yesnoDialog("Delete employee");
    if(confirm){
        int Id=empID.toInt();
        if(Id==0){
            qCritical()<<"could't delete employee";
            return;
        };

        if(!m_dbhandler->deleteEmployee(Id)){
            qCritical()<<"Failed to delete";
            return;
        };
        refreshEmployees();
        qInfo()<<"Employee deleted!";

    }else{
        return;
    };
}

void allemployees::showEvent(QShowEvent *event)
{

    QMainWindow::showEvent(event);

    refreshEmployees();
}
