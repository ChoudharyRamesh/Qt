#ifndef EDGEFILTER_H
#define EDGEFILTER_H
#include<QAbstractVideoFilter>
#include<QVideoFilterRunnable>
#include<QDebug>
#include<QImage>
#include<QVideoFrame>

class VideoProducer;
class EdgeFilter : public QAbstractVideoFilter
{
    Q_OBJECT

public:
    explicit EdgeFilter(QObject * parent = nullptr);
    ~EdgeFilter();
    QVideoFilterRunnable *createFilterRunnable();
    QImage videoFrameToQImage( const QVideoFrame& videoFrame );
    Q_INVOKABLE void setVideoProducer(VideoProducer * videoproducer);

signals:
    void finished(QObject *result);

private:
    VideoProducer * videoProducer;

};

#endif // EDGEFILTER_H
