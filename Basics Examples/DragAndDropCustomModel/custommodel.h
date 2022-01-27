#ifndef CustomModel_H
#define CustomModel_H

#include<QAbstractItemModel>
#include<QDebug>
#include<QMimeData>
#include<QStandardItem>
#include<QDataStream>

class CustomModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit CustomModel(QObject *parent = nullptr);

signals:

public:
    int rowCount(const QModelIndex &parent=QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
    QStringList mimeTypes() const override;
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

private:
    QStringList DragAndDropList;
    int numberOfRows;

};

#endif // CustomModel_H
