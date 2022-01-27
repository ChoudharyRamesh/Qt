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
#include<comboboxdelegate.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    setMinimumSize(QSize(800,800));
    QVBoxLayout * vlayout = new QVBoxLayout(this);
    listview = new ListView(this);
    vlayout->addWidget(listview);
    setLayout(vlayout);
    listmodel = new ListModel(this);
    ComboboxDelegate * delegate = new ComboboxDelegate(this);
    listview->setItemDelegate(delegate);
    listview->setModel(listmodel);

}

Widget::~Widget()
{

}

