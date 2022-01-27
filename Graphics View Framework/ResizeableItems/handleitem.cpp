#include "handleitem.h"
#include "resizablerectitem.h"
#include <QGraphicsSceneMouseEvent>
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QDebug>

HandleItem::HandleItem(Position position) :
    handlePosition(position)
{
    setFlag(QGraphicsItem::ItemIsMovable);

}

void HandleItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    switch (handlePosition) {

    case TopLeft:
    {
        AbstractRectHandle * rectItem = dynamic_cast<AbstractRectHandle *>( parentItem());
        if(rectItem)
        {

            QRectF boundingFrameRect = rectItem->selectorFrameBounds();

            boundingFrameRect.setTop(event->pos().y()); //resize
            boundingFrameRect.setLeft(event->pos().x()); // resize
            if(boundingFrameRect.isValid())
                rectItem->setSelectorFrameBounds(boundingFrameRect);

        }

    }
        break;

    case TopRight:
    {
         AbstractRectHandle * rectItem = dynamic_cast<AbstractRectHandle *>( parentItem());
        if(rectItem){

            QRectF boundingFrameRect = rectItem->selectorFrameBounds();

            boundingFrameRect.setTop(event->pos().y());
            boundingFrameRect.setRight(event->pos().x());
            if(boundingFrameRect.isValid())
                rectItem->setSelectorFrameBounds(boundingFrameRect);
        }

    }
        break;

    case BottomRight:
    {
        AbstractRectHandle * rectItem = dynamic_cast<AbstractRectHandle *>( parentItem());
        if(rectItem){

            QRectF boundingFrameRect = rectItem->selectorFrameBounds();

            boundingFrameRect.setRight(event->pos().x());
            boundingFrameRect.setBottom(event->pos().y());
            if(boundingFrameRect.isValid())
                rectItem->setSelectorFrameBounds(boundingFrameRect);

        }

    }
        break;

    case BottomLeft:
    {
        AbstractRectHandle * rectItem = dynamic_cast<AbstractRectHandle *>( parentItem());
        if(rectItem){

            QRectF boundingFrameRect = rectItem->selectorFrameBounds();

            boundingFrameRect.setBottom(event->pos().y());
            boundingFrameRect.setLeft(event->pos().x());
            if(boundingFrameRect.isValid())
                rectItem->setSelectorFrameBounds(boundingFrameRect);

        }

    }
        break;

    case TopCenter:
    {
        AbstractRectHandle * rectItem = dynamic_cast<AbstractRectHandle *>( parentItem());
        if(rectItem){

            QRectF boundingFrameRect = rectItem->selectorFrameBounds();

            boundingFrameRect.setTop(event->pos().y());

            if(boundingFrameRect.isValid())
                rectItem->setSelectorFrameBounds(boundingFrameRect);
        }

    }
        break;


    case LeftCenter:
    {
       AbstractRectHandle * rectItem = dynamic_cast<AbstractRectHandle *>( parentItem());
        if(rectItem){

            QRectF boundingFrameRect = rectItem->selectorFrameBounds();
            boundingFrameRect.setLeft(event->pos().x());
            if(boundingFrameRect.isValid())
                rectItem->setSelectorFrameBounds(boundingFrameRect);
             scene()->views().at(0)->update();
        }

    }
        break;


    case Center:
    {
       AbstractRectHandle * rectItem = dynamic_cast<AbstractRectHandle *>( parentItem());
        if(rectItem){

            QRectF boundingFrameRect = rectItem->selectorFrameBounds();

            if(boundingFrameRect.isValid())
                rectItem->setSelectorFrameBounds(boundingFrameRect);
        }

    }
        break;


    case RightCenter:
    {
      AbstractRectHandle * rectItem = dynamic_cast<AbstractRectHandle *>( parentItem());
        if(rectItem){

            QRectF boundingFrameRect = rectItem->selectorFrameBounds();

            boundingFrameRect.setRight(event->pos().x());
            if(boundingFrameRect.isValid())
                rectItem->setSelectorFrameBounds(boundingFrameRect);

        }

    }
        break;



    case BottomCenter:
    {
       AbstractRectHandle * rectItem = dynamic_cast<AbstractRectHandle *>( parentItem());
        if(rectItem){

            QRectF boundingFrameRect = rectItem->selectorFrameBounds();

            boundingFrameRect.setBottom(event->pos().y());
            if(boundingFrameRect.isValid())
                rectItem->setSelectorFrameBounds(boundingFrameRect);
        }

    }
        break;

    }

}
