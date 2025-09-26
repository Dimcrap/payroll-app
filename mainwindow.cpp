#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addemployeewindow.h"
#include "allemployees.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QWidget>
#include <QFile>
#include <QKeyEvent>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,m_addemployeewindow(nullptr)
    ,m_allemployeeswindow(nullptr)
{
    ui->setupUi(this);

    setupConnections();

    //setWindowTitle("Payroll System");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnections()
{
    connect(ui->addEmployeeButton,&QPushButton::clicked,
            this,&MainWindow::onAddEmployeeClicked);
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
        m_allemployeeswindow = new allemployees(this);  // 'this' makes it a child
    }

    m_allemployeeswindow->show();
    m_allemployeeswindow->raise();
    m_allemployeeswindow->activateWindow();
}

void MainWindow::resizeEvent(QResizeEvent *event){
    QMainWindow::resizeEvent(event);

    is(isFullScreen()){
        //int centerx=width/2-ui->viewEmployeesButton->width()/2 ;
        int rightmargin=50;
        int buttonX=width()-ui->viewEmployeesButton->width()-rightmargin;

        ui->viewEmployeesButton->move(buttonX,100);
        ui->addEmployeeButton->move(centerx,);
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
