#-------------------------------------------------
#
# Project created by QtCreator 2011-12-12T09:57:02
#
#-------------------------------------------------

QT       += sql

TARGET = qparams
TEMPLATE = lib
CONFIG += staticlib

SOURCES += qparams.cpp \
    sqlitedsmanager.cpp \
    param.cpp \
    dsmanager.cpp \
    unit.cpp \
    value.cpp \
    transformation.cpp \
    category.cpp \
    domain.cpp \
    app.cpp \
    muParser/muParserTokenReader.cpp \
    muParser/muParserTest.cpp \
    muParser/muParserInt.cpp \
    muParser/muParserError.cpp \
    muParser/muParserDLL.cpp \
    muParser/muParserCallback.cpp \
    muParser/muParserBytecode.cpp \
    muParser/muParserBase.cpp \
    muParser/muParser.cpp \
    ParamsTableModel.cpp \
    ParamsTableItemDelegate.cpp \
    ParamsDialog.cpp

HEADERS += qparams.h \
    sqlitedsmanager.h \
    param.h \
    dsmanager.h \
    unit.h \
    value.h \
    transformation.h \
    category.h \
    domain.h \
    app.h \
    ParamsTableModel.h \
    ParamsTableItemDelegate.h \
    ParamsDialog.h
unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

OTHER_FILES += \
    qparamsst.pro.user

INCLUDEPATH += . muParser/include

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

FORMS += \
    ParamsDialog.ui




















