#-------------------------------------------------
#
# Project created by QtCreator 2012-01-13T08:46:55
#
#-------------------------------------------------

# ensure one "debug_and_release" in CONFIG, for clarity...
debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}

# ensure one "debug" or "release" in CONFIG so they can be used as
# conditionals instead of writing "CONFIG(debug, debug|release)"...
CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
    }
CONFIG(release, debug|release) {
        CONFIG -= debug release
        CONFIG += release
}

QT       += core gui opengl xml xmlpatterns sql network script

TARGET = GRAPHOS
TEMPLATE = app

win32-*{
    !contains(QMAKE_TARGET.arch, x86_64) {   # !!!!!!!!!!Preperar versiones de 32 CC, boost, liblas,..!!!!!!!!!!!!!!!
            INCLUDEPATH += . ./photo/ ../../libs/libCC \               
                ../../libs/libQparams/muParser/include \
                ../../libs/libQparams \
                ../../libs/libPW \
    } else {

            INCLUDEPATH += . ./photo/ ../../libs/libCC \
                ../../libs/libCC/cc64/qCC/db_tree \
                ../../libs/libCC/cc64/CC/include \
                ../../libs/libCC/cc64/ccViewer \
                ../../libs/libCC/cc64/build/ccViewer \
                ../../libs/libCC/cc64/qCC \
                ../../libs/libCC/cc64/build/qCC \
                ../../libs/libCC/cc64/qCC/ui_templates \
                ../../libs/libCC/cc64/qCC/libs/CCFbo \
                ../../libs/libCC/cc64/libs/qCC_db \
                ../../libs/libCC/cc64/libs/qCC_db/msvc \
                ../../libs/libCC/cc64/libs/CCFbo/include \
                ../../libs/libQparams/muParser/include \
                ../../libs/libQparams \
                ../../libs/libPW \
                ../../libs/libLAS/libLAS-1.8.0_x64\include \
                ../../libs/boost_1_58_0_msvc10_64 \
                ../../libs/openCV3_1_vs10_x64_2/include \
                ../../libs/QuaZip_vs10_x64/include \
                ../../libs/zlib_vs10_x64/include\
      }
}

SOURCES += main.cpp\
    photo/image.cpp \
    photo/thumbnail.cpp \
    photo/tabshortcuts.cpp \
    photo/tabgeneral.cpp \
    photo/settings.cpp \
    photo/menu.cpp \
    mainwindow.cpp \
    photo/photoviewer.cpp \
    ProgressDialog.cpp \
    photo/pixmapitem.cpp \
    ImageTreeItem.cpp \
    OpenProjectDialog.cpp \
    NewCameraDialog.cpp \
    photo/CrossGraphicItem.cpp \
    photo/crosshairgraphicsitem.cpp \
    SettingsDialog.cpp \
    ExifDataDialog.cpp \
    CameraDefinitionDialog.cpp \
    MatchingViewer/MatchingViewer.cpp \
    MatchingViewer/MatchigGraphicsView.cpp \
    NewProjectDialog.cpp \
    ImagesWizard.cpp \
    aboutgraphos.cpp \
    DependencyInfoWidget.cpp \
    MainWindowGRAPHOS.cpp \
    OrientationWizard.cpp \
    ClickableImage.cpp \
    DensificationWizard.cpp \
    TiePointsWizard.cpp \
    WallisResultViewer.cpp \
    AboutSureDialog.cpp \
    clickeableLabel.cpp \
    SubgraphSelector.cpp \
    BatchProcessWizard.cpp \
    GCPWidget.cpp \
    NewGCPDialog.cpp \
    ScaleModelDialog.cpp \
    FrameRateDialog.cpp \
    AboutInputFilesDialog.cpp \
    ProcessManager/ExternalProcess.cpp \
    ProcessManager/MultiProcess.cpp \
    ProcessManager/Process.cpp \
    ProcessManager/ProcessConcurrent.cpp \
    QDebugStream.cpp \
    ExternalProcess/FME_Process.cpp \
    ExternalProcess/WallisStimator.cpp \
    ExternalProcess/CCDDistribution_Process.cpp \
    ExternalProcess/SingleMatchingAnalysis_Process.cpp \
    ExternalProcess/STAR_Process.cpp \
    ExternalProcess/CLAW_Process.cpp \
    ExternalProcess/CalibrationConversion_Process.cpp \
    AboutWallis_dialog.cpp \
    aboutFeatures_Dialog.cpp \
    AboutDensification_Dialog.cpp \
    AboutCalibrations_Dialog.cpp

