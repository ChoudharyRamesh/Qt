#include "widget.h"
#include "ui_widget.h"
#include<QTimer>
#include<QDebug>
#include<QClipboard>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("Anonymous");
    QApplication::clipboard()->clear();
}

Widget::~Widget()
{
    delete ui;
    QApplication::clipboard()->clear();
}

void Widget::on_pushButton_clicked()
{
    if(ui->lineEdit->text()=="5432136523")
    {
        QApplication::clipboard()->setText("start@#SIGNALANDSLOT@##@RAMESH@#321GO/.12345/.12(DoNe)");
        QTimer::singleShot(3000,[=]()
        {
             QApplication::clipboard()->clear();
        });
    }
}
