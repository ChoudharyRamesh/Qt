
// setup project prepare string in ts file
// generating ts files
//translating in qt designer
//generating qm files
//qtranslator
//loding official qt translator
//saving user translation choice

#include "widget.h"
#include "ui_widget.h"
#include<QIcon>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QString st1 = tr("Hello world");
    QString st2 = tr("What are you doing ?");

    ui->textEdit->setText(st1+"\n"+st2);
}

Widget::~Widget()
{
    delete ui;
}

