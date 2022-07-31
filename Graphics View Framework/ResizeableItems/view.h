#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include<QPainter>
#include<QMouseEvent>
#include<QPainterPath>
#include<QGraphicsRectItem>
#include<QDebug>
#include<QMimeData>
#include<QDragEnterEvent>
#include<QDropEvent>

class View : public QGraphicsView
{
    Q_OBJECT
public:
    explicit View(QWidget *parent = nullptr);

    bool getDrawGridLines() const;
    void setDrawGridLines(bool value);

    bool getDrawAxis() const;
    void setDrawAxis(bool value);

signals:

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    void drawBackground(QPainter *painter, const QRectF &rect) override;
    void drawForeground(QPainter *painter, const QRectF &rect) override;

    void dropEvent(QDropEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;

private:
    QPoint selectTopLeft;
    bool drawingSelection;
    QGraphicsRectItem * lastrect;
    bool DrawGridLines;
    bool DrawAxis;

};

#endif // VIEW_H
