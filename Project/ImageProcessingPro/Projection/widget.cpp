#include "widget.h"
#include "ui_widget.h"

QPixmap getTransfomedImage(QPixmap pixmap,QPointF tl,QPointF tr,QPointF bl,QPointF br)
{
    QGraphicsScene scene;

    QPolygonF selectedArea,targetArea;
    selectedArea<<tl<<tr<<br<<bl;

    QLineF topLine(tl,tr);
    QLineF leftLine(tl,bl);
    QLineF rightLine(tr,br);
    QLineF bottomLine(bl,br);

    int maxWidth,maxheight;
    if(topLine.length()>bottomLine.length())maxWidth=topLine.length();
    else maxWidth = bottomLine.length();
    if(leftLine.length()>rightLine.length())maxheight=leftLine.length();
    else maxheight = rightLine.length();

    targetArea<< QPointF(0, 0)<<QPointF(maxWidth,0)<<QPointF(maxWidth,maxheight)<<QPointF(0,maxheight);

    auto pixmapItem = scene.addPixmap(pixmap);
    auto polygonItem = scene.addPolygon(selectedArea);

    QTransform transform;
    if(!QTransform::quadToQuad(selectedArea, targetArea, transform))
        return pixmap;

    pixmapItem->setTransform(transform);
    polygonItem->setTransform(transform);

    scene.setSceneRect(QRect(polygonItem->pos().x(),polygonItem->pos().y(),maxWidth,maxheight));

    QPixmap croppedPixmap(scene.sceneRect().width(),scene.sceneRect().height());
    QPainter painter(&croppedPixmap);
    scene.render(&painter);
    painter.end();

    return  croppedPixmap;
}





Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->label1->setAutoFillBackground(true);
    ui->label2->setAutoFillBackground(true);
    QPalette pal =  ui->label1->palette();
    pal.setColor(QPalette::Window, QColor(Qt::black));
    ui->label1->setPalette(pal);
    ui->label2->setPalette(pal);
    ui->label1->setAlignment(Qt::AlignCenter);
    ui->label2->setAlignment(Qt::AlignCenter);
    QPixmap pixmap("C:/ShareShotTransfer/IMG_20210316_133543.jpg");
    QTransform t; t.rotate(90);
    pixmap = pixmap.transformed(t,Qt::SmoothTransformation);


    //    QPointF tl(30/0.12,88.8/0.12);
    //    QPointF tr(267.6/0.12,69.6/0.12);
    //    QPointF bl(60/0.12,453.6/0.12);
    //    QPointF br(316.8/0.12,414/0.12);

    //    QPointF tl(30/0.12,88.8/0.12);
    //    QPointF tr(219.6/0.12,93.6/0.12);
    //    QPointF bl(60/0.12,453.6/0.12);
    //    QPointF br(304.8/0.12,402/0.12);

    QPointF tl(30/0.12,88.8/0.12);
    QPointF tr(267.6/0.12,69.6/0.12);
    QPointF bl(60/0.12,453.6/0.12);
    QPointF br(316.8/0.12,414/0.12);

    QPixmap  map = getTransfomedImage(pixmap,tl,tr,bl,br);

    QLineF topLine(tl,tr);
    QLineF leftLine(tl,bl);
    QLineF rightLine(tr,br);
    QLineF bottomLine(bl,br);

    QPainter painter(&pixmap);
    QPen pen("green"); pen.setWidth(20);
    painter.setPen(pen);
    painter.drawLine(topLine);
    painter.drawLine(leftLine);
    painter.drawLine(rightLine);
    painter.drawLine(bottomLine);
    painter.end();

    pixmap = pixmap.scaled(pixmap.width()*0.12,pixmap.height()*0.12,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label1->setPixmap(pixmap);
    map = map.scaled(map.width()*0.12,map.height()*0.12,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label2->setPixmap(map);

}

Widget::~Widget()
{
    delete ui;
}
