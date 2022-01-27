#include "scene.h"
#include"bird.h"
#include "gameoveritem.h"
#include<QtDebug>

Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    PillerSpeed=0;
    pillerSpawnTimer = new QTimer(this);
    connect(pillerSpawnTimer,&QTimer::timeout,this,[=]()
    {
        if(PillerSpeed<=50) PillerSpeed+=0.5;
         pillerSpawnTimer->setInterval(pillerSpawnTimer->interval()-0.000005);
        auto it = new Piller(width(),height(),PillerSpeed);
        addItem(it);
        it->StartPillerMoveAnimation();
        connect(this,&Scene::pausePillers,it,&Piller::PausePillerMoveAnimation);
        connect(this,&Scene::resumePillers,it,&Piller::ResumePillerMoveAnimation);
        connect(it,&Piller::PcollisionHappened,[=](){emit ScollisionHappened(); });
    });

}

void Scene::stopPillerSpawnTimer()
{
    pillerSpawnTimer->stop();
}

void Scene::startPillerSpawnTimer()
{
  pillerSpawnTimer->setInterval(1400);
  pillerSpawnTimer->start();
}


void Scene::resetScene()
{
    // clear pillers
    QList<QGraphicsItem *> pillerlist = items();
    for(auto it:pillerlist)
    {
        if(dynamic_cast<Piller *>(it))
        {
            removeItem(it);
            delete it;
        }
        if(dynamic_cast<GameOverItem *>(it))
        {
            removeItem(it);
            delete it;
        }
    }
}

