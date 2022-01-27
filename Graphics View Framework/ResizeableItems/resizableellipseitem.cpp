#include "resizableellipseitem.h"
#include <QPen>
#include <QGraphicsScene>
#include <QPainter>
#include<QGraphicsSceneDragDropEvent>
#include<QMimeData>

ResizableEllipseItem::ResizableEllipseItem()
{
    setOwnerItem(this);
    setAcceptDrops(true);
    setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable );
}

QRectF ResizableEllipseItem::boundingRect() const
{
    return selectorFrameBounds();
}

void ResizableEllipseItem::paint(QPainter *painter,
                                 const QStyleOptionGraphicsItem *option,
                                 QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    painter->save();
    painter->setBrush(brush());
    painter->drawEllipse(rect());

    drawHandlesIfNecessary();

    painter->restore();
    QGraphicsEllipseItem::paint(painter,option,widget);

}

QRectF ResizableEllipseItem::selectorFrameBounds() const
{
    return rect();
}

void ResizableEllipseItem::setSelectorFrameBounds(QRectF boundsRect)
{
    prepareGeometryChange();
    setRect(boundsRect);
    update();

}

void ResizableEllipseItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasColor()){
        event->acceptProposedAction();
    }else{
        QGraphicsEllipseItem::dragEnterEvent(event);
    }

}

void ResizableEllipseItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    if(event->mimeData()->hasColor()){
        setBrush(QBrush(event->mimeData()->colorData().value <QColor>())) ;
         event->acceptProposedAction();
     }else{
         QGraphicsEllipseItem::dropEvent(event);
     }
}


