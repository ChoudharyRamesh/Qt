#include "MainWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Assignment Generator");
    a.setOrganizationName("QByteCore");
    Widget w;
    w.show();
    return a.exec();
}
