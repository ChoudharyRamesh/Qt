#ifndef CONTAINTER_H
#define CONTAINTER_H

#include <QWidget>
#include<QLabel>
#include<QPixmap>
#include<QPainter>
#include<QMouseEvent>
#include<QDragEnterEvent>
#include<QDragLeaveEvent>
#include<QDragMoveEvent>
#include<QDropEvent>
#include<QPoint>
#include<QApplication>
#include<QMimeData>
#include<QDataStream>
#include<QByteArray>
#include<QDebug>
#include<QDrag>

class Container : public QWidget
{
    Q_OBJECT
public:
    explicit Container(QWidget *parent = nullptr);

signals:

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QPoint startPos;


};

#endif // CONTAINTER_H
