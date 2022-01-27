#include "shapecanvas.h"

ShapeCanvas::ShapeCanvas(QWidget *parent) : QWidget(parent)
{
    shape = Polygon;
    antialiased = false;
    transformed = false;
    QPixmap pic("E:/pic3.png");
    pixmap = pic.scaled(250, 250);
}


void ShapeCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    //Polygon
    static const QPoint points[4] = {
        QPoint(250, 250),
        QPoint(270, 90),
        QPoint(280, 110),
        QPoint(500, 80)
    };

    QRect rect(250, 80, 250, 250);

    int startAngle = 20 * 16;
    int arcLength = 120 * 16;

    painter.setPen(pen);
    painter.setBrush(brush);
    painter.setFont( QFont ("Consolas", 8, QFont::Bold));

    if (antialiased)
        painter.setRenderHint(QPainter::Antialiasing, true);

    //Save the painter
    painter.save();

    if (transformed)
    {
        painter.translate(375, 205);
        painter.rotate(60.0);
        painter.scale(0.6, 0.9);
        painter.translate(-375, -205);
    }

    switch (shape) {

    case Polygon:
        painter.drawPolygon(points, 4);
        break;

    case Rect:
        painter.drawRect(rect);
        break;

    case RoundedRect:
        painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
        break;

    case Ellipse:
        painter.drawEllipse(rect);
        break;

    case Chord:
        painter.drawChord(rect, startAngle, arcLength);
        break;

    case Pie:
        painter.drawPie(rect, startAngle, arcLength);
        break;

    case Text:
        painter.drawText(rect,Qt::AlignCenter,tr("127.0.0.1"));

        break;

    case Pixmap:
        painter.drawPixmap(250, 80, pixmap);


    }
    painter.restore();


    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(Qt::red);
    painter.drawRect(QRect(0, 0, width() - 1, height() - 1));
}

ShapeCanvas::Shape ShapeCanvas::getShape() const
{
    return shape;
}

void ShapeCanvas::setShape(const Shape &value)
{
    shape = value;
    update();
}

QSize ShapeCanvas::sizeHint() const
{
    return QSize(1000,800);
}

QSize ShapeCanvas::minimumSizeHint() const
{
    return QSize(200,200);
}

QBrush ShapeCanvas::getBrush() const
{
    return brush;
}

void ShapeCanvas::setBrush(const QBrush &value)
{
    brush = value;
    update();
}

QPen ShapeCanvas::getPen() const
{
    return pen;
}

void ShapeCanvas::setPen(const QPen &value)
{
    pen = value;
    update();
}

bool ShapeCanvas::getTransformed() const
{
    return transformed;
}

void ShapeCanvas::setTransformed(bool value)
{
    transformed = value;
    update();
}

void ShapeCanvas::setAntialiased(bool value)
{
    antialiased = value;
    update();
}

bool ShapeCanvas::getAntialiased() const
{
    return antialiased;
}
