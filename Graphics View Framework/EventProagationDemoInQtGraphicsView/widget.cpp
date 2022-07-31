#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    View * v = new View(this);
    Scene *s = new Scene;
    s->setSceneRect(-200,-200,400,400);

    QGraphicsRectItem * i1 = new QGraphicsRectItem;
    i1->setRect(0,0,400,400);
    i1->setPos(-200,-200);
    i1->setPen(QPen(Qt::red));
    i1->setBrush(Qt::green);
    s->addItem(i1);

    Item * i = new Item;
    i->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
    i->setRect(0,0,50,50);
    i->setPen(QPen(Qt::black));
    i->setBrush(Qt::red);
    s->addItem(i);
    v->setScene(s);
    ui->verticalLayout->addWidget(v);
}

Widget::~Widget()
{
    delete ui;
}

