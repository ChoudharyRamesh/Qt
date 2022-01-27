#include "multithreadedwork.h"
MultiThreadedWork::MultiThreadedWork(QString dirPath,QObject *parent) : QObject(parent)
{
    this->dirPath = dirPath;
}

void MultiThreadedWork::doWork()
{
    QList<QString>list;
    list.append(this->dirPath);

    QElapsedTimer timer;
     int result=0;
    timer.start();
    QFuture<QPair<int,QList<QString>>> future = QtConcurrent::mappedReduced
            (list,threadedScaning,ReducedWork,QtConcurrent::UnorderedReduce);
    future.waitForFinished();

     result = future.result().first;
    while(!future.result().second.isEmpty())
    {
        future = QtConcurrent::mappedReduced
                    (future.result().second,threadedScaning,ReducedWork,QtConcurrent::UnorderedReduce);
        future.waitForFinished();
        result +=  future.result().first;
    }
    emit workDone(result,QString::number(timer.elapsed()));
   QThread::currentThread()->exit(0);

}


void MultiThreadedWork::ReducedWork
(QPair<int,QList<QString>> & txtcount_isrunning ,
 const QPair<int,QList<QString>> & intermediate_result)
{
    txtcount_isrunning.first+=intermediate_result.first;
    txtcount_isrunning.second.append(intermediate_result.second);
}

QPair<int,QList<QString>>
MultiThreadedWork::threadedScaning(QString dirPath)
{
    QList<QString>list;
    int txtCount=0;
    if(dirPath.isEmpty()) return QPair<int,QList<QString>>(txtCount,list);
    QRegularExpression istxt("\\.txt$|\\.TXT$|\\.Txt$");
     QDirIterator it(dirPath ,QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot);
     while (it.hasNext() )
     {  it.next();
         if(it.fileInfo().isFile())
         {
           if(istxt.match(it.fileName()).hasMatch())
             {
                txtCount++;
             }
         }
         else if(it.fileInfo().isDir())
         {
             list.append(it.fileInfo().filePath());
         }
     }
   return QPair<int,QList<QString>>(txtCount,list);
}
