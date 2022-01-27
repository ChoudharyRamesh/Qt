#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    filter = new CustomEventFilter(this);
    ui->pushButton_1->installEventFilter(filter);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_2_clicked()
{
    QMouseEvent * newevent \
   = new QMouseEvent(QEvent::MouseButtonPress, \
    ui->pushButton_1->pos(),Qt::LeftButton,Qt::LeftButton,Qt::NoModifier);

    //spontneous event -- event which is coming from windows

    // send event
    if(QApplication::sendEvent(ui->pushButton_1,newevent))
    {
        qDebug()<<"Clicked from button_2";
    }
    else qDebug()<<"event rejected";
    //post event
    QApplication::postEvent(ui->pushButton_1,newevent);

}
