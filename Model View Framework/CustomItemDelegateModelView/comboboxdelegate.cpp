#include "comboboxdelegate.h"

ComboboxDelegate::ComboboxDelegate(QObject *parent) : QStyledItemDelegate(parent)
{
    fruitlist<<"apple"<<"avocado"<<"banana"<<"blueberries"<<"cucumber"<<"eggfruit"
            <<"fig"<<"grape"<<"mango"<<"pear"<<"pineapple"<<"watermellon";
}


QWidget *ComboboxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.row()==2)
    {
        QComboBox * editor = new QComboBox(parent);
        for(int i=0;i<fruitlist.size();i++)
        {
            editor->addItem(QIcon(":/images/"+fruitlist[i]+".png"),fruitlist[i]);
        }
        return editor;
    }
    else
        return QStyledItemDelegate::createEditor(parent,option,index);
}

void ComboboxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.row()==2)
    {
        QComboBox * temp = static_cast<QComboBox *>(editor);
        temp->setCurrentIndex(index.row());
    }
    else {
        return QStyledItemDelegate::setEditorData(editor,index);
    }
}

void ComboboxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.row()==2)
    {
        QComboBox * temp = static_cast<QComboBox *>(editor);
        model->setData(index,temp->currentText());
    }
    else
        return QStyledItemDelegate::setModelData(editor,model,index);
}

void ComboboxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.row()==2)
    {
        Q_UNUSED(editor);
        Q_UNUSED(index);
        editor->setGeometry(option.rect);
    }
    else
      return QStyledItemDelegate::updateEditorGeometry(editor,option,index);
}
