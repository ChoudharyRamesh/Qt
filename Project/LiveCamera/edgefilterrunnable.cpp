#include "edgefilterrunnable.h"
#include "videoproducer.h"
#include "edgefilter.h"
#include<QtConcurrent>
#include<QDebug>


EdgeFilterRunnable::EdgeFilterRunnable(EdgeFilter * edgeFilter,VideoProducer * videoproducer)
{
    this->edgeFilter=edgeFilter;
    this->videoproducer=videoproducer;
}

EdgeFilterRunnable::~EdgeFilterRunnable(){}


QVideoFrame EdgeFilterRunnable::run(QVideoFrame *input,
                                    const QVideoSurfaceFormat & surfaceFormat,
                                    QVideoFilterRunnable::RunFlags flags)
{
    Q_UNUSED(flags);

    QImage iFrame = edgeFilter->videoFrameToQImage(*input);
    if( iFrame.isNull())return QVideoFrame();
    videoproducer->setVideoSurfaceFormat(surfaceFormat);
    detectEdgeAndPresent(iFrame,surfaceFormat);
    return QVideoFrame();
}

void EdgeFilterRunnable::detectEdgeAndPresent(QImage iFrame, const QVideoSurfaceFormat &surfaceFormat)
{

    int w =iFrame.width(); int h = iFrame.height();
    iFrame = iFrame.scaled(500,500,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    iFrame.convertTo(QImage::Format_Grayscale8);
    ipalgorithms.applyBoxBlur(iFrame,1,1);
    auto magAndTheta =  ipalgorithms.getMagAndTheta(ipalgorithms.getGx(iFrame),ipalgorithms.getGy(iFrame));
    ipalgorithms.nonMaxSupression(magAndTheta.first,magAndTheta.second,2);
    magAndTheta.first =  ipalgorithms.hysteresis(magAndTheta.first,60,70);

//    ipalgorithms.removeNoise(magAndTheta.first,15);

    HoughTransform houghTransform(magAndTheta.first);
    houghTransform.getDetectedLines();
    auto lines = houghTransform.getDetectedLines();
    auto polygon = ipalgorithms.getMaxPolygon(lines,iFrame.width(),iFrame.height());


    magAndTheta.first.convertTo(QImage::Format_RGB32);

    if(!polygon.isEmpty())ipalgorithms.drawPolygon(magAndTheta.first,polygon,2);

    magAndTheta.first = magAndTheta.first.scaled(w,h,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    videoproducer->setVideoSurfaceFormat(surfaceFormat);
    videoproducer->present(magAndTheta.first);

}



