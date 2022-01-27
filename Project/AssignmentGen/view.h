#ifndef QGRAPHICSCUSTOMVIEW_H
#define QGRAPHICSCUSTOMVIEW_H

#include <QWidget>
#include<QGraphicsView>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);
};

#endif // QGRAPHICSCUSTOMVIEW_H
