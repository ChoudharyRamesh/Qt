#include "singlethreadedwork.h"
#include<QRegularExpression>
#include<QDirIterator>
#include<QDebug>
#include<QThread>

SingleThreadedWork::SingleThreadedWork(QString dirPath ,QObject *parent) : QObject(parent)
{
    this->dirPath = dirPath;
}

void SingleThreadedWork::doWork()
{
   if(dirPath.isEmpty()) return;
   QElapsedTimer timer;
   timer.start();
   QRegularExpression istxt("\\.txt$|\\.TXT$|\\.Txt$");
   int fileCount=0;
    QDirIterator it(dirPath ,QDir::AllEntries | QDir::NoSymLinks | QDir::NoDotAndDotDot
                    ,QDirIterator::Subdirectories);
    while (it.hasNext() )
    {  it.next();
        if(it.fileInfo().isFile())
        {
          if(istxt.match(it.fileName()).hasMatch())
            { fileCount++;
            }
        }
    }
    emit workDone(fileCount,QString::number(timer.elapsed()));
   QThread::currentThread()->exit(0);
}
