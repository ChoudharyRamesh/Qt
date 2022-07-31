#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    Filter * filter = new Filter(&w);  //applying filter on event loop
    a.installEventFilter(filter);
    w.show();
    return a.exec();
}
