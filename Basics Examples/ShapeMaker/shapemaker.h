#ifndef SHAPEMAKER_H
#define SHAPEMAKER_H

#include <QWidget>
#include "shapecanvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ShapeMaker; }
QT_END_NAMESPACE

class ShapeMaker : public QWidget
{
    Q_OBJECT

public:
    ShapeMaker(QWidget *parent = nullptr);
    ~ShapeMaker();

private slots:
    void on_comboBox_shape_activated(int index);

    void on_spinBox_pen_width_valueChanged(int arg1);

    void on_comboBox_pen_style_activated(int index);

    void on_comboBox_pen_cap_activated(int index);

    void on_comboBox_pen_join_activated(int index);

    void on_comboBox_brush_style_activated(int index);

    void on_checkBox_antialising_toggled(bool checked);

    void on_checkBox_trasnform_toggled(bool checked);

    void penChanged();
    void brushChanged();

private:
    Ui::ShapeMaker *ui;

};
#endif // SHAPEMAKER_H
