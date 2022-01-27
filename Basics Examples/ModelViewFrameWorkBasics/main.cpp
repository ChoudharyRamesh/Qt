#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}


/*
 * each item in model view architecture or model view data structure is represented by row and column
 * each item must also have parent
 * the root item is to top level parent in the entire data structure
 * the list like data structure is a particular case where root item has one child table eith only one column of data.
 * an item is represtend by QModelIndex class object
 * */

/*
 * differencw between (list,table,treeview ) (list,table,treeWidget )
 * Single level lists of items are typically displayed using a QListWidget and a number of QListWidgetItems.
 * A list widget is constructed in the same way as any other widget:
 * */
