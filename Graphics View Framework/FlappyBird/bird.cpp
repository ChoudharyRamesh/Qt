#include "bird.h"
#include<QDebug>
#include<QScreen>
#include<QGuiApplication>
#include"view.h"

Bird::Bird(QPixmap pixmap)
{

    setPixmap(pixmap);
    setPos(-boundingRect().width(),0);

    wingFlipTimer = new QTimer(this);
    connect(wingFlipTimer,&QTimer::timeout,this,&Bird::updateBirdWingState);
    wingFlipTimer->setInterval(80);
    wingFlipTimer->start();
    yAnimation = new QPropertyAnimation(this,"y",this);
    rotationAnimation = new QPropertyAnimation(this,"rotation",this);
    WingPixmapNumber=1;
}

Bird::~Bird()
{

}

qreal Bird::rotation() const
{
    return m_rotation;
}

qreal Bird::y() const
{
    return m_y;
}

void Bird::setRotation(qreal rotation)
{
    m_rotation = rotation;
    QPointF center = boundingRect().center();
    QTransform transform;
    transform.translate(center.x(),center.y());  // placing center at bird center
    transform.rotate(rotation);
    transform.translate(-center.x(),-center.y());
    setTransform(transform);
}

void Bird::setY(qreal y)
{
    m_y = y;
    setPos(pos().x(),y);

}

void Bird::rotateTo(const qreal &end, const int &duration, const QEasingCurve &curve)
{
    rotationAnimation->setStartValue(rotation());
    rotationAnimation->setEndValue(end);
    rotationAnimation->setEasingCurve(curve);
    rotationAnimation->setDuration(duration);
    rotationAnimation->start();
}

void Bird::shootBirdUp()
{


    yAnimation->stop();
    rotationAnimation->stop();
    qreal currentypos = y();
    yAnimation->setStartValue(currentypos);
    if(scene()->sceneRect().height()>scene()->sceneRect().width())
    { //portrait
        // yAnimation->setEndValue(currentypos - scene()->sceneRect().height()/28);
        yAnimation->setEndValue(currentypos - 120);
        yAnimation->setDuration(130);
//        qDebug()<<"portrait "<<groundPosition;
    }
    else
    {
        // yAnimation->setEndValue(currentypos - scene()->sceneRect().height()/15);
        yAnimation->setEndValue(currentypos - 100);
        yAnimation->setDuration(100);
//        qDebug()<<"landscape "<<groundPosition;
    }

   yAnimation->setEasingCurve(QEasingCurve::InCirc);
    connect(yAnimation,&QPropertyAnimation::finished,this,&Bird::fallBirdToGround);
    yAnimation->start();
    rotateTo(-20,200,QEasingCurve::OutCubic);

    //    QRect rect(10, 20, 30, 40);
    //    QPixmap original('image.png');
    //    QPixmap cropped = original.copy(rect);

}

void Bird::fallBirdToGround()
{
    if(scene()->sceneRect().height()>scene()->sceneRect().width())
        groundPosition = scene()->height()/2 -boundingRect().height();
    else
        groundPosition = scene()->height()/2 -boundingRect().height();

    if(y()<groundPosition)
    {
        rotationAnimation->stop();
        yAnimation->stop();
        if(scene()->sceneRect().height()>scene()->sceneRect().width())
        {

            yAnimation->setDuration(1300);
        }
        else
        {
            yAnimation->setDuration(900);
        }
        yAnimation->setEasingCurve(QEasingCurve::InQuad);
        yAnimation->setStartValue(scenePos().y());
        yAnimation->setEndValue(groundPosition);
        yAnimation->start();

        rotateTo(90,1200,QEasingCurve::InQuad);
    }
    disconnect(yAnimation,&QPropertyAnimation::finished,this,&Bird::fallBirdToGround);
}


void Bird::updateBirdWingState()
{
    int xScale =150;
    int yScale =150;
    setPixmap(QPixmap(":/images/RedBird"+QString::number(WingPixmapNumber)+".png").scaled(xScale,yScale));
    if(WingPixmapNumber>=9)WingPixmapNumber=1;
    else WingPixmapNumber++;
}
