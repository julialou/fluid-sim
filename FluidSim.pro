#-------------------------------------------------
#
# Project created by QtCreator 2012-11-07T14:10:36
#
#-------------------------------------------------

QT += opengl
QT += core \
        gui \
        xml
QMAKE_CXX=gcc

CONFIG += console
CONFIG -= app_bundle
TARGET = FluidSim
TEMPLATE = app
UI_HEADERS_DIR=ui
INCLUDEPATH+=include \
    += ui


SOURCES += src/main.cpp\
        src/MainWindow.cpp \
    src/GLWindow.cpp \
    src/Particle.cpp \
    src/FluidSystem.cpp \
    src/Grid.cpp \
    src/FluidBBox.cpp \
    src/Parser.cpp \
    src/Obstacle.cpp \
    src/Sphere.cpp \
    src/Cube.cpp \
    src/MarchingCubes.cpp \
    src/GridCell.cpp \
    src/MCGrid.cpp

HEADERS  += include/MainWindow.h \
    include/GLWindow.h \
    include/Particle.h \
    include/FluidSystem.h \
    include/Grid.h \
    include/FluidBBox.h \
    include/Parser.h \
    include/Obstacle.h \
    include/Common.h \
    include/Sphere.h \
    include/Cube.h \
    include/GridCell.h \
    include/MarchingCubes.h \
    include/MCGrid.h
FORMS += \
    ui/MainWindow.ui

macx:INCLUDEPATH+=$$(HOME)/boost_1_47_0
DEFINES+=GL_DO_NOT_WARN_IF_MULTI_GL_VERSION_HEADERS_INCLUDED

QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx:QMAKE_CXXFLAGS+= -arch x86_64
macx:INCLUDEPATH+=/usr/local/boost/
linux-g++:QMAKE_CXXFLAGS +=  -march=native
linux-g++-64:QMAKE_CXXFLAGS +=  -march=native
# define the _DEBUG flag for the graphics lib
DEFINES +=NGL_DEBUG

LIBS += -L/usr/local/lib
# add the ngl lib
LIBS +=  -L/$(HOME)/NGL/lib -l NGL

# now if we are under unix and not on a Mac (i.e. linux) define GLEW
linux-g++:linux-g++-64 {
    DEFINES += LINUX
    LIBS+= -lGLEW
}
linux-clang {
    DEFINES += LINUX
    LIBS+= -lGLEW
}
DEPENDPATH+=include
# if we are on a mac define DARWIN
macx:DEFINES += DARWIN
# this is where to look for includes
INCLUDEPATH += $$(HOME)/NGL/include/

win32: {
        DEFINES+=USING_GLEW
        INCLUDEPATH+=-I c:/boost_1_44_0
        INCLUDEPATH+=-I c:/boost

        INCLUDEPATH+= -I C:/NGL/Support/glew
        LIBS+= -L C:/NGL/lib
        LIBS+= -lmingw32
        DEFINES += WIN32
        DEFINES += USING_GLEW
        DEFINES +=GLEW_STATIC
        DEFINES+=_WIN32
        SOURCES+=C:/NGL/Support/glew/glew.c
        INCLUDEPATH+=C:/NGL/Support/glew/
}

OTHER_FILES += \
    shaders/Phong.vs \
    shaders/Phong.fs \
    shaders/Colour.vs \
    shaders/Colour.fs \
    data/params.txt

