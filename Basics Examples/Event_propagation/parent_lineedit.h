#ifndef PARENT_LINEEDIT_H
#define PARENT_LINEEDIT_H
#include <QWidget>
#include<QDebug>
#include<QKeyEvent>
#include<QLineEdit>

class Parent_LineEdit : public QLineEdit
{
    Q_OBJECT

public:
    Parent_LineEdit(QWidget *parent = nullptr);
    ~Parent_LineEdit();

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *event)override;

};
#endif // PARENT_LINEEDIT_H
