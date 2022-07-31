#include "customtreeview.h"
#include <QHeaderView>
#include<QMouseEvent>
#include<QDebug>
#include<QStringListModel>
#include<QStandardItemModel>
#include<QScrollBar>

CustomTreeView::CustomTreeView(QWidget *parent) : QTreeView(parent)
{
    setHeaderHidden(false);
    lineedit = new LineEdit(this);
    lineedit->setVisible(false);
    connect(this->header(),&QHeaderView::sectionDoubleClicked,this,[=](int logicalIndex)
    {
        lineedit->setText(model()->headerData(logicalIndex,Qt::Horizontal,Qt::EditRole).toString());
        int x1 = header()->sectionPosition(logicalIndex);
        int w1 = header()->sectionSize(logicalIndex);
        QRect rect(header()->x()+x1-horizontalScrollBar()->value(),header()->y(),w1,header()->height());
        lineedit->currentLogicalIndex=logicalIndex;
        lineedit->setGeometry(rect);
        lineedit->setVisible(true);
        lineedit->setFocus();
    });

    connect(this->header(),&QHeaderView::sectionResized,this,[=](int logicalIndex,int oldsize,int newsize)
    { if(lineedit->currentLogicalIndex==logicalIndex)
        {int x1 = header()->sectionPosition(logicalIndex);
            int w1 = header()->sectionSize(logicalIndex);
            QRect rect(header()->x()+x1,header()->y(),w1,header()->height());
            lineedit->setGeometry(rect);
        }
        Q_UNUSED(oldsize);
        Q_UNUSED(newsize);
    });

    connect(this->horizontalScrollBar(),&QScrollBar::valueChanged,this,[=](int value)
    {
        int x1 = header()->sectionPosition(lineedit->currentLogicalIndex);
        int w1 = header()->sectionSize(lineedit->currentLogicalIndex);
        QRect rect(header()->x()-value+x1,header()->y(),w1,header()->height());
        lineedit->setGeometry(rect);
    });

    // this signal is emitted when lineEdit loses foucs or when return key pressed
    // so when return key is pressed and if you want to make lineedit invisible at the end then
    // this connection will invoke again after return key
    // if you want signal only for return key then use return pressed signal

    connect(this->lineedit,&LineEdit::editingFinished,this,[=]()
    {
        if(lineedit->currentLogicalIndex!=-1)
        {
            model()->setHeaderData(lineedit->currentLogicalIndex,Qt::Horizontal,lineedit->text(),Qt::EditRole);
            lineedit->clear();
            lineedit->currentLogicalIndex=-1;
            lineedit->setVisible(false);  // again invoke
        }
    });

    // or

//    connect(this->lineedit,&LineEdit::returnPressed,this,[=]()
//    {
//        if(lineedit->currentLogicalIndex!=-1)
//        {  model()->setHeaderData(lineedit->currentLogicalIndex,Qt::Horizontal,lineedit->text(),Qt::EditRole);
//            lineedit->clear();
//            lineedit->currentLogicalIndex=-1;
//            lineedit->setVisible(false);
//        }
//    });

}

