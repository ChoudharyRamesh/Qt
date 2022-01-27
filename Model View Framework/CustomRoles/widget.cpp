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
    listview = new ListView(this);
    listmodel = new ListModel(this);
    listview->setModel(listmodel);

    QPushButton * CustomRoleButton = new QPushButton("Check CustomRole",this);
    QVBoxLayout * vlayout = new QVBoxLayout(this);
    vlayout->addWidget(listview);
    vlayout->addWidget(CustomRoleButton);
    vlayout->setStretch(0,8); vlayout->setStretch(1,1);

    connect(CustomRoleButton,&QPushButton::clicked,[=]()
    {
        QVariant temp =  listmodel->data(listview->currentIndex(),listmodel->TextChangeRole);
        listmodel->setData(listview->currentIndex(),temp,listmodel->TextChangeRole);
        // this is not the right way to use custom role
        // custom role can be used in view or model class to interact with each other

    });

}

Widget::~Widget()
{

}

