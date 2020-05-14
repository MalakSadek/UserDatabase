#-------------------------------------------------
#
# Project created by QtCreator 2015-10-31T19:18:40
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GroupProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    loginform.cpp

HEADERS  += mainwindow.h \
    loginform.h \
    hashtable.h \
    binarysearchtree.h

FORMS    += mainwindow.ui \
    loginform.ui

DISTFILES += \
    Logins
