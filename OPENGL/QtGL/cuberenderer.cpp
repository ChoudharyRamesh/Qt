#include "cuberenderer.h"

QQuickFramebufferObject::Renderer * Cube::createRenderer() const
{
    return new CubeRenderer(this);
}

CubeRenderer::CubeRenderer(const Cube * cubeWindow):cubeWindow(cubeWindow)
{
    initialize();
}

void CubeRenderer::render()
{
    glClearColor(0,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    static const float vertices2[]=
    {
        -0.5, 0.5,-0.5    ,1,0,0,
        -0.5, 0.5, 0.5    ,0,1,0,
        -0.5,-0.5,-0.5    ,0,0,1,
        -0.5,-0.5, 0.5    ,1,1,0,

        0.5, 0.5,-0.5    ,0,1,1,
        0.5, 0.5, 0.5    ,1,0,1,
        0.5,-0.5, 0.5    ,1.0f,0.75f,0.796f,
        0.5,-0.5,-0.5    ,1.0f,0.647f,0.0f
    };

    static const uint indices[]=
    {
        0,7,2,0,4,7,
        4,5,7,5,7,6,
        1,5,6,6,1,3,
        0,1,2,2,1,3,
        0,1,4,4,1,5,
        2,7,3,3,7,6
    };

    glEnable(GL_DEPTH_TEST);
    program.bind();


    // position attribute
    createVBO(vertices2,sizeof(vertices2));
    createEBO(indices,sizeof(indices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    static int rotation = 0;
    rotation++;
    QMatrix4x4 model,view,projection;
    model.rotate(rotation,1,0.1,0.5);
    view.translate(0,0,-5);
    projection.perspective(30,cubeWindow->width()/cubeWindow->height(),0.1f,100.0f);
    QMatrix4x4 mvp = projection*view*model;
    program.setUniformValue(program.uniformLocation("mvp"),mvp);
    // glDrawArrays(GL_TRIANGLES, 0, 36);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    program.release();
}

QOpenGLFramebufferObject * CubeRenderer::createFramebufferObject(const QSize &size) {
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}

void CubeRenderer::initialize()
{
    initializeOpenGLFunctions();

    QString vs = R"END(
        #version 320 es
        layout ( location = 0 ) in vec3 aPos;
        layout ( location = 1 ) in vec3 aColor;
        out vec3 vertexColor;
        uniform mat4 mvp;
        void main()
        {
           gl_Position =  mvp * vec4(aPos, 1.0f);
           vertexColor = aColor;
        }
        )END";

    QString fs = R"END(
        #version 320 es
       // precision mediump float;
        in vec3 vertexColor;
        out vec4 fragColor;
        void main()
        {
           fragColor  = vec4(vertexColor,1.0f);
        }
        )END";

    program.addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vs);
    program.addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fs);
    program.link();
}

uint CubeRenderer::createVBO(const float *data, int size)
{
    unsigned int vbo_id;
    glGenBuffers(1,&vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    return vbo_id;
}

uint CubeRenderer::createEBO(const uint *data, int size)
{
    unsigned int ebo_id;
    glGenBuffers(1,&ebo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    return ebo_id;
}
