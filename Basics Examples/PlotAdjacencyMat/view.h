#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include<QGraphicsView>
#include<QTimeLine>
#include<QWheelEvent>
#include<QMouseEvent>
#include<QGraphicsScene>
#include<QRandomGenerator>
#include<QtMath>
#include "qgraphicsnodeitem.h"
#include"amgraph.h"

class View : public QGraphicsView
{
    Q_OBJECT

public:
    View(QWidget *parent = nullptr);
    void plotAdjacencyMatrix(QList<QList<int>> matrix);
    ~View();

private slots:
    // smoothly zoom view , code taken from https://wiki.qt.io/Smooth_Zoom_In_QGraphicsView
    void scalingTime(qreal);
    void animFinished();

private:
    QGraphicsScene scene;
    int _numScheduledScalings=0;
    bool isMousPressed=false;
    QPointF lastpoint;
    QColor bidirectionalEdgeColor="white";
    QColor nodeBrushColor = "white";
    QColor backgroundColor = "black";
    int nodePenWidth=7;
    int linePenWidth=3;
    int nodeRadius=30;
    QList<QColor> colors;

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};


#endif // VIEW_H
