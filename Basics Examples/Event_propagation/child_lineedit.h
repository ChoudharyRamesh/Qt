#ifndef CHILD_LINEEDIT_H
#define CHILD_LINEEDIT_H
#include<parent_lineedit.h>

class Child_LineEdit : public Parent_LineEdit
{
public:
    Child_LineEdit(QWidget * parent=nullptr);

protected:
    void keyPressEvent(QKeyEvent *event)override;
};

#endif // CHILD_LINEEDIT_H
