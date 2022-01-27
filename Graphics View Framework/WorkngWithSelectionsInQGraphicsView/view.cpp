#include "view.h"
#include<QMouseEvent>
#include<QPainterPath>
#include<QGraphicsRectItem>
#include<QDebug>

View::View(QWidget *parent) : QGraphicsView(parent),drawingSelection(false)
{
    //default initialization
    lastrect = nullptr;
    DrawGridLines = true;
    DrawAxis = true;
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
        lastrect->setBrush(QColor(0,0,255,80));
        lastrect->setPen(QPen(Qt::NoPen));
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
    painter->restore();
}

void View::drawForeground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    if(DrawGridLines)
    {
        painter->save();
        QPen pen(QColor::fromRgb(0,0,0,60));
        // to make same pen width constant across transformation
        // https://stackoverflow.com/questions/17075623/how-do-you-keep-qpen-pixel-width-the-same-when-zooming-in-a-qgraphicsview
       pen.setCosmetic(true);
        painter->setPen(pen);
        for(int i=0;i<30;i++)
            painter->drawLine(-300+(20*i),-300,-300+(20*i),300);

        for(int i=0;i<30;i++)
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



