#include "customeventfilter.h"

CustomEventFilter::CustomEventFilter(QObject *parent) : QObject(parent)
{

}


bool CustomEventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress)
    {
        qDebug()<<watched->objectName()<<" clicked "<<event->type();
        return true;
    }
    else
        return  QObject::eventFilter(watched,event);
}
