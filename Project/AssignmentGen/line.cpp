#include "line.h"

Line::Line(QPointF point1, QPointF point2,QPen pen, QGraphicsItem *parent)
    :QGraphicsLineItem(point1.x(),point1.y(),point2.x(),point2.y(),parent)
{
   setPen(pen);
}


void Line::paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
    QGraphicsLineItem::paint(painter,option,widget);
    painter->setRenderHint(QPainter::Antialiasing, false);
}
