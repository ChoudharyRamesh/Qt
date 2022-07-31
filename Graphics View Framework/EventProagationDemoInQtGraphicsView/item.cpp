#include "item.h"
#include<QDebug>
#include<QGraphicsSceneMouseEvent>
Item::Item()
{
    setFlag(QGraphicsItem::ItemIsFocusable,true);
}

void Item::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"mouse event in"<<"QGraphicsItem";
   Q_UNUSED(event);
    QGraphicsRectItem::keyPressEvent(event);
}

void Item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"mouse event in"<<"QGraphicsItem "<<event->pos();
    Q_UNUSED(event);
    QGraphicsRectItem::mousePressEvent(event);

}
