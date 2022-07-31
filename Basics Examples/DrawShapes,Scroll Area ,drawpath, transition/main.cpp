#include "scrollarea.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ScrollArea w;
    w.show();
    return a.exec();
}
