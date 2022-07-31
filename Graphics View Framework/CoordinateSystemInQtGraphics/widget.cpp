#include "widget.h"
#include "ui_widget.h"
#include<QGraphicsView>
#include<QGraphicsScene>
#include <QGraphicsRectItem>
#include "view.h"
// view coardinate is coardinate of  view starting from top left corner of view
//  item coardinate is coardinate system for scene for parent child item management , it also start from
// top left corner of item
// scene coardinate start from center of scene


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsScene  * scene = new QGraphicsScene(this);
    View * view  = new View(this);
    ui->verticalLayout->addWidget(view);
    view->setScene(scene);

   scene->setSceneRect(100,100,width()-100,height()-100); // fixed scene size;

    QPen pen(Qt::red); pen.setWidth(5);
    QBrush brush(Qt::green);
    QGraphicsRectItem  * rectitem = scene->addRect(100,100,200,200,pen,QColor::fromRgb(0,0,125,125));
    rectitem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

}

Widget::~Widget()
{
    delete ui;
}
