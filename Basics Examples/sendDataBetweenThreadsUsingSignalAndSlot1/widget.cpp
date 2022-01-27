#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
#include<QTextEdit>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    pthread = new QThread(this);
    cthread = new QThread(this);
    producer = new Producer;
    consumer = new Consumer;

    // these all connectionn is queued connection bcz it will runn through event loop of
    // corresponding thread
   connect(this,&Widget::sendDataToProducerThread,producer,&Producer::recieveDataFromMainThread);
   connect(producer,&Producer::forwardDataToConsumerThread,consumer,&Consumer::recieveDataFromProducerThread);
    connect(consumer,&Consumer::sendBacktoUi,this,&Widget::recieveDataFromConsumerThread);

    connect(pthread,&QThread::finished,[&]()
    {
        producer->deleteLater();
    });

    connect(cthread,&QThread::finished,[&]()
    {
        consumer->deleteLater();
    });

    // for checking
    connect(pthread,&QThread::destroyed,[&]()
    {
        qDebug()<<" pthread deleted";
    });
    connect(cthread,&QThread::destroyed,[&]()
    {
        qDebug()<<" cthread deleted";
    });
    connect(producer,&Producer::destroyed,[&]()
    {
        qDebug()<<" producer deleted";
    });
    connect(consumer,&Consumer::destroyed,[&]()
    {
        qDebug()<<" consumer deleted";
    });

    producer->moveToThread(pthread);
    consumer->moveToThread(cthread);

    cthread->start();
    pthread->start();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::closeEvent(QCloseEvent *event)
{
    cthread->exit(0);
    pthread->exit(0);
    QWidget::closeEvent(event);
}


void Widget::on_sendData_clicked()
{
    qDebug()<<"Widget::on_sendData_clicked,running-thread ="<<QThread::currentThread();
    qDebug()<<"Widget::on_sendData_clicked ,object leaving="<<thread();
    emit sendDataToProducerThread(ui->producerTextEdit->toPlainText());
   // consumer->recieveDataFromProducerThread(ui->producerTextEdit->toPlainText());
    //if both are un commented then data races will start )
}

void Widget::recieveDataFromConsumerThread(const QString &data)
{
    qDebug()<<"Widget::recieveDataFromConsumerThread,running-thread ="<<QThread::currentThread();
    qDebug()<<"Widget::recieveDataFromConsumerThread ,object leaving="<<thread();
    ui->consumerTextEdit->setPlainText(data);
}


/*
 ( on calling consumer function from main thread ( comment  producer ))
 ( comment line 70 and uncomment line 71 )
Widget::on_sendData_clicked,running-thread = QThread(0x16e3fb0)
Widget::on_sendData_clicked ,object leaving= QThread(0x16e3fb0)
Consumer::recieveDataFromProducerThread,running-thread = QThread(0x16e3fb0)
Consumer::recieveDataFromProducerThread ,object leaving= QThread(0x16f05a0)  // ( thread affinity)
Widget::recieveDataFromConsumerThread,running-thread = QThread(0x16e3fb0)
Widget::recieveDataFromConsumerThread ,object leaving= QThread(0x16e3fb0)


Widget::on_sendData_clicked,running-thread = QThread(0x2e33fb0)
Widget::on_sendData_clicked ,object leaving= QThread(0x2e33fb0)
Producer::recieveDataFromMainThread,running-thread = QThread(0x2e40280)
Producer::recieveDataFromMainThread ,object leaving= QThread(0x2e40280)
Consumer::recieveDataFromProducerThread,running-thread = QThread(0x2e3fea0)
Consumer::recieveDataFromProducerThread ,object leaving= QThread(0x2e3fea0)
Widget::recieveDataFromConsumerThread,running-thread = QThread(0x2e33fb0)
Widget::recieveDataFromConsumerThread ,object leaving= QThread(0x2e33fb0)


conclusion
agar koi object thread affinity A ko belong karta hai or agar us object ke member
function ko kisi dusre thread se call kiya jaayega to wo us call wale thread affinity
 mai chalega
*/
