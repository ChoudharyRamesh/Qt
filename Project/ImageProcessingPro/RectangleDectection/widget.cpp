#include "widget.h"
#include "ui_widget.h"

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
        QLabel * lable2 =new QLabel(ui->scrollAreaWidget);
        lable1->setMinimumSize(800,800);
        lable2->setMinimumSize(800,800);
        QImage image("C:/mycode/Qt Quick/ImageProcessing/testImage/nbg/temp"+QString::number(iteration)+".png");
        lable1->setPixmap(QPixmap::fromImage(image.scaled(800,800,Qt::KeepAspectRatio,Qt::SmoothTransformation)));

        image = image.scaled(400,400,Qt::KeepAspectRatio,Qt::SmoothTransformation);

        image = Convolution2(image,generateGaussianKernel(2,1));
        image=drawEdge(&image);
        image = MedianFilter(image,1);

        image = image.scaled(800,800,Qt::KeepAspectRatio,Qt::SmoothTransformation);
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

QList<QList<double> > Widget::generateGaussianKernel(unsigned int radius, double sigma)
{
    // G(x,y)= {1/sqrt(2.pi.sigma^2)}.e^-(x^2+y^2 / 2.sigma^2)
    // where sigma is deviation,
    // x is the distance from the origin in the horizontal axis, y is the distance from the origin in the vertical axis
    // source :- https://en.wikipedia.org/wiki/Gaussian_blur

    // reform
    // G(x,y) = constant1 . e^-(var/ constant2);
    // where var = x^2+y^2 ; constant1 = 1/sqrt(2.pi.sigma^2; constant2= 2.sigma^2;

    int kernelSize = 2*radius+1;
    QList<QList<double>> kernel(kernelSize,QList<double>(kernelSize));
    double constant2 = 5*sigma*sigma;
    double constant1 = 1/qSqrt(constant2*M_PI_2);
    double var =0;
    double sumForNormalize=0;


    //generate kernal
    int center = kernelSize/2;
    for(int x=-center;x<=center;x++)
        for(int y=-center;y<=center;y++)
        {
            var = (x*x)+(y*y);
            kernel[x+center][y+center]=constant1*qExp(-(var/constant2));
            sumForNormalize+= kernel[x+center][y+center];
        }

    //normalize
    for(int y=0;y<kernelSize;y++)
        for(int x=0;x<kernelSize;x++)
            kernel[x][y] = kernel[x][y]/sumForNormalize;

    return kernel;
}

QImage Widget::Convolution2(const QImage & image, const QList<QList<double> > &kernel)
{
    if(kernel.size()<0)return QImage();
    if(kernel.size()!=kernel.at(0).size())return QImage();

    int kernelSize =  kernel.size();
    int offset = kernelSize/2;
    int width = image.width();
    int height = image.height();
    QImage out(width,height,image.format());
    double g;

    for(int y=0;y<height;y++)
    {
        QList<QRgb * > scanlines;
        for(int line=y-offset;line<=y+offset;line++)
            scanlines.append((QRgb *)image.scanLine(qBound(0,line,height-1)));

        QRgb * outputLine = (QRgb *)out.scanLine(y);

        for(int x=0;x<width;x++)
        {
            g=0;
            for(int yd=0;yd<kernelSize;yd++)
            {
                QRgb * currentLine = scanlines.at(yd);

                for(int xd=x-offset;xd<=x+offset;xd++)
                {
                    int iIndex= qBound(0,xd,width-1);
                    int kindex = kernelSize -(xd-(x-offset))-1;
                    g+= qGray(currentLine[iIndex])   *  kernel.at(kindex).at(kernelSize-yd-1);
                }
            }
            outputLine[x]=qRgb(g,g,g);
        }
    }
    return out;
}

QImage Widget::MedianFilter(const QImage &image, unsigned int radius)
{
    int kernalSize = 2*radius+1;
    int center = kernalSize/2;
    int width = image.width();
    int height = image.height();
    QImage outPutImage(width,height,image.format());

    for(int y=0;y<height;y++)
    {
        QList<QRgb * > scanLines;
        for(int line=y-center;line<=y+center;line++)
            scanLines.append((QRgb *)image.scanLine(qBound(0,line,height-1)));

        QRgb * outputMiddle = (QRgb *)outPutImage.scanLine(y);

        for(int x=0;x<width;x++)
        {
            QList<unsigned int> pixels;
            for(int i=0;i<kernalSize;i++)
                for(int j=x-center;j<=x+center;j++)
                    pixels.append(scanLines.at(i)[qBound(0,j,width-1)]);

            std::sort(pixels.begin(),pixels.end());
            int size = pixels.size();
            unsigned int median;
            if(size%2!=0)median=pixels.at(size/2);
            else median = (pixels.at(size/2)+pixels.at(size/2+1))/2;

            outputMiddle[x]=median;
        }
    }
    return outPutImage;
}


