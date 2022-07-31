#include "myrunnable.h"

MyRunnable::MyRunnable(qintptr socketDescripter)
{
    this->socketDescripter=socketDescripter;

}

void MyRunnable::run()
{
    qDebug()<<"runnable task started";
    QTcpSocket  socket;
   if(!socket.setSocketDescriptor(socketDescripter))return;
    socket.write("HTTP/1.1\r\n");
    socket.write("Connection: Keep-Alive\r\n");
    socket.write("\r\n");
    socket.write("<!DOCTYPE html>\
                 <html>\
                 <body>\
                 \
                 <h2>Hello Client , Images from fb server</h2>\
                 \
                 <img src=\"https://scontent.fbom8-1.fna.fbcdn.net/v/t1.0-9/74274955_1237994239733785_4133151431005831168_o.jpg?_nc_cat=104&_nc_sid=09cbfe&_nc_ohc=NB0-lEOpM-EAX9Fxz7I&_nc_ht=scontent.fbom8-1.fna&oh=45a91ed69ecf635d8e962842c8d9bdbd&oe=5F8BBDC6\" alt=\"thecodepanel.com\" style=\"width:580px;height:800px;\">\
            \
            </body>\
            </html>\r\n");
            socket.waitForBytesWritten(1000);
            socket.close();

}

MyRunnable::~MyRunnable()
{
    qDebug()<<"runnable task deleted";
}
