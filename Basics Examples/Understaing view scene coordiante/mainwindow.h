#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<scene.h>
#include<QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_action_FitInView_triggered();
    void on_actionscene_Rect_triggered();
    void on_actionview_rect_triggered();
    void on_actionview_center_triggered();
    void on_actionscene_center_triggered();
    void on_actionitem_Bounding_rect_triggered();
    void on_actionitem_pos_triggered();
    void on_actionall_item_Bounding_rect_triggered();
    void on_actionplus_triggered();
    void on_actionminus_triggered();
    void on_actionpin_scene_center_triggered();
    void on_actionmap_view_center_in_scene_triggered();
    void on_actionmap_scene_center_in_view_triggered();

private:
    Ui::MainWindow *ui;
    Scene scene;
    QGraphicsEllipseItem * ellipse;
    QGraphicsRectItem * sceneRectangleItem;
    QGraphicsEllipseItem * sceneCenterItem;

    QGraphicsEllipseItem * pincenterItem;
};
#endif // MAINWINDOW_H
