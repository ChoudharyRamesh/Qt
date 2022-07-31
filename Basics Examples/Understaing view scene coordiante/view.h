#ifndef VIEW_H
#define VIEW_H

#include<QGraphicsView>
#include<QTimeLine>
#include<QWheelEvent>
#include<QMouseEvent>
#include<QtMath>

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    void resetScenePos();
    ~View();
private:
    int _numScheduledScalings=0;
    bool isMousPressed=false;
    QPointF lastpoint;
    QPointF sceneMoved=QPointF(0,0);

private slots:
    // smoothly zoom view , code taken from https://wiki.qt.io/Smooth_Zoom_In_QGraphicsView
    void scalingTime(qreal);
    void animFinished();

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};


#endif // VIEW_H
