#ifndef HANDLEITEM_H
#define HANDLEITEM_H

#include <QGraphicsRectItem>

class HandleItem : public QGraphicsRectItem
{
public:

    enum Position
    {
        TopLeft,TopCenter,TopRight,
        LeftCenter,Center,RightCenter,
       BottomLeft ,BottomCenter,BottomRight
    };
    explicit HandleItem(Position position);


    // QGraphicsItem interface
protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
private:
    Position handlePosition;
};

#endif // HANDLEITEM_H
