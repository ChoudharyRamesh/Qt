#include "stareditor.h"
#include<QtCore/qmath.h>

StarEditor::StarEditor(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
    tempWidth= (width()/5);
    h = height();
   if(tempWidth/2>h/2) { r=h/2; transform=h; w=h; }
   else { r=tempWidth/2; transform=tempWidth; w=tempWidth; }
}

StarEditor::~StarEditor()
{

}

void StarEditor::mouseMoveEvent(QMouseEvent *event)
{
    tempWidth= (width()/5);
    h = height();
   if(tempWidth/2>h/2) { r=h/2; transform=h; w=h; }
   else { r=tempWidth/2; transform=tempWidth; w=tempWidth; }

    rating= (event->x()+(w/2))/(w);
    if(rating<6){
        update();
    }
}

int StarEditor::getStarRating() const
{
    return rating;
}

void StarEditor::setStarRating(int value)
{
    rating = value;
}

void StarEditor::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);

    emit editingFinished();
}

void StarEditor::paintEvent(QPaintEvent *event)
{
    int ir = r*0.38196601125;  // ineer radius of star
   QPoint a = QPoint(r*qCos(qDegreesToRadians(-18.0f)), r*qSin(qDegreesToRadians(-18.0f)));
   QPoint b = QPoint(r*qCos(qDegreesToRadians(54.0f)), r*qSin(qDegreesToRadians(54.0f)));
   QPoint c = QPoint(r*qCos(qDegreesToRadians(126.0f)), r*qSin(qDegreesToRadians(126.0f)));
   QPoint d = QPoint(r*qCos(qDegreesToRadians(198.0f)), r*qSin(qDegreesToRadians(198.0f)));
   QPoint e = QPoint(r*qCos(qDegreesToRadians(270.0f)), r*qSin(qDegreesToRadians(270.0f)));

   QPoint ad = QPoint(ir*qCos(qDegreesToRadians(-54.0f)), ir*qSin(qDegreesToRadians(-54.0f)));
   QPoint bd = QPoint(ir*qCos(qDegreesToRadians(18.0f)), ir*qSin(qDegreesToRadians(18.0f)));
   QPoint cd = QPoint(ir*qCos(qDegreesToRadians(90.0f)), ir*qSin(qDegreesToRadians(90.0f)));
   QPoint dd = QPoint(ir*qCos(qDegreesToRadians(162.0f)), ir*qSin(qDegreesToRadians(162.0f)));
   QPoint ed = QPoint(ir*qCos(qDegreesToRadians(234.0f)), ir*qSin(qDegreesToRadians(234.0f)));

   poly.clear();
   poly<<e<<ad<<a<<bd<<b<<cd<<c<<dd<<d<<ed<<e;


   Q_UNUSED(event);
   QPainter painter(this);
   painter.save();
   painter.setRenderHint(QPainter::Antialiasing, true);
   painter.setBrush(Qt::black);
   painter.drawRect(rect());
   painter.setPen(Qt::NoPen);
   painter.setBrush(Qt::white);

   for(int i=0;i<5;i++)
   {
       painter.resetTransform();
       painter.translate(r+(transform*i),h/2);
       painter.drawPolygon(poly);
   }

   painter.setBrush(Qt::green);
   for(int i=0;i<rating && i<5 ;i++)
   {
       painter.resetTransform();
       painter.translate(r+(transform*i),h/2);
       painter.drawPolygon(poly);
   }

   painter.restore();

}

void StarEditor::resizeEvent(QResizeEvent *event)
{
    tempWidth= (width()/5);
    h = height();
   if(tempWidth/2>h/2) { r=h/2; transform=h; w=h; }
   else { r=tempWidth/2; transform=tempWidth; w=tempWidth; }
   update();
   QWidget::resizeEvent(event);
}

