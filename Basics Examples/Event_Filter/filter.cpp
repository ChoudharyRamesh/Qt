#include "filter.h"

Filter::Filter(QObject *parent) : QObject(parent)
{

}

bool Filter::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress
            || event->type()==QEvent::MouseButtonDblClick)
    {
        qDebug()<<"event is hijacked in filter";
        return true;
    }
    else
        return QObject::eventFilter(watched,event);
}
