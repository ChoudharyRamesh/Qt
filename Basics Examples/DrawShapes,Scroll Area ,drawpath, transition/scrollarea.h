#ifndef SCROLLAREA_H
#define SCROLLAREA_H

#include <QWidget>
#include<QScrollArea>
#include<QScroller>
#include "multiplewidget.h"


class ScrollArea : public QScrollArea
{
    Q_OBJECT
public:
    explicit ScrollArea(QWidget *parent = nullptr);
public:
    QSize sizeHint() const override;
private:
     MultipleWidget * multiwidget;
};

#endif // SCROLLAREA_H
