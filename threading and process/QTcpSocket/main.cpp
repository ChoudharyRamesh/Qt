#include "widget.h"
#include "qtcpsocketobjectoriented.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    Qtcpsocketobjectoriented obj;
    w.show();
    return a.exec();
}
