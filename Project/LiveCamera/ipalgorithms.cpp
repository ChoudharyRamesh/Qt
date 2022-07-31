#include "ipalgorithms.h"
#include<QDebug>
#include<QPainter>

IPAlgorithms::IPAlgorithms(){}


float IPAlgorithms::getAreaOfQuadrilateral(QPolygonF quadrilateral)
{
    float a,b,c,d,e1,e2,s1,s2;
    a = QLineF(quadrilateral.at(0),quadrilateral.at(1)).length();
    b = QLineF(quadrilateral.at(1),quadrilateral.at(2)).length();
    c = QLineF(quadrilateral.at(2),quadrilateral.at(3)).length();
    d = QLineF(quadrilateral.at(3),quadrilateral.at(0)).length();

    e1 =  QLineF(quadrilateral.at(1),quadrilateral.at(3)).length();
    e2 =  QLineF(quadrilateral.at(0),quadrilateral.at(2)).length();

    float area;
    if(e2>e1)
    {
        s1 = (a+b+e2)/2;
        s2 = (c+d+e2)/2;
        area = sqrt(s1*(s1-a)*(s1-b)*(s1-e2))+sqrt(s2*(s2-c)*(s2-d)*(s2-e2));
    }
    else
    {
        s1 = (a+d+e1)/2;
        s2 = (c+b+e1)/2;
        area = sqrt(s1*(s1-a)*(s1-d)*(s1-e1))+sqrt(s2*(s2-c)*(s2-b)*(s2-e1));
    }

    return  area;
}



QList<QPair<QPolygonF,int>> IPAlgorithms::detectQuadrilateral(QList<QLineF> &detectedLines, int imageWidth, int imageHeight)
{
    //polygons with priority if polygon is outside of scene then its priority is 0 else 1
    QList<QPair<QPolygonF,int>> polygons;
    if(detectedLines.size()>=4)
    {
        QList<QLineF> approxHorizontal_lines,approxVertical_lines;
        for(auto line:detectedLines)
        {
            qreal angle = line.angle();
            if(angle>180)angle=angle-180;
            if( angle<=45 || 180-angle<=45 )approxHorizontal_lines.append(line);
            else approxVertical_lines.append(line);
        }

        for(int h1=0;h1<approxHorizontal_lines.size()-1;h1++)
        {
            for(int h2=h1+1;h2<approxHorizontal_lines.size();h2++)
            {
                for(int v1=0;v1<approxVertical_lines.size()-1;v1++)
                {
                    for(int v2=v1+1;v2<approxVertical_lines.size();v2++)
                    {
                        QPointF p1,p2,p3,p4;
                        int priority=4;

                        if(approxHorizontal_lines.at(h1).intersects(approxVertical_lines.at(v1),&p1)==QLineF::NoIntersection)continue;
                        else
                        {
                            if(approxHorizontal_lines.at(h1).intersects(approxVertical_lines.at(v1),&p1)!=QLineF::BoundedIntersection)
                            {
                                if(p1.x()<0)p1.setX(0);
                                if(p1.y()<0)p1.setY(0);
                                if(p1.x()>imageWidth)p1.setX(imageWidth-2);
                                if(p1.y()>imageHeight)p1.setY(imageHeight-2);
                                priority--;
                            }
                        }

                        if(approxHorizontal_lines.at(h1).intersects(approxVertical_lines.at(v2),&p2)==QLineF::NoIntersection)continue;
                        else
                        {
                            if(approxHorizontal_lines.at(h1).intersects(approxVertical_lines.at(v2),&p2)!=QLineF::BoundedIntersection)
                            {
                                if(p2.x()<0)p2.setX(0);
                                if(p2.y()<0)p2.setY(0);
                                if(p2.x()>imageWidth)p2.setX(imageWidth-2);
                                if(p2.y()>imageHeight)p2.setY(imageHeight-2);
                                priority--;
                            }
                        }

                        if(approxHorizontal_lines.at(h2).intersects(approxVertical_lines.at(v2),&p3)==QLineF::NoIntersection)continue;
                        else
                        {
                            if(approxHorizontal_lines.at(h2).intersects(approxVertical_lines.at(v2),&p3)!=QLineF::BoundedIntersection)
                            {
                                if(p3.x()<0)p3.setX(0);
                                if(p3.y()<0)p3.setY(0);
                                if(p3.x()>imageWidth)p3.setX(imageWidth-2);
                                if(p3.y()>imageHeight)p3.setY(imageHeight-2);
                                priority--;
                            }
                        }

                        if(approxHorizontal_lines.at(h2).intersects(approxVertical_lines.at(v1),&p4)==QLineF::NoIntersection)continue;
                        else
                        {
                            if(approxHorizontal_lines.at(h2).intersects(approxVertical_lines.at(v1),&p4)!=QLineF::BoundedIntersection)
                            {
                                if(p4.x()<0)p4.setX(0);
                                if(p4.y()<0)p4.setY(0);
                                if(p4.x()>imageWidth)p4.setX(imageWidth-2);
                                if(p4.y()>imageHeight)p4.setY(imageHeight-2);
                                priority--;
                            }
                        }

                        polygons.append(QPair<QPolygonF,int>(QVector<QPointF>({p1,p2,p3,p4}),priority));

                    }
                }
            }
        }
    }
    return polygons;
}


