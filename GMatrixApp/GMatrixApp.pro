#-------------------------------------------------
#
# Project created by QtCreator 2018-12-11T14:46:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GMatrixApp
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
        main.cpp \
        gmatrixapp.cpp \
        sitvgloader.cpp \
        sitvgdata.cpp \
        sitvgviewer.cpp \
        transformationlist.cpp \
        sitvgwindow.cpp \
    bitmapwindow.cpp \
    bitmapviewer.cpp \
    transformation.cpp

HEADERS += \
        gmatrixapp.h \
        sitvgloader.h \
        sitvgdata.h \
        rgbcolor.h \
        sitvgviewer.h \
        transformationlist.h \
        transformation.h \
        sitvgwindow.h \
    bitmapwindow.h \
    bitmapviewer.h

FORMS += \
        gmatrixapp.ui \
        sitvgviewer.ui \
    sitvgwindow.ui \
    bitmapwindow.ui \
    bitmapviewer.ui
