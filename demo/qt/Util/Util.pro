#-------------------------------------------------
#
# Project created by QtCreator 2017-02-05T14:37:41
#
#-------------------------------------------------

QT       -= core gui

TARGET = Util
TEMPLATE = lib
CONFIG += staticlib

SOURCES += \
    XLock.cpp \
    BaseTopic.cpp \
    Path.cpp

HEADERS += Util.h \
    XLock.h \
    AutoLock.h \
    MixUtil.h \
    BaseTopic.h \
    IObserver.h \
    Path.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

