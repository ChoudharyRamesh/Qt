#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QStandardItemModel * model = new QStandardItemModel(this);

    // create standard items
    QStandardItem * item1 = new QStandardItem();
    item1->setText("can drag ,can drop");
    item1->setDragEnabled(true);
    item1->setDropEnabled(true);
    QStandardItem * item2 = new QStandardItem();
    item2->setText("can't drag, can drop");
    item2->setDragEnabled(false);
    item2->setDropEnabled(true);
    QStandardItem * item3 = new QStandardItem();
    item3->setText("can drag,can't drop");
    item3->setDragEnabled(true);
    item3->setDropEnabled(false);
    QStandardItem * item4 = new QStandardItem();
    item4->setText("can't drag,can't drop");
    item4->setDragEnabled(false);
    item4->setDropEnabled(false);

    //add standard items to model
    model->appendRow(item1);
    model->appendRow(item2);
    model->appendRow(item3);
    model->appendRow(item4);

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

    listview->setModel(model);
    tableview->setModel(model);
    treeview->setModel(model);

    // same selection model
    tableview->setSelectionModel(listview->selectionModel());
    treeview->setSelectionModel(listview->selectionModel());

    h->addWidget(listview);
    h->addWidget(tableview);
    h->addWidget(treeview);
}

Widget::~Widget()
{
}

