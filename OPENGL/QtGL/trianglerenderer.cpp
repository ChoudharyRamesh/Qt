#include "trianglerenderer.h"

QQuickFramebufferObject::Renderer * Triangle::createRenderer() const
{
    return new TriangleRenderer();
}

TriangleRenderer::TriangleRenderer()
{
    colors.append(QVector3D(1,0,0));
    colors.append(QVector3D(0,1,0));
    colors.append(QVector3D(0,0,1));

    colors.append(QVector3D(0,1,0));
    colors.append(QVector3D(0,1,1));
    colors.append(QVector3D(0,0,1));

    initialize();
}

void TriangleRenderer::render()
{
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT);

    vertices.clear();
    vertices.append(QVector3D(-1,1,0));
    vertices.append(QVector3D(-1,-1,0));
    vertices.append(QVector3D(1,1,0));

    vertices.append(QVector3D(-1,-1,0));
    vertices.append(QVector3D(1,-1,0));
    vertices.append(QVector3D(1,1,0));


    program.bind();
    vertexAttrib = program.attributeLocation("vertex");
    colorAttrib = program.attributeLocation("color");
    program.enableAttributeArray(vertexAttrib);
    program.enableAttributeArray(colorAttrib);

    program.setAttributeArray(vertexAttrib,vertices.constData());
    program.setAttributeArray(colorAttrib,colors.constData());

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    program.disableAttributeArray(vertexAttrib);
    program.disableAttributeArray(colorAttrib);

    program.release();
}

QOpenGLFramebufferObject * TriangleRenderer::createFramebufferObject(const QSize &size) {
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}

void TriangleRenderer::initialize()
{
    initializeOpenGLFunctions();

    QString vs = R"END(
        #version 330 core
        layout ( location=0 ) in vec3 vertex;
        layout ( location=1 ) in vec3 color;
        out vec3 fragColor;
        void main()
        {
            gl_Position = vec4(vertex,1.0f);
            fragColor = color;
        }
        )END";

    QString fs = R"END(
        #version 330 core
        in vec3 fragColor;
        void main()
        {
            gl_FragColor = vec4(fragColor,1.0f);
        }
        )END";

    program.addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vs);
    program.addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fs);
    program.link();
}
