#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGraphicsEllipseItem>

//center on ---> view
// move center --> scene rect

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    scene.setBackgroundBrush(QBrush("black"));
    resize(600,626);
    //ui->graphicsView->resize(600,600);

    ellipse = new QGraphicsEllipseItem;
    ellipse->setFlag(QGraphicsItem::ItemIsMovable);
    ellipse->setBrush(QBrush("cyan"));
    scene.addItem(ellipse);
    ellipse->setRect(QRectF(0,0,100,100));



    sceneCenterItem = new QGraphicsEllipseItem;
    sceneCenterItem->setBrush(QBrush("green"));
    scene.addItem(sceneCenterItem);
    sceneCenterItem->setRect(QRectF(0,0,10,10));

    sceneRectangleItem = new QGraphicsRectItem(scene.sceneRect());
    QPen pen("red");
    pen.setWidth(4);
    sceneRectangleItem->setPen(pen);
    scene.addItem(sceneRectangleItem);
    connect(&scene,&QGraphicsScene::sceneRectChanged,this,[this]()
    {
        sceneRectangleItem->setRect(scene.sceneRect()-QMarginsF(5,5,5,5));
    });



    pincenterItem = new QGraphicsEllipseItem;
    pincenterItem->setBrush(QBrush("white"));
    scene.addItem(pincenterItem);
    pincenterItem->setRect(QRectF(0,0,10,10));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_action_FitInView_triggered()
{
    scene.removeItem(sceneCenterItem);
    scene.removeItem(sceneRectangleItem);
    scene.removeItem(pincenterItem);


    scene.setSceneRect(scene.itemsBoundingRect());
    ui->graphicsView->fitInView(scene.sceneRect(),Qt::KeepAspectRatio);

    scene.addItem(sceneCenterItem);
    scene.addItem(sceneRectangleItem);
    scene.addItem(pincenterItem);
}

void MainWindow::on_actionscene_Rect_triggered()
{
    qDebug()<<" scene rect is "<<scene.sceneRect();
}

void MainWindow::on_actionview_rect_triggered()
{
    qDebug()<<" view rect is "<<ui->graphicsView->rect();
}

void MainWindow::on_actionview_center_triggered()
{
    qDebug()<<" view center "<<ui->graphicsView->rect().center();
}

void MainWindow::on_actionscene_center_triggered()
{
    qDebug()<<" scene center "<<scene.sceneRect().center();
}

void MainWindow::on_actionitem_Bounding_rect_triggered()
{
    qDebug()<<" ellipse bounding rect is "<<ellipse->boundingRect();
}

void MainWindow::on_actionitem_pos_triggered()
{
    qDebug()<<" ellipse pos is "<<ellipse->pos()<<" "<<ellipse->scenePos();
}

void MainWindow::on_actionall_item_Bounding_rect_triggered()
{
    scene.removeItem(sceneCenterItem);
    scene.removeItem(sceneRectangleItem);
    scene.removeItem(pincenterItem);
    qDebug()<<" all item bounding rect is "<<scene.itemsBoundingRect();
    scene.addItem(sceneCenterItem);
    scene.addItem(sceneRectangleItem);
    scene.addItem(pincenterItem);
}

void MainWindow::on_actionplus_triggered()
{
    ellipse->setRect(ellipse->rect()+QMarginsF(2,2,2,2));
}

void MainWindow::on_actionminus_triggered()
{
     ellipse->setRect(ellipse->rect()-QMarginsF(2,2,2,2));
}

void MainWindow::on_actionpin_scene_center_triggered()
{
    QPointF vc = ui->graphicsView->rect().center();
    QPointF scenePointInViewCenter = ui->graphicsView->mapToScene(vc.toPoint());


    scene.removeItem(sceneCenterItem);
    scene.removeItem(sceneRectangleItem);
    scene.removeItem(pincenterItem);
    QRectF itemBRect = scene.itemsBoundingRect();
    QPointF itemsCenter = itemBRect.center();
    scene.addItem(sceneCenterItem);
    scene.addItem(sceneRectangleItem);
    scene.addItem(pincenterItem);


    QPointF diff = scenePointInViewCenter-itemsCenter;
    QPointF newPos = ellipse->pos()+diff;
    ellipse->setPos(newPos);


    QRectF rect = itemBRect; //scene.sceneRect();
    rect.moveCenter(scenePointInViewCenter);
    scene.setSceneRect(rect);

    pincenterItem->setRect(QRectF(scenePointInViewCenter.x(),scenePointInViewCenter.y(),10,10));
}

void MainWindow::on_actionmap_view_center_in_scene_triggered()
{
     QPointF vc = ui->graphicsView->rect().center();
     qDebug()<<" view center "<<vc<<"  mapped in scene "<<ui->graphicsView->mapToScene(vc.toPoint());
}

void MainWindow::on_actionmap_scene_center_in_view_triggered()
{
    QPointF sc = scene.sceneRect().center();
    qDebug()<<" scene center "<<sc<<"  mapped in view "<<ui->graphicsView->mapFromScene(sc.toPoint());
}
