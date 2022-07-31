#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QtMath>
#include<QDebug>
#include<QLabel>
#include<iostream>
#include<QQueue>
#include<QPair>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT


public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    QList<QList<double>> generateGaussianKernel(unsigned int radius=1,double sigma=1);
    QImage Convolution2(const QImage & image,const QList<QList<double>> & kernel);
    QImage MedianFilter(const QImage & image ,unsigned int  radius = 1);
    void grayScale(QImage * image,unsigned int  threshold=0);
    void Blur(QImage *image,float power=0.9);
    QImage boxBlur(const QImage & image,unsigned int radius=1);
    QImage drawEdge(QImage * image);

private:
    Ui::Widget *ui;
    QList<QList<double>> sobelx={{-1,0,1},{-2,0,2},{-1,0,1}};
    QList<QList<double>> sobely={{1,2,1},{0,0,0},{-1,-2,-1}};
 };
#endif // WIDGET_H
