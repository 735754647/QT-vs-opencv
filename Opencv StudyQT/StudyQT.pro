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
    mythread.cpp

HEADERS  += mainwindow.h \
    hikvisionsdk.h \
    camerainterface.h \
    mythread.h

FORMS    += mainwindow.ui

INCLUDEPATH += $$PWD/opencv2 \
               $$PWD/Hik_Includes

LIBS += -L$$PWD/Hik_Libs/ -lMvCameraControl\

LIBS += -L$$PWD/lib/ -lopencv_world455\
                     -lopencv_world455d\
                     -lopencv_img_hash455d\

