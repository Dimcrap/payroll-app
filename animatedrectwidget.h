#ifndef ANIMATEDRECTWIDGET_H
#define ANIMATEDRECTWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPropertyAnimation>

class animatedrectwidget:public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int yOffset READ getYOffset WRITE setYOffset)
public:
    explicit animatedrectwidget(QWidget *parent=nullptr);
    ~animatedrectwidget();

    void startAnimation();
    void stopAnimation();
    int getYOffset()const;
    void setYOffset(int offset);

protected:
    void paintEvent(QPaintEvent *event)override;
    void resizeEvent(QResizeEvent *event)override;

private slots:
    void updateAnimation();

private:
  void setupAnimation();

    QTimer *m_timer;
    QPropertyAnimation *m_animation;
    int m_yOffset;
    bool m_movingUp;
    QPoint m_startingPosition;
    QRect m_rect;
    QColor m_rectColor;

};

#endif // ANIMATEDRECTWIDGET_H
