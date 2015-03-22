#-------------------------------------------------
#
# Project created by QtCreator 2014-11-30T23:30:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PCA_interface
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    config.cpp \
    eigen.cpp \
    test.cpp \
    matrix.cpp

HEADERS  += mainwindow.h \
    config.h \
    eigen.h \
    matrix.h \
    test.h

FORMS    += mainwindow.ui
