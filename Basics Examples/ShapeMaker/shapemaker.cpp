#include "shapemaker.h"
#include "ui_shapemaker.h"

ShapeMaker::ShapeMaker(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ShapeMaker)
{
    ui->setupUi(this);
    ui->comboBox_shape->addItem(tr("Poloygon"),ShapeCanvas::Polygon);
    ui->comboBox_shape->addItem(tr("Rectangle"),ShapeCanvas::Rect);
    ui->comboBox_shape->addItem(tr("Rounded Rectangle"),ShapeCanvas::RoundedRect);
    ui->comboBox_shape->addItem(tr("Ellipse"),ShapeCanvas::Ellipse);
    ui->comboBox_shape->addItem(tr("Pie"),ShapeCanvas::Pie);
    ui->comboBox_shape->addItem(tr("Chord"),ShapeCanvas::Chord);
    ui->comboBox_shape->addItem(tr("Text"),ShapeCanvas::Text);
    ui->comboBox_shape->addItem(tr("Pixmap"),ShapeCanvas::Pixmap);

    ui->comboBox_pen_style->addItem(tr("Solid"),static_cast<int>(Qt::SolidLine));
    ui->comboBox_pen_style->addItem(tr("Dash"),static_cast<int>(Qt::DashLine));
    ui->comboBox_pen_style->addItem(tr("Dot"),static_cast<int>(Qt::DotLine));
    ui->comboBox_pen_style->addItem(tr("Dash Dot"),static_cast<int>(Qt::DashDotLine));
    ui->comboBox_pen_style->addItem(tr("Dash Dot Dot"),static_cast<int>(Qt::DashDotDotLine));
    ui->comboBox_pen_style->addItem(tr("None"),static_cast<int>(Qt::NoPen));

    ui->comboBox_pen_cap->addItem(tr("Flat"),Qt::FlatCap);
    ui->comboBox_pen_cap->addItem(tr("Square"),Qt::SquareCap);
    ui->comboBox_pen_cap->addItem(tr("Round"),Qt::RoundCap);


    ui->comboBox_pen_join->addItem(tr("Miter"),Qt::MiterJoin);
    ui->comboBox_pen_join->addItem(tr("Bevel"),Qt::BevelJoin);
    ui->comboBox_pen_join->addItem(tr("Round"),Qt::RoundJoin);

    ui->comboBox_brush_style->addItem(tr("None"),static_cast<int>(Qt::NoBrush));
    ui->comboBox_brush_style->addItem(tr("Texture"),static_cast<int>(Qt::TexturePattern));
    ui->comboBox_brush_style->addItem(tr("Solid"),static_cast<int>(Qt::SolidPattern));
    ui->comboBox_brush_style->addItem(tr("Horizontal"),static_cast<int>(Qt::HorPattern));
    ui->comboBox_brush_style->addItem(tr("Vertical"),static_cast<int>(Qt::VerPattern));
    ui->comboBox_brush_style->addItem(tr("Cross"),static_cast<int>(Qt::CrossPattern));
    ui->comboBox_brush_style->addItem(tr("Backward Diagonal"),static_cast<int>(Qt::BDiagPattern));
    ui->comboBox_brush_style->addItem(tr("Forward Diagonal"),static_cast<int>(Qt::FDiagPattern));
    ui->comboBox_brush_style->addItem(tr("Diagonal Cross"),static_cast<int>(Qt::DiagCrossPattern));
    ui->comboBox_brush_style->addItem(tr("Dense 1"),static_cast<int>(Qt::Dense1Pattern));
    ui->comboBox_brush_style->addItem(tr("Dense 2"),static_cast<int>(Qt::Dense2Pattern));
    ui->comboBox_brush_style->addItem(tr("Dense 3"),static_cast<int>(Qt::Dense3Pattern));
    ui->comboBox_brush_style->addItem(tr("Dense 4"),static_cast<int>(Qt::Dense4Pattern));
    ui->comboBox_brush_style->addItem(tr("Dense 5"),static_cast<int>(Qt::Dense5Pattern));
    ui->comboBox_brush_style->addItem(tr("Dense 6"),static_cast<int>(Qt::Dense6Pattern));
    ui->comboBox_brush_style->addItem(tr("Dense 7"),static_cast<int>(Qt::Dense7Pattern));
    ui->comboBox_brush_style->addItem(tr("Linear Gradient"),static_cast<int>(Qt::LinearGradientPattern));
    ui->comboBox_brush_style->addItem(tr("Radial Gradient"),static_cast<int>(Qt::RadialGradientPattern));
    ui->comboBox_brush_style->addItem(tr("Conical Gradient"),static_cast<int>(Qt::ConicalGradientPattern));




}

