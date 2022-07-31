#include "widget.h"
#include "progressnumber.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qRegisterMetaType<ProgressNumber>("ProgressNumber");
    Widget w;
    w.show();
    return a.exec();
}
