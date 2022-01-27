#include "undoredo.h"

AddPixmapCommand::AddPixmapCommand(QPixmap * pixmap,QLabel * label,QUndoCommand * parent )
    :QUndoCommand(parent)
{
    this->pixmap=pixmap;
    this->label=label;
}

AddPixmapCommand::~AddPixmapCommand()
{

}


void AddPixmapCommand::undo()
{
   label->clear();
}

void AddPixmapCommand::redo()
{
    if(pixmap)
    label->setPixmap(*pixmap);
}
