#include "view.h"
#include "gameoveritem.h"
#include<QSizePolicy>
#include<QScrollBar>
#include<QScreen>

View::View(QWidget *parent)
    : QGraphicsView(parent)
{
    if(QSysInfo::productType()=="windows")
    {
        setGeometry(1060,20,830,950);
    }
    else
    {  // android
        setGeometry(QGuiApplication::screens().at(0)->geometry());
        setWindowState(Qt::WindowMaximized);
    }

    verticalScrollBar()->setEnabled(false);
    horizontalScrollBar()->setEnabled(false);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);



    bird = new Bird(QPixmap(":/images/RedBird4.png"));
    label  = new QLabel;
    playPauseButton = new QPushButton(label);
    restartbutton = new QPushButton(label);
    timerlabel = new QLabel(label);
    gameMeter = new QGraphicsProxyWidget;
    sky= new QGraphicsPixmapItem(QPixmap(":/images/background.jpg").scaled(skyPixmapSize));
    scene = new Scene(this);
    scene->setSceneRect(sceneRectGemoetry);
    setScene(scene);

    setGeometries();

    sky->setPos(skyPixmapPosition);
    scene->addItem(sky);
    scene->addItem(bird);

    // scene->addLine(0,-height()/2,0,height());
    // scene->addLine(-width()/2,0,width(),0);

    playPauseButton->setIcon(QIcon(QPixmap(":/images/pause.png").scaled(playPauseButton->height(),playPauseButton->height())));
    restartbutton->setIcon(QIcon(QPixmap(":/images/restart.png").scaled(restartbutton->height(),restartbutton->height())));

    isResetInProcess=false;
    timer.setInterval(10);
    playPauseButton->setGeometry(playPauseButtonGeometry);
    restartbutton->setGeometry(restartButtonGeometry);
    label->setPalette(QPalette(QColor(Qt::blue)));
    label->setBackgroundRole(QPalette::Background);

    timerlabel->setText("00:00:000");
    timerlabel->setGeometry(timerlabelGeometry);
    timerlabel->setAlignment(Qt::AlignCenter);
    timerlabel->setFont(QFont("consals",timerTextSize));

    gameMeter->setWidget(label);
    gameMeter->setZValue(1);
    gameMeter->setGeometry(gameMeterProxyItemGeometry);
    gameMeter->setPos(gameMeterProxyItemPosition);
    scene->addItem(gameMeter);
    connect(scene,&Scene::ScollisionHappened,this,&View::stopGame);

    connect(playPauseButton,&QPushButton::clicked,[=]()
    {
        if(!isGamePaused && !isGameEnded)
         {
            pauseGame();
            playPauseButton->setIcon(QIcon(QPixmap(":/images/resume.png").scaled(playPauseButton->height(),playPauseButton->height())));
            playPauseButton->clearFocus();
         }
        else if(!isGameEnded)
         {
            resumeGame();
            playPauseButton->setIcon(QIcon(QPixmap(":/images/pause.png").scaled(playPauseButton->height(),playPauseButton->height())));
            playPauseButton->clearFocus();
        }
    });


    connect(restartbutton,&QPushButton::clicked,this,&View::restartGame);


    connect(&timer,&QTimer::timeout,[=]()
    {
        timerlabel->setText(clock.elaspedTime().toString("mm:ss:zzz"));
    });

    connect(this,&View::WindowSizeChanged,[=]()
    {
        // if(isGameEnded )
        setGeometries();
    });
    // meter geometry

    startGame();
    setWindowFlag(Qt::WindowStaysOnTopHint);
}

void View::startGame()
{
    isGamePaused = false;
    isGameEnded = false;

    bird->hide();
    isResetInProcess=true;
    QTimer::singleShot(100,[=]()
    {  auto it1 = scene->addText("3",QFont("consolas",countDownNumberSize));
        it1->setPos(-it1->boundingRect().width()/2,-it1->boundingRect().height()/2);
        it1->setDefaultTextColor(Qt::red);
        QTimer::singleShot(1000,[=]()
        {  scene->removeItem(it1); delete it1;
            auto it2 = scene->addText("2",QFont("consolas",countDownNumberSize));
            it2->setPos(-it2->boundingRect().width()/2,-it2->boundingRect().height()/2);
            it2->setDefaultTextColor(Qt::red);
            QTimer::singleShot(1000,[=]()
            {   scene->removeItem(it2); delete it2;
                bird->show();
                auto it3= scene->addText("1",QFont("consolas",countDownNumberSize));
                it3->setPos(-it3->boundingRect().width()/2,-it3->boundingRect().height()/2);
                it3->setDefaultTextColor(Qt::red);
                scene->startPillerSpawnTimer();
                QTimer::singleShot(1000,[=]()
                {  scene->removeItem(it3); delete it3;
                    bird->setY(0);
                    bird->setRotation(0);
                    bird->wingFlipTimer->start();
                    bird->fallBirdToGround();
                    // scene->startPillerSpawnTimer();
                    clock.restart();
                    timer.start();
                    restartbutton->clearFocus();
                    isResetInProcess=false;
                    isGamePaused = false;
                    isGameEnded = false;
                });
            });
        });
    });

    // experiment  code end
}

