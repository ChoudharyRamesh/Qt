#include <QCoreApplication>
#include<QUdpSocket>
#include<QProcess>
#include<iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    system("mode con: cols=60 lines=30");
    QProcess process;
    process.setProgram("QUdpSocketSender.exe");
    process.start();
    QUdpSocket  socket;
    forever
    {
        std::string string;
        std::getline(std::cin,string);
        if(string=="clear")system("cls");
        socket.writeDatagram(QByteArray::fromStdString(string),QHostAddress::LocalHost,1234);
    }
    return a.exec();
}
