s#-------------------------------------------------
#
# Project created by QtCreator 2020-12-17T10:20:47
#
#-------------------------------------------------

QT       += core gui network serialport printsupport svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SuperDT
TEMPLATE = app
DESTDIR = $$PWD/Bin
RC_ICONS = AppIcon64.ico

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += QT_MESSAGELOGCONTEXT
DEFINES += PRO_DIR=\\\"'$$PWD'\\\"

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    CMainWindow.cpp \
    Ctrller/CByte2Text.cpp \
    Ctrller/CSettings.cpp \
    Ctrller/CText2Byte.cpp \
    Network/AbsConnection.cpp \
    Network/CSerialPort.cpp \
    Network/CTcpClient.cpp \
    Network/CTcpServer.cpp \
    Network/CUdp.cpp \
    Test/CQssTest.cpp \
    Tools/CConversion.cpp \
    Tools/CIconFont.cpp \
    Tools/CUIHelper.cpp \
    Views/Session/VCharts.cpp \
    Views/Session/VReceiveTrig.cpp \
    Views/Session/VSessionInterface.cpp \
    Views/VAbout.cpp \
    Views/Session/VQuickSend.cpp \
    Views/Session/VReceive.cpp \
    Views/Session/VSend.cpp \
    Views/VBaseSplitter.cpp \
    Views/VBaseSplitterForm.cpp \
    Views/VDialogSkin.cpp \
    Views/VSession.cpp \
    Views/VSettings.cpp \
    Views/VWindowSplitter.cpp \
    Views/VToast.cpp \
    Network/CConnectManager.cpp \
    Tools/CHelper.cpp \
    Views/Session/VConnection.cpp \
    Tools/qcustomplot.cpp \
    Views/VGraphsEditor.cpp \
    Views/VDialogProtocal.cpp \
    Views/VDialogAscii.cpp

HEADERS  += \
    CMainWindow.h \
    Ctrller/CByte2Text.h \
    Ctrller/CSettings.h \
    Ctrller/CText2Byte.h \
    Network/AbsConnection.h \
    Network/CSerialPort.h \
    Network/CTcpClient.h \
    Network/CTcpServer.h \
    Network/CUdp.h \
    Network/IConnectInterface.h \
    Test/CQssTest.h \
    Tools/CConversion.h \
    Tools/CIconFont.h \
    Tools/CUIHelper.h \
    Views/Session/VCharts.h \
    Views/Session/VReceiveTrig.h \
    Views/Session/VSessionInterface.h \
    Views/VAbout.h \
    Views/Session/VQuickSend.h \
    Views/Session/VReceive.h \
    Views/Session/VSend.h \
    Views/VBaseSplitter.h \
    Views/VBaseSplitterForm.h \
    Views/VDialogSkin.h \
    Views/VSession.h \
    Views/VSettings.h \
    Views/VWindowSplitter.h \
    Views/VToast.h \
    Network/CConnectManager.h \
    Tools/CHelper.h \
    Views/Session/VConnection.h \
    Tools/qcustomplot.h \
    Views/VGraphsEditor.h \
    Views/VDialogProtocal.h \
    Views/VDialogAscii.h


FORMS += \
    CMainWindow.ui \
    Test/CQssTest.ui \
    Views/Session/VCharts.ui \
    Views/Session/VReceiveTrig.ui \
    Views/VAbout.ui \
    Views/Session/VQuickSend.ui \
    Views/Session/VReceive.ui \
    Views/Session/VSend.ui \
    Views/VDialogSkin.ui \
    Views/VSession.ui \
    Views/VSettings.ui \
    Views/Session/VConnection.ui \
    Views/VGraphsEditor.ui \
    Views/VDialogProtocal.ui \
    Views/VDialogAscii.ui


INCLUDEPATH += \
    $$PWD/Ctrller\
    $$PWD/Network\
    $$PWD/Tools\
    $$PWD/Views\
    $$PWD/Views/Session \
    $$PWD/Test

RESOURCES += \
    resource.qrc

DISTFILES += \
    style.qss

TRANSLATIONS += \
    $$PWD/Trans/zh_CN.ts \
    $$PWD/Trans/english.ts
