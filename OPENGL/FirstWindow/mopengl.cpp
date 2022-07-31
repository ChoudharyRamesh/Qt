#include "mopengl.h"
#include<QImage>
#include<execution>


bool setUpGlew(GLFWwindow *window)
{
    // set the context for glew to  use
    glfwMakeContextCurrent(window);

    // allow modern extension feature
    glewExperimental = GL_TRUE;

    if(glewInit()!=GLEW_OK)return false;

    GLint bufferWidth,bufferHeight;
    glfwGetFramebufferSize(window,&bufferWidth,&bufferHeight);

    // setup viewport
    glViewport(0,0,bufferWidth,bufferHeight);
    return true;
}

GLFWwindow * createNewWindow(GLuint width, GLuint height, int majorVersion, int minorVersion, const char *windowName)
{
    if(!glfwInit()) return nullptr;

    //set up glfwWindowProperty
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,majorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,minorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);

    GLFWwindow * window = glfwCreateWindow(width,height,windowName,NULL,NULL);
    if(!window)  return nullptr;

    if(!setUpGlew(window))
    {
        glfwDestroyWindow(window);
        window = nullptr;
        qDebug()<<"glew is not initialized";
        return nullptr;
    }

    if(!window) glfwTerminate();
    return window;
}


int compileVertexShader(const char * code)
{
    unsigned int vertexShader= glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &code, NULL);
    glCompileShader(vertexShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return vertexShader;
}


int compileFragmentShader(const char * code)
{
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &code, NULL);
    glCompileShader(fragmentShader);

    int  success;
    char infoLog[512];
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return 0;
    }
    return fragmentShader;
}



int createShaderProgram(std::string color, const char * vertexShadercode, const char * fragmentShadercode)
{
    unsigned int vertexShader ,fragmentShader;
    if(!strcmp(vertexShadercode,""))
    {
        const char * vertexShadercode = "#version 330 core\n"
                                        "layout (location = 0) in vec3 aPos;\n"
                                        "void main()\n"
                                        "{\n"
                                        "   gl_Position = vec4(aPos , 1.0);\n"
                                        "}\0";
        vertexShader = compileVertexShader(vertexShadercode);
    }
    else vertexShader = compileVertexShader(vertexShadercode);

    if(!strcmp(fragmentShadercode,""))
    {
        if(!color.compare(""))color="1.0f,0.0f,0.0f,1.0f";
        std::string code  =  "#version 330 core\n"
                             "out vec4 FragColor;\n"
                             "void main()\n"
                             "{\n"
                             "  FragColor = vec4("+color+");\n"
                                                         "}\0";
       fragmentShader = compileFragmentShader(code.c_str());
    }
    else fragmentShader = compileFragmentShader(fragmentShadercode);

    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "linking falied\n" << infoLog << std::endl;
        return 0;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return shaderProgram;
}

uint createVBO(const float * data,int size)
{
    unsigned int vbo_id;
    glGenBuffers(1,&vbo_id);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    return vbo_id;
}