void View::pauseGame()
{
    if(!isGamePaused && isGameEnded==false)
    {
        isGamePaused=true;
        bird->wingFlipTimer->stop();
        scene->stopPillerSpawnTimer();
        if(bird->yAnimation->state()==QAbstractAnimation::Running)
            bird->yAnimation->pause();
        if(bird->rotationAnimation->state()==QAbstractAnimation::Running)
            bird->rotationAnimation->pause();
        emit scene->pausePillers();

        timer.stop();
        clock.pause();
    }
}

void View::resumeGame()
{
    if(isGamePaused && isGameEnded==false)
    {
        isGamePaused=false;

        scene->startPillerSpawnTimer();
        bird->wingFlipTimer->start();
        if(bird->yAnimation->state()==QAbstractAnimation::Paused)
            bird->yAnimation->resume();
        if(bird->rotationAnimation->state()==QAbstractAnimation::Paused)
            bird->rotationAnimation->resume();
        emit scene->resumePillers();
        clock.resume();
        timer.start();
    }
}


void View::stopGame()
{
    if(isGameEnded==false )
    {  isGamePaused=true;
        scene->stopPillerSpawnTimer();
        emit scene->pausePillers();
        bird->yAnimation->stop();
        bird->rotationAnimation->stop();
        bird->wingFlipTimer->stop();
        timer.stop();
        clock.pause();
        auto it =new GameOverItem(clock.elaspedTime());
        connect(it->restart,&QPushButton::clicked,[=]()
        {
            if(isGameEnded)
                restartGame();
        });

        connect(it->exit,&QPushButton::clicked,[=]()
        {
            qDebug()<<"exit occured";
            if(it==nullptr)qDebug()<<"over item is nullptr";
            QApplication::exit(0);
        });
        scene->addItem(it);
        timerlabel->setText("00:00:000");
        isGameEnded = true;
    }
}




View::~View()
{

}


void View::keyPressEvent(QKeyEvent *event)
{
    if(!isGamePaused)
        if(event->key()==Qt::Key_Space)
            bird->shootBirdUp();

    if(event->key()==Qt::Key_P && !isGameEnded && !isGamePaused)
    {
        pauseGame();
        playPauseButton->setIcon(QIcon(QPixmap(":/images/resume.png").scaled(playPauseButton->height(),playPauseButton->height())));
    }
    if(event->key()==Qt::Key_R && !isGameEnded && isGamePaused)
    {
        resumeGame();
        playPauseButton->setIcon(QIcon(QPixmap(":/images/pause.png").scaled(playPauseButton->height(),playPauseButton->height())));
    }
}


void View::mousePressEvent(QMouseEvent *event)
{
    if(!isGamePaused)
        if(event->button()==Qt::LeftButton)
            bird->shootBirdUp();
    QGraphicsView::mousePressEvent(event);
}


