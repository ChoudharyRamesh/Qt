//#include <iostream>
//#include<GL/glew.h>
//#include<GLFW/glfw3.h>

//#include<QtMath>
//#include<QMatrix4x4>

//bool setUpGlew(GLFWwindow *window)
//{
//    glfwMakeContextCurrent(window);
//    glewExperimental = GL_TRUE;

//    if(glewInit()!=GLEW_OK)return false;

//    GLint bufferWidth,bufferHeight;
//    glfwGetFramebufferSize(window,&bufferWidth,&bufferHeight);

//    glViewport(0,0,bufferWidth,bufferHeight);
//    return true;
//}

//GLFWwindow * createNewWindow(GLuint width, GLuint height, int majorVersion, int minorVersion, const char *windowName)
//{
//    if(!glfwInit()) return nullptr;

//    //set up glfwWindowProperty
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,majorVersion);
//    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,minorVersion);
//    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
//    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GLFW_TRUE);

//    GLFWwindow * window = glfwCreateWindow(width,height,windowName,NULL,NULL);
//    if(!window)  return nullptr;

//    if(!setUpGlew(window))
//    {
//        glfwDestroyWindow(window);
//        window = nullptr;
//        qDebug()<<"glew is not initialized";
//        return nullptr;
//    }

//    if(!window) glfwTerminate();
//    return window;
//}


//int compileVertexShader(const char * code)
//{
//    unsigned int vertexShader= glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertexShader, 1, &code, NULL);
//    glCompileShader(vertexShader);

//    int  success;
//    char infoLog[512];
//    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//    if(!success)
//    {
//        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//        return 0;
//    }
//    return vertexShader;
//}

//int compileFragmentShader(const char * code)
//{

//    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragmentShader, 1, &code, NULL);
//    glCompileShader(fragmentShader);

//    int  success;
//    char infoLog[512];
//    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//    if (!success)
//    {
//        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//        return 0;
//    }
//    return fragmentShader;
//}

//int createShaderProgram(const char * vertexShadercode, const char * fragmentShadercode)
//{
//    unsigned int vertexShader ,fragmentShader;
//    vertexShader = compileVertexShader(vertexShadercode);
//    fragmentShader = compileFragmentShader(fragmentShadercode);

//    unsigned int shaderProgram;
//    shaderProgram = glCreateProgram();
//    glAttachShader(shaderProgram, vertexShader);
//    glAttachShader(shaderProgram, fragmentShader);
//    glLinkProgram(shaderProgram);

//    int  success;
//    char infoLog[512];
//    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//    if(!success)
//    {
//        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//        std::cout << "linking falied\n" << infoLog << std::endl;
//        return 0;
//    }
//    glDeleteShader(vertexShader);
//    glDeleteShader(fragmentShader);
//    return shaderProgram;
//}

//unsigned int createVBO(const float * data,int size)
//{
//    unsigned int vbo_id;
//    glGenBuffers(1,&vbo_id);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
//    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
//    return vbo_id;
//}

//unsigned int createVAO()
//{
//    unsigned int vao_id;
//    glGenVertexArrays(1,&vao_id);
//    glBindVertexArray(vao_id);
//    return vao_id;
//}


//void learnPerspectiveProjection(GLFWwindow *mainWindow)
//{
//    const char * vertexShaderSource ="#version 330 core\n"
//                                     "layout (location = 0) in vec3 aPos;\n"
//                                     "layout (location = 1) in vec3 aColor;\n"
//                                     "uniform mat4 mvp;\n"
//                                     "out vec3 vertexColor;\n"
//                                     "void main()\n"
//                                     "{\n"
//                                     "    gl_Position =  mvp * vec4(aPos, 1.0);\n"
//                                     "vertexColor = aColor;\n"
//                                     "}\0";

//    const char * fragmentShaderSource  =  "#version 330 core\n"
//                                          "out vec4 FragColor;\n"
//                                          "in vec3 vertexColor;\n"
//                                          "void main(){ \n"
//                                          "FragColor = vec4(vertexColor,1.0); \n"
//                                          "}\0";


//    unsigned int shaderProgram = createShaderProgram(vertexShaderSource,fragmentShaderSource);

