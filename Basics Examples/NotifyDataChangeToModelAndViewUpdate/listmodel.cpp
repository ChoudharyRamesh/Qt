#include "listmodel.h"
#include<QColor>
#include<QSize>
#include<QFont>
#include<QIcon>
#include<QTime>
#include<QDebug>

ListModel::ListModel(QObject *parent) : QAbstractListModel(parent)
{
    fruitlist<<"apple"<<"avocado"<<"banana"<<"blueberries"<<"cucumber"<<"eggfruit"
              <<"fig"<<"grape"<<"mango"<<"pear"<<"pineapple"<<"watermellon";
     rows = fruitlist.size();
    //internal data source
    // jab eis class ka data change hota hai to signal (datachanged automatic call ho jata hai )
    QTimer::singleShot(8000,[&](){ fruitlist[1]="changed"; });

    timer = new QTimer(this);
    timer->setInterval(1000);
    //notify view ( outer data source )
    connect(timer,&QTimer::timeout,[=]()
    {
        QModelIndex zeroIndex = index(0,0);
        emit dataChanged(zeroIndex,zeroIndex,{Qt::DisplayRole}); // starting index , end index
        // this signal is recieved in view where this model is connected
        // and take appropriate action based on QModelIndex
    });
    timer->start();


}

void ListModel::setRowCount(int count)
{
    if(count>=0)rows=count;
}

int ListModel::rowCount(const QModelIndex & parent) const
{
    return rows;
    Q_UNUSED(parent);
}

QVariant ListModel::data(const QModelIndex &index, int role) const
{
    switch (role)
    {
    case Qt::DisplayRole :
        if(index.row()==0)
        {
            //to demonstrate how to notify model when view is changed)
            return  QVariant(QTime::currentTime().toString("hh:mm:ss AP"));
        }
        else return QVariant(fruitlist.at(index.row()));

    case Qt::TextColorRole:
        return QVariant(QColor(Qt::red));

    case Qt::FontRole:
        return QVariant(QFont("consolas",20,QFont::Bold,false));

    case Qt::BackgroundColorRole:
        return QVariant(QColor(136,200,127,127));

    case Qt::TextAlignmentRole:
        return  QVariant(Qt::AlignmentFlag(Qt::AlignCenter));

    case Qt::SizeHintRole:
        return QVariant(QSize(10,100));

    case Qt::DecorationRole:
        return QVariant(QIcon(":/images/"+index.data().toString()+".png"));

    case Qt::WhatsThisRole:
        return QVariant(QIcon(":/images/"+index.data().toString()+".png"));

    case Qt::ToolTipRole:
    {
        return QVariant(fruitlist.at(index.row()));
    }
    default:return QVariant();
    }
}

