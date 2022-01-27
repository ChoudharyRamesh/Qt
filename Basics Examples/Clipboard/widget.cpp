#include "widget.h"
#include "ui_widget.h"
#include<QKeyEvent>
#include<QApplication>
#include<QMimeData>
#include<QClipboard>
#include<QDebug>
#include<QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if(event->matches(QKeySequence::Paste))
    { QDebug debug = qDebug();
       const QMimeData * mimedata = QApplication::clipboard()->mimeData();
       // not cheking here ,simple demo
       ui->label->setPixmap(QPixmap(mimedata->urls().at(0).toLocalFile()).scaled(260,600,Qt::KeepAspectRatio));
      debug.noquote()<<mimedata->urls().at(0).toLocalFile();
    }
    else
        QWidget::keyPressEvent(event);
}
