#include "widget.h"
#include<QAbstractItemView>
#include<QVBoxLayout>
#include<QDebug>
#include<QTableView>
#include<QTreeView>
#include<QFileSystemModel>
#include<QStringListModel>
#include<QSortFilterProxyModel>
#include<QLineEdit>
#include<QDebug>
#include<QPushButton>
#include<QHBoxLayout>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    setMinimumSize(QSize(800,800));
    QVBoxLayout * vlayout = new QVBoxLayout(this);
    listview = new ListView(this);
    vlayout->addWidget(listview);
    setLayout(vlayout);
    listmodel = new ListModel(this);
    listview->setModel(listmodel);

}

Widget::~Widget()
{

}