QPolygonF IPAlgorithms::getMaxPolygon(QList<QLineF> & detectedLines,int imageWidth,int imageHeight)
{
    QList<QPair<QPolygonF, int>>  polygons = detectQuadrilateral(detectedLines,imageWidth,imageHeight);
    float area = 0,tempArea=0;
    int priority=0;
    QPolygonF maxPolygon;

    //    int counter = 1;
    for(const QPair<QPolygonF, int> & pair :polygons)
    {
        tempArea = getAreaOfQuadrilateral(pair.first);

        if(pair.second>=priority)
        {
            if(priority==pair.second)
            {
                if(tempArea>area)
                {
                    area=tempArea;
                    maxPolygon=pair.first;
                }
            }
            else
            {
                priority=pair.second;
                area=tempArea;
                maxPolygon=pair.first;
            }
        }
    }
    return maxPolygon;
}


void IPAlgorithms::nonMaxSupression(QImage & in, std::vector<std::vector<int> > &thetaXY, int supressionRadius)
{
    QImage image = in.copy(-supressionRadius,-supressionRadius,in.width()+(2*supressionRadius),in.height()+(2*supressionRadius));
    const int offset = supressionRadius;
    const int width = image.width();
    const int height = image.height();
    int intensityofCenterPixel;
    int index;
    int theta;
    unsigned char * middleLine;

    for(int y=offset;y<height-offset;y++)
    {
        const std::vector<int> & theta_y = thetaXY[y-offset];
        middleLine =  image.scanLine(y);
        for(int x=offset;x<=width-offset;x++)
        {

            if(middleLine[x]==0) continue;
            theta = theta_y[x-offset];

            if(theta>22.5 && theta<=67.5)theta=45;
            else if(theta>-157.5 && theta<=-112.5)theta=45;
            else if(theta>67.5 && theta<=112.5)theta=90;
            else if(theta>-112.5 && theta<=-67.5)theta=90;
            else if(theta>112.5 && theta<=157.5)theta=135;
            else if(theta>-67.5 && theta<=-22.5)theta=135;
            else theta=0;

            intensityofCenterPixel = middleLine[x];

            if(theta==0)
            {
                for(index=-offset;index<=offset;index++)
                {
                    if(intensityofCenterPixel< image.scanLine(y+index)[x])
                    {
                        middleLine[x]=0;
                        break;
                    }
                }
            }
            else if(theta==90)
            {
                for(index=-offset;index<=offset;index++)
                {
                    if(intensityofCenterPixel< middleLine[x+index])
                    {
                        middleLine[x]=0;
                        break;
                    }
                }
            }
            else if(theta==45)
            {
                for(index=-offset;index<=offset;index++)
                {
                    if(intensityofCenterPixel< image.scanLine(y+index)[x+index])
                    {
                        middleLine[x]=0;
                        break;
                    }
                }
            }
            else if(theta==135 )
            {
                for(index=-offset;index<=offset;index++)
                {
                    if(intensityofCenterPixel< image.scanLine(y+index)[x-index])
                    {
                        middleLine[x]=0;
                        break;
                    }
                }
            }
        }
    }
    in = image.copy(supressionRadius,supressionRadius,image.width()-(2*supressionRadius),image.height()-(2*supressionRadius));
}


