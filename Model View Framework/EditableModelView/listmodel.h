#ifndef LISTMODEL_H
#define LISTMODEL_H

#include<QAbstractListModel>
#include<QTimer>

class ListModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit ListModel(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setRowCount(int count);

    //for editing
     bool setData(const QModelIndex &index, const QVariant &value, int role) override;
      Qt::ItemFlags flags(const QModelIndex &index) const override;

//private:
    int rows;
    QStringList fruitlist;
    QTimer * timer;

};

#endif // LISTMODEL_H
