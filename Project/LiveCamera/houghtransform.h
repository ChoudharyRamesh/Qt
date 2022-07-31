#ifndef HOUGHTRANSFORM_H
#define HOUGHTRANSFORM_H

#include<QImage>
#include<QtMath>
#include<QMap>
#include<QStack>

class HoughTransform{

public:
    HoughTransform(const QImage & cannyImage);
    QList<QLineF>  getDetectedLines();


private:
    void scanImage();
    void insertPair(int theta,int rho);
    void applyThreshold(int threshold=0);
    QPair<int,int> getMaxAccumlatorKey( QMap<QPair<int,int>,int> & map);
    void filterTheta();
    void computeFilteredLines();
    QLineF getLineFromThetaAndRho(int theta,int rho);


private:
    QMap<QPair<int,int>,int> roughRhoAndTheta;  // ((theta,rho),Accumaltor)
    QMap<QPair<int,int>,int> filteredRhoAndTheta;
    QList<QLineF> filteredLines;
    QImage mImage;
    int imageHyp=0;
    int imageHeight=0;
    int imageWidth=0;

};

#endif // HOUGHTRANSFORM_H
