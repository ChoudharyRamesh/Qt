#include <QCoreApplication>
#include<QtConcurrent>
#include<QList>
#include<QFuture>
#include<QObject>
#include<QDebug>
#include<QFutureWatcher>
#include<QTimer>

int function(int input)
{
    return input-100;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> list;

    for(int i=0;i<10;i++)
        list.push_back(i);

    // run function has many overlaod but key part is that it's take function and run it in differnt
    // thread and return the result in QFuture object

    QFuture<int> future = QtConcurrent::run(function,55);
    future.waitForFinished();
    qDebug()<<future.result();

    return a.exec();
}
