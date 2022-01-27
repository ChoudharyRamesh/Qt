#include "widget.h"
#include "ui_widget.h"
#include<QDataStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setGeometry(50,50,500,700);
    setWindowTitle("Server");
    socket = nullptr;
    server = new QTcpServer(this);
    server->listen(QHostAddress::LocalHost,6868);
    connect(server,&QTcpServer::newConnection,this,&Widget::gotNewConnection);

    process.setProgram("TcpClient.exe");
    process.start();

}

Widget::~Widget()
{
    if(socket!=nullptr) socket->deleteLater();
    delete ui;
}

void Widget::gotNewConnection()
{
    socket = server->nextPendingConnection();
    ui->label->setText("new connection attached");
    connect(socket,&QTcpSocket::readyRead,this,&Widget::readData);
    connect(socket,&QTcpSocket::disconnected,this,&Widget::disconnected);

    QListWidgetItem * item = new QListWidgetItem(QString("Hello Client"));
    item->setTextAlignment(Qt::AlignRight);
    ui->listWidget->addItem(item);
    QDataStream out(socket);
    out<<QString("Hello Client");
}

void Widget::readData()
{
    QDataStream in(socket);
    in.startTransaction();

    QString temp;
    in>>temp;

    if(!in.commitTransaction()) return;

    QListWidgetItem * item = new QListWidgetItem(temp);
    item->setTextAlignment(Qt::AlignLeft);
    ui->listWidget->addItem(item);
}

void Widget::disconnected()
{
    socket = nullptr;
    process.terminate();
}


void Widget::on_pushButton_clicked()
{
     if(ui->lineEdit->text()!="" && socket!=nullptr )
     {
         QListWidgetItem * item = new QListWidgetItem(ui->lineEdit->text());
         item->setTextAlignment(Qt::AlignRight);
         ui->listWidget->addItem(item);
         QDataStream out(socket);
         out<<ui->lineEdit->text();
         ui->label->setText("reply sent to client");
         ui->lineEdit->clear();
     }
}
