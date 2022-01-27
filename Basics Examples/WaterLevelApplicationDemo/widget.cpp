#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    indicator = new Indicator;
   watertank = new WaterTank;
  // ui->horizontalLayout->setStretch(0,1);
 //  ui->horizontalLayout->setStretch(1,1);
   ui->horizontalLayout->addWidget(watertank);
   ui->horizontalLayout->addWidget(indicator);

   connect(watertank,&WaterTank::normal,indicator,&Indicator::activateNormal);
   connect(watertank,&WaterTank::warning,indicator,&Indicator::activateWarning);
   connect(watertank,&WaterTank::danger,indicator,&Indicator::activateDanger);

}

Widget::~Widget()
{
    delete ui;
}
