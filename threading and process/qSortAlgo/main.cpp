#include <QCoreApplication>
#include<QList>
#include<QDebug>
int main(int argc, char *argv[])
{
    // http://www.cplusplus.com/reference/algorithm/
    QCoreApplication a(argc, argv);
    QList<int> list;
    list<<2<<10<<8<<4;
    std::sort(list.begin(),list.end());
    qDebug()<<list;
    QVector<int> vector(4);
    std::copy(list.begin(),list.end(),vector.begin());
    qDebug()<<vector;
    QVector<int> vector2(5,100) ; // default fill
    std::fill(vector2.begin(),vector2.end(),200);  // after constructor
    qDebug()<<vector2;

    qDebug()<<std::find(vector2.begin(),vector2.end(),200);
    return a.exec();
}
