#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "view.h"
#include <QGraphicsScene>
#include<QGraphicsView>
#include<QGraphicsRectItem>
#include <QTransform>
#include<QDebug>
#include<QRubberBand>
#include<QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_checkBox_CheckGrid_toggled(bool checked);
    void on_pushButton_CenterView_clicked();
    void on_pushButton_EnsureVisible_clicked();
    void on_pushButton_ZoomIn_clicked();
    void on_pushButton_ZoomOut_clicked();
    void on_pushButton_Reset_clicked();

    void on_checkBox_ShowAxis_toggled(bool checked);

    void on_pushButton_FitInView_clicked();

private:
    Ui::Widget *ui;
    View * view;
    QGraphicsScene * scene;
    QGraphicsRectItem * item;
};
#endif // WIDGET_H
