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
        return QVariant(fruitlist.at(index.row()));

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

    case Qt::EditRole:
    {
        qDebug()<<"edit role in data "<<fruitlist.at(index.row());
        return QVariant(fruitlist.at(index.row()));
    }
    case Qt::ToolTipRole:
    {
        return QVariant(fruitlist.at(index.row()));
    }
    default:return QVariant();
    }
}

// for editing
bool ListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug()<<"edit role in set data";
    if(!index.isValid()) return false;
    if(role==Qt::EditRole)
    {
        if(fruitlist[index.row()]!=value.toString())
        {
            fruitlist[index.row()]=value.toString();
            return true;
        }
        else
            return  false;
    }
    return false;
}


Qt::ItemFlags ListModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
    {
        return QAbstractListModel::flags(index);
    }
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


