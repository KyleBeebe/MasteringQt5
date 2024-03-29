#-------------------------------------------------
#
# Project created by QtCreator 2019-08-07T21:06:45
#
#-------------------------------------------------

QT       += core gui charts
CONFIG   += C++14

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ch02-sysinfo
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
        CpuWidget.cpp \
        MemoryWidget.cpp \
        SysInfo.cpp \
        SysInfoWidget.cpp \
        main.cpp \
        MainWindow.cpp

HEADERS += \
    CpuWidget.h \
    MainWindow.h \
    MemoryWidget.h \
    SysInfo.h \
    SysInfoWidget.h

COMPILE_MSG = "Compiling on"

windows {
    SOURCES += SysInfoWindows.cpp
    HEADERS += SysInfoWindows.h
    message($$COMPILE_MSG windows)
}

linux {
    SOURCES += SysInfoLinux.cpp
    HEADERS += SysInfoLinux.h
    message($$COMPILE_MSG linux)
}

FORMS += \
        MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
