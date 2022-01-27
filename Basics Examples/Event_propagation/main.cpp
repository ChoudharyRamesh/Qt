#include "child_lineedit.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget * mainwidget = new QWidget;
    Child_LineEdit w(mainwidget);
    w.setGeometry(125,250,500,50);
    mainwidget->show();
    return a.exec();
}
