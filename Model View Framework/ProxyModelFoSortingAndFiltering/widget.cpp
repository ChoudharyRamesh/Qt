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
    // proxy model for sorting and filtering
    setMinimumSize(QSize(800,800));
    QVBoxLayout * vlayout = new QVBoxLayout(this);
    listview = new ListView(this);
    listview->setEditTriggers(QAbstractItemView::NoEditTriggers);
    vlayout->addWidget(listview);
    setLayout(vlayout);
    QStringList fruitlist;
    fruitlist<<"apple"<<"avocado"<<"banana"<<"blueberries"<<"cucumber"<<
               "eggfruit"<<"fig"<<"grape"<<"mango"<<"pear"<<"pineapple"<<"watermellon";
    QStringListModel * stringmodel = new QStringListModel(fruitlist,this);
    QSortFilterProxyModel * proxymodel = new QSortFilterProxyModel(this);
    proxymodel->setSourceModel(stringmodel);
    listview->setModel(proxymodel);
    QLineEdit * lineedit = new QLineEdit(this);
    vlayout->addWidget(lineedit);
    vlayout->setStretch(0,8);
    vlayout->setStretch(1,1);
    connect(lineedit,&QLineEdit::textChanged,[=]()
     {
         proxymodel->setFilterRegExp(lineedit->text());
     });

}

Widget::~Widget()
{

}

