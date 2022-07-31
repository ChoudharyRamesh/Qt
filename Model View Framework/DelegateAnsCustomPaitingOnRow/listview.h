#ifndef LISTVIEW_H
#define LISTVIEW_H

#include<QAbstractItemView>
#include<QListView>

class ListView : public QListView
{
    Q_OBJECT
public:
    explicit ListView(QWidget *parent = nullptr);
signals:
    void selectionChanged(const QItemSelection &selected, const QItemSelection &deselected) override;

};

#endif // LISTVIEW_H
