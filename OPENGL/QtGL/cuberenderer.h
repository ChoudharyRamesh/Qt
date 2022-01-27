#ifndef CUBERENDERER_H
#define CUBERENDERER_H

#include<QtMath>
#include<QMatrix4x4>
#include<QOpenGLFunctions>
#include <QOpenGLBuffer>
#include<QOpenGLShaderProgram>
#include<QQuickFramebufferObject>
#include<QOpenGLFramebufferObjectFormat>

class Cube : public QQuickFramebufferObject
{
    Q_OBJECT
public:
    QQuickFramebufferObject::Renderer * createRenderer() const;
};


class CubeRenderer : public QQuickFramebufferObject::Renderer,protected QOpenGLFunctions
{
public:
   CubeRenderer(const Cube * cubeWindow);
    void render() override;
    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override;

private:
    QOpenGLShaderProgram program;
    void initialize();
    uint createVBO(const float * data,int size);
    uint createEBO(const uint * data,int size);

    const Cube * cubeWindow;
};

#endif // CUBERENDERER_H

