#include "view.h"
#include<QMouseEvent>
#include<QGraphicsRectItem>

View::View(QWidget *parent) : QGraphicsView(parent)
{

}


void View::mousePressEvent(QMouseEvent *event)
{
   QPointF point = mapToScene(event->pos());
   scene()->addRect(point.x()-25,point.y()-25,50,50,QPen(Qt::red),Qt::green);
   QGraphicsView::mousePressEvent(event);
}
