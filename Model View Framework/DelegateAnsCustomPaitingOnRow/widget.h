#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "listmodel.h"
#include "listview.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    ListView * listview;
    ListModel * listmodel;
};
#endif // WIDGET_H
