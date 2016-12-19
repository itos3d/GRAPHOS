#-------------------------------------------------
#
# Project created by QtCreator 2011-11-21T12:26:53
#
#-------------------------------------------------

QT       += core gui sql

TARGET = photo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    thumbnail.cpp\
    settings.cpp \
    tabshortcuts.cpp \
    tabgeneral.cpp \
    image.cpp \
    menu.cpp

HEADERS  += mainwindow.h \
    thbthread.h \
    thumbnail.h \
    settings.h \
    tabshortcuts.h \
    tabgeneral.h \
    image.h \
    menu.h

FORMS    +=

RESOURCES += \
    res.qrc

TRANSLATIONS += photo_de.ts\
		photo_el.ts\
		photo_cz.ts

target.path=/usr/bin
INSTALLS += target











