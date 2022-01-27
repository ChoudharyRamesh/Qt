#ifndef BIRD_H
#define BIRD_H
#include<QGraphicsPixmapItem>
#include<QTimer>
#include<QPropertyAnimation>
#include<QGraphicsScene>

class Bird:public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
    Q_PROPERTY(qreal rotation READ rotation WRITE setRotation)
    Q_PROPERTY(qreal y READ y WRITE setY)
public:
    Bird(QPixmap pixmap);
    ~Bird();
    qreal rotation() const;
    qreal y() const;
    QPropertyAnimation *yAnimation;
    QPropertyAnimation *rotationAnimation;
    QTimer * wingFlipTimer;

public slots:
    void setRotation(qreal rotation);
    void setY(qreal y);
    void rotateTo(const qreal & end , const int & duration,const QEasingCurve & curve);
    void shootBirdUp();
    void fallBirdToGround();

private:

    void updateBirdWingState();
     int WingPixmapNumber;

    qreal m_rotation;
    qreal m_y;
    qreal groundPosition;
     int upShootLength;


};

#endif // BIRD_H
