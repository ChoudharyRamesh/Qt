#include "widget.h"
#include "ui_widget.h"
#include<QDir>
#include <QDirIterator>
#include<QUrl>
#include <QFileDialog>
#include<QMimeDatabase>
#include<QMimeType>
#include<QDebug>
#include<QMovie>
#include<QtConcurrent>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,isworkFinished_single(true)
    ,isworkFinished_multi(true)
{
    ui->setupUi(this);
    movie = new QMovie(this);
    movie->setScaledSize(QSize(100,80));
    movie->setSpeed(300);
    movie->setFileName(":/gif/resources/original.gif");
    qDebug()<<"hello starter";  // for QProcess
}

Widget::~Widget()
{
    if(!isworkFinished_single)
        if(singlethread->isRunning())singlethread->exit(0);
    if(!isworkFinished_multi)
        if(multithread->isRunning())multithread->exit(0);
    delete ui;
}


void Widget::on_chooseFolder_single_clicked()
{
    ui->chooseFolder_single->setEnabled(false);
    isworkFinished_single =false;
    QString dirPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                        "/home",
                                                        QFileDialog::ShowDirsOnly
                                                        | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_single->setText(dirPath);

    ui->result_label_single->setAlignment(Qt::AlignCenter);
    ui->result_label_single->setMovie(movie);
    movie->start();

    singlethread = new QThread;
    singleworker = new SingleThreadedWork(dirPath);
    connect(singlethread,&QThread::started,singleworker,&SingleThreadedWork::doWork);
    connect(singleworker,&SingleThreadedWork::workDone,movie,&QMovie::stop);
    connect(singleworker,&SingleThreadedWork::workDone,[=](int fileCount,QString time)
    {
        ui->result_label_single->clear();
        ui->result_label_single->setText("Time took :"+time+" ms\nFile found:"+QString::number(fileCount));
        ui->chooseFolder_single->setEnabled(true);
        isworkFinished_single=true;
        delete singleworker;
    });

    singleworker->moveToThread(singlethread);
    singlethread->start();
}

void Widget::on_chooseFolder_multi_clicked()
{
    ui->chooseFolder_multi->setEnabled(false);
    isworkFinished_multi =false;
        QString dirPath = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                            "/home",
                                                            QFileDialog::ShowDirsOnly
                                                            | QFileDialog::DontResolveSymlinks);
    ui->lineEdit_multi->setText(dirPath);

    ui->result_label_multi->setAlignment(Qt::AlignCenter);
    ui->result_label_multi->setMovie(movie);
    movie->start();

    multithread = new QThread;
    multiworker = new MultiThreadedWork(dirPath);
    connect(multithread,&QThread::started,multiworker,&MultiThreadedWork::doWork);

    connect(multiworker,&MultiThreadedWork::workDone,movie,&QMovie::stop);
    connect(multiworker,&MultiThreadedWork::workDone,[=](int fileCount,QString time)
    {
        ui->result_label_multi->clear();
        ui->result_label_multi->setText("Time took :"+time+" ms\nFile found:"+QString::number(fileCount));
        ui->chooseFolder_multi->setEnabled(true);
        isworkFinished_multi=true;
        delete multiworker;
    });

    multiworker->moveToThread(multithread);
    multithread->start();
}

