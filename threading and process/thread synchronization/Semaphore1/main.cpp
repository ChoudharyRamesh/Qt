#include <QCoreApplication>
#include<QSemaphore>
#include<QThread>
#include<QMutex>
#include<iostream>


QString data = \
"So what happens when we run the program? Initially, the producer thread is the\n\
only one that can do anything; the consumer is blocked waiting for the usedBytes\n\
semaphore to be released (its initial available() count is 0). Once the producer has\n\
put one byte in the buffer, freeBytes.available() is BufferSize - 1 and usedBytes.\n\
available() is 1. At that point, two things can happen: Either the consumer thread\n\
takes over and reads that byte, or the producer thread gets to produce a second byte.\n\
\n\
The producer-consumer model presented in this example makes it possible to write\n\
highly concurrent multithreaded applications. On a multiprocessor machine, the\n\
program is potentially up to twice as fast as the equivalent mutex-based program,\n\
since the two threads can be active at the same time on different parts of the buffer.\n\
\n\
Be aware though that these benefits aren't always realized. Acquiring and releasing\n\
a QSemaphore has a cost. In practice, it would probably be worthwhile to divide the\n\
buffer into chunks and to operate on chunks instead of individual bytes. The buffer\n\
size is also a parameter that must be selected carefully, based on experimentation.\n\
*\
* What is problem and why mutex can't be used  for solution ?\n\
* jab hum mutex ko lock unlock karte hai to mutex yh gurantee nhi deta ki konsa thread unlock hone\n\
* ke baad buffer ko access karega , matlab yh bhi possible hai ki jis thread ne eisko lock kiya tha vo\n\
* khud hi usko wapas lock karke rewrite kar ke , to mutex keval yh gurantee deta hai ki at a time only\n\
* ek thread hi shared resources ko access kar skta hai ,but konsa thread access karega yh gurantee nhi\n\
* deta . eis problem ko solve karne k liye semaphor sabse best tarika hai .\n\
*\n\
* How semaphore solve this problem ?\n\
* let say hamare paas 2 thread hai ,ek data produce kar raha hai ( Producer ) or ek data consume kar\n\
* (Consumer ) kar raha hai. Now, agar consumer-thread resources access karna chahta hai to usko\n\
* token (Semaphor for _read ) Producer-thread se lena padega and agar producer-thread resources access\n\
* karna chahta hai to usko token ( semaphor for_write) consumer-thread se lena padega.\n\
* Now, intially hamare paas koi deta nhi hai to hum producer thread ko 2 token free de dete hai taaki vo\n\
* data generate kar paaye .\n\
* Now, producer-thread ek token use karega or kuch fix byte ka data genrate karega, uske baad\n\
* consumer-thread ko ek token dega taaki vo us fix byte ke data ko read kar sake ,jab consumer thread\n\
* ( Note :: fix byte for read write == bufferSize/2);\n\
* data read kar raha hoga to producer-thread buffer thread cusmer-thread ke next-half-part mai data generate\n\
*  kar dega and ek or token consumer-thread k reading ke liye generate kar dega.\n\
* Jab consumer-thread first half reading complete karega to producer-threaad (writing k liye ) ko ek token dega\n\
* (to ab producer thread ke pass firse ek token aa jaayega bcz do usne use kar liye ) or producer thread buffer ke\n\
* first half part mai firse se writing start kar dega ,or edar consumer thread second half buffer ko read karega ,\n\
* or yh process end tk chalta rahega.\n\
* cool\n\
* */";


//const int DataSize = data.size();

//const int BufferSize = 200;
//QChar buffer[BufferSize];

//QSemaphore sem_writebytes(2);  //used for writing
//QSemaphore sem_readbytes(0);  // use for reading


//class Producer : public QThread
//{
//public:
//    void run() override
//    {  int  toggle =100;
//        for (int i = 0; i < DataSize;i++)
//        {
//            sem_writebytes.acquire(1);
//            toggle==100 ? toggle=0:toggle=100;
//            for(int j=0+toggle;j<100+toggle &&  i < DataSize;j++,i++)
//            {
//                buffer[j] = data.at(i);
//            }i--;
//            sem_readbytes.release(1);
//        }
//    }
//};

//class Consumer : public QThread
//{

