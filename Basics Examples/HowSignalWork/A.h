#include<QObject>
#include<QDebug>

class A :public QObject
{
    Q_OBJECT
signals:
    void startexe();
public:
    void print()
    {
        for(int i=0;i<10;i++)
        {
            qDebug().noquote()<<i;
            if(i==5) emit startexe();
        }
    }
};
