#ifndef FILTER_H
#define FILTER_H

#include <QObject>
#include<QEvent>
#include<QDebug>

class Filter : public QObject
{
    Q_OBJECT
public:
    explicit Filter(QObject *parent = nullptr);    
    bool eventFilter(QObject *watched, QEvent *event)override;
};

#endif // FILTER_H
