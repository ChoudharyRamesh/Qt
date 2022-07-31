#include "videoproducer.h"


VideoProducer::VideoProducer()
{

}

QAbstractVideoSurface *VideoProducer::videoSurface() const
{
    return m_videoSurface;
}

void VideoProducer::setVideoSurfaceFormat(const QVideoSurfaceFormat &format)
{
    if(m_surfaceFormat==format || m_videoSurface==nullptr)return;
    m_videoSurface->stop();
    m_surfaceFormat = m_videoSurface->nearestFormat(format);
    m_videoSurface->start(m_surfaceFormat);
}


void VideoProducer::setVideoSurface(QAbstractVideoSurface *videoSurface)
{
    if (m_videoSurface == videoSurface)return;
    if(m_videoSurface!=nullptr)
        m_videoSurface->stop();

    m_videoSurface = videoSurface;
    m_surfaceFormat = m_videoSurface->nearestFormat(m_surfaceFormat);
    m_videoSurface->start(m_surfaceFormat);
    emit videoSurfaceChanged(m_videoSurface);
}

void VideoProducer::present(const QVideoFrame &frame)
{
    m_videoSurface->present(frame);
}
