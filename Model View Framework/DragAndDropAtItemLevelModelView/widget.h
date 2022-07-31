#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QModelIndex>
#include<QListView>
#include<QHBoxLayout>
#include<QTableView>
#include<QTreeView>
#include<QDebug>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

};
#endif // WIDGET_H
