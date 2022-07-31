#include "view.h"
#include"resizableellipseitem.h"
#include "resizablepixmapitem.h"
#include "resizablerectitem.h"
#include "resizablestaritem.h"

View::View(QWidget *parent) : QGraphicsView(parent),drawingSelection(false)
{
    //default initialization
    lastrect = nullptr;
    DrawGridLines = true;
    DrawAxis = true;
    setAcceptDrops(true);
}


void View::mousePressEvent(QMouseEvent *event)
{
    QGraphicsItem * item = scene()->itemAt(mapToScene(event->pos()),transform());
    if(!item)
    {
        selectTopLeft  = event->pos();
        drawingSelection = true;
    }
    QGraphicsView::mousePressEvent(event);
}

void View::mouseMoveEvent(QMouseEvent *event)
{
    if(drawingSelection)
    {
        QRect selectionregion = QRect(selectTopLeft,event->pos());
        QPainterPath path;
        path.addRect(selectionregion);
        scene()->setSelectionArea(mapToScene(path));
        if(lastrect!=nullptr){ scene()->removeItem(lastrect); delete lastrect; }
        lastrect = scene()->addRect(QRectF(mapToScene(selectTopLeft),mapToScene(event->pos())).normalized());
        lastrect->setBrush(QColor(0,255,255,150));
        lastrect->setPen(QPen(Qt::cyan));
    }
    QGraphicsView::mouseMoveEvent(event);
}

void View::mouseReleaseEvent(QMouseEvent *event)
{
    if(drawingSelection)
    {
        QGraphicsItem * itemTORemove = lastrect;
        if(lastrect)
        {
            scene()->removeItem(itemTORemove);
            delete itemTORemove;
            lastrect =nullptr;
        }
    }
    drawingSelection = false;
    QGraphicsView::mouseReleaseEvent(event);
}

void View::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    painter->save();
    painter->setBrush(Qt::yellow);
    // painter will draw on scene not on view
    painter->drawRect(-300,-300,600,600);
    if(DrawAxis)
    {
        QPen pen(QColor::fromRgb(0,0,0,80));
        pen.setWidth(2);
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawLine(0,-300,0,300);
        painter->drawLine(-300,0,300,0);
    }
    painter->restore();
}

void View::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    if(DrawGridLines)
    {
        painter->save();
        QPen pen(QColor::fromRgb(0,0,0,60));
        pen.setCosmetic(true);
        painter->setPen(pen);
        for(int i=0;i<=30;i++)
            painter->drawLine(-300+(20*i),-300,-300+(20*i),300);

        for(int i=0;i<=30;i++)
            painter->drawLine(-300,-300+(20*i),300,-300+(20*i));

        painter->restore();
    }
    if(DrawAxis)
    {
        QPen pen(QColor::fromRgb(0,0,0,80));
        pen.setWidth(2);
        pen.setCosmetic(true);
        painter->setPen(pen);
        painter->setBrush(Qt::NoBrush);
        painter->drawLine(0,-300,0,300);
        painter->drawLine(-300,0,300,0);
    }
    else
    {
        QGraphicsView::drawForeground(painter,rect);
    }
}

bool View::getDrawAxis() const
{
    return DrawAxis;
}

void View::setDrawAxis(bool value)
{
    if(DrawAxis != value)
    {
        DrawAxis = value;
        scene()->update();
    }
}

bool View::getDrawGridLines() const
{
    return DrawGridLines;
}

void View::setDrawGridLines(bool value)
{
    if(DrawGridLines != value)
    {
        DrawGridLines = value;
        scene()->update();
    }
}




void View::dropEvent(QDropEvent *event)
{
    if(event->mimeData()->property("Key").canConvert(QMetaType::Int)){

           int key = event->mimeData()->property("Key").toInt();


           switch (key) {
           case 10:{
               //Ellipse
               ResizableEllipseItem * ellipse = new ResizableEllipseItem();
               ellipse->setRect(0,0,80,50);
               ellipse->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
               ellipse->setBrush(Qt::gray);
               scene()->addItem(ellipse);

               ellipse->setPos( mapToScene(event->pos()) -QPointF((ellipse->boundingRect().width()/2),
                                                          (ellipse->boundingRect().height()/2))) ;

           }
               break;
           case 20:{
               //Qt Quick Image
               ResizablePixmapItem * pixItem = new ResizablePixmapItem(QPixmap(":/images/quick.png"));
               pixItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
               scene()->addItem(pixItem);
               pixItem->setPos( mapToScene(event->pos())) ;
           }
               break;
           case 30:{
               //Rectangle
               ResizableRectItem * rectItem = new ResizableRectItem();
               rectItem->setRect(0,0,80,50);
               rectItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
               rectItem->setBrush(Qt::gray);
               scene()->addItem(rectItem);
               rectItem->setPos( mapToScene(event->pos())-QPointF((rectItem->boundingRect().width()/2),
                                                          (rectItem->boundingRect().height()/2))) ;
           }
               break;
           case 40:{
               //Star
               ResizableStarItem * starItem = new ResizableStarItem();
               starItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
               starItem->setBrush(Qt::gray);
               scene()->addItem(starItem);
               starItem->setPos( mapToScene(event->pos())) ;
           }
               break;

           }



           event->acceptProposedAction();
       }else{
           QGraphicsView::dropEvent(event);
       }
}



void View::dragMoveEvent(QDragMoveEvent *event)
{
    if(event->mimeData()->property("Key").canConvert(QMetaType::Int)){
         event->acceptProposedAction();
     }else{
         QGraphicsView::dragMoveEvent(event);
     }
}