void IPAlgorithms::removeNoise(QImage & in , int radius)
{
    QImage image = in.copy(-radius,-radius,in.width()+(2*radius),in.height()+(2*radius));
    int height = image.height()-1;
    int width = image.width()-1;
    unsigned char * scanLine1,*scanLine2 ,*scanLine3;
    int index;

    for(int offset =1;offset<=radius;offset++)
        for(int y=offset+1;y<height-offset;y++)
        {
            for(int x=offset+1;x<width-offset;x++)
            {
                // if  intensity of CenterPixel is zero then skip
                if(image.scanLine(y)[x]==0)continue;

                for(index=-offset;index<=offset;index++)
                {
                    if(image.scanLine(y+index)[x+offset]!=0)
                        goto out;
                }

                for(index=-offset;index<=offset;index++)
                {
                    if(image.scanLine(y+index)[x-offset]!=0)
                        goto out;
                }

                scanLine1 = image.scanLine(y-offset);
                for(index=-offset+1;index<=offset-1;index++)
                {
                    if(scanLine1[x+index]!=0)
                        goto out;
                }

                scanLine2 = image.scanLine(y+offset);
                for(index=-offset+1;index<=offset-1;index++)
                {
                    if(scanLine2[x+index]!=0)
                        goto out;
                }

                for(int j=y-offset-1;j<=y+offset-1;j++)
                {
                    scanLine3 = image.scanLine(j);
                    for(index=x-offset-1;index<=x+offset-1;index++)
                        scanLine3[index]=0;
                }
                x+=offset;
out:;
            }
        }

     in = image.copy(radius,radius,image.width()-(2*radius),image.height()-(2*radius));

}

