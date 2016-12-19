#-------------------------------------------------
#
# Project created by QtCreator 2012-01-31T09:26:40
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = cc
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11

DEFINES += USE_GLEW

    win32-*{
        !contains(QMAKE_TARGET.arch, x86_64) {
            INCLUDEPATH += . CC64/qCC/db_tree \
                CC/CC/include \
                CC/ccViewer \
                CC/qCC \
                CC/build/qCC \
                CC/build/ccViewer \
                CC/qCC/ui_templates \
                CC/qCC/libs/CCFbo \
                CC/libs/qCC_db \
                CC/libs/qCC_db/msvc \
                CC/libs/CCFbo/include \
                CC/libs/Glew/include \
                ../liblas/libLAS-1.8.0_x64/include \    # !!!!!!!!!!!!!!!!!!!!!!!!!!
                ../boost_1_58_0_msvc10_64               # !!!!!!!!!!!!!!!!!!!!!!!!!!
        }else{
            INCLUDEPATH += . CC64/qCC/db_tree \
                CC64/CC/include \
                CC64/ccViewer \
                CC64/qCC \
                CC64/build/qCC \
                CC64/build/ccViewer \
                CC64/qCC/ui_templates \
                CC64/qCC/libs/CCFbo \
                CC64/libs/qCC_db \
                CC64/libs/qCC_db/msvc \
                CC64/libs/CCFbo/include \
                CC64/libs/Glew/include \
                ../liblas/libLAS-1.8.0_x64/include \
                ../boost_1_58_0_msvc10_64
        }
    }

SOURCES += \
    CC64/ccViewer/main.cpp \
    CC64/ccViewer/ccviewer.cpp \
    CC64/qCC/ccCameraParamEditDlg.cpp \
    CC64/qCC/ccRenderingTools.cpp \
    CC64/qCC/ccGuiParameters.cpp \
    CC64/qCC/ccGLWindow.cpp \
    CC64/qCC/ccConsole.cpp \
    CC64/qCC/fileIO/SoiFilter.cpp \
    CC64/qCC/fileIO/rply.c \
    CC64/qCC/fileIO/PVFilter.cpp \
    CC64/qCC/fileIO/PovFilter.cpp \
    CC64/qCC/fileIO/PNFilter.cpp \
    CC64/qCC/fileIO/PlyOpenDlg.cpp \
    CC64/qCC/fileIO/PlyFilter.cpp \
    CC64/qCC/fileIO/ObjFilter.cpp \
    CC64/qCC/fileIO/MAFilter.cpp \
    CC64/qCC/fileIO/LASFilter.cpp \
    CC64/qCC/fileIO/IcmFilter.cpp \
    CC64/qCC/fileIO/FileIOFilter.cpp \
    CC64/qCC/fileIO/DepthMapFileFilter.cpp \
    CC64/qCC/fileIO/BinFilter.cpp \
    CC64/qCC/fileIO/AsciiOpenDlg.cpp \
    CC64/qCC/fileIO/AsciiFilter.cpp \
    ccviewerwrapper.cpp \
    CC64/qCC/fileIO/VTKFilter.cpp \
    CC64/qCC/fileIO/BundlerFilter.cpp \
    CC64/qCC/fileIO/X3DXIOTNodeHandler.cpp \
    CC64/qCC/fileIO/X3DFilter.cpp \
    CC64/qCC/fileIO/BundlerImportDlg.cpp \
    CC64/qCC/ccOverlayDialog.cpp \
    CC64/qCC/ccCoordinatesShiftManager.cpp \
    CC64/qCC/fileIO/AsciiSaveDlg.cpp \
    CC64/qCC/ccShiftAndScaleCloudDlg.cpp \
    CC64/qCC/fileIO/STLFilter.cpp \
    CC64/qCC/ccDisplayOptionsDlg.cpp \
    CC64/qCC/ccPointPropertiesDlg.cpp \
    CC64/qCC/fileIO/LASOpenDlg.cpp

