TEMPLATE = app
CONFIG +=  c++17
CONFIG -= app_bundle console
CONFIG += qt core

SOURCES += \
    main.cpp \
    mopengl.cpp \
    temp.cpp
LIBS +=  -lopengl32 -luser32 -lshell32 -lgdi32
LIBS += -L"C:/mycode/OPENGL/OpenGL/glew/lib" -lglew32
LIBS += -L"C:/mycode/OPENGL/OpenGL/glfw/lib" -lglfw3
INCLUDEPATH += "C:/mycode/OPENGL/OpenGL/glfw/include"
INCLUDEPATH += "C:/mycode/OPENGL/OpenGL/glew/include"
INCLUDEPATH += "C:/mycode/OPENGL/OpenGL/glm"
HEADERS += \
    mopengl.h
