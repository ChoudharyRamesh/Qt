#include "container.h"

Container::Container(QWidget * parent) : QWidget(parent)
{
    setMinimumSize(250,250);
    setAcceptDrops(true);
    QLabel * pic1 = new QLabel(this);
    pic1->setPixmap(QPixmap(":/images/circle.gif").scaled(100,100));
    pic1->move(20,20);

    QLabel * pic2 = new QLabel(this);
    pic2->setPixmap(QPixmap(":/images/circuit-20200402-2257 (1).png").scaled(100,100));
    pic2->move(140,20);

    QLabel * pic3 = new QLabel(this);
    pic3->setPixmap(QPixmap(":/images/circuit-20200402-2257.png").scaled(100,100));
    pic3->move(20,140);

    QLabel * pic4 = new QLabel(this);
    pic4->setPixmap(QPixmap(":/images/textfx.png").scaled(100,100));
    pic4->move(140,140);


}


void Container::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        startPos = event->pos();
    QWidget::mousePressEvent(event);
}

void Container::mouseMoveEvent(QMouseEvent *event)
{

    if (event->buttons() & Qt::LeftButton) {  qDebug()<<"mouse move event";

        int distance = (event->pos() - startPos).manhattanLength();

        if (distance >= QApplication::startDragDistance())
        {
            //Start Drag

            QLabel * grabbedLabel = static_cast<QLabel *>(childAt(event->pos()));

            if(grabbedLabel==nullptr)
                return;

            QPixmap pixmap = grabbedLabel->pixmap(Qt::ReturnByValueConstant());

            QByteArray ba;

            QDataStream dataStream(&ba,QIODevice::WriteOnly);

            dataStream << pixmap;

            QMimeData * mimeData = new QMimeData;
            mimeData->setData("mycustomMimeType",ba);

            QDrag * drag = new QDrag(this);
            drag->setMimeData(mimeData);
            // optional
            drag->setPixmap(pixmap);
            drag->setHotSpot(QPoint(drag->pixmap().width()/2,drag->pixmap().height()/2));


            //optional
            //Blur the original label
            QPixmap tempPix = pixmap;
            QPainter painter(&tempPix);
            painter.fillRect(tempPix.rect(),QColor(127, 127, 127, 127));
            grabbedLabel->setPixmap(tempPix);


            //Call to drag->exec() is blocking
            // when this drag is executed it will block mouse event on this widget until drop
            // and grab all mouse event for drag object  we can see that in drag move event
            if(drag->exec(Qt::MoveAction | Qt::CopyAction,Qt::CopyAction)== Qt::MoveAction)
            {
                //Move data
                qDebug()<< "Moving data";
                grabbedLabel->close();   // delete grabbed level
            }
            else
            {
                //Copy action
                grabbedLabel->setPixmap(pixmap);  // unblur pixmap
                qDebug() << "Copying data";
            }

        }
    }
}

void Container::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasFormat("mycustomMimeType")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
        } else {
            event->acceptProposedAction();
        }

    }else{
        event->ignore();
    }

}

void Container::dragMoveEvent(QDragMoveEvent *event)
{
    qDebug()<<"mouse moce event is closed and drag event started";
    if (event->mimeData()->hasFormat("mycustomMimeType")) {
        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            //event->ignore();
        } else {
            event->acceptProposedAction();
        }

    }else{
        event->ignore();
    }
}



void Container::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasFormat("mycustomMimeType")) {

        QByteArray ba = event->mimeData()->data("mycustomMimeType");
        QDataStream dataStream(&ba,QIODevice::ReadOnly);

        QPixmap pixmap;
        dataStream >> pixmap;


        QLabel * newLabel = new QLabel(this);
        newLabel->setPixmap(pixmap);
        newLabel->move(event->pos().x()-pixmap.width()/2,event->pos().y()-pixmap.height()/2);
        newLabel->show();
        newLabel->setAttribute(Qt::WA_DeleteOnClose);

        if (event->source() == this) {
            event->setDropAction(Qt::MoveAction);
            event->accept();
            //event->ignore();
        } else {
            event->acceptProposedAction();
        }

    }else{
        event->ignore();
    }

}

void Container::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawRoundedRect(0,5,width()-10, height()-10,3,3);
    QWidget::paintEvent(event);

}
