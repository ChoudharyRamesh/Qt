#include <QCoreApplication>
#include<QDebug>
#include<QFile>
#include<QTimer>
#include<QDataStream>
#include<QWaitCondition>
#include<QMutex>
#include<QThread>
#include<iostream>
#include<QProcess>
#define FILE_PATH "C:/Users/Nishant Choudhary/Desktop/temp.bin"
//writer
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    system("mode con: cols=60 lines=28");
    QFile file(FILE_PATH);
    QWaitCondition condition;
    QMutex mutex;
    bool block = true;
    std::string data;

    QThread * thread = QThread::create([&]()
    {
        forever
        {
            mutex.lock();
            if(file.size()>0)
            {
                block=true;
            }
            else
            {
                block=false; condition.wakeAll();
            }
            mutex.unlock();
        }
    });

    thread->start();

    forever
    {
        mutex.lock();
        if(block)condition.wait(&mutex);
        std::getline(std::cin,data);
        if(!file.open(QFile::ReadWrite))
        {
            qDebug()<<"file doesn't open "<<file.errorString();
            QCoreApplication::exit(1);
        }
        file.write(QByteArray::fromStdString(data));
        file.close();
        mutex.unlock();
    }
   return a.exec();
}



