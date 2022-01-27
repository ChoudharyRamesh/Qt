#include "widget.h"
#include "ui_widget.h"
#include<QKeyEvent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    undoStack = new QUndoStack(this);
    QPixmap * pix = new QPixmap(QPixmap("C:/Users/Nishant Choudhary/Downloads/RedBird/Green_1920x1080.jpg").scaled(200,400));
    undoStack->push(new AddPixmapCommand(pix,ui->label));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->matches(QKeySequence::Undo))
        undoStack->undo();
    else   if(event->matches(QKeySequence::Redo))
        undoStack->redo();
   else QWidget::keyPressEvent(event);
}
