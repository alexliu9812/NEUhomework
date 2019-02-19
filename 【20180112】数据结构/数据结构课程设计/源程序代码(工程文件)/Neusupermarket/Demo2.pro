#-------------------------------------------------
#
# Project created by QtCreator 2017-12-15T09:18:53
#
#-------------------------------------------------

QT       += core gui
QT += network

CONFIG += c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    quiwidget.cpp \
    supermarket.cpp

HEADERS  += \
    quiwidget.h \
    head.h \
    supermarket.h

FORMS    += \
    supermarket.ui

RESOURCES += \
    main.qrc \
    qss.qrc \
    demo.qrc \
    image.qrc

DISTFILES += \
    Demo2.pro.user \
    main.ico \
    image/Font Awesome Cheatsheet.png
 QT += network
RC_FILE=icon.rc
