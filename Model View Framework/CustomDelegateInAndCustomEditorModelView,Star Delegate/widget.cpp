#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

     QHBoxLayout * h = new QHBoxLayout(this);
    tableWidget = new QTableWidget(this);
    h->addWidget(tableWidget);
    StarDelegate * delegate = new StarDelegate(this);

     data.append({"College","Teaching Style",1});
     data.append({"College","Value of Time",1});
     data.append({"College","Value of Money",1});
     data.append({"YouTube","Teaching Style",4});
     data.append({"YouTube","Value of Time",3});
     data.append({"YouTube","Value of Money",4});
     data.append({"Self Learning","Value of Time",4});

     tableWidget->setRowCount(data.size());
     tableWidget->setColumnCount(data[0].size());
     tableWidget->setItemDelegateForColumn(2,delegate);

     for( int row = 0 ; row < data.size() ; row++){

         QTableWidgetItem *item0 = new QTableWidgetItem(data[row][0].toString());
         QTableWidgetItem *item1 = new QTableWidgetItem(data[row][1].toString());
         QTableWidgetItem *item2 = new QTableWidgetItem(data[row][2].toString());

         tableWidget->setItem(row, 0, item0);
         tableWidget->setItem(row, 1, item1);
         tableWidget->setItem(row, 2, item2);
     }

}

Widget::~Widget()
{
}

