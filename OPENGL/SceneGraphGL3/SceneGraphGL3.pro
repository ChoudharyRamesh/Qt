QMAKE_PRE_LINK = "C:/mycode/OPENGL/SceneGraphGL3/Shaders/compileShader.bat"

QT += quick

SOURCES += \
        customitem.cpp \
        main.cpp

resources.files = main.qml  \
Temp.qml \
Shaders/shader.vert.qsb \
Shaders/shader.frag.qsb \

resources.prefix = /$${TARGET}
RESOURCES += resources

DISTFILES += Shaders/vertex.vert  \
Shaders/fragment.frag  \
Shaders/compileShader.bat \

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    customitem.h
