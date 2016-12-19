#-------------------------------------------------
#
# Project created by QtCreator 2014-05-01T09:34:01
#
#-------------------------------------------------

QT       -= gui

TARGET = orsaAsift
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += .
INCLUDEPATH += ./libMatch
INCLUDEPATH += ./io_png
INCLUDEPATH += ./libNumerics
INCLUDEPATH += ./third_party

#DEFINES += LIBORSAASIFT_LIBRARY

SOURCES += LibOrsaAsift.cpp \
    orsa.cpp \
    libNumerics/vector.cpp \
    libNumerics/rodrigues.cpp \
    libNumerics/numerics.cpp \
    libNumerics/matrix.cpp \
    libNumerics/homography.cpp \
    libNumerics/computeH.cpp

HEADERS += LibOrsaAsift.h\
    orsa.h \
    libNumerics/rodrigues.h \
    libNumerics/numerics.h \
    libNumerics/matrix.h \
    libNumerics/homography.h

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

CONFIG(debug, debug|release) {
    win32-*{
        !contains(QMAKE_TARGET.arch, x86_64) {
            DESTDIR = build/debug
        }else{
            DESTDIR = build64/debug
        }
    }
} else {
    win32-*{
        !contains(QMAKE_TARGET.arch, x86_64) {
            DESTDIR = build/release
        }else{
            DESTDIR = build64/release
        }
    }
}
