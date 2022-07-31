#include "listview.h"
#include<QLineEdit>
#include<QDebug>
#include<listmodel.h>
#include<QMap>

ListView::ListView(QWidget *parent) : QListView(parent)
{
    setIconSize(QSize(70,100));
    setEditTriggers(QAbstractItemView::AllEditTriggers);
    connect(this,&ListView::selectionChanged,[=]()
    {
        qDebug()<<"selection changed";
        qDebug()<<currentIndex().data(Qt::DisplayRole);
    });

}

