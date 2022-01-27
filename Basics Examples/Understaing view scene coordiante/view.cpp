#include "view.h"
#include<QDebug>

View::~View(){}

View::View(QWidget *parent)
    : QGraphicsView(parent)
{
    resize(800,800);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void View::resetScenePos()
{
    QRectF sR = sceneRect();
    setSceneRect(sR.x()-sceneMoved.x(),sR.y()-sceneMoved.y(),sR.width(),sR.height());
    sceneMoved=QPointF(0,0);
}


void View::mouseMoveEvent(QMouseEvent *event)
{
    if(isMousPressed && event->modifiers()==Qt::KeyboardModifier::ControlModifier)
    {
        QPointF newPoint =  event->pos();
        QPointF dif =  lastpoint - newPoint;
        if(transform().m11()<1)
            dif =  QPointF(dif.x()/transform().m11(),dif.y()/transform().m22());
        QRectF sR = sceneRect();
        sceneMoved+=dif;
        setSceneRect(sR.x()+dif.x(),sR.y()+dif.y(),sR.width(),sR.height());
        lastpoint = newPoint;
    }
    else QGraphicsView::mouseMoveEvent(event);
}

void View::mousePressEvent(QMouseEvent *event)
{

    isMousPressed=true;
    lastpoint =  event->pos();
    QGraphicsView::mousePressEvent(event);

}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    isMousPressed=false;
    QGraphicsView::mouseReleaseEvent(event);
}


void View::scalingTime(qreal q) {
    Q_UNUSED(q);
    qreal factor = 1.0+ qreal(_numScheduledScalings)/300.0;
    scale(factor,factor);
}

void View::animFinished() {

    if (_numScheduledScalings > 0)  _numScheduledScalings--;
    else  _numScheduledScalings++;
    sender()->~QObject();
}

void View::wheelEvent(QWheelEvent *event)
{
    if(event->modifiers()==Qt::KeyboardModifier::ControlModifier)
    {
        int numDegrees = event->delta() / 8;
        int numSteps = numDegrees / 15; // see QWheelEvent documentation
        _numScheduledScalings += numSteps;
        if (_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
            _numScheduledScalings = numSteps;
        QTimeLine *anim = new QTimeLine(350, this);
        anim->setUpdateInterval(20);
        connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
        connect(anim, SIGNAL (finished()), SLOT (animFinished()));
        anim->start();
    }
    else QGraphicsView::wheelEvent(event);
}



