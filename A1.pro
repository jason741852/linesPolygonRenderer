#-------------------------------------------------
#
# Project created by QtCreator 2016-09-25T23:25:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    client.cpp \
    renderarea361.cpp \
    window361.cpp

HEADERS  += mainwindow.h \
    client.h \
    drawable.h \
    pageturner.h \
    renderarea361.h \
    window361.h

FORMS    += mainwindow.ui

SUBDIRS += \
    qtqt.pro
