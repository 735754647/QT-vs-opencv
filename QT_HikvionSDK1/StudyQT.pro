#-------------------------------------------------
#
# Project created by QtCreator 2020-05-14T20:05:29
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = StudyQT
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        hikvisionsdk.cpp \
        camerainterface.cpp \
        mythread.cpp \
        halconself.cpp

HEADERS  += mainwindow.h \
            hikvisionsdk.h \
            camerainterface.h \
            mythread.h \
            halconself.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/include/Hik_Includes
INCLUDEPATH += $$PWD/include/halcon12X64
INCLUDEPATH += $$PWD/include/halcon12X64/halconcpp


LIBS += -L$$PWD/lib/Hik_Libs/ -lMvCameraControl
LIBS += -L$$PWD/lib/halcon12X64 -lhalcon
LIBS += -L$$PWD/lib/halcon12X64 -lhalconcpp




