#ifndef ANIMATEDRECTWIDGET_H
#define ANIMATEDRECTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>

class animatedrectwidget:public QWidget
{
    Q_OBJECT

public:
    explicit animatedrectwidget(QWidget *parent=nullptr);
    ~animatedrectwidget();

    void startAnimation();
    void stopAnimation();

protected:
    void paintEvent(QPaintEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;

private slots:
    void updateAnimation();

private:
    void initialzieInternalRectangles();

    QTimer *m_timer;
    QVector <QRect> m_relativeinternalRects;
    QColor m_mainRectColor=QColor("#eeeee4");
    QColor m_internalRectColor=QColor("#cdc4c8");

    QPoint m_mainRectPosition=QPoint(100,160);
    QSize m_mainRectSize=QSize(300,330);
    int m_yOffset;
    bool m_movingUp;
    //QPoint m_startingPosition;

};

#endif // ANIMATEDRECTWIDGET_H