ShapeMaker::~ShapeMaker()
{
    delete ui;
}


void ShapeMaker::on_comboBox_shape_activated(int index)
{
    ShapeCanvas::Shape shape = ShapeCanvas::Shape(index);
       ui->ShapeCanvas_widget->setShape(shape);
}

void ShapeMaker::on_spinBox_pen_width_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
      penChanged();

}

void ShapeMaker::on_comboBox_pen_style_activated(int index)
{
    Q_UNUSED(index);
        penChanged();
}

void ShapeMaker::on_comboBox_pen_cap_activated(int index)
{
    Q_UNUSED(index);
    penChanged();
}

void ShapeMaker::on_comboBox_pen_join_activated(int index)
{
    Q_UNUSED(index);
       penChanged();
}

void ShapeMaker::on_comboBox_brush_style_activated(int index)
{
    Q_UNUSED(index);
        brushChanged();
}

void ShapeMaker::on_checkBox_antialising_toggled(bool checked)
{
   ui->ShapeCanvas_widget->setAntialiased(checked);
}

void ShapeMaker::on_checkBox_trasnform_toggled(bool checked)
{
   ui->ShapeCanvas_widget->setTransformed(checked);
}

void ShapeMaker::penChanged()
{
  int penwidth = ui->spinBox_pen_width->value();

  Qt::PenStyle style = Qt::PenStyle(ui->comboBox_pen_style->itemData(
                                        ui->comboBox_pen_style->currentIndex()).toInt());

  Qt::PenCapStyle cap = Qt::PenCapStyle(ui->comboBox_pen_cap->itemData(
                                        ui->comboBox_pen_cap->currentIndex()).toInt());

  Qt::PenJoinStyle join = Qt::PenJoinStyle(ui->comboBox_pen_join->itemData(
                                        ui->comboBox_pen_join->currentIndex()).toInt());
   QPen pen;
   pen.setWidth(penwidth);
   pen.setStyle(style);
   pen.setCapStyle(cap);
   pen.setJoinStyle(join);

   ui->ShapeCanvas_widget->setPen(pen);
}

void ShapeMaker::brushChanged()
{
    Qt::BrushStyle style = Qt::BrushStyle(ui->comboBox_brush_style->itemData(
                 ui->comboBox_brush_style->currentIndex()).toInt());

         if (style == Qt::LinearGradientPattern) {
             QLinearGradient linearGradient(250+125, 80+125, 50, 50);
             linearGradient.setColorAt(0, Qt::green);
             linearGradient.setColorAt(1, Qt::yellow);
              linearGradient.setSpread(QGradient::RepeatSpread);
             ui->ShapeCanvas_widget->setBrush(linearGradient);
         } else if (style == Qt::RadialGradientPattern) {
             QRadialGradient radialGradient(250+125, 80+125, 30);
             radialGradient.setColorAt(0, Qt::green);
             radialGradient.setColorAt(1, Qt::yellow);
             radialGradient.setSpread(QGradient::RepeatSpread);
             ui->ShapeCanvas_widget->setBrush(radialGradient);
         } else if (style == Qt::ConicalGradientPattern) {
             QConicalGradient conicalGradient(250+125, 80+125, 100);
              conicalGradient.setColorAt(0, Qt::green);
             conicalGradient.setColorAt(1, Qt::yellow);
              conicalGradient.setSpread(QGradient::RepeatSpread);
             ui->ShapeCanvas_widget->setBrush(conicalGradient);
         } else if (style == Qt::TexturePattern) {
             ui->ShapeCanvas_widget->setBrush(QBrush(QPixmap(QPixmap("E:/pic3.png").scaled(30,30))));
         } else {
             ui->ShapeCanvas_widget->setBrush(QBrush(Qt::blue, style));
         }
}
