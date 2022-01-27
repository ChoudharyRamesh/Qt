#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

   connect(ui->watertank,&WaterTank::normal,ui->indicator,&Indicator::activateNormal);
   connect(ui->watertank,&WaterTank::warning,ui->indicator,&Indicator::activateWarning);
   connect(ui->watertank,&WaterTank::danger,ui->indicator,&Indicator::activateDanger);

}

Widget::~Widget()
{
    delete ui;
}
