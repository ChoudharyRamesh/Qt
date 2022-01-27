#ifndef SCENE_H
#define SCENE_H

#include <QObject>
#include<QGraphicsScene>
#include<QKeyEvent>
#include<QGraphicsSceneMouseEvent>
#include "textitem.h"
#include "line.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(bool * isPenEditingEnabled,int * penWidth,bool * isPen,QRectF * maxSceneRect,QObject *parent = nullptr);

 protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

 public:
    TextItem * textItem=nullptr;
    TextItem * sideTextItem=nullptr;
    TextItem * pageNumber=nullptr;
    TextItem * Date=nullptr;
    TextItem * header=nullptr;
private:
    QPointF lastPoint;
    QPen pen;
    int adjustment;
    bool drawing=false;

    //control
    bool * isPenEditingEnabled; //disable pen,enable pen,disable text, enable text
    int * penWidth; //set pen width
    bool * isPen; //pen eraser selection
   QRectF * maxSceneRect;

};

#endif // SCENE_H
