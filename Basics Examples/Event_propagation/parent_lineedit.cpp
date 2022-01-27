#include "parent_lineedit.h"

Parent_LineEdit::Parent_LineEdit(QWidget * parent)
    : QLineEdit(parent)
{

}

Parent_LineEdit::~Parent_LineEdit()
{

}

void Parent_LineEdit::keyPressEvent(QKeyEvent *event)
{
      qDebug()<<"event is in parent ";
      QLineEdit::keyPressEvent(event);
}

