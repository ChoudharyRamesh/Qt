#include "qgraphicsnodeitem.h"

QGraphicsNodeItem::QGraphicsNodeItem(int radius , int nodeNumber
                                     ,QPointF nodeCenter, QPen pen, QBrush brush,QGraphicsItem * parent)
    : QGraphicsEllipseItem(parent)
{
    this->radius=radius;
    this->nodeCenter = nodeCenter;
    setRect(nodeCenter.x()-radius,nodeCenter.y()-radius,2*radius,2*radius);
    setPen(pen);
    setBrush(brush);
    setFlags(QGraphicsItem::ItemIsMovable);


    textitem = new QGraphicsTextItem(QString::number(nodeNumber),this);
    QFont font;
    font.setPixelSize(radius);
    textitem->setFont(font);
    textitem->setDefaultTextColor(textColor);
    textitem->setPos(nodeCenter.x()-textitem->boundingRect().width()/2,
                     nodeCenter.y()-textitem->boundingRect().height()/2);

}


void QGraphicsNodeItem::addLine(QGraphicsLineItem *line, int whichPoint)
{
    this->connectedLines.append(QPair<int,QGraphicsLineItem *>(whichPoint,line));
}

QPointF QGraphicsNodeItem::getNodeCenter() const{ return  nodeCenter;}

QGraphicsLineItem * QGraphicsNodeItem::checkConnectedLine(const QLineF & line)
{
    for(int i=0;i<connectedLines.size();i++)
    {
        QLineF linein = connectedLines.at(i).second->line();
        if( (line.p1()==linein.p1() || line.p1()==linein.p2())
                && (line.p2()==linein.p1() || line.p2()==linein.p2()))
          {
             return  connectedLines.at(i).second;
          }
    }
    return nullptr;
}


void QGraphicsNodeItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseMoveEvent(event);
    QGraphicsLineItem  * currentLine;
    QPointF tpos = textitem->pos();
    QRectF rect = textitem->boundingRect();
    QPointF newPoint = mapToScene(tpos.x()+rect.width()/2,tpos.y()+rect.height()/2);

    for(int i=0;i<connectedLines.size();i++)
    {
        currentLine = connectedLines.at(i).second;
        if(connectedLines.at(i).first==1)  currentLine->setLine(QLineF(newPoint,currentLine->line().p2()));
        else currentLine->setLine(QLineF(currentLine->line().p1(),newPoint));
    }
}
