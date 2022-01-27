#include "child_lineedit.h"

Child_LineEdit::Child_LineEdit(QWidget * parent)
    :Parent_LineEdit(parent)
{
}

void Child_LineEdit::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"event is in child ";
    if(event->key()==Qt::Key_Delete)
    {
        event->accept();
        clear();
    }
    else
    {
        Parent_LineEdit::keyPressEvent(event);
    }
}
