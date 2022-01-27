#include "scrollarea.h"
ScrollArea::ScrollArea(QWidget *parent) : QScrollArea(parent)
{
    multiwidget=new MultipleWidget;
    setWidget(multiwidget);
    QScroller::grabGesture(multiwidget,QScroller::TouchGesture);
}

QSize ScrollArea::sizeHint() const
{
    return QSize(900,900);
}
