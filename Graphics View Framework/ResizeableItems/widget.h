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
#include "resizablerectitem.h"
#include<QFileDialog>
#include<QImage>
#include<QMap>

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


    void on_pushButton_RenderScene_clicked();

    void on_pushButton_AddWidget_clicked();

private:
    Ui::Widget *ui;
    View * view;
    QGraphicsScene * scene;
    ResizableRectItem * item;
    QGraphicsProxyWidget * pw;
      QMap<int,QString> shapeMap;

    // QWidget interface
protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
};
#endif // WIDGET_H
