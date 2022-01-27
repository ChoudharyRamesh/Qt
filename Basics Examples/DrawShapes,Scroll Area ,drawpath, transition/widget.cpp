#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{

}

void Widget::paintEvent(QPaintEvent *event)
{
    QBrush brush(Qt::green);
    QPainter painter(this);
    QPen pen(Qt::red);
    // pen style
    pen.setStyle(Qt::DashLine);
    pen.setStyle(Qt::NoPen);
    pen.setStyle(Qt::DotLine);
    pen.setStyle(Qt::DashDotLine);
    pen.setStyle(Qt::DashDotDotLine);
    //custom pen style
    QVector<qreal> dashes;
    qreal space = 4;
    dashes<<1<<space<<3<<space<<9<<space<<27<<space<<9<<space;
    pen.setDashPattern(dashes);
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(4);
    painter.setPen(pen);
    painter.setBrush(brush);

    // draw rect
    painter.drawRect(10,10,100,100);

    //draw ellipse
    painter.drawEllipse(120,10,200,100);

    //draw round rectangle
    painter.drawRoundedRect(330,10,100,100,20,20);

    //draw lines
    painter.drawLine(450,30,550,30);
    painter.drawLine(450,50,550,50);
    painter.drawLine(450,70,550,70);
    painter.drawLine(450,90,550,90);

    // prepare vector of points
    QVector<QPointF> vecpoints;
    vecpoints<<QPointF(560,30)<<QPointF(660,30);
    vecpoints<<QPointF(560,50)<<QPointF(660,50);
    vecpoints<<QPointF(560,70)<<QPointF(660,70);
    vecpoints<<QPointF(560,90)<<QPointF(660,90);
    painter.drawLines(vecpoints);

    //polygons
    // prepare polygon
    QPolygonF polygon;
    polygon<<QPointF(240.0,150.0)<<QPointF(10.0,150.0)<<
             QPointF(60.0,200.0)<<
             QPointF(30.0,300.0)<<QPointF(120.0,300.0);
    painter.drawPolygon(polygon);


    //draw arc
    QRectF rectangle(250.0,150.0,150.0,150.0);
    int startAngle = 30*16;
    int endAngle =240*16;
    painter.drawArc(rectangle,startAngle,endAngle);

    // draw chord
    QRectF crectangle(450.0,150.0,150.0,150.0);
    int cstartAngle = 30*16;
    int cendAngle =240*16;
    painter.drawChord(crectangle,cstartAngle,cendAngle);

    // draw chord
    QRectF prectangle(650.0,150.0,150.0,150.0);
    int pstartAngle = 30*16;
    int pendAngle =240*16;
    painter.drawPie(prectangle,pstartAngle,pendAngle);

    // Draw Text
    QFont font("Consolas",20,QFont::Bold);
    painter.setFont(font);
    painter.drawText(10,310,150,200,Qt::AlignHCenter | Qt::AlignVCenter,"Hello\nworld");

    // draw pixmap
    QPixmap pixmap("E:/pic3.png");
    painter.drawPixmap(170,310,150,200,pixmap);

    // cap style
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidth(20);
    painter.setPen(pen);
    painter.drawLine(340,385,450,385);
    // restore
    pen.setWidth(4);
    painter.setPen(pen);

    //pen join style
    QPointF points[4]=
    {
        QPointF(455.0,310.0), QPointF(555.0,325.0), QPointF(470.0,380), QPointF(500.0,380)
    };
    pen.setJoinStyle(Qt::MiterJoin);
    pen.setJoinStyle(Qt::BevelJoin);
    pen.setJoinStyle(Qt::RoundJoin);
    painter.setPen(pen);
    painter.drawPolygon(points,4);
    //restore
    pen.setJoinStyle(Qt::MiterJoin);

    // brush styles
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(10,560,100,100);
    brush.setStyle(Qt::Dense1Pattern);
    painter.setBrush(brush);
    painter.drawRect(120,560,100,100);
    brush.setStyle(Qt::Dense2Pattern);
    painter.setBrush(brush);
    painter.drawRect(230,560,100,100);
    brush.setStyle(Qt::Dense3Pattern);
    painter.setBrush(brush);
    painter.drawRect(340,560,100,100);
    brush.setStyle(Qt::Dense4Pattern);
    painter.setBrush(brush);
    painter.drawRect(450,560,100,100);
    brush.setStyle(Qt::Dense5Pattern);
    painter.setBrush(brush);
    painter.drawRect(560,560,100,100);
    brush.setStyle(Qt::Dense6Pattern);
    painter.setBrush(brush);
    painter.drawRect(670,560,100,100);
    brush.setStyle(Qt::Dense7Pattern);
    painter.setBrush(brush);
    painter.drawRect(780,560,100,100);

    brush.setStyle(Qt::NoBrush);
    painter.setBrush(brush);
    painter.drawRect(10,670,100,100);
    brush.setStyle(Qt::HorPattern);
    painter.setBrush(brush);
    painter.drawRect(120,670,100,100);
    brush.setStyle(Qt::VerPattern);
    painter.setBrush(brush);
    painter.drawRect(230,670,100,100);
    brush.setStyle(Qt::CrossPattern);
    painter.setBrush(brush);
    painter.drawRect(340,670,100,100);
    brush.setStyle(Qt::BDiagPattern);
    painter.setBrush(brush);
    painter.drawRect(450,670,100,100);
    brush.setStyle(Qt::FDiagPattern);
    painter.setBrush(brush);
    painter.drawRect(560,670,100,100);
    brush.setStyle(Qt::DiagCrossPattern);
    painter.setBrush(brush);
    painter.drawRect(670,670,100,100);

    // texture
    brush.setTexture(QPixmap("E:/pic3.png").scaled(50,50,Qt::KeepAspectRatio));
    painter.setBrush(brush);
    painter.drawRect(780,670,100,100);

    // restore
    brush.setStyle(Qt::SolidPattern);

    // gradient type
    QRadialGradient gradient(210,980,80);
    gradient.setColorAt(0, Qt::green);
    gradient.setColorAt(1, Qt::yellow);
    //spread type
    gradient.setSpread(QGradient::ReflectSpread);
    gradient.setSpread(QGradient::PadSpread);
    gradient.setSpread(QGradient::RepeatSpread);
    QBrush newBrush(gradient);
    painter.setBrush(newBrush);
    painter.drawRect(10,780,400,400);


    QConicalGradient gradient2(620,980,80);
    gradient2.setColorAt(0, Qt::green);
    gradient2.setColorAt(1, Qt::yellow);
    //spread type
    gradient2.setSpread(QGradient::ReflectSpread);
    gradient2.setSpread(QGradient::PadSpread);
    gradient2.setSpread(QGradient::RepeatSpread);
    QBrush newBrush2(gradient2);
    painter.setBrush(newBrush2);
    painter.drawRect(420,780,400,400);

    QLinearGradient gradient3;
    gradient3.setColorAt(0, Qt::green);
    gradient3.setColorAt(1, Qt::yellow);
    //spread type
    gradient3.setSpread(QGradient::ReflectSpread);
    gradient3.setSpread(QGradient::PadSpread);
    gradient3.setSpread(QGradient::RepeatSpread);
    QBrush newBrush3(gradient3);
    painter.setBrush(newBrush3);
    painter.drawRect(830,780,400,400);


    //restore
    painter.setBrush(brush);
    //painter path
    QPainterPath path;
    // path.addRect(10,1300,100,100);
    path.addEllipse(10,1200,200,200);
    path.addEllipse(500,1200,200,200);
    path.moveTo(110,1200);
    path.lineTo(600,1200);
    path.moveTo(110,1400);
    path.lineTo(600,1400);
    painter.drawPath(path);
    path.translate(250,250);
    painter.drawPath(path);


    //painter rotate transform ( actually coordinate system is going to transform not object )
    painter.drawRect(100,1850,200,200);
    painter.translate(200,1950);
    painter.rotate(45);
    painter.translate(-200,-1950);
    painter.drawRect(100,1850,200,200);

    //restore transform
    //     painter.translate(200,1950);
    //    painter.rotate(-45);
    //    painter.translate(-200,-1950);
    //or
    painter.resetTransform();


    //painter scale transform
    painter.scale(1.14,1.02);
    painter.setBrush(Qt::NoBrush);
    painter.drawRect(100,1850,200,200);
    painter.resetTransform();


    //painter shear transform
    painter.drawRect(100,2200,200,200);
    painter.translate(200,2300);
    painter.shear(0.2,0.2);
    painter.translate(-200,-2300);
    painter.drawRect(100,2200,200,200);
    painter.resetTransform();




}


QSize Widget::sizeHint() const
{
    return QSize(1500,3000);
}
