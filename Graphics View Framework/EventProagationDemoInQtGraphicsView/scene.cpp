#include "scene.h"
#include<QDebug>
#include<QGraphicsSceneMouseEvent>
Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
}

void Scene::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"mouse event in"<<"QGraphicsScene";
   Q_UNUSED(event);
    QGraphicsScene::keyPressEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<"key event in"<<"QGraphicsScene "<<event->scenePos();  // pos() will not work here;
    Q_UNUSED(event);
    QGraphicsScene::mousePressEvent(event);
}
