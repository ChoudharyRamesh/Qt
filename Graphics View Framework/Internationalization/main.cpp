#include "widget.h"
#include<QTranslator>
#include <QApplication>
#include<QIcon>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator * translator = new QTranslator;
    translator->load(":/translations/hindi.qm");
    a.installTranslator(translator);
    // you can install more than one translator
    Widget w;
    w.show();
    return a.exec();

}
