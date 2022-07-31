#ifndef SCENE_H
#define SCENE_H

#include<QGraphicsScene>
#include<QGraphicsRectItem>

class Scene:public QGraphicsScene
{
public:
    Scene(QObject * parent =nullptr);

private:
    QGraphicsRectItem * sceneRectangleItem;
};

#endif // SCENE_H