void IPAlgorithms::applyBoxBlur(QImage &image, int radius, int iteration)
{
    int diameter = (2*radius)+1;
    QImage out(image.width(),image.height(),image.format());
    unsigned char * inScanLine,*outScanLine;
    unsigned char * firstAddressIn = out.scanLine(0);
    unsigned char * firstAddressOut = image.scanLine(0);
    const int width = image.width();
    const int height = image.height();
    int next_accumulation=0;


    for(int pass = 0;pass<iteration;pass++)
    {
        // in x dir

        for(int y=0;y<height;y++)
        {
            inScanLine = image.scanLine(y);
            outScanLine = out.scanLine(y);

            next_accumulation=0;
            for(int i=0;i<diameter;i++)
                next_accumulation+=inScanLine[i];
            outScanLine[radius]=next_accumulation/diameter;


            for(int x=radius+1;x<width-radius;x++)
            {
                next_accumulation = next_accumulation+inScanLine[x+radius]-inScanLine[x-radius-1];
                outScanLine[x]=next_accumulation/diameter;
            }
        }


        // remaing in x dir
        for(int y=0;y<height;y++)
        {
            inScanLine = image.scanLine(y);
            outScanLine = out.scanLine(y);

            next_accumulation=0;
            next_accumulation=inScanLine[0]*(radius+1);
            for(int x=1;x<=radius;x++)
                next_accumulation+=inScanLine[x];

            outScanLine[0]=next_accumulation/diameter;


            for(int x=1;x<radius;x++)
            {
                next_accumulation = next_accumulation+inScanLine[x+radius]-inScanLine[0];
                outScanLine[x]=next_accumulation/diameter;
            }


            next_accumulation=0;
            next_accumulation=inScanLine[width-1]*(radius+1);
            for(int x=width-2;x>=width-radius-1;x--)
                next_accumulation+=inScanLine[x];
            outScanLine[width-1]=next_accumulation/diameter;


            for(int x=width-2;x>=width-radius;x--)
            {
                next_accumulation = next_accumulation+inScanLine[x-radius]-inScanLine[width-1];
                outScanLine[x]=next_accumulation/diameter;
            }

        }

        // in y dir
        for(int x=0;x<width;x++)
        {
            inScanLine =  firstAddressIn+x;
            outScanLine = firstAddressOut+x;

            next_accumulation=0;
            for(int index=0;index<diameter;index++)
                next_accumulation+=inScanLine[index*width];
            outScanLine[radius*width]= next_accumulation/diameter;


            for(int y=radius+1;y<height-radius;y++)
            {
                next_accumulation = next_accumulation+inScanLine[(y+radius)*width]-inScanLine[(y-radius-1)*width];
                outScanLine[y*width]= next_accumulation/diameter;
            }
        }

        // remaing in y dir
        for(int x=0;x<width;x++)
        {
            inScanLine =  firstAddressIn+x;
            outScanLine = firstAddressOut+x;

            next_accumulation=0;
            next_accumulation=inScanLine[0]*(radius+1);
            for(int y=1;y<=radius;y++)
                next_accumulation+=inScanLine[y*width];

            outScanLine[0]=next_accumulation/diameter;


            for(int y=1;y<radius;y++)
            {
                next_accumulation = next_accumulation+inScanLine[(y+radius)*width]-inScanLine[0];
                outScanLine[y*width]=next_accumulation/diameter;
            }


            next_accumulation=0;
            next_accumulation=inScanLine[(height-1)*width]*(radius+1);
            for(int y=height-2;y>=height-radius-1;y--)
                next_accumulation+=inScanLine[y*width];
            outScanLine[(height-1)*width]=next_accumulation/diameter;


            for(int y=height-2;y>=height-radius;y--)
            {
                next_accumulation = next_accumulation+inScanLine[(y-radius)*width]-inScanLine[(height-1)*width];
                outScanLine[y*width]=next_accumulation/diameter;
            }

        }
    }

}

std::vector<std::vector<int> > IPAlgorithms::getGx(QImage &image)
{
    const int width = image.width();
    const int height = image.height();
    unsigned char * inScanLine;
    std::vector<std::vector<int>> gx(height,std::vector<int>(width,0));
    std::vector<std::vector<int>> interGX(height,std::vector<int>(width,0));

    for(int y=0;y<height;y++)
    {
        inScanLine = image.scanLine(y);
        std::vector<int> & interY = interGX[y];

        for(int x=1;x<width-1;x++)
            interY[x]= inScanLine[x-1] + (inScanLine[x]*2)  +  inScanLine[x+1];
    }


    for(int x=0;x<width;x++)
        for(int y=1;y<height-1;y++)
            gx[y][x]=  -interGX[y-1][x] + interGX[y+1][x];

    return gx;
}

std::vector<std::vector<int> > IPAlgorithms::getGy(QImage &image)
{
    const int width = image.width();
    const int height = image.height();
    unsigned char * inScanLine;
    std::vector<std::vector<int>> gy(height,std::vector<int>(width,0));
    std::vector<std::vector<int>> interGY(height,std::vector<int>(width,0));

    for(int y=0;y<height;y++)
    {
        inScanLine = image.scanLine(y);
        std::vector<int> & interY = interGY[y];

        for(int x=1;x<width-1;x++)
            interY[x]= -inScanLine[x-1]+inScanLine[x+1];
    }

    for(int x=0;x<width;x++)
        for(int y=1;y<height-1;y++)
            gy[y][x]=  interGY[y-1][x] + ( 2* interGY[y][x]  )+ interGY[y+1][x];

    return gy;
}

