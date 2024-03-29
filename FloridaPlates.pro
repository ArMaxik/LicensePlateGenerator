#-------------------------------------------------
#
# Project created by QtCreator 2019-07-05T16:08:39
#
#-------------------------------------------------

QT       += core gui 3dcore 3drender 3dinput 3dextras

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FloridaPlates
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    licenseplatemanager.cpp \
        main.cpp \
    mainwidget.cpp \
    material.cpp \
    offscreenengine.cpp \
    offscreensurfaceframegraph.cpp \
    texturegenerator.cpp \
    materialmanager.cpp \
    scene.cpp \
    renderableentity.cpp \
    light.cpp \
    texturerendertarget.cpp

HEADERS += \
    licenseplatemanager.h \
    mainwidget.h \
    material.h \
    offscreenengine.h \
    offscreensurfaceframegraph.h \
    texgenhelpfunctions.h \
    texturegenerator.h \
    materialmanager.h \
    scene.h \
    imagetexture.h \
    renderableentity.h \
    light.h \
    texturerendertarget.h

RESOURCES += \
    res.qrc

FORMS += \
    mainwidget.ui
