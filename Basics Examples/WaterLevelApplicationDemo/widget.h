#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "watertank.h"
#include "indicator.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    Indicator * indicator;
    WaterTank * watertank;
};

#endif // WIDGET_H