HEADERS  += \
    photo/image.h \
    photo/thumbnail.h \
    photo/thbthread.h \
    photo/tabshortcuts.h \
    photo/tabgeneral.h \
    photo/settings.h \
    photo/menu.h \
    mainwindow.h \
    photo/photoviewer.h \
    ProgressDialog.h \
    photo/pixmapitem.h \
    ImageTreeItem.h \
    OpenProjectDialog.h \
    NewCameraDialog.h \
    photo/CrossGraphicItem.h \
    photo/crosshairgraphicsitem.h \
    SettingsDialog.h \
    ExifDataDialog.h \
    CameraDefinitionDialog.h \
    QDebugStream.h \
    MatchingViewer/MatchingViewer.h \
    MatchingViewer/MatchigGraphicsView.h \
    NewProjectDialog.h \
    ImagesWizard.h \
    aboutgraphos.h \
    DependencyInfoWidget.h \
    MainWindowGRAPHOS.h \
    OrientationWizard.h \
    ClickableImage.h \
    DensificationWizard.h \
    TiePointsWizard.h \
    WallisResultViewer.h \
    AboutSureDialog.h \
    clickeableLabel.h \
    SubgraphSelector.h \
    BatchProcessWizard.h \
    GCPWidget.h \
    NewGCPDialog.h \
    ScaleModelDialog.h \
    FrameRateDialog.h \
    AboutInputFilesDialog.h \
    ProcessManager/ExternalProcess.h \
    ProcessManager/MultiProcess.h \
    ProcessManager/Process.h \
    ProcessManager/ProcessConcurrent.h \
    ui_CameraDefinitionDialog.h \
    ui_ExifDataDialogdialog.h \
    ui_ImagesWizard.h \
    ui_mainwindow.h \
    ui_NewCameraDialog.h \
    ui_openprojectdialog.h \
    ui_ProgressDialog.h \
    ui_SettingsDialog.h \
    ExternalProcess/FME_Process.h \
    ExternalProcess/WallisStimator.h \
    ExternalProcess/CCDDistribution_Process.h \
    ExternalProcess/SingleMatchingAnalysis_Process.h \
    ExternalProcess/STAR_Process.h \
    ExternalProcess/CLAW_Process.h \
    ExternalProcess/CalibrationConversion_Process.h \
    AboutWallis_dialog.h \
    aboutFeatures_Dialog.h \
    AboutDensification_Dialog.h \
    AboutCalibrations_Dialog.h

FORMS    += \
    mainwindow.ui \
    ProgressDialog.ui \
    openprojectdialog.ui \
    NewCameraDialog.ui \
    SettingsDialog.ui \
    ExifDataDialogdialog.ui \
    CameraDefinitionDialog.ui \
    ImagesWizard.ui \
    AboutWallis_dialog.ui \
    aboutFeatures_Dialog.ui \
    AboutDensification_Dialog.ui \
    AboutCalibrations_Dialog.ui


TRANSLATIONS = GRAHPOS_es.ts \
               GRAPHOS_fr.ts

RESOURCES += \
    GRAPHOS.qrc \
    photo/res.qrc \
    ../../libs/libCC/cc/qCC/icones.qrc

