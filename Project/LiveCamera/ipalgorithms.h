#ifndef CANNY_H
#define CANNY_H
#include<QVector>
#include<QList>
#include<QPair>
#include<QPolygonF>
#include<QLineF>
#include<QImage>
#include<QtMath>
#include<queue>
#include<QPainter>

/// \brief Image Processing Algorithms
class IPAlgorithms
{
public:
    IPAlgorithms();
    QPair<QImage,QVector<QVector<int>>> getMagnitudeAndTheta(const QImage & image);
    void nonMaxSupression(QImage & image ,std::vector<std::vector<int>> &  thetaXY,int supressionRadius);


    QImage hysteresis(const QImage& image, float tmin, float tmax);
    QImage applyGaussainBlur(const QImage & image,const QVector<QVector<double>> & kernel);
    QVector<QVector<double>> generateGaussianKernel(double sigma);
    QPolygonF getMaxPolygon(QList<QLineF> & detectedLines, int imageWidth, int imageHeight);


    //new
    void removeNoise(QImage & image,int radius);
    void applyBoxBlur(QImage & image,int radius=3,int iteration=1);
    std::vector<std::vector<int>> getGx(QImage & image);
    std::vector<std::vector<int>> getGy(QImage & image);
    QImage getGradinetImage(std::vector<std::vector<int>> gradient);
    QPair<QImage,std::vector<std::vector<int>>>
    getMagAndTheta(std::vector<std::vector<int> > gx , std::vector<std::vector<int> > gy);
    void drawPolygon(QImage & image, QPolygonF &polygon,int penWidth);


private:
    float getAreaOfQuadrilateral(QPolygonF quadrilateral);
    QList<QPair<QPolygonF, int>> detectQuadrilateral(QList<QLineF> & detectedLines, int imageWidth, int imageHeight);

public://temp
    QPair<QList<QLineF>,QList<QLineF>> getHorizonatalAndVerticalLines(QList<QLineF> & lines);
    QVector<QVector<double>> kernel_guassian7 = {
            { 1.96519e-05, 0.000239409, 0.00107296, 0.00176901, 0.00107296, 0.000239409, 1.96519e-05},
            { 0.000239409, 0.0029166, 0.0130713, 0.0215509, 0.0130713, 0.0029166, 0.000239409 },
            { 0.00107296, 0.0130713, 0.0585815, 0.0965846, 0.0585815, 0.0130713, 0.00107296},
            { 0.00176901, 0.0215509, 0.0965846, 0.159241, 0.0965846, 0.0215509, 0.00176901},
            { 0.00107296, 0.0130713, 0.0585815, 0.0965846, 0.0585815, 0.0130713, 0.00107296},
            { 0.000239409, 0.0029166, 0.0130713, 0.0215509, 0.0130713, 0.0029166, 0.000239409},
            { 1.96519e-05, 0.000239409, 0.00107296, 0.00176901, 0.00107296, 0.000239409, 1.96519e-05}
    };

private:
    QVector<QVector<double>> kernel_sobelx3 = {{-1,0,1},{-2,0,2},{-1,0,1}};
    QVector<QVector<double>> kernel_sobely3 = {{-1,-2,-1},{0,0,0},{1,2,1}};
};

#endif // CANNY_H
