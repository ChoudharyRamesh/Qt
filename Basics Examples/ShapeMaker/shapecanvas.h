#ifndef SHAPECANVAS_H
#define SHAPECANVAS_H

#include <QWidget>
#include <QWidget>
#include<QPixmap>
#include<QDebug>
#include<QPen>
#include<QPainter>
#include<QFont>
#include<QFile>
#include<QPainterPath>

class ShapeCanvas : public QWidget
{
    Q_OBJECT
public:
    enum Shape{Polygon,Rect,RoundedRect,Ellipse,Pie,Chord,Text,Pixmap};
    explicit ShapeCanvas(QWidget *parent = nullptr);

    QPen getPen() const;
    void setPen(const QPen &value);

    QBrush getBrush() const;
    void setBrush(const QBrush &value);

    Shape getShape() const;
    void setShape(const Shape &value);

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

    bool getTransformed()const;
    void setTransformed(bool value);
    bool getAntialiased()const;
    void setAntialiased(bool value);

signals:

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QPen  pen;
    QBrush  brush;
    Shape shape;
    QPixmap pixmap;
    bool transformed;
    bool antialiased;

};

#endif // SHAPECANVAS_H
