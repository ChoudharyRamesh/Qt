#include "keyboardeventfilter.h"

KeyboardEventFilter::KeyboardEventFilter(QObject *parent) : QObject(parent)
{

}

bool KeyboardEventFilter::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::KeyPress)
    {
        qDebug()<<"event is hijacked in filter ,key pressed";
        QKeyEvent * keyevent = static_cast<QKeyEvent *>(event);
        QString numbers = QString("1234567890");
        if(numbers.indexOf(keyevent->text()) != -1)
        {
            qDebug()<<"number is filtered out";
             return true;
        }
        else
            return QObject::eventFilter(watched,event);
    }
    else
        return QObject::eventFilter(watched,event);
}
