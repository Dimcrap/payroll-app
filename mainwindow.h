#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "allemployees.h"
#include "addemployeewindow.h"
#include <QTimer>
#include <QStack>
#include <QStackedWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
class allemployees;
class addemployeewindow;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();
private slots:
    void onAddEmployeeClicked();
    void onViewEmployeeClicked();

private:
    Ui::MainWindow *ui;

    std::shared_ptr<DatabaseHandler> m_dbhandler;
    addemployeewindow *m_addemployeewindow;
    allemployees * m_allemployeeswindow;

    QStackedWidget *stackWidget;
    QWidget *mainPage;
public:
    std::shared_ptr<DatabaseHandler> getDatabasehandler();

protected:
    void keyPressEvent(QKeyEvent * event) override;
    void resizeEvent(QResizeEvent *event) override;
};


class GlobalErrorHandler{
    public:
        static void install();
    private:
        static void globalErrorHandler(QtMsgType type,const QMessageLogContext &context,
                                   const QString &msg);
        static void showGlobalPopup(QtMsgType,const QString &msg);
};

#endif // MAINWINDOW_H
