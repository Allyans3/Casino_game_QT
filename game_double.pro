#-------------------------------------------------
#
# Project created by QtCreator 2018-06-15T18:24:05
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = game_double
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    game.cpp \
    qcustomplot.cpp \
    wining.cpp

HEADERS  += mainwindow.h \
    game.h \
    qcustomplot.h \
    wining.h

FORMS    += mainwindow.ui \
    game.ui \
    wining.ui

RESOURCES += \
    photos.qrc
