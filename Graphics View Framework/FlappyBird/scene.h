#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include"piller.h"
#include<QTimer>
#include<QGraphicsProxyWidget>
#include<QLabel>

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = nullptr);
    void resetScene();
    void stopPillerSpawnTimer();
    void startPillerSpawnTimer();

signals:
    void pausePillers();
    void resumePillers();
    void ScollisionHappened();
private:
    double PillerSpeed;
    QTimer * pillerSpawnTimer;
};

#endif // SCENE_H
