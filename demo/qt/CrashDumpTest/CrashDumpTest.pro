#-------------------------------------------------
#
# Project created by QtCreator 2016-12-20T23:14:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CrashDumpTest
TEMPLATE = app

include (../public.pri)
include (src/src.pri)

LIBS += -ldbghelp
