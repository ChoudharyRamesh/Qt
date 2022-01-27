#include "shapemaker.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShapeMaker w;
    w.show();
    return a.exec();
}
