#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

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
    void esizeEvent(QResizeEvent *event);

    ~MainWindow();
private slots:
    void onAddEmployeeClicked();
    void onViewEmployeeClicked();

private:
    Ui::MainWindow *ui;

    addemployeewindow *m_addemployeewindow;
    allemployees * m_allemployeeswindow;

    void setupConnections();
protected:
    void keyPressEvent(QKeyEvent * event) override;
    void resizeEvent(QResizeEvent *event);
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
