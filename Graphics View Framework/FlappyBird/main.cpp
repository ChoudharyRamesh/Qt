#include "view.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setApplicationName("Flappy Bird");
    View w;
    w.show();
    return a.exec();
}