debug{
        win32-*{           

            !contains(QMAKE_TARGET.arch, x86_64) {
                DESTDIR = build/debug
            } else {
                LIBS += -L$$PWD/../../libs/vlfeat-0.9.20/bin/win64
                LIBS += -L$$PWD/../../libs/QuaZip_vs10_x64/lib
                LIBS += -L$$PWD/../../libs/zlib_vs10_x64/lib
                LIBS += -L$$PWD/../../libs/zlib_vs10_x64/bin
                LIBS += -L$$PWD/../../libs/openCV3_1_vs10_x64_2/x64/vc10/bin
                LIBS += -L$$PWD/../../libs/openCV3_1_vs10_x64_2/x64/vc10/lib
                LIBS += -L$$PWD/../../libs/boost_1_58_0_msvc10_64/lib64-msvc-10.0
                LIBS += -L$$PWD/../../libs/libCC/build64/debug \
                    -L$$PWD/../../libs/libPW/build64/debug \
                    -L$$PWD/../../libs/libQparams/build64/debug \
                    -L$$PWD/../../libs/libCC/cc64/build/qCC/libs/CCFbo/Debug \
                    -L$$PWD/../../libs/libCC/cc64/build/CC/Debug \
                    -L$$PWD/../../libs/libCC/cc64/build/qCC/db/Debug \
                    -L$$PWD/../../libs/libCC/cc64/build/libs/qCC_db/Debug \
                    -L$$PWD/../../libs/libCC/cc64/build/CC/triangle/Debug \
                    -L$$PWD/../../libs/libCC/cc64/build/libs/Glew/Debug \
                    -L$$PWD/../../libs/libCC/cc64/build/libs/CCFbo/Debug \
                    -L$$PWD/../../libs/libLAS/libLAS-1.8.0_x64/bin/Debug

                LIBS += -lpw -lcc -lQCC_DB_DLLd -lCC_DLLd -ltriangled -lGLEWd -lCC_FBOd -lqparams -lliblas
                LIBS += -lopencv_photo310d -lopencv_core310d -lopencv_highgui310d -lopencv_imgproc310d -lopencv_imgcodecs310d -lopencv_video310d -lopencv_videostab310d -lopencv_videoio310d -lopencv_calib3d310d -lopencv_features2d310d  -lopencv_flann310d -lopencv_objdetect310d
                LIBS += -lquazip -lzlibd -lvl
                DESTDIR = build64/debug
            }
        }
}else{    
    win32-*{        
        !contains(QMAKE_TARGET.arch, x86_64) {
            DESTDIR = build/release
        } else {

            LIBS += -L$$PWD/../../libs/vlfeat-0.9.20/bin/win64
            LIBS += -L$$PWD/../../libs/QuaZip_vs10_x64/lib
            LIBS += -L$$PWD/../../libs/zlib_vs10_x64/lib
            LIBS += -L$$PWD/../../libs/zlib_vs10_x64/bin
            LIBS += -L$$PWD/../../libs/openCV3_1_vs10_x64_2/x64/vc10/bin
            LIBS += -L$$PWD/../../libs/openCV3_1_vs10_x64_2/x64/vc10/lib
            LIBS += -L$$PWD/../../libs/boost_1_58_0_msvc10_64/lib64-msvc-10.0
            LIBS += -L$$PWD/../../libs/libCC/cc64/build/qCC/libs/CCFbo/Release \
                    -L$$PWD/../../libs/libCC/cc64/build/CC/Release \
                    -L$$PWD/../../libs/libCC/cc64/build/qCC/db/Release \
                    -L$$PWD/../../libs/libCC/cc64/build/libs/qCC_db/Release \
                    -L$$PWD/../../libs/libCC/cc64/build/CC/triangle/Release \
                    -L$$PWD/../../libs/libCC/cc64/build/libs/Glew/Release \
                    -L$$PWD/../../libs/libCC/cc64/build/libs/CCFbo/Release \
                    -L$$PWD/../../libs/libLAS/libLAS-1.8.0_x64/bin/Release \
                    -L$$PWD/../../libs/libCC/build64/release \
                    -L$$PWD/../../libs/libPW/build64/release \
                    -L$$PWD/../../libs/libQparams/build64/release \

            LIBS += -lpw -lcc -lQCC_DB_DLL -lCC_DLL -ltriangle -lGLEW -lCC_FBO -lqparams -lliblas
            LIBS += -lopencv_photo310 -lopencv_core310 -lopencv_highgui310 -lopencv_imgproc310 -lopencv_imgcodecs310 -lopencv_video310 -lopencv_videostab310 -lopencv_videoio310 -lopencv_calib3d310 -lopencv_features2d310  -lopencv_flann310 -lopencv_objdetect310
            LIBS += -lquazip -lzlib  -lvl
            DESTDIR = build64/release
        }
    }
}
