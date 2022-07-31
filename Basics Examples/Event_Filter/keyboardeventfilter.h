#ifndef KEYBOARDEVENTFILTER_H
#define KEYBOARDEVENTFILTER_H

#include <QObject>
#include<QKeyEvent>
#include<QDebug>

class KeyboardEventFilter : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardEventFilter(QObject *parent = nullptr);
  bool eventFilter(QObject *watched, QEvent *event)override;
signals:

};

#endif // KEYBOARDEVENTFILTER_H
