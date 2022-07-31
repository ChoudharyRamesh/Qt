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

    case Qt::WhatsThisRole:
        return QVariant(QIcon(":/images/"+index.data().toString()+".png"));

    case Qt::DecorationRole:
        return QVariant(QIcon(":/images/"+index.data().toString()+".png"));

    case CustomRoles::TextChangeRole:
    {
       qDebug()<<"TextChangeRole detected in set method";
        return QVariant(QString("this is through custom role"));
    }

    case Qt::ToolTipRole:
    {
        return QVariant(fruitlist.at(index.row()));
    }
    default:return QVariant();
    }
}


bool ListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(!index.isValid()) return false;
    if(role==CustomRoles::TextChangeRole)
    {
        qDebug()<<"TextChangeRole detected in setData method";
            if(fruitlist[index.row()]!=value.toString() && !value.toString().isEmpty())
            {
                fruitlist[index.row()]=value.toString();
                return true;
            }
            else
                return  false;
    }
    return false;
}


QHash<int, QByteArray> ListModel::roleNames() const
{
    QHash <int,QByteArray> roles;
    roles[TextChangeRole]= "IconRole";
    roles[NewUserRole]="NewUserRole";
    return roles;
}
