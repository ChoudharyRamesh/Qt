#include<QSharedMemory>
#include <QCoreApplication>
#include<sys/types.h>
#include<sys/stat.h>
#include <fcntl.h>
#define SHARED_KEY "LQIOSK_QDDFIO_GLIOQIO_SMTPQIO_MEMQIODl"
QSharedMemory sharedMemory;
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    sharedMemory.setKey(SHARED_KEY);
    //any first intance of this program (process ) is going to create shared memory
    // and all other process is able to read
    return a.exec();
}
