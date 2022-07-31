#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    CustomModel * model = new CustomModel(this);

    // add models to view
    QHBoxLayout * h = new QHBoxLayout(this);

    QListView * listview = new QListView(this);
    listview->setDragEnabled(true);
    listview->setAcceptDrops(true);

    QTableView * tableview = new QTableView(this);
    tableview->setDragEnabled(true);
    tableview->setAcceptDrops(true);

    QTreeView * treeview = new QTreeView(this);
    treeview->setDragEnabled(true);
    treeview->setAcceptDrops(true);

//    connect(model,&QAbstractListModel::dataChanged,tableview,[=](){
//        listview->setModel(NULL);
//        tableview->setModel(NULL);
//        treeview->setModel(NULL);
//        listview->setModel(model);
//        tableview->setModel(model);
//        treeview->setModel(model);
//    });

    tableview->setModel(model);
    treeview->setModel(model);
    listview->setModel(model);

    // same selection model
  //  listview->setSelectionMode(QAbstractItemView::MultiSelection);
    tableview->setSelectionModel(listview->selectionModel());
    treeview->setSelectionModel(listview->selectionModel());

    h->addWidget(listview);
    h->addWidget(tableview);
    h->addWidget(treeview);
}

Widget::~Widget()
{
}

