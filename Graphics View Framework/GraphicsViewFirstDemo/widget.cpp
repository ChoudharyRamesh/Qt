#include "widget.h"
#include "ui_widget.h"
#include<QGraphicsView>
#include<QGraphicsScene>
#include <QGraphicsRectItem>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsScene  * scene = new QGraphicsScene(this);
    QGraphicsView * view  = new QGraphicsView(this);
    ui->verticalLayout->addWidget(view);
    view->setScene(scene);

    scene->setBackgroundBrush(QColor::fromRgb(125,120,55,125));
    scene->setSceneRect(100,100,width()-100,height()-100); // fixed scene size;
    view->setAlignment(Qt::AlignTop | Qt::AlignLeft);  // set scene to top left

    QGraphicsRectItem  * rectitem = new QGraphicsRectItem;
    rectitem->setRect(10,10,400,400);
    QPen pen(Qt::red); pen.setWidth(5);
    QBrush brush(Qt::green);
    rectitem->setPen(pen);
    rectitem->setBrush(brush);
    rectitem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    scene->addItem(rectitem);
               //or
   QGraphicsRectItem  * rectitem2 = scene->addRect(100,100,200,200,pen,QColor::fromRgb(0,0,125,125));
   rectitem2->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

}

Widget::~Widget()
{
    delete ui;
}
