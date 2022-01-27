#ifndef MULTIPLEWIDGET_H
#define MULTIPLEWIDGET_H

#include "widget.h"
#include<QVBoxLayout>

class MultipleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MultipleWidget(QWidget *parent = nullptr);
public:
    QSize sizeHint() const override;
private:
    QVBoxLayout  * vlayout;
    Widget * paintwidget;
};

#endif // MULTIPLEWIDGET_H
