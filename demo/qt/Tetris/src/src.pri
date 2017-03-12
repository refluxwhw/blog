INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

SOURCES += \
    $$PWD/main.cpp\
    $$PWD/mainwindow.cpp \
    $$PWD/Tetris.cpp \

HEADERS  += \
    $$PWD/mainwindow.h \
    $$PWD/Tetris.h \

FORMS    += \
    $$PWD/mainwindow.ui


include(shapes/shapes.pri)
