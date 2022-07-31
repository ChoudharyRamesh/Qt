TEMPLATE = app
CONFIG -= app_bundle
QT -=  gui
CONFIG += core

CONFIG += c++17


#dynamic linking
INCLUDEPATH +=3rdparty/Mylib/include
DEPENDPATH += $$PWD/3rdparty/Mylib/include
LIBS += -L$$PWD/3rdparty/Mylib/Libs/ -lMYLIB  -lImageProcessingL

#static linking
LIBS += -L$$PWD/3rdparty/Mylib/Libs/ -lMYLIB  -lOpenCV



SOURCES += \
        main.cpp


win32: LIBS += -L$$PWD/../../../TenserflowC/lib/ -ltensorflow
INCLUDEPATH += $$PWD/../../../TenserflowC/include
DEPENDPATH += $$PWD/../../../TenserflowC/include