//public:
//    void run() override
//    {  int  toggle =100;
//        for (int i = 0; i < DataSize; i++)
//        {
//            sem_readbytes.acquire(1);
//            toggle==100 ? toggle=0:toggle=100;
//            for(int j=0+toggle;j<100+toggle && i < DataSize;j++,i++)
//            { std::cout<<buffer[j].toLatin1();  }
//            i--;
//            sem_writebytes.release(1);
//        }
//        std::cout<<"\n";
//    }
//};

//try acquire

const int DataSize = data.size();

const int BufferSize = 200;
QChar buffer[BufferSize];

QSemaphore sem_writebytes(2);  //used for writing
QSemaphore sem_readbytes(0);  // use for reading


class Producer : public QThread
{
public:
    void run() override
    {  int  toggle =100;
        for (int i = 0; i < DataSize;i++)
        {
            if(!sem_writebytes.tryAcquire(1)) { i--; continue; }
            toggle==100 ? toggle=0:toggle=100;
            for(int j=0+toggle;j<100+toggle &&  i < DataSize;j++,i++)
            {
                buffer[j] = data.at(i);
            }i--;
            sem_readbytes.release(1);
        }
    }
};

class Consumer : public QThread
{

public:
    void run() override
    {  int  toggle =100;
        for (int i = 0; i < DataSize; i++)
        {
            if(!sem_readbytes.tryAcquire(1)) { i--; continue; }
             toggle==100 ? toggle=0:toggle=100;
            for(int j=0+toggle;j<100+toggle && i < DataSize;j++,i++)
            { std::cout<<buffer[j].toLatin1();  }
            i--;
            sem_writebytes.release(1);
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

/* analogy
 * What is problem and why mutex can't be used  for solution ?
 * jab hum mutex ko lock unlock karte hai to mutex yh gurantee nhi deta ki konsa thread unlock hone
 * ke baad buffer ko access karega , matlab yh bhi possible hai ki jis thread ne eisko lock kiya tha vo
 * khud hi usko wapas lock karke rewrite kar ke , to mutex keval yh gurantee deta hai ki at a time only
 * ek thread hi shared resources ko access kar skta hai ,but konsa thread access karega yh gurantee nhi
 * deta . eis problem ko solve karne k liye semaphor sabse best tarika hai .
 *
 * How semaphore solve this problem ?
 * let say hamare paas 2 thread hai ,ek data produce kar raha hai ( Producer ) or ek data consume kar
 * (Consumer ) kar raha hai. Now, agar consumer-thread resources access karna chahta hai to usko
 * token (Semaphor for _read ) Producer-thread se lena padega and agar producer-thread resources access
 * karna chahta hai to usko token ( semaphor for_write) consumer-thread se lena padega.
 * Now, intially hamare paas koi deta nhi hai to hum producer thread ko 2 token free de dete hai taaki vo
 * data generate kar paaye .
 * Now, producer-thread ek token use karega or kuch fix byte ka data genrate karega, uske baad
 * consumer-thread ko ek token dega taaki vo us fix byte ke data ko read kar sake ,jab consumer thread
 * ( Note :: fix byte for read write == bufferSize/2);
 * data read kar raha hoga to producer-thread buffer thread cusmer-thread ke next-half-part mai data generate
 *  kar dega and ek or token consumer-thread k reading ke liye generate kar dega.
 * Jab consumer-thread first half reading complete karega to producer-threaad (writing k liye ) ko ek token dega
 * (to ab producer thread ke pass firse ek token aa jaayega bcz do usne use kar liye ) or producer thread buffer ke
 * first half part mai firse se writing start kar dega ,or edar consumer thread second half buffer ko read karega ,
 * or yh process end tk chalta rahega.
 * cool
 * */


//working
/*
 * acquire function thread ko tab tk block kar deta jab tak semaphore ki value mangi gayi value se kam ho
 * block yani function return nhi karta .
 *
 * try acquire function turant return kar deta hai agar yadi semaphore ki value mangi gayi value se kam ho
 * what is use of try aquire :: - agar aap apne thread ko block nhi karna chahte or koi or kam us se karwana
 * chahte ho jab tk usko token mile to aap try acquire use kar sakte hai.
 * */

