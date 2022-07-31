#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPixmap>
#include<QDebug>
#include<QPen>
#include<QPainter>
#include<QFont>
#include<QFile>
#include<QPainterPath>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


protected:
    void paintEvent(QPaintEvent *event) override;

public:
    QSize sizeHint() const override;
};
#endif // WIDGET_H
