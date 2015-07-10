#-------------------------------------------------
#
# Project created by QtCreator 2015-07-09T10:58:42
#
#-------------------------------------------------

QT       += core gui sql webkitwidgets

QT += xlsx # https://github.com/dbzhang800/QtXlsxWriter

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += link_pkgconfig
PKGCONFIG += json-c # https://linuxprograms.wordpress.com/2010/05/20/json-c-libjson-tutorial/

TARGET = qt-web-app
TEMPLATE = app

#QMAKE_CXXFLAGS += -std=c++0x -pthread
QMAKE_CFLAGS += -DMONGOOSE_ENABLE_THREADS
#LIBS += -pthread


SOURCES += main.cpp mainwindow.cpp mongoose.c \
    web_server.cpp \
    database.cpp

HEADERS  += mainwindow.h mongoose.h \
    web_server.h \
    database.h

FORMS    += mainwindow.ui

OTHER_FILES += README.md

RESOURCES += \
    static_resources.qrc
