#ifndef QGRAPHICSNODEITEM_H
#define QGRAPHICSNODEITEM_H

#include<QGraphicsSceneMouseEvent>
#include <QGraphicsEllipseItem>
#include<QGraphicsLineItem>
#include<QBrush>
#include<QFont>
#include<QPen>

class QGraphicsNodeItem : public QGraphicsEllipseItem
{
public:
    explicit QGraphicsNodeItem(int radius ,int nodeNumber,
    QPointF nodeCenter,QPen pen = QPen(),QBrush brush = QBrush(),QGraphicsItem *parent = nullptr);
    QPointF getNodeCenter()const;
    // return pointer to lineItem if any of connected lineItem match input line
    QGraphicsLineItem *checkConnectedLine(const QLineF & line);
    void addLine(QGraphicsLineItem * line,int whichPoint);

private:
    QList<QPair<int,QGraphicsLineItem * >> connectedLines;
    QGraphicsTextItem * textitem;
    QPointF nodeCenter;
    int radius;
    QColor textColor="black";

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
};


#endif // QGRAPHICSNODEITEM_H