void Widget::grayScale(QImage *image, unsigned int threshold)
{
    QRgb* scanline;
    for(int y=1;y<image->height()-1;y++)
    {
        scanline =(QRgb *)image->scanLine(y);
        for(int x=1;x<image->width()-1;x++)
        {
            unsigned int  gray =  qGray(scanline[x]);
            if(gray>threshold)
                scanline[x]=qRgb(gray,gray,gray);
            else  scanline[x]=qRgb(0,0,0);
        }
    }
}

void Widget::Blur(QImage *image, float power)
{
    float c[3]={0};
    unsigned char * pixels = image->bits();

    for(int y=0;y<image->height();y++)
        for(int x=0;x<image->width();x++)
        {
            for(int i=0;i<3;i++)
            {
                c[i]=c[i]+power * (pixels[ 4 * (x+y*image->width()) + i]-c[i]);
                pixels[ 4 * (x+y*image->width()) + i]=c[i];
            }
        }

    for(int y=0;y<image->height();y++)
        for(int x=image->width()-1;x>=0;x--)
        {
            for(int i=0;i<3;i++)
            {
                c[i]=c[i]+power * (pixels[ 4 * (x+y*image->width()) + i]-c[i]);
                pixels[ 4 * (x+y*image->width()) + i]=c[i];
            }
        }

    for(int x=0;x<image->width();x++)
        for(int y=0;y<image->height();y++)
        {
            for(int i=0;i<3;i++)
            {
                c[i]=c[i]+power * (pixels[ 4 * (x+y*image->width()) + i]-c[i]);
                pixels[ 4 * (x+y*image->width()) + i]=c[i];
            }
        }

    for(int x=image->width()-1;x>=0;x--)
        for(int y=0;y<image->height();y++)
        {
            for(int i=0;i<3;i++)
            {
                c[i]=c[i]+power * (pixels[ 4 * (x+y*image->width()) + i]-c[i]);
                pixels[ 4 * (x+y*image->width()) + i]=c[i];
            }
        }
}

QImage Widget::boxBlur(const QImage &image, unsigned int radius)
{

    int kernelSize = 2*radius+1;
    int offset = kernelSize/2;
    int width = image.width();
    int height = image.height();
    int normlizeSum = kernelSize*kernelSize;
    QImage out(width,height,image.format());
    double r,g,b;

    for(int y=0;y<height;y++)
    {
        QList<QRgb * > scanlines;
        for(int line=y-offset;line<=y+offset;line++)
            scanlines.append((QRgb *)image.scanLine(qBound(0,line,height-1)));

        QRgb * outputLine = (QRgb *)out.scanLine(y);

        for(int x=0;x<width;x++)
        {
            r=g=b=0;
            for(int yd=0;yd<kernelSize;yd++)
            {
                QRgb * currentLine = scanlines.at(yd);

                for(int xd=x-offset;xd<=x+offset;xd++)
                {
                    int iIndex= qBound(0,xd,width-1);

                    r   +=   qRed(currentLine[iIndex]);
                    g  +=  qGreen(currentLine[iIndex]);
                    b  +=  qBlue(currentLine[iIndex]);
                }
            }
            outputLine[x]=qRgb(r/normlizeSum,g/normlizeSum,b/normlizeSum);
        }
    }
    return out;
}

QImage Widget::drawEdge(QImage *image)
{
    QImage outPut = *image;
    int kernel [3][3];

    kernel[0][0] = -1;  kernel[0][1] = -1; kernel[0][2] = -1;
    kernel[1][0] = -1;  kernel[1][1] =  8; kernel[1][2] = -1;
    kernel[2][0] = -1;  kernel[2][1] = -1; kernel[2][2] = -1;

    for(int y=1;y<image->height()-1;y++)
    {
        QRgb* top =(QRgb *)image->scanLine(y-1);
        QRgb* middle =(QRgb *)image->scanLine(y);
        QRgb* down =(QRgb *)image->scanLine(y+1);
        QRgb * outputMiddle = (QRgb *)outPut.scanLine(y);

        for(int x=1;x<image->width()-1;x++)
        {
            unsigned int pixelSumGray =
                    qGray(top[x-1])*kernel[2][2]+qGray(top[x])*kernel[2][1]+qGray(top[x+1])*kernel[2][0]+
                    qGray( middle[x-1])*kernel[1][2]+qGray(middle[x])*kernel[1][1]+qGray(middle[x+1])*kernel[1][0]+
                    qGray(down[x-1])*kernel[0][2]+qGray(down[x])*kernel[0][1]+qGray(down[x+1])*kernel[0][0];

            outputMiddle[x]= qRgb(pixelSumGray,pixelSumGray,pixelSumGray);
        }
    }

    return outPut;
}






















