#include <QCoreApplication>
#include<QThreadPool>
#include "worker.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Worker  * worker = new Worker;
    QThreadPool::globalInstance()->start(worker);
    return a.exec();
}
