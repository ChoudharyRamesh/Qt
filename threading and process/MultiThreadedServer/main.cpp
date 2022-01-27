#include <QCoreApplication>
#include"myserver.h"
#include<QThread>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
     MyServer server;
    return a.exec();
}
