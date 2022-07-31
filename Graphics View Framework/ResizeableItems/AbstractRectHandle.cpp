#include "abstractrecthandle.h"
#include <QDebug>
#include <QPen>
#include <QGraphicsScene>
#include <QPainter>

AbstractRectHandle::AbstractRectHandle()
{

}

AbstractRectHandle::~AbstractRectHandle()
{

}

void AbstractRectHandle::drawHandles()
{

    //Populate handles in list
    if(handleList.count() == 0){
        handleList.append(new HandleItem(HandleItem::TopLeft));
        handleList.append(new HandleItem(HandleItem::TopRight));
        handleList.append(new HandleItem(HandleItem::BottomRight));
        handleList.append(new HandleItem(HandleItem::BottomLeft));

        handleList.append(new HandleItem(HandleItem::TopCenter));
        handleList.append(new HandleItem(HandleItem::LeftCenter));
        handleList.append(new HandleItem(HandleItem::Center));
        handleList.append(new HandleItem(HandleItem::RightCenter));
        handleList.append(new HandleItem(HandleItem::BottomCenter));
    }


    //Set up pen  and brush
    QPen pen;
    pen.setWidth(1);
    pen.setCosmetic(true);
    pen.setColor(Qt::black);
    QBrush brush(Qt::NoBrush);
    // handlesize
    int HandelSize = 12;

    //Top left handle
    QPointF topLeftCorner = selectorFrameBounds().topLeft() + QPointF(-HandelSize/2,-HandelSize/2);
    topleftHandleRect  = QRectF(topLeftCorner,QSize(HandelSize,HandelSize));
    handleList[0]->setRect(topleftHandleRect);
    if(!handleList.isEmpty() && (!handlesAddedToScene))
    {
        handleList[0]->setPen(pen);
        handleList[0]->setBrush(QBrush(brush));
        ownerItem->scene()->addItem(handleList[0]);
        handleList[0]->setParentItem(ownerItem);

    }

    //Top right
    QPointF topRightCorner = selectorFrameBounds().topRight() + QPointF(-HandelSize/2,-HandelSize/2);
    topRightHandleRect  = QRectF(topRightCorner,QSize(HandelSize,HandelSize));
    handleList[1]->setRect(topRightHandleRect);
    if(!handleList.isEmpty() && (!handlesAddedToScene)){
        handleList[1]->setPen(pen);
        handleList[1]->setBrush(QBrush(brush));
        ownerItem->scene()->addItem(handleList[1]);
        handleList[1]->setParentItem(ownerItem);
    }

    //Bottom right
    QPointF bottomRightCorner = selectorFrameBounds().bottomRight() +  QPointF(-HandelSize/2,-HandelSize/2);
    bottomRightHandleRect  = QRectF(bottomRightCorner,QSize(HandelSize,HandelSize));
    handleList[2]->setRect(bottomRightHandleRect);
    if(!handleList.isEmpty() && (!handlesAddedToScene)){
        handleList[2]->setPen(pen);
        handleList[2]->setBrush(QBrush(brush));
        ownerItem->scene()->addItem(handleList[2]);
        handleList[2]->setParentItem(ownerItem);
    }

    //Bottom left
    QPointF bottomLeftCorner = selectorFrameBounds().bottomLeft() +  QPointF(-HandelSize/2,-HandelSize/2);
    bottomLeftHandleRect  = QRectF(bottomLeftCorner,QSize(HandelSize,HandelSize));
    handleList[3]->setRect(bottomLeftHandleRect);
    if(!handleList.isEmpty() && (!handlesAddedToScene)){
        handleList[3]->setPen(pen);
        handleList[3]->setBrush(QBrush(brush));
        ownerItem->scene()->addItem(handleList[3]);
        handleList[3]->setParentItem(ownerItem);
    }

    //TopCenter
    QPointF topCenterPoint = QPointF(selectorFrameBounds().center().rx()-HandelSize/2,selectorFrameBounds().top()-HandelSize/2);
    topCenterHandleRect  = QRectF(topCenterPoint,QSize(HandelSize,HandelSize));
    handleList[4]->setRect(topCenterHandleRect);
    if(!handleList.isEmpty() && (!handlesAddedToScene)){
        handleList[4]->setPen(pen);
        handleList[4]->setBrush(QBrush(brush));
        ownerItem->scene()->addItem(handleList[4]);
        handleList[4]->setParentItem(ownerItem);
    }


    //LeftCenter
    QPointF leftCenterPoint =  QPointF(selectorFrameBounds().left()-HandelSize/2,selectorFrameBounds().center().ry()-HandelSize/2);
    leftCenterHandleRect  = QRectF(leftCenterPoint,QSize(HandelSize,HandelSize));
    handleList[5]->setRect(leftCenterHandleRect);
    if(!handleList.isEmpty() && (!handlesAddedToScene)){
        handleList[5]->setPen(pen);
        handleList[5]->setBrush(QBrush(brush));
        ownerItem->scene()->addItem(handleList[5]);
        handleList[5]->setParentItem(ownerItem);
    }


    //Center
    QPointF centerPoint = QPointF(selectorFrameBounds().center().rx()-HandelSize/2,selectorFrameBounds().center().ry()-HandelSize/2);
    centerHandleRect  = QRectF(centerPoint,QSize(HandelSize,HandelSize));
    handleList[6]->setRect(centerHandleRect);
    if(!handleList.isEmpty() && (!handlesAddedToScene)){
        handleList[6]->setPen(pen);
        handleList[6]->setBrush(QBrush(brush));
        ownerItem->scene()->addItem(handleList[6]);
        handleList[6]->setParentItem(ownerItem);
    }


    //RightCenter
    QPointF rightCenterPoint = QPointF(selectorFrameBounds().right()-HandelSize/2,selectorFrameBounds().center().ry()-HandelSize/2);
    rightCenterHandleRect  = QRectF(rightCenterPoint,QSize(HandelSize,HandelSize));
    handleList[7]->setRect(rightCenterHandleRect);
    if(!handleList.isEmpty() && (!handlesAddedToScene)){
        handleList[7]->setPen(pen);
        handleList[7]->setBrush(QBrush(brush));
        ownerItem->scene()->addItem(handleList[7]);
        handleList[7]->setParentItem(ownerItem);
    }


    //BottomCenter
    QPointF bottomCenterPoint = QPointF(selectorFrameBounds().center().rx()-HandelSize/2,selectorFrameBounds().bottom()-HandelSize/2);
    bottomCenterHandleRect  = QRectF(bottomCenterPoint,QSize(HandelSize,HandelSize));
    handleList[8]->setRect(bottomCenterHandleRect);
    if(!handleList.isEmpty() && (!handlesAddedToScene)){
        handleList[8]->setPen(pen);
        handleList[8]->setBrush(QBrush(brush));
        ownerItem->scene()->addItem(handleList[8]);
        handleList[8]->setParentItem(ownerItem);
    }

    handlesAddedToScene = true;

    handlesAddedToScene = true;

}

void AbstractRectHandle::setOwnerItem(QGraphicsItem *value)
{
    ownerItem = value;
}

void AbstractRectHandle::drawHandlesIfNecessary()
{
    if(!ownerItem){
        qWarning() << "AbstractRectHandle : No ownerItem set. Not drawing any\
                      handle. Please call setOwnerItem on your AbstractRectHandle subclass";
                      return;
    }

    if(ownerItem->isSelected()){
        drawHandles();
        handlesAddedToScene = true;
    }else{

        //Remove the handles
        foreach (HandleItem * handleItem, handleList) {
            ownerItem->scene()->removeItem(handleItem);
        }
        qDeleteAll(handleList);
        handleList.clear();
        handlesAddedToScene = false;
    }

}
