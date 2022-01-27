#include "view.h"
#include<QDebug>
#include<QMouseEvent>
View::View(QWidget *parent) : QGraphicsView(parent)
{

}

void View::mousePressEvent(QMouseEvent *event)
{
   qDebug()<<"mouse event in"<<"QGraphicsView "<<event->pos();
  Q_UNUSED(event);
   QGraphicsView::mousePressEvent(event);
}

void View::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"key event in"<<"QGraphicsView";
    Q_UNUSED(event);
    QGraphicsView::keyPressEvent(event);
}
