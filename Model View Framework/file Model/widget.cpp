#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    parentIndex = model->setRootPath("D:/Program Files");

}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    int rowCount = model->rowCount(parentIndex);
    ui->textEdit->setText(QString::number(rowCount));
    for(int i=0;i<rowCount;i++)
    {
        QModelIndex index = model->index(i,0,parentIndex);
        ui->textEdit->append(model->data(index,Qt::DisplayRole).toString());
    }
}
