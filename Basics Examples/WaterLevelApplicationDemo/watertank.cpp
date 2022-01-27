#include "watertank.h"

WaterTank::WaterTank(QWidget *parent)
  : QWidget(parent),waterHeight(50),timer(new QTimer(this))
{
  setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
//  setMinimumSize(QSize(0,0));
//  setMaximumSize(QSize(16777215,16777215));
  timer->setInterval(70);
  connect(timer,&QTimer::timeout,[=](){
      if(waterHeight>=340){  timer->stop(); }
      else if(waterHeight>=290){ emit danger(); playDangerAlert(); }
      else if(waterHeight>=231){ emit  warning(); playWarningAlert(); } //261
      else  if(waterHeight<=230){ emit  normal(); } //260
      waterHeight+=1;
      update();
  });
  timer->start();
}


void WaterTank::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen mpen;
    mpen.setWidth(3);
    mpen.setColor(Qt::black);

    painter.setPen(mpen);
    painter.setBrush(Qt::gray); // fill color

    // paint watertank
    painter.setBrush(Qt::black);
    painter.drawLine(10,10,10,340); // left
    painter.drawLine(10,340,210,340); // bottom
    painter.drawLine(210,10,210,340); //right
    painter.setBrush(Qt::blue);
    painter.drawRect(10,340,200,-waterHeight);
}

void WaterTank::playWarningAlert()
{  static bool isPlaying=false;
    if(isPlaying==false)
    { player.setMedia(QUrl("file:///C:/mycode/Qt Quick/WaterLevelApplicationDemo/Sounds/warning.mp3"));
        connect(&player,&QMediaPlayer::mediaStatusChanged,&player,&QMediaPlayer::play);
        player.setVolume(80);
        player.play();
        isPlaying=true;
    }
}

void WaterTank::playDangerAlert()
{ static bool isPlaying=false;
    if(isPlaying==false)
    {
        disconnect(&player,&QMediaPlayer::mediaStatusChanged,&player,&QMediaPlayer::play);
        player.setMedia(QUrl("file:///C:/mycode/Qt Quick/WaterLevelApplicationDemo/Sounds/danger.wav"));
        connect(&player,&QMediaPlayer::mediaStatusChanged,&player,&QMediaPlayer::play);
        player.setVolume(80);
        player.play();
        isPlaying=true;
    }
}

QSize WaterTank::sizeHint() const
{
    return QSize(220,360); //200,340
}
