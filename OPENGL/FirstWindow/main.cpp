#include<mopengl.h>
int main()
{
    GLFWwindow * mainWindow = createNewWindow(800,600,4,3,"MainWindow");
    if(!mainWindow)
    {
        qDebug()<<"glfwWindow is not created";
        return 1;
    }

    drawMagicFilter(mainWindow);

}
