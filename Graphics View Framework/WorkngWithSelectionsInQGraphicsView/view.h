#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include<QPainter>

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

private:
    QPoint selectTopLeft;
    bool drawingSelection;
    QGraphicsRectItem * lastrect;
    bool DrawGridLines;
    bool DrawAxis;

};

#endif // VIEW_H
