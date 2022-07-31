#include <QCoreApplication>
#include<QtConcurrent>
#include<QDebug>

// filter reduced

bool function(const int & number)
{
    if(number<100)return true; else return false;
}

void reduced(int &total_sum, const int  &intermediate)
{
    total_sum+=intermediate;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> numbers;
    for(int i=50;i<150;i++)
        numbers.append(i);
    QFuture<int> temp =QtConcurrent::filteredReduced(numbers,function,reduced);
    temp.waitForFinished();
    qDebug()<<"sum of all item which is less then 100  is "<<temp.result();
    return a.exec();
}


/*  filter

bool function(const int & number)
{
    if(number<100)return true; else return false;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> numbers;
    for(int i=50;i<150;i++)
        numbers.append(i);
    QFuture<void> temp =QtConcurrent::filter(numbers,function);
    temp.waitForFinished();
    for(auto num:numbers)
        qDebug()<<num;
    return a.exec();
}

*/


/*  filtered
bool function(const int & number)
{
    if(number<100)return true; else return false;
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QList<int> numbers;
    for(int i=50;i<150;i++)
        numbers.append(i);
    QFuture<int> temp =QtConcurrent::filtered(numbers,function);
    temp.waitForFinished();
    qDebug()<<temp.results();
    return a.exec();
}

*/
