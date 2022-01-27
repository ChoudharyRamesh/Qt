#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    view = new View(this);
    scene = new QGraphicsScene;
    scene->setSceneRect(-300,-300,600,600);
    view->setScene(scene);
    ui->verticalLayout->addWidget(view);

    item = new QGraphicsRectItem;
    item->setPen(QPen(Qt::red));
    item->setBrush(Qt::green);
    item->setRect(0,0,100,100);
    item->setFlag(QGraphicsItem::ItemIsSelectable);
    scene->addItem(item);

    //default initialization
    ui->checkBox_CheckGrid->setChecked(view->getDrawAxis());
    ui->checkBox_ShowAxis->setChecked(view->getDrawAxis());
}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_checkBox_CheckGrid_toggled(bool checked)
{
    view->setDrawGridLines(checked);
}

void Widget::on_pushButton_CenterView_clicked()
{
   view->centerOn(QPoint(0,0));
      //or
 //  view->centerOn(QPoint());
}

void Widget::on_pushButton_EnsureVisible_clicked()
{
   view->ensureVisible(item);
}

void Widget::on_pushButton_ZoomIn_clicked()
{
   double scaleFactor  = 1.1;
   view->scale(scaleFactor,scaleFactor);
}

void Widget::on_pushButton_ZoomOut_clicked()
{
    double scaleFactor  = 1.1;
    view->scale(1/scaleFactor,1/scaleFactor);
}

void Widget::on_pushButton_Reset_clicked()
{
  view->resetTransform();
}

void Widget::on_checkBox_ShowAxis_toggled(bool checked)
{
     view->setDrawAxis(checked);
}

void Widget::on_pushButton_FitInView_clicked()
{
    view->fitInView(item);
}
