#include "CustomPushButton.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget * parentWidget = new QWidget;
    CustomPushButton w(parentWidget);
    parentWidget->show();
    return a.exec();
}
