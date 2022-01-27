#include <QCoreApplication>
#include<QThread>
#include<QWaitCondition>
#include<QMutex>
#include<atomic>
#include<iostream>


QString data = \
"So what happens when we run the program? Initially, the producer thread is the\n\
only one that can do anything; the consumer is blocked waiting for the usedBytes\n\
semaphore to be released (its initial available() count is 0). Once the producer has\n\
put one byte in the buffer, freeBytes.available() is BufferSize - 1 and usedBytes.\n\
available() is 1. At that point, two things can happen: Either the consumer thread\n\
takes over and reads that byte, or the producer thread gets to produce a second byte.\n\
....\n\
The producer-consumer model presented in this example makes it possible to write\n\
highly concurrent multithreaded applications. On a multiprocessor machine, the\n\
program is potentially up to twice as fast as the equivalent mutex-based program,\n\
since the two threads can be active at the same time on different parts of the buffer.\n\
....\n\
Be aware though that these benefits aren't always realized. Acquiring and releasing\n\
a QSemaphore has a cost. In practice, it would probably be worthwhile to divide the\n\
buffer into chunks and to operate on chunks instead of individual bytes. The buffer\n\
size is also a parameter that must be selected carefully, based on experimentation.";


const int DataSize = data.size();
const int BufferSize = 100;
QChar buffer[BufferSize];
QWaitCondition wait_for_writing;
QWaitCondition wait_for_reading;
QMutex mutex;

class Producer : public QThread
{
public:
    void run() override
    {
        for (int i = 0; i < DataSize;i++)
        { static  bool start=true;

            mutex.lock();
            if(!start)
                wait_for_reading.wait(&mutex);
            else start=false;
            mutex.unlock();

            for(int j=0;j<100 && i<DataSize;j++,i++)
            {
                buffer[j] = data.at(i);
            }i--;

            wait_for_writing.wakeAll();
        }
        wait_for_writing.wakeAll();
    }
};

class Consumer : public QThread
{

public:
    void run() override
    {
        for (int i = 0; i < DataSize; i++)
        {
            mutex.lock();
            wait_for_writing.wait(&mutex);
            mutex.unlock();

            for(int j=0;j<100 && i < DataSize;j++,i++)
            { std::cout<<buffer[j].toLatin1();  }
            i--;
            wait_for_reading.wakeAll();
        }
        std::cout<<"\n";
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    Producer producer;
    Consumer consumer;
    consumer.start();
    producer.start();
    producer.wait();
    consumer.wait();
    return 0;
}


/*explanation
 * The mutex is used to protect the condition variable itself. That's why you need it locked
 * before you do a wait.
 * The wait will "atomically" unlock the mutex, allowing others thread access to the condition
 * variable (for signalling). Then when the condition variable is signalled or broadcast to, one
 * or more of the threads on the waiting list will be woken up and the mutex will be magically
 *  locked again for that thread
 *
 * uses
 * 1. for pause and resume thread by another thread
 * 2. if first thread completed somework and that work is needed for second thread to do
 *    work then first thread should notify second thread to wake and do task
 * */

/* for better understanding
 * link
 * https://stackoverflow.com/questions/26581699/whats-the-point-of-locking-and-unlocking-a-mutex-if-pthread-cond-wait-does-that
 * example
 * https://www.youtube.com/watch?v=eh_9zUNmTig
*/
