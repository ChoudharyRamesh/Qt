#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include<QItemDelegate>
   // or
#include<QStyledItemDelegate>
#include<QComboBox>
#include<QPainter>
#include<QColor>
#include<QIcon>

class ComboboxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit ComboboxDelegate(QObject *parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    QStringList fruitlist;
};

#endif // COMBOBOXDELEGATE_H
