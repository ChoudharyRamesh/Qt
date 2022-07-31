#ifndef VIDEOPRODUCER_H
#define VIDEOPRODUCER_H
#include<QObject>
#include<QAbstractVideoSurface>
#include<QVideoSurfaceFormat>

class VideoProducer:public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractVideoSurface * videoSurface READ videoSurface WRITE setVideoSurface NOTIFY videoSurfaceChanged);
public:
    VideoProducer();
    QAbstractVideoSurface * videoSurface() const;
    void setVideoSurfaceFormat(const QVideoSurfaceFormat & format);
    Q_INVOKABLE void present(const QVideoFrame & frame);

public slots:

    void setVideoSurface(QAbstractVideoSurface * videoSurface);

signals:
    void videoSurfaceChanged(QAbstractVideoSurface * videoSurface);

private:
    QAbstractVideoSurface * m_videoSurface=nullptr;
    QVideoSurfaceFormat  m_surfaceFormat;

};

#endif // VIDEOPRODUCER_H
