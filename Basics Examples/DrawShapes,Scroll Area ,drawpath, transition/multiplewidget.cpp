#include "multiplewidget.h"

MultipleWidget::MultipleWidget(QWidget *parent) : QWidget(parent)
{
    vlayout = new QVBoxLayout;
    paintwidget  = new Widget;
    vlayout->addWidget(paintwidget);
    Widget * paintwidget2  = new Widget;
    vlayout->addWidget(paintwidget2);
    setLayout(vlayout);

}


QSize MultipleWidget::sizeHint() const
{
    return QSize(2*paintwidget->sizeHint());
}
