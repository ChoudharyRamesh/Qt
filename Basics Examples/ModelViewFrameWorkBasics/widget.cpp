#include "widget.h"

/*
 * each item in model view architecture or model view data structure is represented by row and column
 * each item must also have parent
 * the root item is to top level parent in the entire data structure
 * root item is imaginary item .
 * the list like data structure is a particular case where root item has one child table eith only one column of data.
 * an item is represtend by QModelIndex class object
 * */

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    QStandardItemModel * model = new QStandardItemModel(this);

    // create standard items
    QStandardItem * item1 = new QStandardItem();
    item1->setText("item1");
    QStandardItem * item2 = new QStandardItem();
    item2->setText("item2");
    QStandardItem * item3 = new QStandardItem();
    item3->setText("item3");

    //add standard items to model
    model->appendRow(item1);
    model->appendRow(item2);
    model->appendRow(item3);


    QModelIndex  index1 =  model->index(0,0,QModelIndex());
    QModelIndex  index2 =  model->index(1,0,QModelIndex());
    QModelIndex  index3 =  model->index(2,0,QModelIndex());
    QModelIndex  index4 =  model->index(3,0,QModelIndex());


    qDebug()<<index1.isValid()<<index2.isValid()<<index3.isValid()<<index4.isValid();
    // index 4 is invalid bcz no data is inserted yet in row number four

    /*
     * QModelIndex() method is gimic for place holder for root item , so
     * this can be used as parent for first level items in model
     * the index of root item is invalid bcz it doesn't exist
     * */
    qDebug()<<"Index of root item "<<QModelIndex().isValid();


//    // add models to view
//    QHBoxLayout * h = new QHBoxLayout(this);
//    QListView * listview = new QListView(this);
//    listview->setModel(model);
//    h->addWidget(listview);

//    //making table like view
//    QStandardItem * item4 = new QStandardItem();
//    item4->setText("item4");
//    model->setItem(2,1,item4);
//    QHBoxLayout * h = new QHBoxLayout(this);
//    QTableView * tableview = new QTableView(this);
//    tableview->setModel(model);
//    h->addWidget(tableview);


    //making tree like view
    QStandardItem * item4 = new QStandardItem();
    item4->setText("item4");
    item3->appendRow(item4);

    QStandardItem * item5 = new QStandardItem();
    item5->setText("item5");
    model->setItem(0,1,item5);

    QHBoxLayout * h = new QHBoxLayout(this);
    QTreeView * treeview = new QTreeView(this);
    treeview->setModel(model);
    h->addWidget(treeview);

}


Widget::~Widget()
{
}

