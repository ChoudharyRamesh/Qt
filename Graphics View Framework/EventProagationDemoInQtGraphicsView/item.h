#ifndef ITEM_H
#define ITEM_H

#include<QGraphicsRectItem>
// graphics item don't handle signal and slots by default thats why it does not has QObject parent

class Item : public QGraphicsRectItem
{
public:
    explicit Item();

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
};

#endif // ITEM_H
