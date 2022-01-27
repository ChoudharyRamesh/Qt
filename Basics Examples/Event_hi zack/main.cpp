#include "widget.h"
#include "application.h"
//#include <QApplication>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);
    Application a(argc,argv);
    Widget w;
    w.show();
    return a.exec();
}
