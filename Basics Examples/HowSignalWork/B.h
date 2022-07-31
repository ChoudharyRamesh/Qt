#include<QObject>
#include<QDebug>

class B:public QObject
{
    Q_OBJECT
public:
    void print()
    {
        for(int i=0;i<1000;i++)
        {
            qDebug()<<"hello";
        }
    }
};
