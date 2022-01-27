#include "paintercanvas.h"

PainterCanvas::PainterCanvas(QWidget *parent) : QWidget(parent),
    tool(Pen),
    fill(false),
    drawing(false),
    penWidth(3),
    fillColor(Qt::red),
    penColor(Qt::green),
    lastRect(QRectF(0,0,0,0)),
    lastEraserRect(QRectF(0,0,0,0))
{

}

PainterCanvas::ToolType PainterCanvas::getTool() const
{
    return tool;
}

void PainterCanvas::setTool(const ToolType &value)
{
    tool = value;
}

bool PainterCanvas::getFill() const
{
    return fill;
}

void PainterCanvas::setFill(bool value)
{
    fill = value;
}

int PainterCanvas::getPenWidth() const
{
    return penWidth;
}

void PainterCanvas::setPenWidth(int value)
{
    penWidth = value;
}

QColor PainterCanvas::getFillColor() const
{
    return fillColor;
}

void PainterCanvas::setFillColor(const QColor &value)
{
    fillColor = value;
}

QColor PainterCanvas::getPenColor() const
{
    return penColor;
}

void PainterCanvas::setPenColor(const QColor &value)
{
    penColor = value;
}

void PainterCanvas::drawLineTo(const QPoint &endPoint)
{
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.drawLine(lastPoint, endPoint);
    int adjustment = penWidth  + 2;
    update(QRect(lastPoint, endPoint).normalized()
           .adjusted(-adjustment, -adjustment, +adjustment, +adjustment));
    lastPoint = endPoint;
}

void PainterCanvas::drawRectTo(const QPoint &endPoint, bool elipse)
{
    QPainter painter(&image);
    painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap,
                        Qt::RoundJoin));


    if (fill)
        painter.setBrush(fillColor);
    else
        painter.setBrush(Qt::NoBrush);

    if(!elipse)
        painter.drawRect(QRect(lastPoint, endPoint));
    else {
        painter.drawEllipse(QRect(lastPoint,endPoint));
    }

    if(drawing){

        painter.setPen(QPen(Qt::white, penWidth+2, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));

        if(fill)
            painter.setBrush(Qt::white);
        else
            painter.setBrush(Qt::NoBrush);

        if(!elipse)
            painter.drawRect(lastRect);
        else {
            painter.drawEllipse(lastRect);
        }

        //Reset the pen and brush
        painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap,
                            Qt::RoundJoin));
        painter.setBrush(fillColor);

    }

    lastRect = QRectF(lastPoint,endPoint);

    // code for paste data

    update();

}

void PainterCanvas::eraseUnder(const QPoint &topLeft)
{

    QPainter painter(&image);
    //Erase last eraser rect
    painter.setBrush(Qt::white);
    painter.setPen(Qt::white);
    painter.drawRect(lastEraserRect);


    //Erase the content under current eraser rect. Brush and pen still white
    QRect currentRect(topLeft,QSize(100,100));
    painter.setBrush(Qt::white);
    painter.setPen(Qt::white);
    painter.drawRect(currentRect);


    //Draw current eraser rect
    painter.setBrush(Qt::black);
    painter.setPen(Qt::black);
    painter.drawRect(currentRect);

    lastEraserRect = currentRect;

    if(!drawing){
        painter.setBrush(Qt::white);
        painter.setPen(Qt::white);
        painter.drawRect(lastEraserRect);
        lastEraserRect = QRect(0,0,0,0);
    }

    update();


}

void PainterCanvas::resizeImage(QImage *image, const QSize &newSize)
{
    if (image->size() == newSize)
        return;

    QImage newImage(newSize, QImage::Format_RGB32);
    newImage.fill(qRgb(255, 255, 255));
    QPainter painter(&newImage);
    painter.drawImage(QPoint(0, 0), *image);
    *image = newImage;
}

void PainterCanvas::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    if (event->button() == Qt::LeftButton) {
        lastPoint = event->pos();
        drawing = true;
    }
}

void PainterCanvas::mouseMoveEvent(QMouseEvent *event)
{
    if ((event->buttons() & Qt::LeftButton) && drawing){
        if( tool == Pen){
            drawLineTo(event->pos());
        }
        if(tool == Rect){
            drawRectTo(event->pos());
        }
        if(tool == Ellipse)
        {
            drawRectTo(event->pos(),true);
        }
        if(tool == Eraser){
            eraseUnder(event->pos());
        }
    }
}

void PainterCanvas::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        drawing = false;
        if(tool == Pen){
            drawLineTo(event->pos());
        }
        if(tool == Rect){
            drawRectTo(event->pos());
        }
        if(tool == Ellipse)
        {
            drawRectTo(event->pos(),true);
        }
        if(tool ==Eraser){
            eraseUnder(event->pos());
        }
        //Reset the last rect
        lastRect = QRect(0,0,0,0);
    }

}

void PainterCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QRect rectToDraw = event->rect();
    painter.drawImage(rectToDraw, image, rectToDraw);

}

void PainterCanvas::resizeEvent(QResizeEvent *event)
{
    if (width() > image.width() || height() > image.height()) {
        int newWidth = qMax(width() + 128, image.width());
        int newHeight = qMax(height() + 128, image.height());
        resizeImage(&image, QSize(newWidth, newHeight));
        update();
    }
    QWidget::resizeEvent(event);
}


void PainterCanvas::keyPressEvent(QKeyEvent *event)
{
    if(event->matches(QKeySequence::Paste))
    {
        const QMimeData * mimedata = QApplication::clipboard()->mimeData();
        QPainter painter(&image);
        painter.drawPixmap(10,10,QPixmap(mimedata->urls().at(0).toLocalFile()).scaled(260,600,Qt::KeepAspectRatio));
        update();
    }
    else if(event->matches(QKeySequence::Copy))
    {
//       QClipboard * clipboard = QApplication::clipboard();
//        QMimeData * tempmime = new QMimeData;
//        tempmime->setImageData(image);
//        clipboard->setMimeData(tempmime);
          //or
        QApplication::clipboard()->setImage(image);
    }
    else
        QWidget::keyPressEvent(event);
}
