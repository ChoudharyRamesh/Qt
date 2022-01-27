#include "houghtransform.h"
#include<QDebug>

HoughTransform::HoughTransform(const QImage &cannyImage)
{
    //apply fast scaling::Remaining
    this->mImage = cannyImage;
    this->imageWidth = mImage.width();
    this->imageHeight = mImage.height();
    this->imageHyp = qSqrt((imageWidth*imageWidth)+(imageHeight*imageHeight));

}


QList<QLineF> HoughTransform::getDetectedLines()
{
    roughRhoAndTheta.clear();
    filteredRhoAndTheta.clear();
    filteredLines.clear();

    scanImage();
    applyThreshold();
    filterTheta();

    computeFilteredLines();
    return filteredLines;
}




void HoughTransform::filterTheta()
{
    QPointF temp;
    while (!roughRhoAndTheta.isEmpty())
    {
        auto mkey = getMaxAccumlatorKey(roughRhoAndTheta);
        auto maxAcc = roughRhoAndTheta[mkey];
        QLineF mLine = getLineFromThetaAndRho(mkey.first,mkey.second);

        for(auto key : roughRhoAndTheta.keys())
        {
            if(key!=mkey)
            {
                QLineF line = getLineFromThetaAndRho(key.first,key.second);

                //new added
                bool removed = false;
                qreal angleToXaxis = line.angle();
                if(angleToXaxis>180)angleToXaxis=angleToXaxis-180;
                if( angleToXaxis<=45 || 180-angleToXaxis<=45 )
                {
                    if(line.length()<imageWidth/2)
                    {  roughRhoAndTheta.remove(key); removed=true; }
                }
                else
                {
                    if(line.length()<imageHeight/2)
                    { roughRhoAndTheta.remove(key); removed=true; }
                }
                // new added end

                if(!removed)
                {
                    qreal angleBetweenLine = line.angleTo(mLine);
                    QLineF::IntersectType interSectionType = line.intersects(mLine,&temp);

                    if(angleBetweenLine>180)
                        angleBetweenLine=angleBetweenLine-180;

                    if( angleBetweenLine<=45 || 180-angleBetweenLine<=45 )
                    {
                        if(interSectionType==QLineF::BoundedIntersection)
                            roughRhoAndTheta.remove(key);
                        else
                        {
                            if(QLineF(mLine.center(),line.center()).length()<=imageHyp*0.1)
                                roughRhoAndTheta.remove(key);
                        }
                    }
                }

            }
        }
        filteredRhoAndTheta.insert(mkey,maxAcc);
        roughRhoAndTheta.remove(mkey);
    }


}

void HoughTransform::applyThreshold(int threshold){

    if(threshold==0)
        threshold = 0.3*roughRhoAndTheta[getMaxAccumlatorKey(roughRhoAndTheta)];

    for(auto keyy:roughRhoAndTheta.keys())
        if(roughRhoAndTheta.value(keyy)<threshold)
            roughRhoAndTheta.remove(keyy);

}

void HoughTransform::scanImage()
{
    for(int y=0;y<imageHeight;y+=2)
    {
        for(int x=0;x<imageWidth;x++)
        {
            unsigned char pixel = mImage.pixel(x,y);
            if(pixel>10)
            {
                for(double theta=-90;theta<90;theta++)
                {
                    int rho = qRound(x*qCos(qDegreesToRadians(theta)))+qRound(y*(qSin(qDegreesToRadians(theta))));
                    insertPair(theta,rho);
                }
            }
        }
    }
}

void HoughTransform::insertPair(int theta, int rho)
{
    QPair<int,int> key(theta,rho);
    if(roughRhoAndTheta.find(key)!=roughRhoAndTheta.end())
        roughRhoAndTheta[key]=roughRhoAndTheta.value(key)+1;
    else roughRhoAndTheta.insert(key,0);
}


