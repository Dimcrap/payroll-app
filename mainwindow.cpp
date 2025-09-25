#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "addemployeewindow.h"
#include "allemployees.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
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
