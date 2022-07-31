#ifndef RESIZABLERECTITEM_H
#define RESIZABLERECTITEM_H

#include <QGraphicsRectItem>
#include "abstractrecthandle.h"


class ResizableRectItem : public QGraphicsRectItem,public AbstractRectHandle
{
public:
    explicit ResizableRectItem();
    // QGraphicsItem interface

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    // ResizableHandleRect interface

    QRectF selectorFrameBounds() const override;
    void setSelectorFrameBounds(QRectF boundsRect) override;

    // QGraphicsItem interface
protected:
    void dragEnterEvent(QGraphicsSceneDragDropEvent *event) override;
    void dropEvent(QGraphicsSceneDragDropEvent *event) override;
};

#endif // RESIZABLERECTITEM_H
