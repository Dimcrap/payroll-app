#include "mainwindow.h"
#include "DatabaseHandler.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GlobalErrorHandler::install();


    QString sourceDir="C:/programming/cpp/C++/exercise p/payroll-system/";
    QFile stylefile(sourceDir+"/styles/styles.qss");
    qDebug()<<"looking in"<<stylefile.fileName();
    if(stylefile.open(QIODevice::ReadOnly|QIODevice::Text)){
        QTextStream stream(&stylefile);
        QString stylesheet=stream.readAll();
        a.setStyleSheet(stylesheet);
        stylefile.close();
    }else{
        qDebug()<<"Error while opening stylefile,using default styling";
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "payroll-system_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
