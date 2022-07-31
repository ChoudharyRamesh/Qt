#ifndef CUSTOMTREEMODEL_H
#define CUSTOMTREEMODEL_H

#include<QAbstractItemModel>
#include<QStringList>
#include<QDebug>
#include<familytree.h>
#include<QInputDialog>

class CustomTreeModel :public QAbstractItemModel
{
public:
    explicit CustomTreeModel(QObject * parent = nullptr );

    // QAbstractItemModel interface
public:
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    // for header
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    bool setHeaderData(int section, Qt::Orientation orientation, const QVariant &value, int role) override;
   // for editing
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
private:
    QStringList familyname;
    FamilyTree * rootNode;
    QStringList HeaderDataStorage; // only horizontal header
};

#endif // CUSTOMTREEMODEL_H
