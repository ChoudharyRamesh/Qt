#include "widget.h"
#include "ui_widget.h"
#include <QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsRectItem>
#include <QTransform>
#include<QDebug>
#include<QRubberBand>
#include<QTimer>


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QGraphicsView * view = new QGraphicsView(this);
    QGraphicsScene * scene = new QGraphicsScene;
    view->setScene(scene);
    ui->verticalLayout->addWidget(view);

    QGraphicsRectItem * item = new QGraphicsRectItem;
    item->setPen(QPen(Qt::red));
    item->setBrush(Qt::green);
    item->setRect(0,0,100,100);
    scene->addItem(item);


    QTransform transform = item->transform();
//    transform.rotate(45,Qt::ZAxis);
//    transform.scale(1.2,1.2);
//    transform.shear(2,2);
      qDebug()<<transform.m11()<<" "<<transform.m12()<<" "<<transform.m13()
           <<" "<<transform.m21()<<" "<<transform.m22()<<" "<<transform.m23()
           <<" "<<transform.m31()<<" "<<transform.m32()<<" "<<transform.m33();

    transform.setMatrix(1,0,0.4,0,1,0,0,0,1);
    item->setTransform(transform);

}

Widget::~Widget()
{
    delete ui;
}


void Widget::mousePressEvent(QMouseEvent *event)
{

    QRubberBand * rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    rubberBand->setGeometry(50,50,100,100);
    rubberBand->show();
    QTimer::singleShot(2500,rubberBand,[=]()
    {
        delete rubberBand;
    });
}



