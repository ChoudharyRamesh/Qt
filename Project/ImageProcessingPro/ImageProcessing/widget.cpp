#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QLabel>


void drawPoints(QImage * image ,QList<QPoint> plist)
{
    QPainter painter(image);
    QPen pen;

    pen.setWidth(2);
    pen.setColor("yellow");
    painter.setPen(pen);
     painter.drawPoints(plist);

    //painter.drawPolygon(QPolygon(plist).boundingRect());

//    pen.setColor("green");
//    pen.setWidth(2);
//    painter.setPen(pen);
//    painter.drawPolygon(QPolygon(plist));
}


void drawLine(QImage * image,float slop,float constant)
{

    QPoint p1(0,constant),p2(image->width(), slop*image->width()+constant);
    QPainter painter(image);
    QPen pen; pen.setWidth(5);
    pen.setColor("blue");
    painter.setPen(pen);
    painter.drawLine(p1,p2);
}

void drawTwoColorPoint(QImage * image,QPoint p1,QPoint p2)
{
    QPainter painter(image);
    QPen pen; pen.setWidth(5);
    pen.setColor("red");
    painter.setPen(pen);
    painter.drawPoint(p1);
    pen.setColor("blue");
    painter.setPen(pen);
    painter.drawPoint(p2);
}



Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QLayout * verticalLayout = ui->scrollAreaWidget->layout();


    for(int iteration =1;iteration<=12;iteration++)
    {
        QHBoxLayout * hb = new QHBoxLayout;
        QLabel * lable1 =new QLabel(ui->scrollAreaWidget);
        QImage image("C:/mycode/Qt Quick/ImageProcessing/temp"+QString::number(iteration)+".png");
        lable1->setMinimumSize(50,210);
        lable1->setPixmap(QPixmap::fromImage(image));
        QLabel * lable2 =new QLabel(ui->scrollAreaWidget);
        lable2->setMinimumSize(50,210);


        ///
        QList<QPoint> finalPointList;
        QList<QPoint> finalTwoPointList;
        bool square = true;
        QList<QPair<float,float>> lineSlopeAndConstant;
        int nextX=0;
        for(int angle=0;angle<4;angle++)
        {
            QTransform transform;
            transform.rotate(-angle*90);
            image= image.transformed(transform);

            QList<QPoint> pointListinternal;
            bool recording=false;
            QPoint temp(0,image.height());

            int x=nextX;
            for(;x<image.width();x++)
            {
                for(int y=0;y<image.height();y++)
                {
                    int grey =  qGray(image.pixel(x,y));
                    if(grey==0)
                    {
                        if(y<temp.y())recording=true;
                        else if(y>temp.y())
                        {
                            if(recording==true)
                            {
                                pointListinternal.append(temp);
                                recording=false;
                            }
                        }
                        temp=QPoint(x,y);
                        break;
                    }
                }
            }

            if(pointListinternal.isEmpty()) pointListinternal.append(temp);
            else if(temp.y()<pointListinternal.last().y()) pointListinternal.append(temp);

            if(pointListinternal.size()==1)
            {
                int lastX = image.width()/2;
                for(int y=0;y<image.height();y++)
                {
                    int grey =  qGray(image.pixel(lastX,y));
                    if(grey==0)
                    {
                        if(temp.y()<y && !pointListinternal.contains(temp))
                            pointListinternal.append(temp);
                        else
                        {
                            if(lastX<pointListinternal.last().x())
                                pointListinternal.prepend(QPoint(lastX,y));
                            else
                                pointListinternal.append(QPoint(lastX,y));
                        }
                        break;
                    }
                }

                drawTwoColorPoint(&image,pointListinternal.at(0),pointListinternal.at(1)); //temp
            }

            nextX=pointListinternal.last().y();

            if(pointListinternal.size()>=2 && square)
            {  // reduce pointListinternal into two point which has lowest y value
                // and sort according to ascending x value
                auto tempPointList = pointListinternal;
                QPoint min1,min2; int index=0;

                for(int t=0;t<tempPointList.size();t++)
                {
                    if(min1.isNull())min1=tempPointList.at(t);
                    else  if(tempPointList.at(t).y()<min1.y())
                    {  min1 = tempPointList.at(t); index=t; }
                }

                tempPointList.removeAt(index);

                for(int t=0;t<tempPointList.size();t++)
                {
                     if(min2.isNull())min2=tempPointList.at(t);
                     else if(tempPointList.at(t).y()<min2.y())
                         min2 = tempPointList.at(t);
                }


                if(min1.x()<min2.x())
                {
                     finalTwoPointList.append(min1);
                     finalTwoPointList.append(min2);
                }
                else
                {
                    finalTwoPointList.append(min2);
                    finalTwoPointList.append(min1);
                }

                // make line
                float slope,constant;
                if(min2.x()-min1.x()==0)slope=INFINITY;
                else slope = (float)(min2.y()-min1.y())/(float)(min2.x()-min1.x());
                constant = -slope*min1.x()+min1.y();
                  drawLine(&image,slope,constant);
                lineSlopeAndConstant.append(QPair<float,float>(slope,constant));
                qDebug()<<slope<<" "<<constant<<"\n\n";
            }

            //90
            if(angle==1)
            { for(int i=0;i<pointListinternal.size();i++)
                {
                    QPoint tp =pointListinternal.at(i);
                    pointListinternal[i]=QPoint(image.height()-tp.y(),tp.x());
                }
            }

            //180
            if(angle==2)
            { for(int i=0;i<pointListinternal.size();i++)
                {
                    QPoint tp =pointListinternal.at(i);
                    pointListinternal[i]=QPoint(image.width()-tp.x(),image.height()-tp.y());
                }
            }


            //270
            if(angle==3)
            { for(int i=0;i<pointListinternal.size();i++)
                {
                    QPoint tp =pointListinternal.at(i);
                    pointListinternal[i]=QPoint(tp.y(),image.width()-tp.x());
                }
            }

            transform.reset();
            transform.rotate(angle*90);
            image= image.transformed(transform);
            finalPointList.append(pointListinternal);


        }

        drawPoints(&image,finalPointList);
        ///

        lable2->setPixmap(QPixmap::fromImage(image));
        hb->addWidget(lable1);
        hb->addWidget(lable2);
        verticalLayout->addItem(hb);

    }
}

Widget::~Widget()
{
    delete ui;
}

