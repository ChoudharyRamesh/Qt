#ifndef PAINTERCANVAS_H
#define PAINTERCANVAS_H

#include <QWidget>
#include<QApplication>
#include<QMimeData>
#include<QDebug>
#include<QKeyEvent>
#include<QClipboard>
#include<QPixmap>
#include <QPainter>
#include <QMouseEvent>

class PainterCanvas : public QWidget
{
    Q_OBJECT
public:
    enum ToolType {Pen,Rect, Ellipse, Eraser};

    explicit PainterCanvas(QWidget *parent = nullptr);

    ToolType getTool() const;
    void setTool(const ToolType &value);

    bool getFill() const;
    void setFill(bool value);

    int getPenWidth() const;
    void setPenWidth(int value);

    QColor getFillColor() const;
    void setFillColor(const QColor &value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

private:
    void drawLineTo(const QPoint &endPoint);
    void drawRectTo(const QPoint & endPoint ,bool elipse = false);
    void eraseUnder(const QPoint & topLeft);
    void resizeImage(QImage *image, const QSize &newSize);

    ToolType tool;
    bool fill;
    bool drawing;
    int penWidth;
    QColor fillColor;
    QColor penColor;
    QPoint lastPoint;
    QRectF lastRect;
    QRectF lastEraserRect;
    QImage image;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

protected:
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // PAINTERCANVAS_H
