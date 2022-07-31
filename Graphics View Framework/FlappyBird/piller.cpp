#include "piller.h"
#include<QRandomGenerator>
#include<QDebug>
#include<QGraphicsScene>
#include"bird.h"

Piller::Piller(int width,int height,double speed)
{
    PillerGap = 160; //+QRandomGenerator::global()->bounded(20);  //160
    topPiller = new QGraphicsPixmapItem( QPixmap(":/images/piller.png").scaled(400,height/2+200));  //200,100
    topPiller->setPos(0-topPiller->boundingRect().width()/2,PillerGap);
    bottomPiller = new QGraphicsPixmapItem( QPixmap(":/images/piller.png").scaled(400,height/2+200)); //200,100
    bottomPiller->setPos(0-bottomPiller->boundingRect().width()/2,-bottomPiller->boundingRect().height()-PillerGap);
    addToGroup(topPiller);
    addToGroup(bottomPiller);

    yRandPos = QRandomGenerator::global()->bounded(200);  //100
    xRandPos = QRandomGenerator::global()->bounded(40);  // increase randomess for game complexity

    setPos(QPoint(0,0)+QPoint(370+xRandPos,yRandPos));

    xAnimation = new QPropertyAnimation(this,"x",this);

    xAnimation->setStartValue((width/2)+20+xRandPos);
    xAnimation->setEndValue(-(width/2)-20);

    xAnimation->setEasingCurve(QEasingCurve::Linear);
    xAnimation->setDuration((width*100)/(45+speed));  // t=d/v

    connect(xAnimation,&QPropertyAnimation::finished,[=]()
    {
        scene()->removeItem(this);
        delete this;
    });

}

Piller::~Piller()
{

}

qreal Piller::x() const
{
    return m_x;
}

void Piller::StartPillerMoveAnimation()
{
    xAnimation->start();
}

void Piller::StopPillerMoveAnimation()
{
    xAnimation->stop();
}

void Piller::PausePillerMoveAnimation()
{
    xAnimation->pause();
}

void Piller::ResumePillerMoveAnimation()
{
     xAnimation->resume();
}

void Piller::setX(qreal x)
{
    m_x = x;
    setPos(QPointF(0,0)+QPointF(x,yRandPos));
    if(isBirdCollide(x))
    {
        emit PcollisionHappened();
    }
}

bool Piller::isBirdCollide(int x)
{
    Q_UNUSED(x);
     QList<QGraphicsItem *> collidingItems = topPiller->collidingItems();
       collidingItems.append(bottomPiller->collidingItems());
       for(auto it:collidingItems)
       {
           if(dynamic_cast<Bird *>(it)) return true;
       }   
    return false;
}
