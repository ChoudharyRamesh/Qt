#ifndef LINE_H
#define LINE_H
#include<QGraphicsLineItem>
#include<QPainter>

class Line:public QGraphicsLineItem
{
public:
    Line(qreal x1, qreal y1, qreal x2, qreal y2, QGraphicsItem *parent = nullptr);
    Line(const QLineF &line, QGraphicsItem *parent = nullptr);
    Line(QPointF point1,QPointF point2,QPen pen,QGraphicsItem *parent = nullptr);
    Line(QGraphicsItem *parent = nullptr);

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // LINE_H