QPair<int,int> HoughTransform::getMaxAccumlatorKey(QMap<QPair<int, int>, int> &map)
{
    int accum=0;
    QPair<int,int> maxKey;
    for(auto key :map.keys())
    {  if(map[key]>accum)
        { accum=map[key]; maxKey=key; }
    }
    return maxKey;
}



void HoughTransform::computeFilteredLines()
{
    for(auto keyy : filteredRhoAndTheta.keys())
        filteredLines.append(getLineFromThetaAndRho(keyy.first,keyy.second));
}

QLineF HoughTransform::getLineFromThetaAndRho(int theta, int rho)
{
    QPointF p1,p2;
    float coss = qCos(qDegreesToRadians((float)theta));
    float sinn = qSin(qDegreesToRadians((float)theta));
    float x_when_yIs_IH =(rho-(imageHeight*sinn))/coss;
    float y_when_xIs_IW=(rho-(imageWidth*coss))/sinn;
    float x_when_yIs_0 = rho/coss;
    float y_when_xIs_0 = rho/sinn;

    //y=0
    if(x_when_yIs_0<=imageWidth && x_when_yIs_0>=0)
    {
        p1 =  QPointF(x_when_yIs_0,0);

        //x=W
        if(y_when_xIs_IW<=imageHeight && y_when_xIs_IW>=0)
            p2 = QPointF(imageWidth,y_when_xIs_IW);

        //y=H
        else if(x_when_yIs_IH<=imageWidth && x_when_yIs_IH>=0)
            p2 = QPointF(x_when_yIs_IH,imageHeight);

        //x=0
        else if(y_when_xIs_0<=imageHeight && y_when_xIs_0>=0)
            p2 = QPointF(0,y_when_xIs_0);

    }

    //x=w
    else if(y_when_xIs_IW<=imageHeight && y_when_xIs_IW>=0)
    {
        p1 =  QPointF(imageWidth,y_when_xIs_IW);

        //y=H
        if(x_when_yIs_IH<=imageWidth && x_when_yIs_IH>=0)
            p2 = QPointF(x_when_yIs_IH,imageHeight);

        //x=0
        else if(y_when_xIs_0<=imageHeight && y_when_xIs_0>=0)
            p2 = QPointF(0,y_when_xIs_0);

        //y=0
        else if(x_when_yIs_0<=imageWidth && x_when_yIs_0>=0)
            p2 = QPointF(x_when_yIs_0,0);

    }


    //y=H
    else if(x_when_yIs_IH<=imageWidth && x_when_yIs_IH>=0)
    {
        p1 =  QPointF(x_when_yIs_IH,imageHeight);

        //x=0
        if(y_when_xIs_0<=imageHeight && y_when_xIs_0>=0)
            p2 = QPointF(0,y_when_xIs_0);

        //y=0
        else if(x_when_yIs_IH<=imageWidth && x_when_yIs_IH>=0)
            p2 = QPointF(x_when_yIs_IH,imageHeight);

        //x=W
        else if(y_when_xIs_IW<=imageHeight && y_when_xIs_IW>=0)
            p2 = QPointF(imageWidth,y_when_xIs_IW);

    }

    //x=0
    else if(y_when_xIs_0<=imageHeight && y_when_xIs_0>=0)
    {
        p1 =  QPointF(0,y_when_xIs_0);

        //y=0
        if(x_when_yIs_IH<=imageWidth && x_when_yIs_IH>=0)
            p2 = QPointF(x_when_yIs_IH,imageHeight);

        //x=W
        else if(y_when_xIs_IW<=imageHeight && y_when_xIs_IW>=0)
            p2 = QPointF(imageWidth,y_when_xIs_IW);

        //y=H
        else if(x_when_yIs_IH<=imageWidth && x_when_yIs_IH>=0)
            p2 = QPointF(x_when_yIs_IH,imageHeight);

    }

    return  QLineF(p1,p2);
}







