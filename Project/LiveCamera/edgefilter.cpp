#include "edgefilter.h"
#include"edgefilterrunnable.h"
#include "videoproducer.h"
#include <QOpenGLFunctions>

EdgeFilter::EdgeFilter(QObject *parent):QAbstractVideoFilter(parent){}
EdgeFilter::~EdgeFilter(){}


QImage EdgeFilter::videoFrameToQImage(const QVideoFrame &videoFrame)
{
    if ( videoFrame.handleType() == QAbstractVideoBuffer::NoHandle )
    {
        QImage image = videoFrame.image();
        if ( image.isNull() ) return QImage();
        if ( image.format() != QImage::Format_RGB32 ) return image.convertToFormat( QImage::Format_RGB32 );
        return image;
    }
    if ( videoFrame.handleType() == QAbstractVideoBuffer::GLTextureHandle )
    {
        QImage image( videoFrame.width(), videoFrame.height(), QImage::Format_RGB32 );
        unsigned int textureId = static_cast<unsigned int>( videoFrame.handle().toInt() );
        QOpenGLContext * ctx = QOpenGLContext::currentContext();
        QOpenGLFunctions * f = ctx->functions();
        unsigned int fbo;
        f->glGenFramebuffers( 1, &fbo );
        int prevFbo;
        f->glGetIntegerv( 0x8CA6, &prevFbo );
        f->glBindFramebuffer( 0x8D40, fbo );
        f->glFramebufferTexture2D( 0x8D40, 0x8CE0,  0x0DE1, textureId, 0 );
        f->glReadPixels( 0, 0,  videoFrame.width(),  videoFrame.height(), 0x1908, 0X1401, image.bits() );
        f->glBindFramebuffer( 0x8D40, static_cast<unsigned int>( prevFbo ) );
        return image.rgbSwapped();
    }
    return QImage();
}


void EdgeFilter::setVideoProducer(VideoProducer *videoproducer)
{
    this->videoProducer=videoproducer;
}

QVideoFilterRunnable * EdgeFilter::createFilterRunnable()
{
    // it will called once on starting and Runnable will leave in program till program life
    return new EdgeFilterRunnable(this,videoProducer);
}


