#include "animatedrectwidget.h"
#include <QPainter>
#include <QPaintEvent>
//#include <QEa



animatedrectwidget::animatedrectwidget(QWidget *parent)
    :QWidget(parent)
    ,m_yOffset(0)
    ,m_movingUp(true)
    ,m_rectColor(Qt::blue)
    ,m_startingPosition(100,200)
{
    m_timer=new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&animatedrectwidget::updateAnimation);

    setupAnimation();

    setMinimumSize(200,300);


}

animatedrectwidget::~animatedrectwidget()
{
    stopAnimation();
}

void animatedrectwidget::startAnimation()
{
    m_animation->start();
}


void animatedrectwidget::stopAnimation()
{
    m_animation->stop();
    m_timer->stop();
    m_yOffset=0;
    update();
}

int animatedrectwidget::getYOffset() const
{
    return m_yOffset;

}

void animatedrectwidget::setYOffset(int offset)
{
    if(m_yOffset!=offset){
        m_yOffset=offset;
        update();
    }
}

void animatedrectwidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //painter.fillRect(rect(),Qt::lightGray);

    int animatedX=m_startingPosition.x();
    int animatedY=m_startingPosition.y();

    m_rect=QRect(animatedX,animatedY,80,120);

    painter.setBrush(m_rectColor);
    painter.setPen(QPen(Qt::darkBlue,2));
    painter.drawRect(m_rect);

    /*
    // Optional: Add some text or details
    painter.setPen(Qt::black);
    painter.drawText(m_rect, Qt::AlignCenter, "Moving Paper");
    */

    //implement a poistion report
}

void animatedrectwidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if(width()>1000&&height()>650){
        m_startingPosition=QPoint(140,250);
        m_rect=QRect(m_startingPosition.x(),m_startingPosition.y(),100,150);
    }else{

        m_startingPosition=QPoint(100,200);
        m_rect=QRect(m_startingPosition.x(),m_startingPosition.y(),80,120);
    };
    update();
}


void animatedrectwidget::updateAnimation()
{
    if(m_movingUp){
        m_yOffset--;
        if(m_yOffset<=-15){
            m_movingUp=false;
        };
    }else{
        m_yOffset++;
        if(m_yOffset>=0){
            m_movingUp=true;
        };
    }
    update();

}

void animatedrectwidget::setupAnimation()
{
    m_animation->setDuration(1000);
    m_animation->setStartValue(0);
    m_animation->setEndValue(15);
    m_animation->setEasingCurve(QEasingCurve::InOutSine);
    m_animation->setLoopCount(-1);
}
