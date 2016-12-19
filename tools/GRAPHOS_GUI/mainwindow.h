/**
*-------------------------------------------------
*  Copyright 2016 by Tidop Research Group <daguilera@usal.se>
*
* This file is part of GRAPHOS - inteGRAted PHOtogrammetric Suite.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is free software: you can redistribute
* it and/or modify it under the terms of the GNU General Public
* License as published by the Free Software Foundation, either
* version 3 of the License, or (at your option) any later version.
*
* GRAPHOS - inteGRAted PHOtogrammetric Suite is distributed in the hope that it will
* be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
* of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
*
* @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>
*-------------------------------------------------
*/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#define MAINWINDOW_RESOURCES_DATABASE_FILE              ":/PW/projectsDB"
#define MAINWINDOW_RESOURCES_SPATIALDATABASE_FILE       ":/PW/projectsSpatialDB"
#define MAINWINDOW_RESOURCES_PARAMETERS_DATABASE_FILE   ":/PW/qparamsDB"
#define MAINWINDOW_DATABASE_FILE                        "pw_data.sqlite"
#define MAINWINDOW_SPATIALDATABASE_FILE                 "pw_dataSpatial.sqlite"
#define MAINWINDOW_PARAMETERS_FILE                      "qparams.sqlite"

#include <QMainWindow>
#include <QtConcurrentRun>
#include <QFutureWatcher>
#include <QTimer>
#include <QProcess>
#include <QFileDialog>
#include <QSignalMapper>
#include <QMenu>
#include <QScrollBar>
#include <QMapIterator>
#include <QPropertyAnimation>
#include <QDockWidget>
#include <QTreeWidgetItem>
#include <QTextEdit>

#include "thumbnail.h"
#include "settings.h"
#include "menu.h"
#include "photoviewer.h"
#include "MatchingViewer/MatchingViewer.h"
#include "ccviewerwrapper.h"
#include "Project.h"
#include "ProgressDialog.h"
#include "OpenProjectDialog.h"
#include "Process.h"
#include "MultiProcess.h"
#include "ExternalProcess.h"
#include "PersistenceManager.h"
#include "NewCameraDialog.h"
#include "SettingsDialog.h"
#include "ExifDataDialog.h"
#include "CameraDefinitionDialog.h"
#include "qparams.h"

#include "ImagePreprocessing/ProcessConcurrentTest1.h"

#include "ccCommon.h"
#include "ccGLWindow.h"
#include <ccPointCloud.h>
#include <cc2DLabel.h>
#include <cc2DViewportLabel.h>
#include <QDomDocument>
#include <QTreeWidgetItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QDockWidget *getDockThumbs();
    QFrame *getViewFrame();
    static bool removeDir(QString dirPath);
    static bool removeDir(QString dirName, QStringList exceptions);
    static bool copyDir(QString sourceFolder, QString destFolder, bool move = true);

signals:
    void projectChanged();

protected:

//    QString mOrientationImagesPath; //Variable para almacenara el url de las imágenes con las que orientar
    QDockWidget *mDockProject;
    QTreeWidget *mProjectTreeWidget;
    QDockWidget *mDockThumbs;
    QDockWidget *mDockConsole;

//    AboutDialog *mAboutDialog;
    QSettings *mSettings;
    PW::PersistenceManager *mPersistenceManager;
    Ui::MainWindow *ui;
    bool mSpatialDatabase;
    PW::Project *mProject;
    ProgressDialog *mProgressDialog;
    QTextEdit *mConsole;
    QFrame *mPhotoViewerFrame;
    QFrame *mMatchingsViewerFrame;
    PhotoViewer *mPhotoViewer;
    MatchingViewer *mMatchingsViewer;
    ccViewerWrapper *mCCVW;
    ccViewerWrapper *mCCVW2;
    QString mImagesPath;
    QString mAppTitle;
    QMap<QString, QVector<QString> > mImagesIdsPairs;

    virtual void updateTools()=0;
    void closeEvent(QCloseEvent *event);
    void initSetups();
    int validateImages(QStringList fileNames);

    CameraDefinitionDialog *mCameraDefinitionDialog;
    int replace(QFile *inputFile, QFile *outputFile, QString from, QString to);
    void updatePhotoViewerGraphics();
    void addItem(QTreeWidgetItem *item, QDomNode node);

    OpenProjectDialog *mOpenProjectDialog;
    NewCameraDialog * mNewCameraDialog;
    SettingsDialog *mSettingsDialog;
    ExifDataDialog *mExifDataDialog;

    PW::ExternalProcess *mTapiocaProcess;
    PW::MultiProcess *mComputeOrientationProcess;
    PW::MultiProcess *mSparseProcess;
    PW::Process *mDenseProcess;
    PW::MultiProcess *mDenseGCProcess;
    PW::ExternalProcess *mAperoProcess;
    PW::MultiProcess *mOrientationsGCProcess;
    PW::MultiProcess *mOrthoProcess;
    PW::Process *mPMVSProcess;
    PW::ExternalProcess *mApero2PMVSProcess;
    PW::MultiProcess *mPMVSMultiProcess;


    QString mSparseModelPath;
    QString mDenseModelPath;

    bool mSparseStopped;
    bool mPicking;
    void cleanEnviroment();
    int checkToSave();
    bool isTiePointsTxt(QString basePath);


    bool mToSave; //Open projects explorer to save a project?

    QString mTiePointsMetadata;
    QString mTiePointsPath;
    QString mTiePointsDescription;


    bool mRequiredCameraDefinition;

    bool isRequiredCameraDefinition();
    void setRequiredCameraDefinition(bool required);

protected slots:
    CameraDefinitionDialog * getCameraDefinitionDialog();
    void onProjectSelected(QString projectName);
    void on_actionSettings_2_triggered();

    void on_actionMask_triggered();
    void on_actionPicking_triggered();
    void on_actionSave_triggered();
    void on_actionExit_triggered();
    void on_actionExport_Sparse_Model_triggered();
    void on_actionExport_Dense_Model_triggered();
    void on_actionAbout_PW_triggered();
    void on_actionUndistort_images_triggered();
    void onError(int code, QString cause);
    void onSaveMask(QPolygonF polygon);
    void onTreeItemChanged(QTreeWidgetItem* current,QTreeWidgetItem* previous);
    void onTreeItemDoubleClicked(QTreeWidgetItem*item, int column);
    void onImgDrawn();
    void onTabWidgetCahnge(int index);
    void onThumbsLoadFinished();

    void createMaskImg(int width, int height, QPolygonF polygon);
    void delteMaskImg();
    virtual void loadProject();
    void loadProjectMetadataOnProjectTree();
    void loadProjectImages();
    void loadModelsOnTree();
    QStringList updateImagesTree();

    QTreeWidgetItem * getImageTreeItem(PW::PWImage *image);
    QTreeWidgetItem * getModelsTreeItem(PW::Project *mProject);
    NewCameraDialog *getNewcameraDialog();
    ExifDataDialog *getExifDataDialog();
    SettingsDialog *getSettingsDialog();
    void manageProccesStdOutput(QString data);
    void manageProccesErrorOutput(QString data);
    void on_actionDistance_Tool_triggered();
    void on_actionAngleTool_triggered();
    void on_actionPointTool_triggered();
    void on_actionDefaultTool_triggered();
};

#endif // MAINWINDOW_H