//    static const float cubeVertices[] = {
//        //vertex                  color
//        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
//        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
//        0.5f,  0.5f, -0.5f,  0.0f,0.0f,1.0f,
//        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
//        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,

//        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,
//        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
//        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
//        0.5f,  0.5f,  0.5f,  0.0f,1.0f,0.0f,
//        -0.5f,  0.5f,  0.5f,  1.0f,0.647f,0.0f,
//        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,

//        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,
//        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f,
//        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
//        -0.5f, -0.5f, -0.5f,  1.0f,0.0f,0.0f,
//        -0.5f, -0.5f,  0.5f,   0.5f,0.0f,0.5f,
//        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,

//        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,
//        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,
//        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
//        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
//        0.5f,  0.5f,  0.5f,  1.0f,1.0f,0.0f,

//        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,
//        0.5f, -0.5f, -0.5f,  0.0f,1.0f,0.0f,
//        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
//        0.5f, -0.5f,  0.5f,  1.0f,0.75f,0.796f,
//        -0.5f, -0.5f,  0.5f,  0.5f,0.0f,0.5f,
//        -0.5f, -0.5f, -0.5f,   1.0f,0.0f,0.0f,

//        -0.5f,  0.5f, -0.5f,  1.0f,1.0f,0.0f,
//        0.5f,  0.5f, -0.5f,   0.0f,0.0f,1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,
//        0.5f,  0.5f,  0.5f,  1.0f,0.0f,1.0f,
//        -0.5f,  0.5f,  0.5f,   1.0f,0.647f,0.0f,
//        -0.5f,  0.5f, -0.5f,   1.0f,1.0f,0.0f,
//    };


//    unsigned int VAO = createVAO();
//    createVBO(cubeVertices,sizeof(cubeVertices));

//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
//    glEnableVertexAttribArray(0);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
//    glEnableVertexAttribArray(1);
//    glBindVertexArray(VAO);
//    glUseProgram(shaderProgram);

//    QMatrix4x4 view,projection,model,mvp;
//    view.translate(0.0f, 0.0f, -3.0f);

//    float fov = 90.0f;
//    float tanOfHalfFov = tanf(qDegreesToRadians(fov)/2.0f);
//    float d = 1.0f/tanOfHalfFov;
//    projection = QMatrix4x4(
//                d       ,0.0f   ,0.0f   ,0.0f,
//                0.0f   ,d       ,0.0f   ,0.0f,
//                0.0f   ,0.0f   ,1.0f   ,0.0f,
//                0.0f   ,0.0f   ,1.0f   ,0.0f);

//    // this block is working
//    {
//        //  projection.perspective(45.0f, 800.0f /600.0f, 0.01f, 100.0f);
//    }

//    // but this block is not working
//    {
//        float fov = 90.0f;
//        float tanOfHalfFov = tanf(qDegreesToRadians(fov)/2.0f);
//        float d = 1.0f/tanOfHalfFov;
//        projection = QMatrix4x4(
//                    d       ,0.0f   ,0.0f   ,0.0f,
//                    0.0f   ,d       ,0.0f   ,0.0f,
//                    0.0f   ,0.0f   ,1.0f   ,0.0f,
//                    0.0f   ,0.0f   ,1.0f   ,0.0f);
//    }

//    glEnable(GL_DEPTH_TEST);


//    while(!glfwWindowShouldClose(mainWindow))
//    {
//        _sleep(25);
//        glClearColor(0,0,0,0.0f);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        model.setToIdentity();
//        model.rotate(qRadiansToDegrees(glfwGetTime()),0.0f, 1.0f, 0.0f);
//        mvp =  projection* view * model;

//        unsigned int pvmLoc = glGetUniformLocation(shaderProgram, "mvp");
//        glUniformMatrix4fv(pvmLoc, 1, GL_FALSE,mvp.data());

//        glDrawArrays(GL_TRIANGLES, 0, 36);
//        glfwSwapBuffers(mainWindow);
//        glfwPollEvents();
//    }

//    glfwTerminate();
//}



//int main()
//{

//    GLFWwindow * mainWindow = createNewWindow(800,600,4,3,"MainWindow");
//    if(!mainWindow)
//    {
//        qDebug()<<"glfwWindow is not created";
//        return 1;
//    }
//    learnPerspectiveProjection(mainWindow);
//}

