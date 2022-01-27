#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QAbstractTableModel>
#include<QHBoxLayout>
#include<QVariant>
#include<QVector>
#include<QTableWidget>
#include"stardelegate.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    QVector<QVector<QVariant>> data;
    QTableWidget *tableWidget;
};
#endif // WIDGET_H
