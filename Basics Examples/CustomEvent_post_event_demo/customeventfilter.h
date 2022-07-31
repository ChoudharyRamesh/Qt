#ifndef CUSTOMEVENTFILTER_H
#define CUSTOMEVENTFILTER_H

#include <QObject>
#include<QMouseEvent>
#include<QDebug>

class CustomEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit CustomEventFilter(QObject *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event);
};

#endif // CUSTOMEVENTFILTER_H
