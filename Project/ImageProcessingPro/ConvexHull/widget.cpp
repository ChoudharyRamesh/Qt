#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QLabel>
#include<QList>
#include<vector>
#include<QStack>

////////////////////////////////////////////////////////////
// A global point needed for  sorting points with reference
// to  the first point Used in compare function of qsort()
QPointF p0;

// A utility function to find next to top in a stack
QPointF nextToTop(QStack<QPointF> &S)
{
    QPointF p = S.top();
    S.pop();
    QPointF res = S.top();
    S.push(p);
    return res;
}

// A utility function to swap two points
void swap(QPointF &p1, QPointF &p2)
{
    QPointF temp = p1;
    p1 = p2;
    p2 = temp;
}

// A utility function to return square of distance
// between p1 and p2
int distSq(QPointF p1, QPointF p2)
{
    return (p1.x() - p2.x())*(p1.x() - p2.x()) +
            (p1.y() - p2.y())*(p1.y() - p2.y());
}

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(QPointF p, QPointF q, QPointF r)
{
    int val = (q.y() - p.y()) * (r.x() - q.x()) -
            (q.x() - p.x()) * (r.y() - q.y());

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// A function used by library function qsort() to sort an array of
// points with respect to the first point
int compare(const void *vp1, const void *vp2)
{
    QPointF *p1 = (QPointF *)vp1;
    QPointF *p2 = (QPointF *)vp2;

    // Find orientation
    int o = orientation(p0, *p1, *p2);
    if (o == 0)
        return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;

    return (o == 2)? -1: 1;
}

// return convex hull of a set of n points.
QList<QPointF> convexHull(QList<QPointF> points)
{
    int n = points.size();
    // Find the bottommost point
    int ymin = points[0].y(), min = 0;
    for (int i = 1; i < n; i++)
    {
        int y = points[i].y();

        // Pick the bottom-most or chose the left
        // most point in case of tie
        if ((y < ymin) || (ymin == y &&
                           points[i].x() < points[min].x()))
            ymin = points[i].y(), min = i;
    }

    // Place the bottom-most point at first position
    swap(points[0], points[min]);

    // Sort n-1 points with respect to the first point.
    // A point p1 comes before p2 in sorted output if p2
    // has larger polar angle (in counterclockwise
    // direction) than p1
    p0 = points[0];
    qsort(&points[1], n-1, sizeof(QPointF), compare);

    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0
    // Remember that, in above sorting, our criteria was
    // to keep the farthest point at the end when more than
    // one points have same angle.
    int m = 1; // Initialize size of modified array
    for (int i=1; i<n; i++)
    {
        // Keep removing i while angle of i and i+1 is same
        // with respect to p0
        while (i < n-1 && orientation(p0, points[i],
                                      points[i+1]) == 0)
            i++;


        points[m] = points[i];
        m++;  // Update size of modified array
    }

    // If modified array of points has less than 3 points,
    // convex hull is not possible
    if (m < 3) return QList<QPointF>();

    // Create an empty stack and push first three points
    // to it.
    QStack<QPointF> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Process remaining n-3 points
    for (int i = 3; i < m; i++)
    {
        // Keep removing top while the angle formed by
        // points next-to-top, top, and points[i] makes
        // a non-left turn
        while (S.size()>1 && orientation(nextToTop(S), S.top(), points[i]) != 2)
            S.pop();
        S.push(points[i]);
    }

    // Now stack has the output points, print contents of stack

    QList<QPointF> hullPoints;
    while (!S.empty())
    {
        hullPoints.append(S.top());
        S.pop();
    }
    return hullPoints;
}


QList<QPointF> getSharpPoint(QImage  image)
{
    QList<QPointF> finalpoints;

    int nextX=0;
    for(int angle=0;angle<4;angle++)
    {
        QTransform transform;
        transform.rotate(-angle*90);
        image = image.transformed(transform);
        int x=nextX;
        QPointF lastPoint(0,0),middlePoint(0,0),nextPoint;
        QList<QPointF> points;

        for(;x<image.width();x++)
        {
            for(int y=0;y<image.height();y++)
            {
                if(qGray(image.pixel(x,y))==0)
                {
                    if(nextPoint.isNull()){nextPoint=middlePoint=QPointF(x,y);}

                    lastPoint=middlePoint;
                    middlePoint=nextPoint;
                    nextPoint = QPointF(x,y);

                    float radian_slopeLast,radian_slopeCurrent;

                    if(middlePoint.x()-lastPoint.x()==0)radian_slopeLast=0.15070796;
                    else  radian_slopeLast = ((middlePoint.y()-lastPoint.y())/(middlePoint.x()-lastPoint.x()));
                    if(nextPoint.x()-middlePoint.x()==0)radian_slopeCurrent=0.15070796;
                    else  radian_slopeCurrent = ((nextPoint.y()-middlePoint.y())/(nextPoint.x()-middlePoint.x()));

                    if(radian_slopeLast!=radian_slopeCurrent)
                        if(!finalpoints.contains(middlePoint))
                            points.append(middlePoint);

                    break;
                }
            }
        }

        nextX=points.last().y();


        //90
        if(angle==1)
        { for(int i=0;i<points.size();i++)
            {
                QPointF tp =points.at(i);
                points[i]=QPointF(image.height()-tp.y(),tp.x());
            }
        }

        //180
        if(angle==2)
        { for(int i=0;i<points.size();i++)
            {
                QPointF tp =points.at(i);
                points[i]=QPointF(image.width()-tp.x(),image.height()-tp.y());
            }
        }

        //270
        if(angle==3)
        { for(int i=0;i<points.size();i++)
            {
                QPointF tp =points.at(i);
                points[i]=QPointF(tp.y(),image.width()-tp.x());
            }
        }

        transform.reset();
        transform.rotate(angle*90);
        image= image.transformed(transform);
        finalpoints.append(points);
    }


    finalpoints=convexHull(finalpoints);

    return  finalpoints;
}


void drawPoints(QImage * image ,QList<QPointF> plist)
{
    QPainter painter(image);
    QPen pen;
    pen.setWidth(5);
    int r=0,g=0,b=255;
    for(int i=0;i<plist.size();i++)
    {
        if(g==0 && b==255){b=0; r=255;}
        else if(r==255 && b==0){r=0; g=255;}
        else if(r==0 && g==255){g=0; b=255; }
        pen.setColor(QColor::fromRgb(r,g,b));
        painter.setPen(pen);
        painter.drawPoint(plist.at(i));
    }
}

void drawRect(QImage * image,QRectF rect)
{
    QPainter painter(image);
    QPen pen;
    pen.setColor("red");
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawRect(rect);
}

void drawPolygon(QImage * image ,QList<QPointF> plist,QString color="cyan")
{
    QPainter painter(image);
    QPen pen;
    pen.setColor(color);
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawPolygon(QPolygonF(plist));
}



class Caliper
{

public:

    static QList<QPointF> rotatePolygon(QList<QPointF> points,double angle,QPointF rotateAround)
    {
        QTransform t;
        t.translate(rotateAround.x(),rotateAround.y());
        t.rotate(angle);
        t.translate(-rotateAround.x(),-rotateAround.y());
        return t.map(points);
    }

    static QPair<QRectF,double> minimumBox(QList<QPointF> polygon,QPointF center)
    {
        QRectF minRect = QRectF(QPointF(0,0),QSizeF(INFINITY,INFINITY));
        if(polygon.size()<3)return QPair<QRectF,double>();
        int edges = polygon.size();
        double angleOfMinRect;

        for(int i=0;i<edges;i++)
        {
            //find angle with y axis of edge at index i
            QPointF p1= polygon.at(i);
            QPointF p2;
            if(i!=edges-1) p2= polygon.at(i+1);
            else p2= polygon.at(0);
            double xProjection = p1.x()-p2.x();
            double yProjection = p1.y()-p2.y();
            double distance = qSqrt(  (xProjection*xProjection)  + (yProjection*yProjection)   );
            double angle = qRadiansToDegrees(qAcos(yProjection/distance));

            //rotate polygon and find minimum area
            polygon=rotatePolygon(polygon,angle,center);
            QRectF boundingRect = QPolygonF(polygon).boundingRect();
            double area = boundingRect.width()*boundingRect.height();
            if(area<minRect.width()*minRect.height())
            {  //update min rect
                  angleOfMinRect=angle;
                  minRect=boundingRect;
            }

            //rotate back
            polygon=rotatePolygon(polygon,-angle,center);
        }
       return QPair<QRectF,double>(minRect,-angleOfMinRect);
    }
};




Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QLayout * verticalLayout = ui->scrollAreaWidget->layout();

    for(int iteration =1;iteration<=13;iteration++)
    {
        QHBoxLayout * hb = new QHBoxLayout;
        QLabel * lable1 =new QLabel(ui->scrollAreaWidget);
        QLabel * lable2 =new QLabel(ui->scrollAreaWidget);
        lable1->setMinimumSize(50,210);
        lable2->setMinimumSize(50,210);
        QImage tempImage;
        QImage image("C:/mycode/Qt Quick/ImageProcessing/testImage/nbg/temp"+QString::number(iteration)+".png");


        tempImage =image = image.scaled(310,210,Qt::KeepAspectRatio,Qt::SmoothTransformation);
        lable1->setPixmap(QPixmap::fromImage(tempImage));

        for(int x=0;x<image.width();x++)
        {
            for(int y=0;y<image.height();y++)
            {
                if(qGray(image.pixel(x,y))>190)
                    image.setPixel(x,y,qRgb(0,0,0));
                else image.setPixel(x,y,qRgb(255,255,255));
            }
        }

        auto point = getSharpPoint(image);
        drawPolygon(&tempImage,point,"red");
        auto prect = Caliper::minimumBox(point,QPointF(image.width()/2,image.height()/2));
        auto polygon = Caliper::rotatePolygon(QPolygonF(prect.first),prect.second,QPointF(image.width()/2,image.height()/2));
        drawPolygon(&tempImage,polygon,"yellowgreen");


        lable2->setPixmap(QPixmap::fromImage(tempImage));
        hb->addWidget(lable1);
        hb->addWidget(lable2);
        verticalLayout->addItem(hb);
    }

}

Widget::~Widget()
{
    delete ui;
}
