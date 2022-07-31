#include "widget.h"
#include "ui_widget.h"
#include<QRect>
#include<QGraphicsProxyWidget>
#include<QDial>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget),pw(nullptr)
{
    ui->setupUi(this);
    view = new View(this);
    scene = new QGraphicsScene;
    scene->setSceneRect(-300,-300,600,600);
    view->setScene(scene);
    ui->verticalLayout->addWidget(view);

    item = new ResizableRectItem;
    QPen pen(Qt::red);
    item->setPen(pen);
    item->setBrush(Qt::green);
    item->setRect(-50,-50,100,100);
    item->setPos(0,0);
    scene->addItem(item);

    //default initialization
    ui->checkBox_CheckGrid->setChecked(view->getDrawAxis());
    ui->checkBox_ShowAxis->setChecked(view->getDrawAxis());

    setAcceptDrops(true);

        shapeMap.insert(10, "Ellipse");
        shapeMap.insert(20, "Quick");
        shapeMap.insert(30, "Rectangle");
        shapeMap.insert(40, "Star");

        foreach (int key, shapeMap.keys())
        {
            QListWidgetItem * item = new QListWidgetItem(shapeMap[key],ui->widget_ShapeList);
            QString filename = ":/images/" + shapeMap[key].toLower()+".png";
            item->setIcon(QIcon(filename));
            item->setData(Qt::UserRole,key);

        }

        ui->widget_ColorList->addItems(QColor::colorNames());

        QStringList colors = QColor::colorNames();

        for( int i = 0 ; i < colors.size(); i++){
            QPixmap mPix(40,40);
            mPix.fill(colors[i]);
            QIcon icon;
            icon.addPixmap(mPix);
            ui->widget_ColorList->item(i)->setIcon(icon);

        }

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

void Widget::on_pushButton_RenderScene_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    "fC:/Users/Nishant Choudhary/Desktop/untitled.png",
                                                    tr("Images (*.png *.xpm *.jpg)"));
    if(fileName.isNull()) return;


    QRect rect = scene->sceneRect().toAlignedRect();
    QImage image(rect.size(),QImage::Format_RGBA8888_Premultiplied);
    image.fill(Qt::transparent);

    QPainter painter(&image);
    scene->render(&painter);
    image.save(fileName);
}

void Widget::on_pushButton_AddWidget_clicked()
{
    if(pw==nullptr)
    {QDial * dial = new QDial;
        dial->setMinimum(0);
        dial->setMaximum(360);
        pw = new QGraphicsProxyWidget;
        pw->setPos(0,0);
        pw->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable );
        pw->setWidget(dial);
        scene->addItem(pw);

        connect(dial,&QDial::valueChanged,this,[=](int value)
        {
            item->setRotation(value);
        });
    }
}


void Widget::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        qDebug()<<"drag";
         event->setDropAction(Qt::CopyAction);
         event->accept();
    }
    else
    {
        event->ignore();
    }
}



void Widget::dropEvent(QDropEvent *event)
{
 if (event->mimeData()->hasUrls())
   {  event->accept();
       qDebug()<<"drop ";
        QPixmap pixmap= QPixmap(event->mimeData()->urls().at(0).toLocalFile());
        scene->addPixmap(pixmap);
    }else{
        event->ignore();
    }
}