QImage IPAlgorithms::getGradinetImage(std::vector<std::vector<int> > gradient)
{
    const int height = gradient.size();
    const int width = gradient.at(0).size();
    QImage out(width,height,QImage::Format_Grayscale8);
    out.fill(0);
    unsigned char * scanLine;
    int temp;

    for(int y=1;y<height-1;y++)
    {
        scanLine = out.scanLine(y);
        std::vector<int> & gradientY = gradient[y];
        for(int x=1;x<width-1;x++)
        {
            temp = gradientY[x];
            if(temp<0)temp*=-1;
            scanLine[x]=qBound(0,temp,255);
        }
    }
    return out;
}

QPair<QImage, std::vector<std::vector<int> > > IPAlgorithms::getMagAndTheta( std::vector<std::vector<int> > gx,  std::vector<std::vector<int> > gy)
{

    int  height = gx.size();
    int width = gx.at(0).size();
    int X,Y;
    std::vector<std::vector<int>> theta(height,std::vector<int>(width,0));
    QImage image(width,height,QImage::Format_Grayscale8);
    image.fill(0);

    for(int y=1;y<height-1;y++)
    {
        unsigned char * scanLine = image.scanLine(y);
        std::vector<int>  & y_gy = gy[y];
        std::vector<int>  & y_gx = gx[y];
        for(int x=1;x<width-1;x++)
        {
            X = y_gx[x];
            Y = y_gy[x];
            theta[y][x] = qRadiansToDegrees( atan2 (Y,X) );

            if(Y<0)Y*=-1;
            if(X<0)X*=-1;

            Y = qBound(0,Y,255);
            X= qBound(0,X,255);
            scanLine[x]= qBound(0,static_cast<int>(hypot(X,Y)),255);

        }
    }
    return QPair<QImage,std::vector<std::vector<int>>>(image,theta);
}

void IPAlgorithms::drawPolygon(QImage &image, QPolygonF &polygon, int penWidth)
{
    QPainter painter(&image);
    QPen pen("red");
    pen.setWidth(penWidth);
    painter.setPen(pen);
    painter.drawPolygon(polygon);
}


QPair<QList<QLineF>, QList<QLineF>> IPAlgorithms::getHorizonatalAndVerticalLines(QList<QLineF> &lines)
{
    QList<QLineF> approxHorizontal_lines,approxVertical_lines;
    for(auto line:lines)
    {
        qreal angle = line.angle();
        if(angle>180)angle=angle-180;
        if( angle<=45 || 180-angle<=45 )approxHorizontal_lines.append(line);
        else approxVertical_lines.append(line);
    }
    return  QPair<QList<QLineF>, QList<QLineF>>(approxHorizontal_lines,approxVertical_lines);
}

QPair<QImage, QVector<QVector<int>>> IPAlgorithms::getMagnitudeAndTheta(const QImage &image)
{
    int width = image.width();
    int height = image.height();
    QVector<QVector<int>> theta(image.height(),QVector<int>(image.width(),0));
    QImage image_magnitude(image.width(),image.height(),image.format());
    double sumInX,sumInY;

    for(int y=0;y<height;y++)
    {
        QList<unsigned char * > scanlines;
        for(int line=y-1;line<=y+1;line++)
            scanlines.append((unsigned char *)image.scanLine(qBound(0,line,height-1)));

        unsigned char * outScanLine = image_magnitude.scanLine(y);

        for(int x=0;x<width;x++)
        {
            sumInX=sumInY=0;
            for(int yd=0;yd<3;yd++)
            {
                unsigned char * currentLine = scanlines.at(yd);
                for(int xd=x-1;xd<=x+1;xd++)
                {
                    int iIndex= qBound(0,xd,width-1);
                    int kindex = 3 -(xd-(x-1))-1;
                    sumInX+= currentLine[iIndex] * kernel_sobelx3.at(kindex).at(3-yd-1);
                    sumInY+= currentLine[iIndex] * kernel_sobely3.at(kindex).at(3-yd-1);
                }
            }
            theta[y][x]= qRadiansToDegrees( atan2( sumInY , sumInX ) );
            if(sumInX<0)sumInX*=-1;
            if(sumInY<0)sumInY*=-1;
            sumInX = qBound(0,static_cast<int>(sumInX),255);
            sumInY = qBound(0,static_cast<int>(sumInY),255);
            outScanLine[x]=  qBound(0,static_cast<int>(hypot(sumInX,sumInY)),255);
        }
    }
    return QPair<QImage, QVector<QVector<int>>>(image_magnitude,theta);
}