uint createEBO(const uint * data,int size)
{
    unsigned int ebo_id;
    glGenBuffers(1,&ebo_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    return ebo_id;
}


uint createVAO()
{
    unsigned int vao_id;
    glGenVertexArrays(1,&vao_id);
    glBindVertexArray(vao_id);
    return vao_id;
}

void drawTraingle( GLFWwindow * mainWindow)
{
    unsigned int shaderProgram = createShaderProgram();

    // An array of 3 vectors which represents 3 vertices
    static const float traingleVertices[] =
    {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f
    };

    unsigned int vao = createVAO();
    unsigned int vbo = createVBO(traingleVertices,sizeof(traingleVertices));

    glVertexAttribPointer(
                0,                        // attribute 0. No particular reason for 0, but must match the layout in the shader.
                3,                        // size
                GL_FLOAT,           // type
                GL_FALSE,           // normalized?
                3 * sizeof(float),   // stride
                0                         // array buffer offset
                );
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as
    // the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(mainWindow))
    {
        // get wait and handle user input event
        glfwWaitEvents();


        //clear window
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}


void drawRectangle(GLFWwindow *mainWindow)
{
    unsigned int shaderProgram = createShaderProgram();

    static const float traingleVertices[] = {
        0.5f,  0.5f, 0.0f,  // top right
        0.5f, -0.5f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f,  0.5f, 0.0f   // top left
    };
    static const uint indices[] = {  // note that we start from 0!
                                     0, 1, 3,   // first triangle
                                     1, 2, 3    // second triangle
                                  };

    unsigned int vao = createVAO();
    createVBO(traingleVertices,sizeof(traingleVertices));
    createEBO(indices,sizeof(indices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
    glfwTerminate();
}

void doubleTraingle1(GLFWwindow *mainWindow)
{
    unsigned int shaderProgram = createShaderProgram();

    static const float traingleVertices[] = {
        -1.0f,  -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f ,
        1.0f,  -0.5f, 0.0f
    };
    static const uint indices[] = {  // note that we start from 0!
                                     0, 1, 2,   // first triangle
                                     2, 3, 4    // second triangle
                                  };

    unsigned int vao = createVAO();
    createVBO(traingleVertices,sizeof(traingleVertices));
    createEBO(indices,sizeof(indices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();

        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();

}

void doubleTraingle2(GLFWwindow *mainWindow)
{
    unsigned int shaderProgram = createShaderProgram();

    static const float traingle1[] = {
        -1.0f,  -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f
    };

    unsigned int vao1 = createVAO();
    createVBO(traingle1,sizeof(traingle1));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    float traingle2[] = {
        0.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f ,
        1.0f,  -0.5f, 0.0f
    };

    unsigned int vao2 = createVAO();
    createVBO(traingle2,sizeof(traingle2));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();

        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}

void doubleTraingle3(GLFWwindow *mainWindow)
{
    unsigned int shaderProgram1 = createShaderProgram("1.0f,0.0f,0.0f,1.0f");
    unsigned int shaderProgram2 = createShaderProgram("0.0f,1.0f,0.0f,1.0f");

    static const float traingle1[] =
    {
        -1.0f,  -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        0.0f, -0.5f, 0.0f
    };

    unsigned int vao1 = createVAO();
    createVBO(traingle1,sizeof(traingle1));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    float traingle2[] = {
        0.0f, -0.5f, 0.0f,
        0.5f,  0.5f, 0.0f ,
        1.0f,  -0.5f, 0.0f
    };

    unsigned int vao2 = createVAO();
    createVBO(traingle2,sizeof(traingle2));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();

        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram1);
        glBindVertexArray(vao1);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glUseProgram(shaderProgram2);
        glBindVertexArray(vao2);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}

void drawRectangleButSetColorInVertexShader(GLFWwindow *mainWindow)
{
    const char *  vertexShaderCode =  "#version 330 core\n"
                                      "layout (location = 0) in vec3 aPos;\n"
                                      "out vec4 vertexColor;\n"
                                      "void main()\n"
                                      "{\n"
                                      "   gl_Position = vec4(aPos, 1.0);\n"
                                      " vertexColor = vec4(1.0f,1.0f,0.0f,1.0f);\n"
                                      "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec4 vertexColor;\n"
                                          "void main()\n"
                                          "{\n"
                                          "    FragColor = vertexColor;\n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderCode,fragmentShaderSource);

    static const float traingleVertices[] =
    {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f
    };


    unsigned int vao = createVAO();
    createVBO(traingleVertices,sizeof(traingleVertices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();

        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
    glfwTerminate();
}


void drawRectangleWithUniformDataSharing(GLFWwindow *mainWindow)
{
    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "uniform vec4 ourColor;\n"
                                          "void main()\n"
                                          "{\n"
                                          "    FragColor = ourColor;\n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("","",fragmentShaderSource);

    static const float traingleVertices[] =
    {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f
    };

    unsigned int vao = createVAO();
    createVBO(traingleVertices,sizeof(traingleVertices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // be sure to activate the shader
        glUseProgram(shaderProgram);

        // update the uniform color
        float timeValue = glfwGetTime();
        float greenValue = sin(timeValue) / 2.0f + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
    glfwTerminate();
}


///////////////////////////////////////////////////////////////////////////////////////////////


void drawTraingleWithDiffColor(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource = "#version 330 core\n"
                                      "layout (location = 0) in vec3 aPos;\n"
                                      "layout (location = 1) in vec3 aColor;\n"
                                      "out vec3 ourColor;\n"
                                      "void main()\n"
                                      "{\n"
                                      "   gl_Position = vec4(aPos,1.0);\n"
                                      "ourColor = aColor;\n"
                                      "}\0";

    const char * fragmentShaderSource=  "#version 330 core\n"
                                        "out vec4 FragColor;\n"
                                        "in vec3 ourColor;\n"
                                        "void main()\n"
                                        "{\n"
                                        "    FragColor = vec4(ourColor, 1.0f);\n"
                                        "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);

    float traingleVertices[] = {
        // positions               // colors
        -1.0f, -1.0f, 0.0f,      1.0f, 0.0f, 0.0f,   // bottom right
        1.0f, -1.0f, 0.0f,       0.0f, 1.0f, 0.0f,   // bottom left
        0.0f,  1.0f, 0.0f,        0.0f, 0.0f, 1.0f    // top
    };

    unsigned int vao = createVAO();
    createVBO(traingleVertices,sizeof(traingleVertices));

    // position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

    // color attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        glClearColor(0,0,0,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }
    glfwTerminate();
}

void drawMovableTraingle(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource = "#version 330 core\n"
                                      "layout (location = 0) in vec3 aPos;\n"
                                      "uniform vec3 offset;\n"
                                      "void main()\n"
                                      "{\n"
                                      "   gl_Position = vec4(aPos.x+offset.x , aPos.y+offset.y , aPos.z+offset.z , 1.0f );\n"
                                      "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,"");
    static const float traingleVertices[] =
    {
        -0.5f, -.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };


    unsigned int vao = createVAO();
    createVBO(traingleVertices,sizeof(traingleVertices));

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    float x=0,y=0;
    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        if (glfwGetKey(mainWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            x+=0.02f;
        }
        else if (glfwGetKey(mainWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            x-=0.02f;
        }
        else if (glfwGetKey(mainWindow, GLFW_KEY_UP) == GLFW_PRESS)
        {
            y+=0.02f;
        }
        else if (glfwGetKey(mainWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            y-=0.02f;
        }

        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        int offsetAttributeLocation = glGetUniformLocation(shaderProgram, "offset");
        glUniform3f(offsetAttributeLocation, x, y,0.0f);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}

void drawAnswer2(GLFWwindow *mainWindow)
{

    const char * vertexShaderSource = "#version 330 core\n"
                                      "layout (location = 0) in vec3 aPos;\n"
                                      "out vec4 vertexColor;\n"
                                      "void main()\n"
                                      "{\n"
                                      "   gl_Position = vec4(aPos , 1.0f );\n"
                                      "vertexColor=vec4(aPos,1.0f);"
                                      "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec4 vertexColor;\n"
                                          "void main()\n"
                                          "{\n"
                                          "    FragColor = vertexColor;\n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);
    static const float traingleVertices[] =
    {
        -0.5f, -.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };

    unsigned int vao = createVAO();
    createVBO(traingleVertices,sizeof(traingleVertices));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}

void drawTexture(GLFWwindow *mainWindow)
{

    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "layout (location = 2) in vec2 aTexCoord;\n"
                                     "out vec3 ourColor;\n"
                                     "out vec2 TexCoord;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos, 1.0);\n"
                                     "    ourColor = aColor;\n"
                                     "    TexCoord = aTexCoord;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec3 ourColor;\n"
                                          "in vec2 TexCoord;\n"
                                          "uniform sampler2D ourTexture;\n"
                                          "void main(){ FragColor = texture(ourTexture, TexCoord); //*vec4(ourColor, 1.0);\n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);


    static const float vertices[] = {
        // positions          // colors           // texture coords
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f ,  // top left
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    1.0f, 1.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f   // bottom left
    };

    uint indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));
    createEBO(indices,sizeof(indices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage * image = new QImage("C:/Users/Nishant Choudhary/Pictures/Screenshots/temp/PicsArt_05-22-10.55.00.jpg");
    image->convertTo(QImage::Format::Format_RGB888);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width(),
                 image->height(),0,GL_RGB,GL_UNSIGNED_BYTE,image->bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    delete image;

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}

void drawTexture1(GLFWwindow *mainWindow)
{

    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "layout (location = 2) in vec2 aTexCoord;\n"
                                     "out vec3 ourColor;\n"
                                     "out vec2 TexCoord;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos, 1.0);\n"
                                     "    ourColor = aColor;\n"
                                     "    TexCoord = aTexCoord;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec3 ourColor;\n"
                                          "in vec2 TexCoord;\n"
                                          "uniform sampler2D ourTexture;\n"
                                          "void main(){ FragColor = texture(ourTexture, TexCoord); //*vec4(ourColor, 1.0);\n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);

    // four image in single container
    static const float vertices[] = {
        // positions          // colors           // texture coords
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f ,  // top left
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    2.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    2.0f, 2.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 2.0f   // bottom left
    };

    uint indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));
    createEBO(indices,sizeof(indices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage * image = new QImage("C:/Users/Nishant Choudhary/Pictures/Screenshots/temp/PicsArt_05-22-10.55.00.jpg");
    image->convertTo(QImage::Format::Format_RGB888);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width(),
                 image->height(),0,GL_RGB,GL_UNSIGNED_BYTE,image->bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    delete image;

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}


void drawTexture2(GLFWwindow *mainWindow)
{

    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "layout (location = 2) in vec2 aTexCoord;\n"
                                     "out vec3 ourColor;\n"
                                     "out vec2 TexCoord;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos, 1.0);\n"
                                     "    ourColor = aColor;\n"
                                     "    TexCoord = aTexCoord;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec3 ourColor;\n"
                                          "in vec2 TexCoord;\n"
                                          "uniform sampler2D ourTexture;\n"
                                          "void main(){ FragColor = texture(ourTexture, TexCoord); //*vec4(ourColor, 1.0);\n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);


    static const float vertices[] = {
        // positions          // colors           // texture coords
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 0.0f ,  // top left
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,    1.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,    1.0f, 1.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 1.0f   // bottom left
    };

    uint indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));
    createEBO(indices,sizeof(indices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // set texture filtering to nearest neighbor to clearly see the texels/pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    QImage * image = new QImage("C:/Users/Nishant Choudhary/Pictures/Screenshots/temp/PicsArt_05-22-10.55.00.jpg");
    image->convertTo(QImage::Format::Format_RGB888);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width(),
                 image->height(),0,GL_RGB,GL_UNSIGNED_BYTE,image->bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    delete image;

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}

void drawTexture3(GLFWwindow *mainWindow)
{

    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec2 aTexCoord;\n"
                                     "out vec2 TexCoord;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos, 1.0);\n"
                                     "    TexCoord = aTexCoord;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec2 TexCoord;\n"
                                          "uniform sampler2D ourTexture1;\n"
                                          "uniform sampler2D ourTexture2;\n"
                                          "void main(){ FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord), 0.5f); \n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);


    static const float vertices[] = {
        // positions         // texture coords
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f ,  // top left
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 1.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f   // bottom left
    };


    uint indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));
    createEBO(indices,sizeof(indices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1;
    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage * image = new QImage("C:/Users/Nishant Choudhary/Pictures/Screenshots/temp/PicsArt_05-22-10.55.00.jpg");
    image->convertTo(QImage::Format::Format_RGB888);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width(),
                 image->height(),0,GL_RGB,GL_UNSIGNED_BYTE,image->bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    delete image;


    unsigned int texture2;
    glGenTextures(1,&texture2);
    glBindTexture(GL_TEXTURE_2D,texture2);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage * image2 = new QImage("C:/Users/Nishant Choudhary/Pictures/Saved Pictures/WIN_20190405_22_49_22_Pro.jpg");
    image2->convertTo(QImage::Format_RGBA8888_Premultiplied);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image2->width(),
                 image2->height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image2->bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    delete image2;


    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}

void drawTexture4(GLFWwindow *mainWindow)
{

    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec2 aTexCoord;\n"
                                     "out vec2 TexCoord;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = vec4(aPos, 1.0);\n"
                                     "    TexCoord = aTexCoord;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec2 TexCoord;\n"
                                          "uniform sampler2D ourTexture1;\n"
                                          "uniform sampler2D ourTexture2;\n"
                                          "uniform vec2 transparency;\n"
                                          "void main(){ \n"
                                          "FragColor = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, TexCoord),transparency.x); \n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);


    static const float vertices[] = {
        // positions         // texture coords
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f ,  // top left
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 1.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f   // bottom left
    };


    uint indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));
    createEBO(indices,sizeof(indices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture1;
    glGenTextures(1,&texture1);
    glBindTexture(GL_TEXTURE_2D,texture1);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage * image = new QImage("C:/Users/Nishant Choudhary/Pictures/Screenshots/temp/PicsArt_05-22-10.55.00.jpg");
    image->convertTo(QImage::Format::Format_RGB888);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width(),
                 image->height(),0,GL_RGB,GL_UNSIGNED_BYTE,image->bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    delete image;


    unsigned int texture2;
    glGenTextures(1,&texture2);
    glBindTexture(GL_TEXTURE_2D,texture2);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage * image2 = new QImage("C:/Users/Nishant Choudhary/Pictures/Saved Pictures/WIN_20190405_22_49_22_Pro.jpg");
    image2->convertTo(QImage::Format_RGBA8888_Premultiplied);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image2->width(),
                 image2->height(),0,GL_RGBA,GL_UNSIGNED_BYTE,image2->bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    delete image2;


    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram, "ourTexture2"), 1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    float transparency=0.5f;
    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        if (glfwGetKey(mainWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            transparency+=0.05f;
        }
        else if (glfwGetKey(mainWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            transparency-=0.05f;
        }

        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        //  int transparencyAttributeLocation = glGetUniformLocation(shaderProgram, "transparency");
        glUniform2f(2 /*transparencyAttributeLocation*/ ,transparency,0.0f);

        // bind Texture
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();

    }

    glfwTerminate();
}

void drawMagicFilter(GLFWwindow *mainWindow)
{

    const char * vertexShaderSource =R"END(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
out vec2 TexCoord;
void main()
{
    gl_Position = vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}
)END";


    const char * fragmentShaderSource = R"END(
#version 330 core
out vec4 FragColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;


void main()
{
//    FragColor = texture(ourTexture, TexCoord);

     //brightness
     // vec4 textureColor = texture(ourTexture, TexCoord);
     // FragColor = vec4((textureColor.rgb + vec3(0.3)), textureColor.w);

     //greyscale
    vec4 texelColor =  texture(ourTexture, TexCoord);
    float grey = texelColor.r * 0.31 + texelColor.g * 0.71 + texelColor.b * 0.07;
    FragColor = vec4(grey, grey, grey, 1.0);

     // mix color
    //FragColor = mix(vec4(grey, grey, grey, 1.0),vec4(0.0f,1.0f,0,0),0.2f);

}
)END";
;
    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);


    static const float vertices[] = {
        // positions          // texture coords
        -0.5f,  0.5f, 0.0f,   0.0f, 0.0f ,  // top left
        0.5f,  0.5f, 0.0f,    1.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,    1.0f, 1.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 1.0f    // bottom left
    };

    uint indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));
    createEBO(indices,sizeof(indices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); // set texture filtering to nearest neighbor to clearly see the texels/pixels
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    QImage * image = new QImage("C:/Users/Nishant Choudhary/Pictures/Screenshots/temp/PicsArt_05-22-10.55.00.jpg");
    image->convertTo(QImage::Format::Format_RGB888);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width(),
                 image->height(),0,GL_RGB,GL_UNSIGNED_BYTE,image->bits());
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        unsigned char * pixels = new unsigned char[256*256*4];
        glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
        QImage retimage = QImage::fromData(pixels,256*256*4,"JPG");
        if(retimage.save("C:/Users/Nishant Choudhary/Desktop/LCMake/gpImage.jpg")) qDebug()<<"saved";
        else qDebug()<<"not saved";

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }


    glDeleteTextures(GL_TEXTURE_2D,&texture);


    glfwTerminate();
}



void drawRoated(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec2 aTexCoord;\n"
                                     "out vec2 TexCoord;\n"
                                     "uniform mat4 transform;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position = transform*vec4(aPos, 1.0);\n"
                                     "    TexCoord = aTexCoord;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec2 TexCoord;\n"
                                          "uniform sampler2D ourTexture;\n"
                                          "void main(){ \n"
                                          "FragColor = texture(ourTexture, TexCoord); \n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);


    static const float vertices[] = {
        // positions         // texture coords
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f ,  // top left
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 1.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f   // bottom left
    };


    uint indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));
    createEBO(indices,sizeof(indices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage * image = new QImage("C:/Users/Nishant Choudhary/Pictures/Screenshots/temp/PicsArt_05-22-10.55.00.jpg");
    image->convertTo(QImage::Format::Format_RGB888);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width(),
                 image->height(),0,GL_RGB,GL_UNSIGNED_BYTE,image->bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    delete image;


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    glm::mat4 trans = glm::mat4(1.0f),transCurrent;
    float rotaton = 0;
    while(!glfwWindowShouldClose(mainWindow))
    {
        glfwWaitEvents();
        if (glfwGetKey(mainWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            rotaton-=0.1f;
        }
        else if (glfwGetKey(mainWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            rotaton+=0.1f;
        }

        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        transCurrent = glm::rotate(trans,rotaton, glm::vec3(0.0f, 0.0f, 1.0f));
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transCurrent));

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();

    }

    glfwTerminate();
}

void drawIn3D(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec2 aTexCoord;\n"
                                     "out vec2 TexCoord;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position =  projection * view * model * vec4(aPos, 1.0);\n"
                                     "    TexCoord = aTexCoord;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec2 TexCoord;\n"
                                          "uniform sampler2D ourTexture;\n"
                                          "void main(){ \n"
                                          "FragColor = texture(ourTexture, TexCoord); \n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);


    static const float vertices[] = {
        // positions         // texture coords
        -0.5f,  0.5f, 0.0f,  0.0f, 0.0f ,  // top left
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f,   // top right
        0.5f, -0.5f, 0.0f,   1.0f, 1.0f,   // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f   // bottom left
    };


    uint indices[] = {
        0, 1, 2, // first triangle
        0, 2, 3  // second triangle
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));
    createEBO(indices,sizeof(indices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage * image = new QImage("C:/Users/Nishant Choudhary/Pictures/Screenshots/temp/PicsArt_05-22-10.55.00.jpg");
    image->convertTo(QImage::Format::Format_RGB888);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width(),
                 image->height(),0,GL_RGB,GL_UNSIGNED_BYTE,image->bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    delete image;


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    while(!glfwWindowShouldClose(mainWindow))
    {
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);


        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, glm::radians(-60.0f), glm::vec3(1.0f, 0.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc  = glGetUniformLocation(shaderProgram, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"), 1, GL_FALSE, &projection[0][0]);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}


void draw3dCube1(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec2 aTexCoord;\n"
                                     "out vec2 TexCoord;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position =  projection * view * model * vec4(aPos, 1.0);\n"
                                     "    TexCoord = aTexCoord;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec2 TexCoord;\n"
                                          "uniform sampler2D ourTexture;\n"
                                          "void main(){ \n"
                                          "FragColor = texture(ourTexture, TexCoord); \n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);


    static const float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int texture;
    glGenTextures(1,&texture);
    glBindTexture(GL_TEXTURE_2D,texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    QImage * image = new QImage("C:/Users/Nishant Choudhary/Pictures/Screenshots/temp/PicsArt_05-22-10.55.00.jpg");
    image->convertTo(QImage::Format::Format_RGB888);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->width(),
                 image->height(),0,GL_RGB,GL_UNSIGNED_BYTE,image->bits());
    glGenerateMipmap(GL_TEXTURE_2D);
    delete image;


    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(mainWindow))
    {
        _sleep(25);
        glClearColor(0,0,0,1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc  = glGetUniformLocation(shaderProgram, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"), 1, GL_FALSE, &projection[0][0]);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}



void draw3dCube2(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "out vec3 vertexColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position =  projection * view * model * vec4(aPos, 1.0);\n"
                                     "vertexColor = aColor;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec3 vertexColor;\n"
                                          "void main(){ \n"
                                          "FragColor = vec4(vertexColor,1.0); \n"
                                          "}\0";


    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);

    static const float vertices[] = {
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,

        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,0.647f,0.0f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,

        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,

        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,
        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,

        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(mainWindow))
    {
        _sleep(25);
        glClearColor(0,0,0,1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // create transformations
        glm::mat4 model         = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 view          = glm::mat4(1.0f);
        glm::mat4 projection    = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
        view  = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
        // retrieve the matrix uniform locations
        unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
        unsigned int viewLoc  = glGetUniformLocation(shaderProgram, "view");
        // pass them to the shaders (3 different ways)
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"), 1, GL_FALSE, &projection[0][0]);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}


void draw3dCube3(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "out vec3 vertexColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position =  projection * view * model * vec4(aPos, 1.0);\n"
                                     "vertexColor = aColor;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec3 vertexColor;\n"
                                          "void main(){ \n"
                                          "FragColor = vec4(vertexColor,1.0); \n"
                                          "}\0";


    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);

    static const float vertices[] = {
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,

        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,0.647f,0.0f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,

        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,

        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,
        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,

        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f
    };

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    while(!glfwWindowShouldClose(mainWindow))
    {
        _sleep(25);
        glClearColor(0,0,0,1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // create transformations
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(60.0f),(float)800 / (float)600, 0.1f, 100.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"), 1, GL_FALSE, &projection[0][0]);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            model = glm::rotate(model,  (float)glfwGetTime()+((float)i+1/10), glm::vec3(1.0f, 0.3f, 0.5f));
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"), 1, GL_FALSE, &model[0][0]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}

void draw3dCube4(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "out vec3 vertexColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position =  projection * view * model * vec4(aPos, 1.0);\n"
                                     "vertexColor = aColor;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec3 vertexColor;\n"
                                          "void main(){ \n"
                                          "FragColor = vec4(vertexColor,1.0); \n"
                                          "}\0";


    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);

    static const float vertices[] = {
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,

        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,0.647f,0.0f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,

        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,

        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,
        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,

        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    int angle = 0;
    int angle2 = 0;
    while(!glfwWindowShouldClose(mainWindow))
    {
        _sleep(25);
        glClearColor(0,0,0,1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        // create transformations
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(60.0f),(float)800 / (float)600, 0.1f, 50.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"), 1, GL_FALSE, &projection[0][0]);

        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 2; i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            if(i==1)
            {
                model = glm::translate(model, glm::vec3( 3*cos(glm::radians((float)angle)),  0.0f, -3*sin(glm::radians((float)angle))-3.5f));
                model = glm::rotate(model, glm::radians((float)angle2), glm::vec3(1.0f, 5.0f, 1.0f));
                if(angle>=360)angle=0;else angle+=3;
                if(angle2>=360)angle2=0;else angle2+=10;
            }
            else
            {
                model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  -3.5f));
                model = glm::rotate(model, glm::radians((float)angle), glm::vec3(1.0f, 1.0f, 1.0f));
            }
            glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"), 1, GL_FALSE, &model[0][0]);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}


void draw3dLightningCube(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "layout (location = 2) in vec3 aNormal;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "out vec3 objectColor;\n"
                                     "out vec3 Normal;\n"
                                     "out vec3 FragPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position =  projection * view * model * vec4(aPos, 1.0);\n"
                                     "Normal = mat3(transpose(inverse(model))) * aNormal; \n"
                                     "objectColor = aColor;\n"
                                     " FragPos = vec3(model * vec4(aPos, 1.0));\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec3 objectColor;\n"
                                          "in vec3 Normal;\n"
                                          "in vec3 FragPos;\n"
                                          "uniform vec3 viewPos;\n"
                                          "uniform vec3 lightPos;\n"
                                          "vec3 lightColor = vec3(1.0f);\n"
                                          "void main(){\n"

                                          "float ambientStrength = 0.2;\n"
                                          "vec3 ambient = ambientStrength *lightColor;\n"

                                          "vec3 norm = normalize(Normal);\n"
                                          "vec3 lightDir = normalize(lightPos - FragPos);\n"
                                          "float diff = max(dot(norm, lightDir), 0.0);\n"
                                          "vec3 diffuse = diff * lightColor;  \n"

                                          "float specularStrength = 20;\n"
                                          "vec3 viewDir = normalize(viewPos - FragPos);\n"
                                          "vec3 reflectDir = reflect(-lightDir, norm);  \n"
                                          "float spec = pow(max(dot(viewDir, reflectDir), 0.0), 10);\n"
                                          "vec3 specular = specularStrength * spec * lightColor; \n"

                                          "vec3 result = (ambient + diffuse+specular) * objectColor;\n"
                                          "FragColor = vec4(result, 1.0);\n"
                                          "}\0";


    const char * fragmentShaderForLightSource  =  "#version 330 core\n"
                                                  "out vec4 FragColor;\n"
                                                  "void main(){ \n"
                                                  "FragColor = vec4(1.0); \n"
                                                  "}\0";

    unsigned int lightSourceShaderProgram =createShaderProgram("",vertexShaderSource,fragmentShaderForLightSource);
    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);

    static const float vertices[] = {
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,    0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,     0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,     0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,     0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,    0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,    0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,       0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,    0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,         0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,          0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,0.647f,0.0f,      0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,          0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,   -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f,     -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,      -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,      -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,     -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,   -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,       1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,      1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,       1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,       1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,    1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,       1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,     0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,       0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,    0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,    0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,      0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,     0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,      0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,      0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,       0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,       0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,   0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f,     0.0f,  1.0f,  0.0f
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord aNormal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //aNormal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    int angle = 0;
    int angle2 = 0;

    while(!glfwWindowShouldClose(mainWindow))
    {
        _sleep(25);
        glClearColor(0,0,0,1.0f);
        //glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // create transformations
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(60.0f),(float)800 / (float)600, 0.1f, 50.0f);
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));



        // render boxes
        glBindVertexArray(VAO);

        glm::mat4 lightModel = glm::mat4(1.0f);
        glUseProgram(lightSourceShaderProgram);
        glm::vec3 lightSourcePos = glm::vec3( 3*cos(glm::radians((float)angle)),  0.0f, -3*sin(glm::radians((float)angle))-3.5f);
        lightModel = glm::translate(lightModel,lightSourcePos);
        lightModel = glm::rotate(lightModel, glm::radians((float)angle2), glm::vec3(0.0f, 5.0f, 0.0f));
        if(angle>=360)angle=0;else angle+=3;
        if(angle2>=360)angle2=0;else angle2+=10;
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram,"projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram,"model"), 1, GL_FALSE, &lightModel[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 model = glm::mat4(1.0f);
        glUseProgram(shaderProgram);

        glUniform3fv(glGetUniformLocation(shaderProgram,"lightPos"), 1, &lightSourcePos[0]);
        model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  -3.5f));
        model = glm::rotate(model, glm::radians((float)angle), glm::vec3(1.0f, 0.2f, 0.0f));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"), 1, GL_FALSE, &model[0][0]);


        glCall(glDrawArrays(GL_TRIANGLES, 0, 36));

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////

// camera
glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =  0.0f;
float lastX =  800.0f / 2.0;
float lastY =  600.0 / 2.0;
float fov   =  45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
    lastX = xpos;
    lastY = ypos;

    float sensitivity = 0.1f; // change this value to your liking
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}
void camera(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "layout (location = 2) in vec3 aNormal;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "out vec3 objectColor;\n"
                                     "out vec3 Normal;\n"
                                     "out vec3 FragPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position =  projection * view * model * vec4(aPos, 1.0);\n"
                                     "Normal = mat3(transpose(inverse(model))) * aNormal; \n"
                                     "objectColor = aColor;\n"
                                     " FragPos = vec3(model * vec4(aPos, 1.0));\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec3 objectColor;\n"
                                          "in vec3 Normal;\n"
                                          "in vec3 FragPos;\n"
                                          "uniform vec3 viewPos;\n"
                                          "uniform vec3 lightPos;\n"
                                          "vec3 lightColor = vec3(1.0f);\n"
                                          "void main(){\n"

                                          "float ambientStrength = 0.2;\n"
                                          "vec3 ambient = ambientStrength *lightColor;\n"

                                          "vec3 norm = normalize(Normal);\n"
                                          "vec3 lightDir = normalize(lightPos - FragPos);\n"
                                          "float diff = max(dot(norm, lightDir), 0.0);\n"
                                          "vec3 diffuse = diff * lightColor;  \n"

                                          "float specularStrength = 20;\n"
                                          "vec3 viewDir = normalize(viewPos - FragPos);\n"
                                          "vec3 reflectDir = reflect(-lightDir, norm);  \n"
                                          "float spec = pow(max(dot(viewDir, reflectDir), 0.0), 10);\n"
                                          "vec3 specular = specularStrength * spec * lightColor; \n"

                                          "vec3 result = (ambient + diffuse+specular) * objectColor;\n"
                                          "FragColor = vec4(result, 1.0);\n"
                                          "}\0";


    const char * fragmentShaderForLightSource  =  "#version 330 core\n"
                                                  "out vec4 FragColor;\n"
                                                  "void main(){ \n"
                                                  "FragColor = vec4(1.0); \n"
                                                  "}\0";

    unsigned int lightSourceShaderProgram =createShaderProgram("",vertexShaderSource,fragmentShaderForLightSource);
    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);

    static const float vertices[] = {
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,    0.0f,  0.0f, -1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,     0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,     0.0f,  0.0f, -1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,     0.0f,  0.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,    0.0f,  0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,    0.0f,  0.0f, -1.0f,

        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,       0.0f,  0.0f,  1.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,    0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,         0.0f,  0.0f,  1.0f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,          0.0f,  0.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,0.647f,0.0f,      0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,          0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,   -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f,     -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,      -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,      -1.0f,  0.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,     -1.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,   -1.0f,  0.0f,  0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,       1.0f,  0.0f,  0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,      1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,       1.0f,  0.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,       1.0f,  0.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,    1.0f,  0.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,       1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,     0.0f, -1.0f,  0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,       0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,    0.0f, -1.0f,  0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,    0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,      0.0f, -1.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,     0.0f, -1.0f,  0.0f,

        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,      0.0f,  1.0f,  0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,      0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,       0.0f,  1.0f,  0.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,       0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,   0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f,     0.0f,  1.0f,  0.0f
    };

    unsigned int VAO = createVAO();
    createVBO(vertices,sizeof(vertices));

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord aNormal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //aNormal attribute
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6* sizeof(float)));
    glEnableVertexAttribArray(2);


    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);

    //    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnable(GL_DEPTH_TEST);

    int angle = 0;
    int angle2 = 0;


    glfwSetCursorPosCallback(mainWindow,mouse_callback);
    glfwSetScrollCallback(mainWindow, scroll_callback);

    while(!glfwWindowShouldClose(mainWindow))
    {
        _sleep(25);

        // per-frame time logic
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float cameraSpeed = 2.5 * deltaTime;
        if (glfwGetKey(mainWindow, GLFW_KEY_DOWN) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(mainWindow, GLFW_KEY_UP) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(mainWindow, GLFW_KEY_LEFT) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(mainWindow, GLFW_KEY_RIGHT) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

        glClearColor(0,0,0,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // create transformations
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(fov),(float)800 / (float)600, 0.1f, 50.0f);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);



        // render boxes
        glBindVertexArray(VAO);

        glm::mat4 lightModel = glm::mat4(1.0f);
        glUseProgram(lightSourceShaderProgram);
        glm::vec3 lightSourcePos = glm::vec3( 3*cos(glm::radians((float)angle)),  0.0f, -3*sin(glm::radians((float)angle))-3.5f);
        lightModel = glm::translate(lightModel,lightSourcePos);
        lightModel = glm::rotate(lightModel, glm::radians((float)angle2), glm::vec3(0.0f, 5.0f, 0.0f));
        if(angle>=360)angle=0;else angle+=3;
        if(angle2>=360)angle2=0;else angle2+=10;
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram,"projection"), 1, GL_FALSE, &projection[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(lightSourceShaderProgram,"model"), 1, GL_FALSE, &lightModel[0][0]);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glm::mat4 model = glm::mat4(1.0f);
        glUseProgram(shaderProgram);

        glUniform3fv(glGetUniformLocation(shaderProgram,"lightPos"), 1, &lightSourcePos[0]);
        model = glm::translate(model, glm::vec3( 0.0f,  0.0f,  -3.5f));
        model = glm::rotate(model, glm::radians((float)angle), glm::vec3(1.0f, 0.2f, 0.0f));
        glCall(glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]));
        glCall(glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"), 1, GL_FALSE, &projection[0][0]));
        glCall(glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"), 1, GL_FALSE, &model[0][0]));


        glCall(glDrawArrays(GL_TRIANGLES, 0, 36));

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glfwTerminate();
}




void understandLocalSpace( GLFWwindow * mainWindow)
{

    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "uniform mat4 model;\n"
                                     "uniform mat4 view;\n"
                                     "uniform mat4 projection;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position =  projection * view * model * vec4(aPos, 1.0);\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "void main(){ \n"
                                          "FragColor = vec4(1.0f); \n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);


    static const float traingleVertices[] =
    {
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.5f,  1.0f, 0.0f
    };

    unsigned int vao = createVAO();
    unsigned int vbo = createVBO(traingleVertices,sizeof(traingleVertices));

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float), 0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    while(!glfwWindowShouldClose(mainWindow))
    {

        glfwWaitEvents();
        glClearColor(0,0,1,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 model = glm::mat4(1.0f);
        // translated in world coordiante with respect to world origin
        model = glm::translate(model,glm::vec3(-0.5f,-0.5f,0.0f));

        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"), 1, GL_FALSE, &model[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"), 1, GL_FALSE, &projection[0][0]);

        glBindVertexArray(vao);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(mainWindow);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shaderProgram);
    glfwTerminate();
}



void understandPerspectiveProjection(GLFWwindow *mainWindow)
{
    const char * vertexShaderSource ="#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec3 aColor;\n"
                                     "uniform mat4 mvp;\n"
                                     "out vec3 vertexColor;\n"
                                     "void main()\n"
                                     "{\n"
                                     "    gl_Position =  mvp * vec4(aPos, 1.0);\n"
                                     "vertexColor = aColor;\n"
                                     "}\0";

    const char * fragmentShaderSource  =  "#version 330 core\n"
                                          "out vec4 FragColor;\n"
                                          "in vec3 vertexColor;\n"
                                          "void main(){ \n"
                                          "FragColor = vec4(vertexColor,1.0); \n"
                                          "}\0";

    unsigned int shaderProgram = createShaderProgram("",vertexShaderSource,fragmentShaderSource);

    static const float cubeVertices[] =
    {
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,

        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f,0.647f,0.0f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,

        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,

        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,

        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,
        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,
        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,

        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,
        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,
        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f
    };

    unsigned int VAO = createVAO();
    createVBO( cubeVertices ,sizeof(cubeVertices) );

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glBindVertexArray(VAO);
    glUseProgram(shaderProgram);

    QMatrix4x4 view,projection,model,mvp;
    view.translate(0.0f, 0.0f, -6.0f);

    // projection.perspective(45.0f, 800.0f /600.0f, 0.01f, 100.0f);

    float fov = 45.0f;
    float aspect_WbyH = 800.0f/600.0f;
    float tanOfHalfFov = tanf(qDegreesToRadians(fov)/2.0f);
    float d = 1.0f/tanOfHalfFov;
    float nearZ= 1.0f,farZ=100.0f;
    projection = QMatrix4x4(
                d/aspect_WbyH  ,0.0f   ,0.0f   ,0.0f,
                0.0f   ,d       ,0.0f   ,0.0f,
                0.0f   ,0.0f   ,(farZ+nearZ) / (nearZ - farZ)
                , (2.0f * farZ * nearZ) / (nearZ - farZ),
                0.0f   ,0.0f   ,-1.0f   ,0.0f);

    glEnable(GL_DEPTH_TEST);


    while(!glfwWindowShouldClose(mainWindow))
    {
        _sleep(25);
        glClearColor(0,0,0,0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        model.setToIdentity();
        model.rotate(qRadiansToDegrees(2*glfwGetTime()),1.0f, 1.0f, 1.0f);
        mvp =  projection * view * model;

        unsigned int pvmLoc = glGetUniformLocation(shaderProgram, "mvp");
        glUniformMatrix4fv(pvmLoc, 1, GL_FALSE,mvp.data());

        glDrawArrays(GL_TRIANGLES, 0, 36);
        glfwSwapBuffers(mainWindow);
        glfwPollEvents();

    }

    glfwTerminate();
}
