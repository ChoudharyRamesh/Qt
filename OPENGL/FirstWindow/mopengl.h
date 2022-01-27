#ifndef MOPENGL_H
#define MOPENGL_H

#include<QtMath>
#include<QMatrix4x4>

#include <iostream>
#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<QDebug>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#ifdef QT_DEBUG
#define glCall(x) while(glGetError());\
    x;{\
    GLenum error = glGetError(); \
    Q_ASSERT_X(!error,("OpengGL Error :: ("+QString::number(error)+")").toStdString().c_str(),#x);}
#else
    #define glCall(x) x;
#endif

// create simple window
bool setUpGlew(GLFWwindow * window);
GLFWwindow *  createNewWindow(GLuint width,GLuint height,int majorVersion,int minorVersion,const char * windowName="");


// draw traingle
int compileVertexShader(const char * code);
int compileFragmentShader(const char * code);
int createShaderProgram(std::string color="1.0f,0.0f,0.0f,1.0f",const char *vertexShadercode="", const char *fragmentShadercode="");
void drawTraingle(GLFWwindow *mainWindow);

// draw rectangle ( using ebo ->> element buffer object)
void drawRectangle( GLFWwindow * mainWindow);


//exercise 1
// Try to draw 2 triangles next to each other using glDrawArrays by adding more vertices to your data
void doubleTraingle1( GLFWwindow * mainWindow);
//Now create the same 2 triangles using two different VAOs and VBOs for their data: solution.
void doubleTraingle2( GLFWwindow * mainWindow);
//Create two shader programs where the second program uses a different fragment shader that outputs the color yellow;
//draw both triangles again where one outputs the color yellow
void doubleTraingle3( GLFWwindow * mainWindow);


//shader (in , out  and linking between variables,sharing data between shaders )
void drawRectangleButSetColorInVertexShader( GLFWwindow * mainWindow);


/*uniform
Uniforms are another way to pass data from our application on the CPU to the shaders on the GPU. Uniforms are however
 slightly different compared to vertex attributes. First of all, uniforms are global. Global, meaning that a uniform variable
is unique per shader program object, and can be accessed from any shader at any stage in the shader program. Second,
 whatever you set the uniform value to, uniforms will keep their values until they're either reset or updated.
*/
void drawRectangleWithUniformDataSharing( GLFWwindow * mainWindow);


// use more attributes of shader program
void drawTraingleWithDiffColor( GLFWwindow * mainWindow);


//exercise 2
//Specify a horizontal offset via a uniform and move the triangle to the right side of the screen in the vertex shader using this offset value:
void drawMovableTraingle( GLFWwindow * mainWindow);
// Output the vertex position to the fragment shader using the out keyword and set the fragment's color equal to this vertex position (see
// how even the vertex position values are interpolated across the triangle). Once you managed to do this; try to answer the following
// question: why is the bottom-left side of our triangle black
void drawAnswer2(GLFWwindow * mainWindow);


//texture
void drawTexture(GLFWwindow * mainWindow);
//exercise 3
// Experiment with the different texture wrapping methods by specifying texture coordinates in the range 0.0f to 2.0f instead of
// 0.0f to 1.0f. See if you can display 4 smiley faces on a single container image clamped at its edge: solution, result. See if
// you can experiment with other wrapping methods as well
void drawTexture1(GLFWwindow * mainWindow);
// Try to display only the center pixels of the texture image on the rectangle in such a way that the individual pixels are getting
// visible by changing the texture coordinates. Try to set the texture filtering method to GL_NEAREST to see the pixels more clearly
void drawTexture2(GLFWwindow * mainWindow);
// draw two texture in one container
void drawTexture3(GLFWwindow * mainWindow);
//Use a uniform variable as the mix function's third parameter to vary the amount the two textures are visible. Use the up and down
//arrow keys to change how much the container or the smiley face is visible
void drawTexture4(GLFWwindow * mainWindow);
// apply magic filter on image
void drawMagicFilter(GLFWwindow * mainWindow);



// transformation
void drawRoated(GLFWwindow * mainWindow);


// coordiante system or 3D
void drawIn3D(GLFWwindow * mainWindow);
void draw3dCube1(GLFWwindow * mainWindow);
void draw3dCube2(GLFWwindow * mainWindow);
void draw3dCube3(GLFWwindow * mainWindow);
void draw3dCube4(GLFWwindow * mainWindow);

//camera
void camera(GLFWwindow * mainWindow);


//lightning
void draw3dLightningCube(GLFWwindow * mainWindow);


//remaining
void understandLocalSpace(GLFWwindow * mainWindow);
void understandPerspectiveProjection(GLFWwindow * mainWindow);



#endif // MOPENGL_H
