#include "custommodel.h"

CustomModel::CustomModel(QObject *parent) : QAbstractListModel(parent)
{
    DragAndDropList<<"one"<<"two"
                  <<"three"<<"four";
    numberOfRows= 4;
}


int CustomModel::rowCount(const QModelIndex &parent) const
{
    return numberOfRows;
    Q_UNUSED(parent);
}

QVariant CustomModel::data(const QModelIndex &index, int role) const
{
    if(role==Qt::DisplayRole && index.isValid())
    {
        if(index.row()<DragAndDropList.size())
            return QVariant(DragAndDropList[index.row()]);
        else return  QVariant();
    }else return  QVariant();
}


Qt::ItemFlags CustomModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags defaultFlags = QAbstractListModel::flags(index);

    if (index.isValid())
        return Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled | defaultFlags;
    else
        return Qt::ItemIsDropEnabled | defaultFlags;
}

QStringList CustomModel::mimeTypes() const
{
    QStringList types;
    types<<"text/plain";
    return types;
}

QMimeData *CustomModel::mimeData(const QModelIndexList & indexes) const
{
    QStringList datalist;
    for(auto i:indexes)
        datalist.append(i.data(Qt::DisplayRole).toString());

    QMimeData * mimedata = new QMimeData;
    mimedata->setText(datalist.join(","));
    qDebug()<<mimedata->text();
    return  mimedata;
}


bool CustomModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    if(data->hasText())
    {
        if(parent.isValid())
        { // override
            setData(parent,data->text(),Qt::DisplayRole);
        }
        else
        {  //add new item
            DragAndDropList.append(data->text());
            numberOfRows++;
            emit dataChanged(index(numberOfRows-1),QModelIndex());
            emit layoutChanged();
        }
        return true;
    }
    return  true;
}


bool CustomModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role==Qt::DisplayRole && index.isValid())
    {  qDebug()<<"inside drop";
        DragAndDropList[index.row()]=value.toString();
        emit dataChanged(index,QModelIndex());
        return true;
    }
    return QAbstractListModel::setData(index,value,role);
}

