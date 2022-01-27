#include "texturerenderer.h"

QQuickFramebufferObject::Renderer * Texture::createRenderer() const
{
    return new TextureRenderer();
}

TextureRenderer::TextureRenderer()
{
    colors.append(QVector3D(1,0,0));
    colors.append(QVector3D(0,1,0));
    colors.append(QVector3D(0,0,1));

    colors.append(QVector3D(0,1,0));
    colors.append(QVector3D(0,1,1));
    colors.append(QVector3D(0,0,1));

    float one = 2.0f;
    texCords.append(QVector2D(0,one));
    texCords.append(QVector2D(0,0));
    texCords.append(QVector2D(one,one));

    texCords.append(QVector2D(0,0));
    texCords.append(QVector2D(one,0));
    texCords.append(QVector2D(one,one));

    initialize();

    // Prepare texture
    texture = new QOpenGLTexture(QImage("C:/Users/Nishant Choudhary/Pictures/Saved Pictures/me.jpg"));
    texture->setMinificationFilter(QOpenGLTexture::Nearest);
    texture->setMagnificationFilter(QOpenGLTexture::Nearest);
    // texture->setWrapMode(QOpenGLTexture::Repeat);
}

void TextureRenderer::render()
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
    texcordAttrib = program.attributeLocation("aTexCoord");
    program.enableAttributeArray(vertexAttrib);
    program.enableAttributeArray(colorAttrib);
    program.enableAttributeArray(texcordAttrib);

    program.setAttributeArray(vertexAttrib,vertices.constData());
    program.setAttributeArray(colorAttrib,colors.constData());
    program.setAttributeArray(texcordAttrib,texCords.constData());

    QMatrix4x4 mat;
    static int rotate=1;
    rotate += 1;
    mat.rotate(rotate,0,0,1);
    program.setUniformValue(program.uniformLocation("matrix"),mat);

    texture->bind();
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    program.disableAttributeArray(vertexAttrib);
    program.disableAttributeArray(colorAttrib);
    program.disableAttributeArray(texcordAttrib);

    program.release();
}

QOpenGLFramebufferObject * TextureRenderer::createFramebufferObject(const QSize &size) {
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    format.setSamples(4);
    return new QOpenGLFramebufferObject(size, format);
}

void TextureRenderer::initialize()
{
    initializeOpenGLFunctions();

    QString vs = R"END(
        #version 330 core
        layout ( location=0 ) in vec3 vertex;
        layout ( location=1 ) in vec3 color;
        layout (location=2) in vec2 aTexCoord;
        out vec3 fragColor;
        out vec2 TexCoord;
        uniform mat4 matrix;
        void main()
        {
            //gl_Position = matrix*vec4(vertex,1.0f);
            vec4 pos =  matrix*vec4(vertex,1.0f);
            if(pos.x >1)pos.x = 1;
            if(pos.y >1)pos.y =1;
            if(pos.x<-1)pos.x = -1;
            if(pos.y<-1)pos.y = -1;
            gl_Position = pos;
            fragColor = color;
            TexCoord = aTexCoord;
        }
        )END";

    QString fs = R"END(
        #version 330 core
        in vec3 fragColor;
        in vec2 TexCoord;
        uniform sampler2D ourTexture;
        void main()
        {
            gl_FragColor = texture(ourTexture, TexCoord)*vec4(fragColor,1.0f);
        }
        )END";

    program.addCacheableShaderFromSourceCode(QOpenGLShader::Vertex, vs);
    program.addCacheableShaderFromSourceCode(QOpenGLShader::Fragment, fs);
    program.link();
}