void View::setGeometries()
{

    if(QSysInfo::productType()=="windows")
    {
        int w=width();
        int h=height();
        qDebug()<<w<<" "<<h;
        sceneRectGemoetry.setRect(-w/2,-h/2,w,h);
        skyPixmapSize.setWidth(w);
        skyPixmapSize.setHeight(h);
        skyPixmapPosition.setX(-w/2);
        skyPixmapPosition.setY(-h/2);

        int mw=160,mh=80;
        gameMeterProxyItemGeometry.setRect(-mw/2,-mh/2,mw,mh);
        gameMeterProxyItemPosition.setX(w/2-gameMeterProxyItemGeometry.width());
        gameMeterProxyItemPosition.setY(-h/2);
        timerlabelGeometry.setRect(0,0,gameMeterProxyItemGeometry.width(),gameMeterProxyItemGeometry.height()/2);
        playPauseButtonGeometry.setRect(
                    gameMeterProxyItemGeometry.width()/4-gameMeterProxyItemGeometry.width()/6,
                    gameMeterProxyItemGeometry.height()/2,
                    gameMeterProxyItemGeometry.width()/3,
                    gameMeterProxyItemGeometry.height()/3
                    );
        restartButtonGeometry.setRect(
                    gameMeterProxyItemGeometry.width()/2+playPauseButtonGeometry.x(),
                    gameMeterProxyItemGeometry.height()/2,
                    gameMeterProxyItemGeometry.width()/3,
                    gameMeterProxyItemGeometry.height()/3
                    );
        timerTextSize = 20;

        countDownNumberSize=h/10;

        scene->setSceneRect(sceneRectGemoetry);
        sky->setPixmap(QPixmap(":/images/background.jpg").scaled(skyPixmapSize));
        sky->setPos(skyPixmapPosition);
        playPauseButton->setGeometry(playPauseButtonGeometry);
        restartbutton->setGeometry(restartButtonGeometry);
        timerlabel->setGeometry(timerlabelGeometry);
        timerlabel->setFont(QFont("consals",timerTextSize));
        gameMeter->setGeometry(gameMeterProxyItemGeometry);
        gameMeter->setPos(gameMeterProxyItemPosition);
    }
    else
    {
        int w=width();
        int h=height();
        qDebug()<<w<<" "<<h;
        sceneRectGemoetry.setRect(-w/2,-h/2,w,h);
        skyPixmapSize.setWidth(w);
        skyPixmapSize.setHeight(h);
        skyPixmapPosition.setX(-w/2);
        skyPixmapPosition.setY(-h/2);

        int mw=300,mh=200;
        gameMeterProxyItemGeometry.setRect(-mw/2,-mh/2,mw,mh);
        gameMeterProxyItemPosition.setX(w/2-gameMeterProxyItemGeometry.width());
        gameMeterProxyItemPosition.setY(-h/2);
        timerlabelGeometry.setRect(0,0,gameMeterProxyItemGeometry.width(),gameMeterProxyItemGeometry.height()/2);
        playPauseButtonGeometry.setRect(
                    gameMeterProxyItemGeometry.width()/4-gameMeterProxyItemGeometry.width()/6,
                    gameMeterProxyItemGeometry.height()/2,
                    gameMeterProxyItemGeometry.width()/3,
                    gameMeterProxyItemGeometry.height()/3
                    );
        restartButtonGeometry.setRect(
                    gameMeterProxyItemGeometry.width()/2+playPauseButtonGeometry.x(),
                    gameMeterProxyItemGeometry.height()/2,
                    gameMeterProxyItemGeometry.width()/3,
                    gameMeterProxyItemGeometry.height()/3
                    );
        timerTextSize = 20;

        countDownNumberSize=h/10;

        scene->setSceneRect(sceneRectGemoetry);
        sky->setPixmap(QPixmap(":/images/background.jpg").scaled(skyPixmapSize));
        sky->setPos(skyPixmapPosition);
        playPauseButton->setGeometry(playPauseButtonGeometry);
        restartbutton->setGeometry(restartButtonGeometry);
        timerlabel->setGeometry(timerlabelGeometry);
        timerlabel->setFont(QFont("consals",timerTextSize));
        gameMeter->setGeometry(gameMeterProxyItemGeometry);
        gameMeter->setPos(gameMeterProxyItemPosition);
    }

}

void View::resizeEvent(QResizeEvent *event)
{
    scene->resetScene();
    bird->setY(0);
    bird->setRotation(0);
    emit WindowSizeChanged(); Q_UNUSED(event);
    bird->setY(0);
    bird->setRotation(0);
}


void View::restartGame()
{
    if(!isResetInProcess)
    {   isResetInProcess=true;
        if(!isGameEnded) stopGame();
        scene->resetScene();
        bird->hide();

        QTimer::singleShot(100,[=]()
        {  auto it1 = scene->addText("3",QFont("consolas",countDownNumberSize));
            it1->setPos(-it1->boundingRect().width()/2,-it1->boundingRect().height()/2);
            it1->setDefaultTextColor(Qt::red);
            QTimer::singleShot(1000,[=]()
            {  scene->removeItem(it1); delete it1;
                auto it2 = scene->addText("2",QFont("consolas",countDownNumberSize));
                it2->setPos(-it2->boundingRect().width()/2,-it2->boundingRect().height()/2);
                it2->setDefaultTextColor(Qt::red);
                QTimer::singleShot(1000,[=]()
                {   scene->removeItem(it2); delete it2;
                    bird->show();
                    auto it3= scene->addText("1",QFont("consolas",countDownNumberSize));
                    it3->setPos(-it3->boundingRect().width()/2,-it3->boundingRect().height()/2);
                    it3->setDefaultTextColor(Qt::red);
                    scene->startPillerSpawnTimer();
                    QTimer::singleShot(1000,[=]()
                    {  scene->removeItem(it3); delete it3;
                        bird->setY(0);
                        bird->setRotation(0);
                        bird->wingFlipTimer->start();
                        bird->fallBirdToGround();
                        clock.restart();
                        timer.start();
                        restartbutton->clearFocus();
                        isResetInProcess=false;
                        isGamePaused = false;
                        isGameEnded = false;
                    });
                });
            });
        });
    }
}
