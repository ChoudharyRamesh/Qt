#include "widget.h"
#include "ui_widget.h"
#include<QDataStream>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Client");
    setWindowFlag(Qt::WindowStaysOnTopHint);
    setGeometry(600,50,500,700);

    isconnected = false;

   socket = new QTcpSocket(this);
   connect(socket,&QTcpSocket::readyRead,this,&Widget::readData);
   connect(socket,&QTcpSocket::disconnected,[=]()
   {
       ui->label->setText("disconnected");
       isconnected=false;
   });
   connect(socket,&QTcpSocket::connected,[=]()
   {
       ui->label->setText("connected");
       isconnected=true;
   });

}

Widget::~Widget()
{
    delete ui;
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


void Widget::on_pushButton_clicked()
{
     if(ui->lineEdit->text()!="" && socket!=nullptr  &&  isconnected )
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

void Widget::on_pushButton_2_clicked()
{
   socket->connectToHost("localhost",6868);
}
