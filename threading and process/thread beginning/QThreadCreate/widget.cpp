#include "widget.h"
#include "ui_widget.h"

void dowork(int a=0)
{
    for(int i=a;i<100;i++)
        for(int j=0;j<10000;j++)
            qDebug()<<QThread::currentThread();
    qDebug()<<"completed";
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<<" main thread is "<<thread();
    secondaryThread=nullptr;

}

Widget::~Widget()
{
    delete ui;
}

void Widget::Dowork1(int a)
{
    for(int i=a;i<100;i++)
        for(int j=0;j<10000;j++)
            qDebug()<<QThread::currentThread();
    qDebug()<<"completed";
}

void Widget::Dowork2()
{
    for(int i=0;i<10000;i++)
      qDebug()<<"in second thred isSharedData is "<<isSharedData--;
    qDebug()<<"completed";
}
void Widget::on_global_clicked()
{
    threadOnGlobalFunction();
}

void Widget::on_lambda_clicked()
{
     threadOnLambdaPtrFunction();
}

void Widget::on_lambdaonfly_clicked()
{
     threadOnLambdaDirectFunction();
}

void Widget::on_onMember_clicked()
{
    threadOnMemberFunction();
}


void Widget::on_SharingResources_clicked()
{
     threadOnMemberFunctionAndShareResources();
}

void Widget::threadOnGlobalFunction()
{
     secondaryThread = QThread::create(dowork,99);
    connect(secondaryThread,&QThread::finished,secondaryThread,&QThread::deleteLater);
        secondaryThread->start();
}

void Widget::threadOnLambdaPtrFunction()
{
        auto lambdafunction = [](int a=0){
            for(int i=a;i<100;i++)
                for(int j=0;j<10000;j++)
                    qDebug()<<QThread::currentThread();
            qDebug()<<"completed";
        };
     secondaryThread = QThread::create(lambdafunction,99);
    connect(secondaryThread,&QThread::finished,secondaryThread,&QThread::deleteLater);
        secondaryThread->start();
}


void Widget::threadOnLambdaDirectFunction()
{
     secondaryThread = QThread::create([](int a=0){
         for(int i=a;i<100;i++)
             for(int j=0;j<10000;j++)
                 qDebug()<<QThread::currentThread();
         qDebug()<<"completed";
     },99);
    connect(secondaryThread,&QThread::finished,secondaryThread,&QThread::deleteLater);
        secondaryThread->start();
}

void Widget::threadOnMemberFunction()
{
    secondaryThread = QThread::create([=](int a){this->Dowork1(a);},99);
    connect(secondaryThread,&QThread::finished,secondaryThread,&QThread::deleteLater);
    secondaryThread->start();
}

void Widget::threadOnMemberFunctionAndShareResources()
{
    secondaryThread = QThread::create([=](){this->Dowork2();});
    connect(secondaryThread,&QThread::finished,secondaryThread,&QThread::deleteLater);
    secondaryThread->start(QThread::LowPriority);

    for(int i=0;i<10000;i++)
    {   // sharing resources ( but be carefull ,deadlock )
        qDebug()<<"main thread isSharedData is "<<isSharedData++;
    }
}



