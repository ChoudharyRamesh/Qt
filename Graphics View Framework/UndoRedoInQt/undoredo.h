#ifndef UNDOREDO_H
#define UNDOREDO_H

#include<QUndoCommand>
#include<QPixmap>
#include<QLabel>
class AddPixmapCommand:public QUndoCommand
{
    // undo command is base class of  QUndoRedoFrameWork
public:
   explicit  AddPixmapCommand(QPixmap * pixmap,QLabel * label,QUndoCommand * parent = nullptr);
    ~AddPixmapCommand();
    void undo() override;
    void redo() override;

private:
    QPixmap  * pixmap;
    QLabel * label;

};
#endif // UNDOREDO_H
