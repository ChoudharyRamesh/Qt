#include <QCoreApplication>
#include<QList>
#include<QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> intlist;
    for (int i=1; i<5;i++)
        intlist.append(i);

    // iterate
    QListIterator<int> it(intlist);

    while(it.hasNext())
        qDebug()<<it.next();


    QMutableListIterator<int> it2(intlist);
    if(it2.findNext(3))  it2.remove();


    it2.toFront();
    qDebug()<<"\n";
    while(it2.hasNext())
        qDebug()<<it2.next();



    return a.exec();
}