QImage IPAlgorithms::applyGaussainBlur(const QImage & image, const QVector<QVector<double> > &kernel)
{
    if(kernel.size()<0)return QImage();
    if(kernel.size()!=kernel.at(0).size())return QImage();

    int kernelSize =  kernel.size();
    int offset = kernelSize/2;
    int width = image.width();
    int height = image.height();
    QImage out(width,height,image.format());
    double sum;

    for(int y=0;y<height;y++)
    {
        QList<unsigned char * > scanlines;
        for(int line=y-offset;line<=y+offset;line++)
            scanlines.append((unsigned char *)image.scanLine(qBound(0,line,height-1)));

        unsigned char * outputLine = out.scanLine(y);
        for(int x=0;x<width;x++)
        {
            sum=0;
            for(int yd=0;yd<kernelSize;yd++)
            {
                unsigned char * currentLine = scanlines.at(yd);
                for(int xd=x-offset;xd<=x+offset;xd++)
                {
                    int iIndex= qBound(0,xd,width-1);
                    int kindex = kernelSize -(xd-(x-offset))-1;
                    sum+= currentLine[iIndex] * kernel.at(kindex).at(kernelSize-yd-1);
                }
            }
            if(sum<0)sum*=-1;
            outputLine[x]=  qBound(0,static_cast<int>(sum),255);
        }
    }
    return out;
}

QImage IPAlgorithms::hysteresis(const QImage &image, float tmin, float tmax) {
    auto res = QImage(image.size(), image.format());
    res.fill(0x00);

    const quint8 *original_line;
    quint8 *result_line;
    int ni, nj;
    std::queue<std::pair<int, int>> edges;

    for (int y = 1; y < res.height() - 1; y++) {
        original_line = image.constScanLine(y);
        result_line = res.scanLine(y);

        for (int x = 1; x < res.width() - 1; x++) {
            if (original_line[x] >= tmax && result_line[x] == 0x00) {
                result_line[x] = 0xFF;
                edges.push(std::make_pair(x, y));

                while (!edges.empty()) {
                    auto point = edges.front();
                    edges.pop();

                    for (int j = -1; j <= 1; j++) {
                        nj = point.second + j;
                        if (nj < 0 || nj >= image.height())
                            continue;

                        original_line = image.constScanLine(nj);
                        result_line = res.scanLine(nj);

                        for (int i = -1; i <= 1; i++) {
                            if (!i && !j)
                                continue;

                            ni = point.first + i;
                            if (ni < 0 || ni >= image.width())
                                continue;

                            if (original_line[ni] >= tmin && result_line[ni] == 0x00) {
                                result_line[ni] = 0xFF;
                                edges.push(std::make_pair(ni, nj));
                            }
                        }
                    }
                }
            }
        }
    }

    return res;
}

QVector<QVector<double>> IPAlgorithms::generateGaussianKernel(double sigma)
{
    // G(x,y)= {1/sqrt(2.pi.sigma^2)}.e^-(x^2+y^2 / 2.sigma^2)
    // where sigma is deviation,
    // x is the distance from the origin in the horizontal axis, y is the distance from the origin in the vertical axis
    // source :- https://en.wikipedia.org/wiki/Gaussian_blur

    // reform
    // G(x,y) = constant1 . e^-(var/ constant2);
    // where var = x^2+y^2 ;
    // constant1 = 1/sqrt(2.pi.sigma^2);
    // constant2= 2.sigma^2;

    int kernelSize =  2*ceil(3*sigma)+1;

    QVector<QVector<double>> kernel(kernelSize,QVector<double>(kernelSize));
    double constant2 = 2*sigma*sigma;
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
            kernel[x][y] = (kernel[x][y]/sumForNormalize);

    return kernel;
}



