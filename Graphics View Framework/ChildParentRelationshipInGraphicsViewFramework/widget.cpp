#include "widget.h"
#include "ui_widget.h"
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsRectItem>
#include<cmath>
// scene for child is will be same as scene of parent , so there is no need to set scene to child item
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsRectItem * parentItem = new QGraphicsRectItem(0,0,200,200);
    parentItem->setBrush(Qt::red);
    parentItem->setFlag(QGraphicsItem::ItemIsMovable);
    parentItem->setRect(0,0,200,200);
    QGraphicsRectItem * childItem = new QGraphicsRectItem(50,50,100,100,parentItem);
    childItem->setBrush(Qt::green);
    childItem->setFlag(QGraphicsItem::ItemIsMovable);
    QGraphicsScene * scene = new QGraphicsScene(this);
    scene->addItem(parentItem);
    QGraphicsView * view  = new QGraphicsView(this);
    view->setScene(scene);
    ui->verticalLayout->addWidget(view);


    // painter path
    QGraphicsPathItem * pathItem = new QGraphicsPathItem;
    pathItem->setBrush(Qt::red);
    QPainterPath starPath;
    starPath.moveTo(90, 50);
    for (int i = 1; i < 5; ++i) {
        starPath.lineTo(50 + 40 * std::cos(0.8 * i * M_PI),
                        50 + 40 * std::sin(0.8 * i * M_PI));
    }
    starPath.closeSubpath();
   pathItem->setPath(starPath);
   scene->addItem(pathItem);

}

Widget::~Widget()
{
    delete ui;
}

