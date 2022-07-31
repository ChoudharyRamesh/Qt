#include "indicator.h"

Indicator::Indicator(QWidget *parent)
    : QWidget(parent),
      redActive(false),
      greenActive(false),
      yellowActive(false),
      lightsOn(true)
{
    setSizePolicy(QSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred));
//    setMinimumSize(QSize(0,0));
//    setMaximumSize(QSize(16777215,16777215));
    activateDanger();
    timer = new QTimer(this);
    timer->setInterval(300);
    connect(timer,&QTimer::timeout,[=](){
        toggleLights();
    });
    timer->start();

}

Indicator::~Indicator()
{
}

void Indicator::toggleLights()
{
    if(!lightsOn)
        lightsOn=true;
    else
     lightsOn=false;
    update();
}

void Indicator::paintEvent(QPaintEvent *event)
{
    painter = new QPainter(this);
    mpen.setWidth(3);
    mpen.setColor(Qt::black);

    painter->setPen(mpen);
    painter->setBrush(Qt::gray); // fill color

    painter->drawRect(QRect(0,0,120,340));

    if(redActive)
    {
        painter->setBrush(lightsOn==true ? Qt::red :Qt::black);
        painter->drawEllipse(QRect(10,10,100,100));

        painter->setBrush(Qt::black);
        painter->drawEllipse(QRect(10,120,100,100));

        painter->setBrush(Qt::black);
        painter->drawEllipse(QRect(10,230,100,100));
    }

    else if(greenActive)
    {
        painter->setBrush(Qt::black);
        painter->drawEllipse(QRect(10,10,100,100));

        painter->setBrush(lightsOn==true ? Qt::green :Qt::black);
        painter->drawEllipse(QRect(10,120,100,100));

        painter->setBrush(Qt::black);
        painter->drawEllipse(QRect(10,230,100,100));

    }

   else if(yellowActive)
    {
        painter->setBrush(Qt::black);
        painter->drawEllipse(QRect(10,10,100,100));

        painter->setBrush(Qt::black);
        painter->drawEllipse(QRect(10,120,100,100));

        painter->setBrush(lightsOn==true ? Qt::yellow :Qt::black);
        painter->drawEllipse(QRect(10,230,100,100));
    }

    painter->end();
}

QSize Indicator::sizeHint() const
{
    return QSize(120,340);
}

void Indicator::activateNormal()
{
    greenActive = true;
    redActive = yellowActive = false;
}

void Indicator::activateWarning()
{
    yellowActive = true;
    redActive = greenActive = false;
}

void Indicator::activateDanger()
{
    redActive = true;
    yellowActive = greenActive = false;
}