HEADERS  += \
    cc64/ccViewer/ccviewer.h \
    cc64/qCC/ccRenderingTools.h \
    cc64/qCC/ccGuiParameters.h \
    cc64/qCC/ccGLWindow.h \
    cc64/qCC/ccDisplayOptionsDlg.h \
    cc64/qCC/ccConsole.h \
    cc64/qCC/ccCameraParamEditDlg.h \
    cc64/qCC/fileIO/SoiFilter.h \
    cc64/qCC/fileIO/rply.h \
    cc64/qCC/fileIO/PVFilter.h \
    cc64/qCC/fileIO/PovFilter.h \
    cc64/qCC/fileIO/PNFilter.h \
    cc64/qCC/fileIO/PlyOpenDlg.h \
    cc64/qCC/fileIO/PlyFilter.h \
    cc64/qCC/fileIO/ObjFilter.h \
    cc64/qCC/fileIO/MAFilter.h \
    cc64/qCC/fileIO/LASFilter.h \
    cc64/qCC/fileIO/IcmFilter.h \
    cc64/qCC/fileIO/FileIOFilter.h \
    cc64/qCC/fileIO/DepthMapFileFilter.h \
    cc64/qCC/fileIO/BinFilter.h \
    cc64/qCC/fileIO/AsciiOpenDlg.h \
    cc64/qCC/fileIO/AsciiFilter.h \
    ccviewerwrapper.h \
    cc64/qCC/fileIO/VTKFilter.h \
    cc64/qCC/fileIO/BundlerFilter.h \
    cc64/qCC/fileIO/X3DXIOTNodeHandler.h \
    cc64/qCC/fileIO/X3DFilter.h \
    cc64/qCC/fileIO/BundlerImportDlg.h \
    cc64/qCC/ccOverlayDialog.h \
    cc64/qCC/ccCoordinatesShiftManager.h \
    cc64/qCC/fileIO/AsciiSaveDlg.h \
    cc64/qCC/ccShiftAndScaleCloudDlg.h \
    cc64/qCC/fileIO/STLFilter.h \
    cc64/qCC/ccPointPropertiesDlg.h \
    cc64/qCC/fileIO/LASOpenDlg.h


CONFIG(debug, debug|release) {
    win32-*{
        !contains(QMAKE_TARGET.arch, x86_64) {
            DESTDIR = build/release

            RESOURCES += cc/qCC/icones.qrc
        } else {

            LIBS += -L$$PWD/cc64/build/CC/Release \
                    -L$$PWD/cc64/build/qCC/libs/CCFbo/Release \
                    -L$$PWD/cc64/build/qCC/db/Release \
                    -L$$PWD/cc64/build/libs/qCC_db/Release \
                    -L$$PWD/cc64/build/CC/triangle/Release \
                    -L$$PWD/../libLAS/libLAS-1.8.0_x64/bin/Release

            LIBS += -lqCC_db -lCC_Dll -ltriangle -lqhull -lCC_FBO -lGLEW -lGLU -lGL -llas -lboost

            DESTDIR = build64/debug
        }
    }

} else {
    win32-*{
        !contains(QMAKE_TARGET.arch, x86_64) {
            DESTDIR = build/release

            RESOURCES += cc/qCC/icones.qrc
        } else {
            LIBS += -L$$PWD/cc64/build/CC/Release \
                    -L$$PWD/cc64/build/qCC/libs/CCFbo/Release \
                    -L$$PWD/cc64/build/qCC/db/Release \
                    -L$$PWD/cc64/build/libs/qCC_db/Release \
                    -L$$PWD/cc64/build/CC/triangle/Release \
                    -L$$PWD/../libLAS/libLAS-1.8.0/bin/Release

            LIBS += -lqCC_db -lCC_Dll -ltriangle -lqhull -lCC_FBO -lGLEW -lGLU -lGL -llas -lboost

            DESTDIR = build64/release

            RESOURCES += cc64/qCC/icones.qrc
        }
    }
}

