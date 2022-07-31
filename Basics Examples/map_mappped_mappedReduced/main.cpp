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
    qDebug()<<input;
    return input-100;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> list;

    for(int i=0;i<10;i++)
        list.push_back(i);

    QFuture<void> future = QtConcurrent::map(list,function);
    future.waitForFinished();

    return a.exec();
}

//map ( standard def: -applies a function to every item in a container, modifying the items in-place. )
// map call fucntion for each item in list and any modification will be reflected in list itslef
//  that's why our future object is void type.....

//mapped (standard def: - is like map(), except that it returns a new container with the modifications.)
// .....whereas in mapped Qfuture is not gonna void bcz mapped function return result in
// futrue object list after computation....

//mapped reduced(standard def: is like mapped(), except that the modified results are reduced or folded into a single result.)
//and in mapped it calls reduced function on each return

// see mapped and mapped-reduced example below


// mapped
/*int function(int input)
{
    qDebug()<<input;
    return input-100;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> list;

    for(int i=0;i<10;i++)
        list.push_back(i);

    QFuture<int> future = QtConcurrent::mapped(list,function);
    future.waitForFinished();
    for( auto it : future.results())
        qDebug()<<it;

    return a.exec();
}
*/

//mapped reduced
/*
 * #include <QCoreApplication>
#include<QtConcurrent>
#include<QList>
#include<QFuture>
#include<QObject>
#include<QDebug>
#include<QFutureWatcher>
#include<QTimer>

int inputFunction(int rawInput)
{
    return rawInput+1;
}

void reducedFunction(int & final_result , const int & InterMediatecomputedInput  )
{
    qDebug()<<"InterMediatecomputedInput "<<InterMediatecomputedInput;
    qDebug()<<"calculating result "<<final_result;
    final_result+=InterMediatecomputedInput;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> list;

    for(int i=0;i<10;i++)
        list.push_back(i);

     QFuture<int>future = QtConcurrent::mappedReduced(list,inputFunction,reducedFunction);
     future.waitForFinished();
     qDebug()<<" final result is "<<future.result();
    return a.exec();
}

*/

