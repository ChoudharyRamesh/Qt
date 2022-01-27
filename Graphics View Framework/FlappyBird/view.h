#ifndef VIEW_H
#define VIEW_H

#include"scene.h"
#include "bird.h"
#include "mytimer.h"
#include<QMouseEvent>
#include<QPushButton>
#include<QDebug>
#include<QKeyEvent>
#include<QGraphicsTextItem>
#include<QStyle>
#include<QGraphicsView>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    void startGame();
    void pauseGame();
    void resumeGame();
    void stopGame();
    void restartGame();
    ~View();

private:
    Scene * scene;
    Bird * bird;
    bool isGamePaused;
    QGraphicsPixmapItem * sky;
    QLabel * label;
    QLabel * timerlabel;
    QGraphicsProxyWidget * gameMeter;
    QPushButton * playPauseButton ,* restartbutton;
    MyTimer  clock;
    bool isResetInProcess;
    bool isGameEnded;
    QTimer timer;
    QRect  gameMeterProxyItemGeometry,timerlabelGeometry ,sceneRectGemoetry;
    QRect playPauseButtonGeometry , restartButtonGeometry ;
    QSize skyPixmapSize;
    QPoint skyPixmapPosition,gameMeterProxyItemPosition;
    int timerTextSize , countDownNumberSize;
    void setGeometries();

public:
signals:
   void  WindowSizeChanged();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // VIEW_H
