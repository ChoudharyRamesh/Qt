#ifndef EDGEFILTERRUNNABLE_H
#define EDGEFILTERRUNNABLE_H

#include<QVideoFilterRunnable>
#include<QQueue>
#include<QSemaphore>
#include<QMutex>
#include<QThread>
#include "ipalgorithms.h"
#include "houghtransform.h"

class VideoProducer;
class EdgeFilter;

class EdgeFilterRunnable : public QVideoFilterRunnable
{
public:
    explicit EdgeFilterRunnable(EdgeFilter * edgeFilter,VideoProducer * videoproducer);
    virtual ~EdgeFilterRunnable();
    QVideoFrame run(QVideoFrame * input, const QVideoSurfaceFormat & surfaceFormat, RunFlags flags);

private:
    void detectEdgeAndPresent(QImage iFrame, const QVideoSurfaceFormat &surfaceFormat);

private:
    EdgeFilter * edgeFilter; // refOnly
    VideoProducer * videoproducer; // refOnly
    IPAlgorithms  ipalgorithms;

};

#endif // EDGEFILTERRUNNABLE_H
