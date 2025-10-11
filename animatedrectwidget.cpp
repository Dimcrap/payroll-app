#include "animatedrectwidget.h"
#include <QPainter>
#include <QPaintEvent>
//#include <QEa
#include <QDebug>


animatedrectwidget::animatedrectwidget(QWidget *parent)
    :QWidget(parent)
    ,m_yOffset(0)
    ,m_movingUp(true)
    //,m_startingPosition(100,200)
{
    initialzieInternalRectangles();

    m_timer=new QTimer(this);
    connect(m_timer,&QTimer::timeout,this,&animatedrectwidget::updateAnimation);

    setMinimumSize(400,350);
}

animatedrectwidget::~animatedrectwidget()
{
    stopAnimation();
}

void animatedrectwidget::initialzieInternalRectangles()
{
    m_relativeinternalRects.clear();

    int cols=4;
    int rows=4;

    int smallHeight=55;
    int smallWidth=50;
    int spacing=14;

    int startX=spacing;
    int startY=spacing;

    for (int row=0;row<rows;++row){

        (row==1)?cols=3:(row==3)?cols=2:cols=4;

        for (int col=0;col<cols;++col){
            if(row==3){
                smallWidth=130;
                startX=13;
            };
            if(row==1){
                smallWidth=85;
                startX=8;
            };
            if(row==2&&col==3){
                smallWidth=60;
                startX=0;
            }
            int x=startX+col*(smallWidth+spacing);
            int y=startY+row*(smallHeight+10);
            m_relativeinternalRects.push_back(QRect(x,y,smallWidth,smallHeight));

        }

        cols=4;
        smallWidth=50;
        startX=17;
    }
}


void animatedrectwidget::updateAnimation()
{
    static double frame=0.0;
    frame+=0.5;

    double yOffset =qSin(frame *0.07)*8;
    m_yOffset=static_cast<int>(yOffset);

    update();
}

void animatedrectwidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    //painter.fillRect(rect(),Qt::lightGray);

    int animatedX=m_mainRectPosition.x();
    //qDebug()<<animatedX;
    int animatedY=m_mainRectPosition.y()+m_yOffset;

    QRect mainRect(animatedX,animatedY,m_mainRectSize.width(),m_mainRectSize.height());


    painter.setBrush(m_mainRectColor);
    painter.setPen("#eeeee4");
    painter.drawRect(mainRect);
    //m_internalRectColor,Qt::CrossPattern

    painter.setPen("#2f3c4f");
    QFont titleFont=painter.font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    painter.setFont(titleFont);

    QString titleText="Employee";
    QRect titleRect=mainRect.adjusted(0,0,0,0);
    titleRect.setHeight(30);
    painter.drawText(titleRect,Qt::AlignCenter,titleText);

    QRect contentArea=mainRect;
    contentArea.setTop(mainRect.top()+30);
    contentArea.setHeight(300);

    QPixmap patternPixmap(10,10);
    patternPixmap.fill(m_internalRectColor);
    painter.setBrush(patternPixmap);
    painter.setPen(QPen(Qt::white,1));

    for(const QRect &relativerect:m_relativeinternalRects){
        QRect absluteRect=relativerect.translated(contentArea.topLeft());
        painter.drawRoundedRect(absluteRect,3,3);
    }

    //implement a poistion report
}


void animatedrectwidget::startAnimation()
{
    m_timer->start(6);
}

void animatedrectwidget::stopAnimation()
{
    m_timer->stop();
    m_yOffset=0;
    update();
}

void animatedrectwidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    int xPos=300;
    qDebug()<<"Resize event - Width:"<<width()<<"height:"<<height();
    if(width()>600&&height()>700){

        m_mainRectPosition=QPoint (xPos,270);

    }else{
        m_mainRectPosition =QPoint(100,160);
    };

    update();

}



