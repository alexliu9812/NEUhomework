#-------------------------------------------------
#
# Project created by QtCreator 2013-09-15T09:57:13
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Geist
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    highlighter.cpp \
    files.cpp \
    search.cpp \
    widgets/geisttextedit.cpp \
    utils/conversion.cpp \
    utils/templates.cpp

HEADERS  += mainwindow.h \
    highlighter.h \
    search.h \
    files.h \
    search.h \
    widgets/geisttextedit.h \
    utils/conversion.h \
    utils/templates.h

FORMS    += mainwindow.ui

OTHER_FILES +=
