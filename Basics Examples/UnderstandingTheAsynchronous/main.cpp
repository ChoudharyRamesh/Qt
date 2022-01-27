#include <QCoreApplication>
#include<QTime>
#include<QStack>
#include<QDebug>

QStack<void(*)()>callstack;
bool isHeavyFunctionEvaluated=false;

void fun1()
{
    qDebug()<<"this is fun 1";
}

void fun2()
{
    qDebug()<<"this is fun 2";
}

void fun3()
{
    qDebug()<<"this is fun 3";
}

void fun4()
{
    qDebug()<<"this is fun 4";
}

void fun5()
{
    qDebug()<<"this is fun 5";
}

void fun6()
{
    qDebug()<<"this is fun 6";
}

void fun7()
{
    qDebug()<<"this is fun 7";
}

void fun8()
{
    qDebug()<<"this is fun 8";
}





void heavyFunction()
{
    static auto startTime = QTime::currentTime();
    if(QTime::currentTime()>=startTime.addSecs(8))
    {  qDebug()<<"this is heavy function";   isHeavyFunctionEvaluated =true;}
}

void callBack(void(*callback)())
{
    Q_UNUSED(callback());
}

void runPorgram()
{
    while(!callstack.empty())
    {
        if(callstack.front()==heavyFunction)
        {
            if(!isHeavyFunctionEvaluated)
            {
                callstack.front()();
                callstack.push(callstack.front());
                callstack.pop_front();
            }
            else
            {
                callstack.pop_front();
            }
        }
        else
        {   callstack.front()();
            callstack.pop_front();
        }
    }
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    callstack.push(&fun1);
    callstack.push(&fun2);
    callstack.push(&heavyFunction);
    callstack.push(&fun3);
    callstack.push(&fun4);
    callstack.push(&fun5);
    callstack.push(&fun6);
    callstack.push(&fun7);
    callstack.push(&fun8);

    runPorgram();

    qDebug()<<"call stack is empty";

    return a.exec();
}




