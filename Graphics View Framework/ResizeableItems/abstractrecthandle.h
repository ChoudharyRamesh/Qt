#ifndef RESIZABLEHANDLERECT_H
#define RESIZABLEHANDLERECT_H

#include <QRectF>
#include <QPainter>
#include <QGraphicsItem>
#include "handleitem.h"

// handle interface class
class AbstractRectHandle
{
public:
    AbstractRectHandle();
    virtual ~ AbstractRectHandle();

    virtual QRectF selectorFrameBounds() const = 0;
    virtual void setSelectorFrameBounds(QRectF boundsRect) = 0;

    void drawHandlesIfNecessary();

    QPixmap getPixmap() const;
    void setPixmap(const QPixmap &value);

    void setOwnerItem(QGraphicsItem *value);

private:
    void drawHandles();

    QRectF topleftHandleRect;
    QRectF topRightHandleRect;
    QRectF bottomRightHandleRect;
    QRectF bottomLeftHandleRect;
    QRectF topCenterHandleRect;
    QRectF leftCenterHandleRect;
    QRectF centerHandleRect;
    QRectF rightCenterHandleRect;
    QRectF bottomCenterHandleRect;

    QList<HandleItem * > handleList;
    bool handlesAddedToScene;
    QGraphicsItem * ownerItem;

};

#endif // AbstractRectHandle_H
