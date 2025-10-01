#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addemployeewindow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QWidget>
#include <QFile>
#include <QKeyEvent>
#include <QResizeEvent>
#include <QLayout>
#include <QMargins>
#include <QStackedWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

    ,m_addemployeewindow(nullptr)
    ,m_allemployeeswindow(nullptr)
{
    ui->setupUi(this);

    setupConnections();

    QWidget *orginalCenteralWidget=takeCentralWidget();
    QStackedWidget *stackedWidget = new QStackedWidget(this);
    stackedWidget->addWidget(orginalCenteralWidget);

    m_addemployeewindow  =new addemployeewindow(this);
    stackedWidget->addWidget(m_addemployeewindow);
    setCentralWidget(stackedWidget);

    QPushButton *addEmployeeButton=findChild<QPushButton *>("addEmployeeButton");
    if(!addEmployeeButton){
        qDebug() << "Button not found! Check the object name.";
    };

    connect(addEmployeeButton,&QPushButton::clicked,
            this,[stackedWidget](){
        stackedWidget->setCurrentIndex(1);
    } );

    connect(m_addemployeewindow,&addemployeewindow::backToMain,this,[stackedWidget](){
        stackedWidget->setCurrentIndex(0);
    });
    QPushButton *viewEmployeesButton=findChild<QPushButton*>("viewEmployeesButton");

    if (viewEmployeesButton) {
        connect(viewEmployeesButton, &QPushButton::clicked,
                this, &MainWindow::onViewEmployeeClicked);
    } else {
        qDebug() << "Button not found! Check the object name.";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{

    connect(ui->viewEmployeesButton,&QPushButton::clicked,
            this,&MainWindow::onViewEmployeeClicked);

}

void MainWindow::onAddEmployeeClicked()
{
    if(!m_addemployeewindow){
        m_addemployeewindow=new addemployeewindow(this);
    }
    m_addemployeewindow->show();
    m_addemployeewindow->raise();
    m_addemployeewindow->activateWindow();
}

void MainWindow::onViewEmployeeClicked()
{
    if (!m_allemployeeswindow) {
        m_allemployeeswindow = new allemployees(this);
    }

    m_allemployeeswindow->show();
    m_allemployeeswindow->raise();
    m_allemployeeswindow->activateWindow();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);
    qDebug()<<"Resize event-fullscreen"<<isFullScreen()<<" Size:"<<size();

    QMargins margins=ui->verticalLayout->contentsMargins();

    if(width()>1000&&height()>650){
       margins.setTop(100);
       margins.setLeft(165);
       margins.setRight(55);
        ui->verticalLayout->setContentsMargins(margins);
       ui->verticalLayout->setSpacing(25);
    }else{
    margins.setTop(45);
    margins.setLeft(50);
    margins.setRight(20);
    ui->verticalLayout->setSpacing(25);
    ui->verticalLayout->setContentsMargins(margins);

}
}
void MainWindow::keyPressEvent(QKeyEvent * event){
    if(event->key() ==Qt::Key_F5){
        QString sourceDir="C:/programming/cpp/C++/exercise p/payroll-system/";
        QFile file(sourceDir+"/styles/styles.qss");
        if(file.open(QFile::ReadOnly|QFile::Text)){
            QString styleSheet=QLatin1String(file.readAll());
            qApp->setStyleSheet(styleSheet);
            file.close();
             qDebug() << "Stylesheet reloaded!";
        }
    }
     QMainWindow::keyPressEvent(event);
}

void GlobalErrorHandler::install(){
    qInstallMessageHandler(globalErrorHandler);
}

void GlobalErrorHandler::globalErrorHandler(QtMsgType type,
    const QMessageLogContext &context,const QString &msg){

    QTimer::singleShot(0,[type,msg](){
        showGlobalPopup(type,msg);
    });

    fprintf(stderr, "%s\n", msg.toLocal8Bit().constData());
}


void GlobalErrorHandler::showGlobalPopup(QtMsgType type,const QString &msg){
    QMessageBox msgBox;

    if(type==QtFatalMsg){
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Fatal");
    }
    else if(type==QtCriticalMsg){
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setWindowTitle("Error");
    }
    else if(type==QtWarningMsg){
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("Warning");
    }
    else if(type==QtDebugMsg){
        msgBox.setIcon(QMessageBox::NoIcon);
        msgBox.setWindowTitle("Debug");
    }else{
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setWindowTitle("Info");
    }

    msgBox.setText(msg);
    msgBox.resize(450,250);
    msgBox.exec();

}
