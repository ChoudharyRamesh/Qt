#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout * h = new QHBoxLayout(this);
    CustomTreeView * view = new CustomTreeView(this);
    CustomTreeModel *model = new CustomTreeModel(this);
    view->setModel(model);
    h->addWidget(view);

}

Widget::~Widget()
{
}

