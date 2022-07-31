#ifndef PILLER_H
#define PILLER_H

#include<QGraphicsItemGroup>
#include<QGraphicsPixmapItem>
#include<QPropertyAnimation>

class Piller:public QObject ,public QGraphicsItemGroup
{
    Q_OBJECT
    Q_PROPERTY(qreal x READ x WRITE setX)
public:
    explicit Piller(int width,int height,double speed);
    ~Piller();
    qreal x() const;
    void StartPillerMoveAnimation();
    void StopPillerMoveAnimation();
    void PausePillerMoveAnimation();
    void ResumePillerMoveAnimation();

public slots:
    void setX(qreal x);
signals:
    void PcollisionHappened();

private:
    QGraphicsPixmapItem * topPiller ,* bottomPiller;
    QPropertyAnimation * xAnimation;
    int yRandPos,xRandPos;
    qreal m_x;
    int PillerGap;
    bool isBirdCollide(int x);

};

#endif // PILLER_H
