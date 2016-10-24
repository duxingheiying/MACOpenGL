#-------------------------------------------------
#
# Project created by QtCreator 2016-04-23T13:59:10
#
#-------------------------------------------------

QT       += core gui opengl webview

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 3DEngine
TEMPLATE = app


SOURCES += main.cpp \
    MainWindow.cpp \
    GLWidget.cpp

HEADERS  += \
    MainWindow.h \
    GLWidget.h \
    griding.h

FORMS    += \
    MainWindow.ui \
    GLWidget.ui

RESOURCES += \
    image.qrc
