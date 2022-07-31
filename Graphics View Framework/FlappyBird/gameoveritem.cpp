#include "gameoveritem.h"
#include<QtDebug>
#include<QSettings>
#include<QStandardPaths>
#include <QSysInfo>

GameOverItem::GameOverItem(QTime elapsedTime )
{

    setZValue(2);
    QString str,str1;
    int scoreDivideFactor = 400;
    int w,h,highScoretextSize,textSize;

    if(QSysInfo::productType()=="windows")
    {
        w=300;
        h=500;
        highScoretextSize=10;
        textSize=20;
    }
    else
    {
        //3:5
        w=500;
        h=833;
        highScoretextSize=10;
        textSize=20;
    }

    baselabel =new QLabel;
    pixlabel =new   QLabel(baselabel);
    bestScoreLabel = new QLabel(pixlabel);
    textlabel =new   QLabel(baselabel);
    restart = new QPushButton(baselabel);
    exit = new QPushButton("Exit",baselabel);
    setWidget(baselabel);


    // geometries
    setGeometry(QRect(-w/2,-h/2,w,h));
    pixlabel->setGeometry(0,0,w,(h/5)*3);
    bestScoreLabel->setGeometry(0,((pixlabel->height()/5)*4),w,pixlabel->height()/5);
    textlabel->setGeometry(0,pixlabel->height(),w,(3)*(h/10));
    restart->setGeometry(w/12,pixlabel->height()+textlabel->height(),w/3,(1)*(h/10)-10);
    exit->setGeometry(7*(w/12),pixlabel->height()+textlabel->height(),w/3,(1)*(h/10)-10);

    //decoration
    baselabel->setPalette(QPalette(QColor::fromRgb(0,255,255,150)));
    pixlabel->setPixmap(QPixmap(":/images/game-over.png").scaled(pixlabel->width()-20,pixlabel->height()-20));
    pixlabel->setAlignment(Qt::AlignCenter);
    restart->setIcon(QIcon(QPixmap(":/images/restart.png").scaled(restart->height(),restart->height())));

    bestScoreLabel->setStyleSheet("color: rgb(255, 170, 0);");
    bestScoreLabel->setAlignment(Qt::AlignHCenter);
    QFont font1("consolas",highScoretextSize);
    font1.setBold(true);
    bestScoreLabel->setFont(font1);

    textlabel->setStyleSheet("color: rgb(255, 0, 255);");
    QFont font("consolas",textSize);
    textlabel->setWordWrap(true);
    font.setBold(true);
    textlabel->setFont(font);
    textlabel->setAlignment(Qt::AlignCenter);

    //highScore ,load setting
    //    QSettings setting("FlappyBirdGame","FLAPPY_BIRD_GAME");
    //    setting.beginGroup("GameOverItem");
    //    highScore = setting.value("score").toString();
    //    setting.endGroup();

    QString mPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    QString filename = "flappySetting.ini";
    mPath = mPath + "/" + filename;
    QSettings setting(mPath , QSettings::NativeFormat);
    setting.beginGroup("GameOverItem");
    highScore = setting.value("score").toString();
    setting.endGroup();

    qint64 timeMsec = elapsedTime.msec()+elapsedTime.second()*1000
            +elapsedTime.minute()*60*1000+elapsedTime.hour()*60*60*1000;
    if(highScore.toInt()< (timeMsec/scoreDivideFactor-4))
    {
        int temp = timeMsec/scoreDivideFactor-4;
        if(temp<0)temp=0;
        bestScoreLabel->setText("New High Score\n"+QString::number(temp));
    }
    else  bestScoreLabel->setText("");

    int temp = timeMsec/scoreDivideFactor-4;
    if(temp<0)temp=0;
    textlabel->setText("Score:"+QString::number(temp)
                       +"\nBest Score:"+highScore
                       +"\nTime:"+elapsedTime.toString("hh:mm:ss:zzz"));

}

GameOverItem::~GameOverItem()
{
    //save setting

    QString mPath = QStandardPaths::writableLocation(QStandardPaths::ConfigLocation);
    QString filename = "flappySetting.ini";
    mPath = mPath + "/" + filename;
    QSettings setting(mPath , QSettings::NativeFormat);
    setting.beginGroup("GameOverItem");
    setting.setValue("score",highScore);
    setting.endGroup();
    setting.sync();

    //    QSettings setting("FlappyBirdGame","FLAPPY_BIRD_GAME");
    //    setting.beginGroup("GameOverItem");
    //    setting.setValue("score",highScore);
    //    setting.endGroup();
}



















