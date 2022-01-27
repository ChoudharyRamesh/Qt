#ifndef TEXTURERENDERER_H
#define TEXTURERENDERER_H

#include<QtMath>
#include<QMatrix4x4>
#include<QOpenGLFunctions>
#include<QOpenGLTexture>
#include<QOpenGLShaderProgram>
#include<QQuickFramebufferObject>
#include<QOpenGLFramebufferObjectFormat>

class TextureRenderer : public QQuickFramebufferObject::Renderer,protected QOpenGLFunctions
{
public:
   TextureRenderer();
   ~TextureRenderer(){ qDebug()<<"deleted"; }
    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

private:
    QOpenGLTexture *texture;
    int vertexAttrib;
    int colorAttrib;
    int texcordAttrib;
    QList<QVector3D> vertices;
    QList<QVector3D> colors;
    QList<QVector2D> texCords;
    QOpenGLShaderProgram program;
    void initialize();
};


class Texture : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    QQuickFramebufferObject::Renderer * createRenderer() const;
};


#endif // TEXTURERENDERER_H
