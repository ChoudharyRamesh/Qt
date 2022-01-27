#ifndef TRIANGLERENDERER_H
#define TRIANGLERENDERER_H

#include<QtMath>
#include<QMatrix4x4>
#include<QOpenGLFunctions>
#include<QOpenGLShaderProgram>
#include<QQuickFramebufferObject>
#include<QOpenGLFramebufferObjectFormat>

class TriangleRenderer : public QQuickFramebufferObject::Renderer,protected QOpenGLFunctions
{
public:
   TriangleRenderer();
   ~TriangleRenderer(){ qDebug()<<"deleted"; }
    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

private:
    int vertexAttrib;
    int colorAttrib;
    QList<QVector3D> vertices;
    QList<QVector3D> colors;
    QOpenGLShaderProgram program;
    void initialize();
};


class Triangle : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    QQuickFramebufferObject::Renderer * createRenderer() const;
};

#endif // TRIANGLERENDERER_H
