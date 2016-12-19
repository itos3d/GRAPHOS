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
#include "aboutgraphos.h"
#include "libPW.h"
#include "MainWindowGRAPHOS.h"
#include "PersistenceManager.h"
#include "ui_mainwindow.h"
#include <QStackedWidget>
#include "NewProjectDialog.h"
#include <QBitmap>
#include <math.h>
#include <qtconcurrentmap.h>
#include "PWMatchesCategory.h"
#include "CameraMetadataIO.h"
#include "PersistenceProcess/WriteMatchesProcess.h"
#include "MicMac/TapiocaIO.h"
#include "MicMac/MicMacParametersDefinitions.h"
#include "MicMac/MicMacDenseProcess.h"
#include "Preprocessing/WallisBatchProcess.h"
#include "MicMac/TapasProcess.h"
#include "MicMac/TapiocaProcess.h"
#include "MicMac/AperiCloudProcess.h"
#include "TiePointsIO.h"
#include <SURE/Apero2SureProcess.h>
#include <SURE/SUREProcess.h>
#include <SURE/MergeLasResultsProcess.h>
#include "OrientationWizard.h"
#include <liblas/reader.hpp>
#include <liblas/writer.hpp>
#include <fstream>
#include <iostream>
#include "TiePointsWizard.h"
#include "ImagePairsFileIO.h"
#include "WallisResultViewer.h"
#include "PMVS/PMVSProccess.h"
#include "MicMac/Apero2pmvs.h"
#include "MicMac/MicMacDenseProcessObjectSpace.h"
#include "MSD/MSDProcess.h"
#include "ASIFT_UNIBO/ASIFTUProcess.h"
#include "opencv2/photo.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include "Preprocessing/cvDecolorProcess.h"
#include "SubgraphSelector.h"
#include "quazip/JlCompress.h"
#include <QInputDialog>
#include "MicMac/MicMacMultiMainImage.h"
#include "MicMac/PlyMergeProcess.h"
#include "MicMac/TawnyProcess.h"
#include "MicMac/MaltProcess.h"
#include "MicMac/Nuage2PlyProcess.h"
#include "GCPWidget.h"
#include "BatchAuxProcess/TapiocaFinishedProcess.h"
#include "BatchAuxProcess/MSDFinishedProcess.h"
#include "BatchAuxProcess/ASIFTFinishedProcess.h"
#include "BatchAuxProcess/AperoFinishedProcess.h"
#include "cc/qCC/fileIO/FileIOFilter.h"
#include "ScaleModelDialog.h"
#include "ccGLUtils.h"
#include <QDialogButtonBox>
#include <QTableView>
#include <GeorefMicMac/CampariProcess.h>


#include "ExternalProcess/STAR_Process.h"
#include "ExternalProcess/CLAW_Process.h"
#include "ExternalProcess/CalibrationConversion_Process.h"
#define _USE_MATH_DEFINES
#define ABS(x)    (((x) > 0) ? (x) : (-(x)))


using namespace PW;
using namespace std;

struct sortIMagesByDistance
{
    inline bool operator() (const std::pair<QString,double>& a, const std::pair<QString,double>& b)
    {
        return (a.second < b.second);
    }
};

// make sure vectorA and vectorB are of the same size, before calling function
template <typename T, typename R, typename Compare>
void sortVecPair(std::vector<T>& vecA, std::vector<R>& vecB, Compare cmp)
{

    std::vector<pair<T,R>> vecC;
    vecC.reserve(vecA.size());
    for(int i=0; i<vecA.size(); i++)
     {
        vecC.push_back(std::make_pair(vecA[i],vecB[i]));
     }

    std::sort(vecC.begin(), vecC.end(), cmp);

    vecA.clear();
    vecB.clear();
    vecA.reserve(vecC.size());
    vecB.reserve(vecC.size());
    for(int i=0; i<vecC.size(); i++)
     {
        vecA.push_back(vecC[i].first);
        vecB.push_back(vecC[i].second);
     }
}
QImage scaleIMG(const QString &imageFileName)
{
    QImage image(imageFileName);
    return image.scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

MainWindowGRAPHOS::MainWindowGRAPHOS(bool spatialDatabase):mApero2sure(0),
    mDrunkProcess(0),mSureProcess(0), mTapiocaProcess(0),mApero2PMVSProcess(0),
    mPMVSProcess(0),mMergeLasResultsProcess(0),mASIFTUProcess(0),mMultiMainImageMicMacProcess(0),mMicMacSlavesProcess(0),
    mMaltDensificationProcess(0),mC3DCProcess(0),mBatchProcess(0),mGCPBasculeProcess(0),mScaleProcess(0)
{

    //Temp
    connect(ui->actionOpenDialog,SIGNAL(triggered()),this,SLOT(openNewDialog()));


    CUDA_ENABLED = false;

    mSpatialDatabase=spatialDatabase;

    this->initSetups();
    //Set logo
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));

    //Visual style
        QFile styleSheet(":/styleGRAPHOS.qss");

        if (!styleSheet.open(QIODevice::ReadOnly)) {
            qWarning("Unable to open :/styleGRAPHOS.qss");
            return;
        }
        //Style
        qApp->setStyleSheet(styleSheet.readAll());
        ui->toolBar->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #5d5d5d, stop: 1 #757070)");
        //Inicializo mMapImages
        mMapImages= new QMap<QString, QImage>();
        connect(ui->actionOpen_Project,SIGNAL(triggered()),this,SLOT(on_actionOpen_Project_triggered()));
        connect(ui->actionExport_Project,SIGNAL(triggered()),this,SLOT(on_actionExport_Project_triggered()));
        connect(ui->actionImport_Project,SIGNAL(triggered()),this,SLOT(on_actionImport_Project_triggered()));
        connect(mProjectTreeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
                this,SLOT(onTreeItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
        connect(ui->actionUndistorted_images,SIGNAL(triggered()),this,SLOT(on_actionExport_UndistortedImages_triggered()));
        connect(ui->actionExport_Agisoft_model,SIGNAL(triggered()),this,SLOT(on_actionExport_AgisoftDistortion()));
        connect(ui->actionExport_Balanced_distortion,SIGNAL(triggered()),this,SLOT(on_actionExport_BalancedDistortion()));
        connect(ui->actionExport_GRAPHOS_distortion,SIGNAL(triggered()),this,SLOT(on_actionExport_GRAPHOSDistortion()));
        connect(ui->actionExport_Photomodeller_distortion,SIGNAL(triggered()),this,SLOT(on_actionExport_PhotomodellerDistortion()));
        connect(ui->actionBatch_process,SIGNAL(triggered()),this,SLOT(on_actionBatch_ProcessTriggered()));
        connect(ui->action_ActionPickRotationCenter,SIGNAL(triggered()),this,SLOT(on_actionPickRotationCenter_triggered()));
        connect(ui->on_actionGeorreference,SIGNAL(triggered()),this,SLOT(on_actionGeorreference_triggered()));
        connect(ui->actionScale_cloud,SIGNAL(triggered()),this,SLOT(on_actionScaleCloud_triggered()));
        connect(ui->actionTop_view,SIGNAL(triggered()),this,SLOT(setTopView()));
        connect(ui->actionBottom_view,SIGNAL(triggered()),this,SLOT(setBottomView()));
        connect(ui->actionLeft_view,SIGNAL(triggered()),this,SLOT(setLeftView()));
        connect(ui->actionRight_view,SIGNAL(triggered()),this,SLOT(setRightView()));
        connect(ui->actionFront_view,SIGNAL(triggered()),this,SLOT(setFrontView()));
        connect(ui->actionBack_view,SIGNAL(triggered()),this,SLOT(setBackView()));
        connect(ui->actionFront_isometric_view,SIGNAL(triggered()),this,SLOT(setFronIsometricView()));
        connect(ui->actionBack_isometric_view,SIGNAL(triggered()),this,SLOT(setBackIsometricView()));
        connect(ui->actionCalibration_conversion,SIGNAL(triggered()),this,SLOT(on_actionCalibration_conversion_triggered()));
}


void MainWindowGRAPHOS::on_actionPickRotationCenter_triggered()
{
    mCCVW->activateCenterPickingDisplay();
    mCCVW2->activateCenterPickingDisplay();
    ui->actionDefaultTool->setChecked(false);
    ui->actionDistance_Tool->setChecked(false);
    ui->actionAngleTool->setChecked(false);
    ui->actionPointTool->setChecked(false);
    ui->action_ActionPickRotationCenter->setChecked(true);
}


void MainWindowGRAPHOS::initSetups()
{
    mAppTitle = MAINWINDOWGRAPHOS_PROGRAM_NAME;
    ui->actionAbout_PW->setText(tr("About") + " " + mAppTitle);
    QString methodName="MainWindowGRAPHOS::initSetups";
    mSettings = new QSettings(QSettings::IniFormat, QSettings::UserScope, MAINWINDOWGRAPHOS_PROGRAM_TAG, MAINWINDOWGRAPHOS_PROGRAM_TAG);
    mSettings->setValue("micmac/aux", "a");
    mSettings->sync();
    QString settingsDir = QFileInfo(mSettings->fileName()).absolutePath();
    QDir logDir(settingsDir+"/log");
    if(!logDir.exists())
        logDir.mkdir(logDir.absolutePath());
    PW::LibPW::setStdErrorPath(settingsDir+"/log");

    QString dbFileName;
    if(!mSpatialDatabase)
        dbFileName=settingsDir+"/"+MAINWINDOW_DATABASE_FILE;
    else
        dbFileName=settingsDir+"/"+MAINWINDOW_SPATIALDATABASE_FILE;
    QFile dbFile(dbFileName);
    if(!dbFile.exists())
    {
        if(!mSpatialDatabase)
        {
            QFile dbBaseFile(MAINWINDOW_RESOURCES_DATABASE_FILE);
            if(!dbBaseFile.copy(dbFileName))
            {
                QString title = MAINWINDOWGRAPHOS_PROGRAM_NAME;
                QString msg=tr("Error in method ");
                msg+=methodName;
                msg+=tr("\n error copying database file");
                QMessageBox::warning(this, title,msg);
                exit(1);
            }
            QFile::setPermissions(dbFileName, QFile::ReadOwner | QFile::WriteOwner);
        }
        else
        {
            QFile dbBaseFile(MAINWINDOW_RESOURCES_SPATIALDATABASE_FILE);
            if(!dbBaseFile.copy(dbFileName))
            {
                QString title = MAINWINDOWGRAPHOS_PROGRAM_NAME;
                QString msg=tr("Error in method ");
                msg+=methodName;
                msg+=tr("\n error copying database file");
                QMessageBox::warning(this, title,msg);
                exit(1);
            }
            QFile::setPermissions(dbFileName, QFile::ReadOwner | QFile::WriteOwner);
        }
    }
    mPersistenceManager = new PW::PersistenceManager(dbFileName);
    mPersistenceManager->openDatasource();

    //Draw startScreen
    drawStartScreen();
    drawBasicUserGUI();

    //Set the advanced user GUI
    mQStackedWidget->setContentsMargins(0,0,0,0);
    setCentralWidget(mQStackedWidget);
    mQStackedWidget->setStyleSheet("Background-color:gray;");
    mQStackedWidget->setCurrentIndex(0);

    QString parametersFileName=settingsDir+"/"+MAINWINDOW_PARAMETERS_FILE;
    QFile qparamsFile(parametersFileName);
    if(!qparamsFile.exists())
    {
        QFile qparamsBaseFile(MAINWINDOW_RESOURCES_PARAMETERS_DATABASE_FILE);
        if(!qparamsBaseFile.copy(parametersFileName))
        {
            QString title = MAINWINDOWGRAPHOS_PROGRAM_NAME;
            QString msg=tr("Error in method ");
            msg+=methodName;
            msg+=tr("\n error copying parameters database file");
            QMessageBox::warning(this, title,msg);
            exit(1);
        }
        QFile::setPermissions(parametersFileName, QFile::ReadOwner | QFile::WriteOwner);
    }
    QParams::QParamsManager::initDSManager(parametersFileName);
    //¿First run after update app?:
    QString firstRun = mSettings->value("app/firstRun").toString();
    QString previousVersion = mSettings->value("app/previousVersion").toString();
    if (firstRun == "true")
    {
        mPersistenceManager->updateDBVersion(previousVersion, MAINWINDOWGRAPHOS_VERSION);
        QParams::QParamsManager::updateDBVersion(previousVersion, MAINWINDOWGRAPHOS_VERSION);
        mSettings->setValue("app/version", MAINWINDOWGRAPHOS_VERSION);
        mSettings->setValue("app/bn", MAINWINDOWGRAPHOS_BUILD_NUMBER);
        mSettings->setValue("app/releaseType", MAINWINDOWGRAPHOS_RELEASE_TYPE);
        mSettings->setValue("app/firstRun","false");
        mSettings->setValue("app/cleanProjectAtClossingEvent","1");
        QFile file(settingsDir+"/version");
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);
        out << MAINWINDOWGRAPHOS_VERSION;
        file.close();
    }

    MainWindow::initSetups();

    //Dishable non used actions
    ui->actionDistance_Tool->setEnabled(false);
    ui->action_ActionPickRotationCenter->setEnabled(false);

    QString title = MAINWINDOWGRAPHOS_PROGRAM_NAME + tr(" - Untitled");
    setWindowTitle(title);

    mDockThumbs->setVisible(false);
    mDockProject->setVisible(false);
    mDockProject->setMinimumWidth(250);
    mDockProject->resize(250, mDockProject->height());

    connect(this,SIGNAL(imagesLoaded()),this,SLOT(on_imagesLoaded_emited()));
}

void MainWindowGRAPHOS::on_actionExport_Project_triggered()
{
    QString initPath = mSettings->value("app/lastoutputpath").toString();
    if (initPath.isEmpty())
        initPath = QDir::homePath();

    QString exportPath("");

    QString filters("GRAPHOS file (*.grp)");
    QString defaultFilter="GRAPHOS file (*.grp)";

    exportPath = QFileDialog::getSaveFileName(this, tr("Dense Model"),
                                                initPath,
                                                filters, &defaultFilter);
    if (exportPath.isEmpty()) {
        return;
    }

    //Clean project
    cleanProject();

    QFile auxBDFile;
    auxBDFile.setFileName(":/PW/projectsSpatialDB");
    auxBDFile.copy(mProject->getBasePath() + "/projectDB.gdb");
    QFile::setPermissions(mProject->getBasePath()+ "/projectDB.gdb", QFile::ReadOwner | QFile::WriteOwner);
    PersistenceManager *persistenceManager = new PersistenceManager(mProject->getBasePath()+ "/projectDB.gdb");
    persistenceManager->openAuxDatasource();
    persistenceManager->writeProject(mProject, true, true, mProject->getID());


    //Zip project
    QDir source(mProject->getBasePath());
    QFileInfo dest(exportPath);
    JlCompress::compressDir(dest.absoluteFilePath(),source.absolutePath());

    persistenceManager->closeDatasource();
    //Remove temp db
    QFileInfo tmpDB(mProject->getBasePath()+"/projectDB.gdb");
    if (tmpDB.exists()) {
        QFile::remove(tmpDB.absoluteFilePath());
    }
}

void MainWindowGRAPHOS::on_actionImport_Project_triggered(){

    QString initPath = mSettings->value("app/lastoutputpath").toString();
    if (initPath.isEmpty())
        initPath = QDir::homePath();

    QString importFilePath("");

    QString filters("GRAPHOS file (*.grp)");
    QString defaultFilter="GRAPHOS file (*.grp)";

    importFilePath = QFileDialog::getOpenFileName(this,tr("Select project to import"),initPath,filters, &defaultFilter);

    if (importFilePath.isEmpty()) {
        return;
    }


    //unzip project
    QString unzipPath("");
    unzipPath = QFileDialog::getExistingDirectory(this,"Select folder to import",initPath);


    JlCompress::extractDir(importFilePath,unzipPath);


    if (unzipPath.isEmpty()){
        return;
    }
        PersistenceManager *persistenceManager = new PersistenceManager(unzipPath+"/projectDB.gdb");
        persistenceManager->openAuxDatasource();
        Project *project = persistenceManager->readProject();
        persistenceManager->closeDatasource();

        bool ok;
        QString projectName = QInputDialog::getText(this, tr("Import project"),
                                                    tr("Project name:"), QLineEdit::Normal,
                                                    "",&ok);
        if (ok && !projectName.isEmpty()){

            project->setName(projectName);
            project->setBasePath(unzipPath);
            if (!project->getDenseModelRelativePath().isEmpty()) {
                project->setDenseModelRelativePath(project->getDenseModelRelativePath());
            }
            if (!project->getSparseModelRelativePath().isEmpty()) {
                project->setSparseModelRelativePath(project->getSparseModelRelativePath());
            }

            mPersistenceManager->writeProject(project,true);
            mSettings->setValue("app/lastpath", unzipPath);
            openLatestProject(projectName);
        }
        //Remove temp db
        QFileInfo tmpDB(mProject->getBasePath()+"/projectDB.gdb");
        if (tmpDB.exists()) {
            QFile::remove(tmpDB.absoluteFilePath());
        }

}

void MainWindowGRAPHOS::closeEvent(QCloseEvent *event)
{
    if (mProject->getID()!=0 && PW::LibPW::getCleanProjectAtClossingEvent()) {
        cleanProject();
    }
    //Need to save??
    if (mProject->needToSave()){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("GRAPHOS");
        msgBox.setText("The project has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        int ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            mOpenProjectDialog->setNameVisible(true);
            if (mProject->getName().isEmpty()){
                event->ignore();
                mOpenProjectDialog->setProjectName(mProject->getName());
                mOpenProjectDialog->setForSave(true);
                mOpenProjectDialog->refreshData();
                mToSave = true;
                mOpenProjectDialog->open();
            }
            else{
                mPersistenceManager->updateProject(mProject);
            }
            mPersistenceManager->closeDatasource();
            break;
        case QMessageBox::Discard:
            mPersistenceManager->closeDatasource();
            break;
        case QMessageBox::Cancel:
            event->ignore();
            break;
        default:
            event->ignore();
            break;
        }
    }
}

void MainWindowGRAPHOS::loadProject()
{
    cleanEnviroment();
    loadProjectMetadataOnProjectTree();
    loadProjectImages();

    //Load Models:
    if (!mProject->getSparseModelRelativePath().isEmpty()){
        QFile sparseFile(mProject->getSparseModelFullPath());
        if(sparseFile.exists()){
            mCCVW->addToDB(QStringList() << mProject->getSparseModelFullPath());
        }
    }

    if (!mProject->getDenseModelRelativePath().isEmpty()){
        QFile denseFile(mProject->getDenseModelFullPath());
        if(denseFile.exists()){

                mCCVW2->addToDB(QStringList() << mProject->getDenseModelFullPath());
        }
    }
    loadProjectMetadataOnProjectTree();

    loadModelsOnTree();

    updateTools();
}

void MainWindowGRAPHOS::updateTools()
{
    ui->menuView->actions().first()->setEnabled(false);
    ui->actionMask->setEnabled(false);
    ui->actionExport_Dense_Model->setEnabled(false);
    ui->actionExport_Sparse_Model->setEnabled(false);
    ui->actionUndistorted_images->setEnabled(false);
    ui->actionDefaultTool->setEnabled(false);
    ui->actionDistance_Tool->setEnabled(false);
    ui->action_ActionPickRotationCenter->setEnabled(false);
    ui->actionAngleTool->setEnabled(false);
    ui->actionPointTool->setEnabled(false);
    ui->actionBatch_process->setEnabled(false);
    ui->on_actionGeorreference->setEnabled(false);
    ui->actionScale_cloud->setEnabled(false);
    ui->actionFront_isometric_view->setEnabled(false);
    ui->actionBack_isometric_view->setEnabled(false);
    ui->actionFront_view->setEnabled(false);
    ui->actionBack_view->setEnabled(false);
    ui->actionLeft_view->setEnabled(false);
    ui->actionRight_view->setEnabled(false);
    ui->actionTop_view->setEnabled(false);
    ui->actionBottom_view->setEnabled(false);


    if (mQStackedWidget->currentIndex()==0) {
        ui->menuView->actions().first()->setEnabled(false);
        ui->actionSave->setEnabled(false);
        ui->menuExport->setEnabled(false);
    }else {
        ui->actionSave->setEnabled(true);
        ui->menuExport->setEnabled(true);
    }
    if(mProject->getImages().count()>1){
        ui->actionBatch_process->setEnabled(true);
        ui->actionDefaultTool->setEnabled(true);
        ui->actionMask->setEnabled(true);
    }

    if(!mProject->getSparseModelRelativePath().isEmpty()){
        QFile sparseFile(mProject->getSparseModelFullPath());
        if(sparseFile.exists()){
            ui->menuView->actions().first()->setEnabled(true);
            ui->menuExport->setEnabled(true);
            ui->actionExport_Sparse_Model->setEnabled(true);
            ui->actionUndistorted_images->setEnabled(true);
            ui->actionDistance_Tool->setEnabled(true);
            ui->action_ActionPickRotationCenter->setEnabled(true);
            ui->actionAngleTool->setEnabled(true);
            ui->actionPointTool->setEnabled(true);
            ui->on_actionGeorreference->setEnabled(true);
            ui->actionFront_isometric_view->setEnabled(true);
            ui->actionBack_isometric_view->setEnabled(true);
            ui->actionFront_view->setEnabled(true);
            ui->actionBack_view->setEnabled(true);
            ui->actionLeft_view->setEnabled(true);
            ui->actionRight_view->setEnabled(true);
            ui->actionTop_view->setEnabled(true);
            ui->actionBottom_view->setEnabled(true);
        }
    }

    if(!mProject->getDenseModelRelativePath().isEmpty()){
        QFile denseFile(mProject->getDenseModelFullPath());
        if(denseFile.exists()){
            ui->menuView->actions().first()->setEnabled(true);
            ui->menuExport->setEnabled(true);
            ui->actionExport_Dense_Model->setEnabled(true);
            ui->actionDistance_Tool->setEnabled(true);
            ui->action_ActionPickRotationCenter->setEnabled(true);
            ui->actionAngleTool->setEnabled(true);
            ui->actionPointTool->setEnabled(true);
            ui->actionScale_cloud->setEnabled(true);
        }
    }
}

void MainWindowGRAPHOS::on_actionNew_Project_triggered(){

    if (mProject->getID()!=0 && PW::LibPW::getCleanProjectAtClossingEvent()) {
        cleanProject();
    }

    if (mQStackedWidget->currentIndex()!=0) {
        mQStackedWidget->setCurrentIndex(0);
        mDockProject->setVisible(false);
        mDockThumbs->setVisible(false);
        mDockWorkflow->setVisible(false);
        if (mDockGeorref!=0) {
            mDockGeorref->setVisible(false);
        }
        mQStackedWidget->setStyleSheet("Background-color:gray;");
    }
    //Show new project dialog
    mProject= new PW::Project();
    cleanEnviroment();
    mNewProjectDialog = new NewProjectDialog(this,mProject,mProjectsNames);

    if (!mNewProjectDialog->exec()) {
        return;
    }
    mDockThumbs->setVisible(true);
    mDockProject->setVisible(true);

    this->setWindowTitle(mAppTitle+" - " + mProject->getName());


    mPersistenceManager->writeProject(mProject);

    loadProject();

    setWorkflowWidgetStatus();
    mQStackedWidget->setStyleSheet("Background-color:transparent;");
    mQStackedWidget->setCurrentIndex(1);
    mDockWorkflow->setVisible(true);



}

void MainWindowGRAPHOS::drawStartScreen(){

    menuBar()->setEnabled(false);

    mQStackedWidget = new QStackedWidget;
    //set fonts
    QFont fontLBTitles( "Arial", 15);
    QFont fontLBObjects( "Arial", 10, QFont::Cursive);

    QFrame *startScreenContainer = new QFrame();
    QGridLayout *startScreenContainerLayout = new QGridLayout();

    QFrame *startScreenWidgetParent = new QFrame();
    startScreenWidgetParent->setFixedSize(600,500);
    QVBoxLayout *mStartWidgetVerticalLayout = new QVBoxLayout();

    QFrame *frame1 = new QFrame();
    frame1->setStyleSheet("background-color:white;");

    frame1->setFixedHeight(60);
    QHBoxLayout *frame1Layout = new QHBoxLayout();
    QLabel *lbLogoGRAPHOS = new QLabel();
    QPixmap pix(":/PW/icons/img/graphos.PNG");
    lbLogoGRAPHOS->setPixmap(pix);
    lbLogoGRAPHOS->setStyleSheet("background:transparent;");
    frame1Layout->addWidget(lbLogoGRAPHOS);
    frame1->setLayout(frame1Layout);
    frame1->layout()->setContentsMargins(10, 10, 0, 0);

    QFrame *frame2 = new QFrame();
    frame2->setStyleSheet("background-image: url(:/PW/icons/img/textureprueba.png);");
    QHBoxLayout *frame2Layout = new QHBoxLayout();
    frame2->setLayout(frame2Layout);
    QFrame *frame2_Left = new QFrame();
    frame2_Left->setStyleSheet("background:transparent;");
    QFrame *frame2_Right = new QFrame();
    frame2_Right->setStyleSheet("background:transparent;");

    QGridLayout *frame2_LeftLayout = new QGridLayout();
    frame2_LeftLayout->setAlignment(Qt::AlignCenter);
    QPushButton *bt_NewProject = new QPushButton("New project");
    QPushButton *bt_OpenProject = new QPushButton("Search project");
    bt_NewProject->setStyleSheet("background-color:none;");
    bt_NewProject->setFixedWidth(250);
    bt_OpenProject->setStyleSheet("background-color:none;");
    bt_OpenProject->setFixedWidth(250);
    QLabel *lbNewProject = new QLabel("Create new project");
    lbNewProject->setFont(fontLBTitles);
    QLabel *lbOpenProject = new QLabel("Open existing project");
    lbOpenProject->setFont(fontLBTitles);
    frame2_LeftLayout->addWidget(lbNewProject);
    frame2_LeftLayout->addWidget(bt_NewProject);
    QFrame *verticalSpacer = new QFrame();
    verticalSpacer->setFixedHeight(10);
    frame2_LeftLayout->addWidget(verticalSpacer);
    frame2_LeftLayout->addWidget(lbOpenProject);
    frame2_LeftLayout->addWidget(bt_OpenProject);

    frame2_Left->setLayout(frame2_LeftLayout);
    frame2_Left->layout()->setContentsMargins(0, 0, 0, 0);

    QFrame *lineV = new QFrame();
    lineV->setFrameShape(QFrame::VLine);
    lineV->setFrameShadow(QFrame::Sunken);
    lineV->setStyleSheet("background-color:white;");
    lineV->setFixedSize(3,300);

    QVBoxLayout *frame2_RightLayout = new QVBoxLayout();
    QFrame *frame2_RightTop = new QFrame();
    QFrame *frame2_RightBottom = new QFrame();

    QVBoxLayout *frame2_RightTopLayout = new QVBoxLayout();
    frame2_RightTopLayout->addSpacing(20);
    QLabel *lbRecentProjects = new QLabel("Latest projects");
    lbRecentProjects->setFont(fontLBTitles);
    QFrame *frameRecentProjects = new QFrame();
    mFrameRecentProjectsLayout = new QVBoxLayout();
    setLatestProjectsLayout();

    frameRecentProjects->setLayout(mFrameRecentProjectsLayout);

    frame2_RightTopLayout->addWidget(lbRecentProjects);
    frame2_RightTopLayout->addWidget(frameRecentProjects);
    frame2_RightTop->setLayout(frame2_RightTopLayout);
    frame2_RightLayout->addWidget(frame2_RightTop);

    QFrame *line = new QFrame();
    line->setObjectName(QString::fromUtf8("line"));
    line->setGeometry(QRect(320, 150, 10, 3));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    line->setStyleSheet("background-color:white;");
    frame2_RightLayout->addWidget(line);

    QVBoxLayout *frame2_RightBottomLayout = new QVBoxLayout();
    QLabel *lbAboutUs = new QLabel("About us");
    lbAboutUs->setFont(fontLBTitles);

    QLabel *lbUSAL = new QLabel("<a href=\"http://tidop.usal.es\">TIDOP - University of Salamanca</a>");
    lbUSAL->setTextFormat(Qt::RichText);
    lbUSAL->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lbUSAL->setOpenExternalLinks(true);
    lbUSAL->setFont(fontLBObjects);

    QLabel *lbUCLM = new QLabel("<a href=\"http://www.uclm.es/\">University of Castilla la Mancha</a>");
    lbUCLM->setTextFormat(Qt::RichText);
    lbUCLM->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lbUCLM->setOpenExternalLinks(true);
    lbUCLM->setFont(fontLBObjects);

    QLabel *lbFBK = new QLabel("<a href=\"http://3dom.fbk.eu/\">3DOM - Fondazione Bruno Kessler</a>");
    lbFBK->setTextFormat(Qt::RichText);
    lbFBK->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lbFBK->setOpenExternalLinks(true);
    lbFBK->setFont(fontLBObjects);

    QLabel *lbUNIBO = new QLabel("<a href=\"http://www.unibo.it/en/homepage\">University of Bologna</a>");
    lbUNIBO->setTextFormat(Qt::RichText);
    lbUNIBO->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lbUNIBO->setOpenExternalLinks(true);
    lbUNIBO->setFont(fontLBObjects);

    QPushButton *pbLearnMore = new QPushButton("Learn more about GRAPHOS...");
    pbLearnMore->setStyleSheet("background:none;");
    connect(pbLearnMore,SIGNAL(clicked()),this,SLOT(on_actionAbout_GRAPHOS_triggered()));

    frame2_RightBottomLayout->setAlignment(Qt::AlignTop);
    frame2_RightBottomLayout->addWidget(lbAboutUs);
    frame2_RightBottomLayout->addWidget(lbUSAL);
    frame2_RightBottomLayout->addWidget(lbUCLM);
    frame2_RightBottomLayout->addWidget(lbFBK);
    frame2_RightBottomLayout->addWidget(lbUNIBO);
    frame2_RightBottomLayout->addWidget(pbLearnMore);
    frame2_RightBottom->setLayout(frame2_RightBottomLayout);
    frame2_RightLayout->addWidget(frame2_RightBottom);

    frame2_Right->setLayout(frame2_RightLayout);

    frame2Layout->addWidget(frame2_Left);
    frame2Layout->addWidget(lineV);
    frame2Layout->addWidget(frame2_Right);

    QFrame *frame3 = new QFrame();
    frame3->setStyleSheet("background-color:white;");
    QHBoxLayout *frame3Layout = new QHBoxLayout();
    QString versionInfo;
    versionInfo.append("VERSION ").append(MAINWINDOWGRAPHOS_VERSION).append(" ").append(MAINWINDOWGRAPHOS_RELEASE_TYPE).append("  -  Build number: ").append(MAINWINDOWGRAPHOS_BUILD_NUMBER).append("  /  Licence: GPL V3");
    lbVersionGRAPHOS = new QLabel(versionInfo);
    frame3Layout->addWidget(lbVersionGRAPHOS);
    frame3Layout->setAlignment(Qt::AlignTop);
    frame3->setLayout(frame3Layout);
    frame3->setFixedHeight(15);
    frame3->layout()->setContentsMargins(10, 0, 0, 0);
    mStartWidgetVerticalLayout->addWidget(frame1);
    mStartWidgetVerticalLayout->addWidget(frame2);
    mStartWidgetVerticalLayout->addWidget(frame3);

    startScreenWidgetParent->setLayout(mStartWidgetVerticalLayout);
    startScreenWidgetParent->layout()->setContentsMargins(0,0,0,0);
    startScreenWidgetParent->setStyleSheet("background-color:white;");

    startScreenContainerLayout->addWidget(startScreenWidgetParent);
    startScreenContainer->setLayout(startScreenContainerLayout);
    mQStackedWidget->addWidget(startScreenContainer);

    connect(bt_NewProject,SIGNAL(clicked()),this,SLOT(on_actionNew_Project_triggered()));
    connect(bt_OpenProject,SIGNAL(clicked()),this,SLOT(on_actionOpen_Project_triggered()));
    connect(ui->actionNew_Project,SIGNAL(triggered()),this,SLOT(on_actionNew_Project_triggered()));
}

void MainWindowGRAPHOS::drawBasicUserGUI(){
    menuBar()->setEnabled(true);

    //set fonts
    QFont fontLBTitles( "Arial", 15);
    QFont fontLBObjects( "Arial", 10, QFont::Cursive);

    QFrame *mFrameWorkflow = new QFrame();
    QGridLayout *mFrameWorkflowLayout =new QGridLayout();
    mFrameWorkflowLayout->setContentsMargins(0,0,0,0);

    mWorkflowWidget = new QWidget();
    mWorkflowWidget->setMinimumWidth(1100);
    QPixmap pixmap;

    mWorkflowButtonImages= new QPushButton("Images", mWorkflowWidget);
    connect(mWorkflowButtonImages,SIGNAL(clicked()),this,SLOT(on_actionAdd_Images_triggered()));
    pixmap = QPixmap(":/PW/icons/img/Left.png");
    mWorkflowButtonImages->setMask(pixmap.mask());
    mWorkflowButtonImages->setFixedSize(300,38);

    mWorkflowButtonImages->setGeometry(0, 0, 300, 38);


    mWorkflowButtonTiePoints= new QPushButton("Tie points", mWorkflowWidget);
    connect(mWorkflowButtonTiePoints,SIGNAL(clicked()),this,SLOT(on_actionCompute_Tie_Points_triggered()));
    pixmap = QPixmap(":/PW/icons/img/Mid.png");
    mWorkflowButtonTiePoints->setMask(pixmap.mask());
    mWorkflowButtonTiePoints->setFixedSize(300,38);
    mWorkflowButtonTiePoints->setGeometry((300-38) * 1, 0, 300, 38);

    mWorkflowButtonOrientations= new QPushButton("Orientation", mWorkflowWidget);
    connect(mWorkflowButtonOrientations,SIGNAL(clicked()),this,SLOT(on_actionCompute_Orientations_triggered()));
    mWorkflowButtonOrientations->setMask(pixmap.mask());
    mWorkflowButtonOrientations->setFixedSize(300,38);
    mWorkflowButtonOrientations->setGeometry((300-38) * 2, 0, 300, 38);

    mWorkflowButtonDensification= new QPushButton("Dense matching", mWorkflowWidget);
    connect(mWorkflowButtonDensification,SIGNAL(clicked()),this,SLOT(on_actionDense_Model_triggered()));
    mWorkflowButtonDensification->setMask(pixmap.mask());
    mWorkflowButtonDensification->setGeometry((300-38) * 3, 0, 300, 38);

    mDockWorkflow = new QDockWidget(tr("Workflow"),this);
    addDockWidget(Qt::TopDockWidgetArea,mDockWorkflow);
    mFrameWorkflowLayout->addWidget(mWorkflowWidget,0,0);
    QFrame *logoFrame= new QFrame();
    QHBoxLayout *logoFrameLayout = new QHBoxLayout();
    logoFrameLayout->setContentsMargins(0,0,0,0);
    logoFrameLayout->addStretch(0);
    QLabel *logoGraphosWorkflow = new QLabel();
    QPixmap logographos(":/PW/icons/img/logoGraphosWorkflow.png");
    logoGraphosWorkflow->setPixmap(logographos);
    logoFrameLayout->addWidget(logoGraphosWorkflow);
    logoFrame->setLayout(logoFrameLayout);
    mFrameWorkflowLayout->addWidget(logoFrame,0,1);
    mFrameWorkflow->setLayout(mFrameWorkflowLayout);

    mDockWorkflow->setWidget(mFrameWorkflow);
    mDockWorkflow->setStyleSheet("Background-color:#e9e9e9;");

    mDockWorkflow->setMinimumHeight(38);
    mDockWorkflow->setMaximumHeight(38);
    mDockWorkflow->setTitleBarWidget(new QWidget());
    mDockWorkflow->setVisible(false);

    mDockGeorref = new QDockWidget(tr("Georeferencing"),this);
    mDockGeorref->setVisible(false);


    mBasicUserGUI = new QStackedWidget();
    connect(mBasicUserGUI,SIGNAL(currentChanged(int)),this,SLOT(on_QStackedWidget_currentChanged(int)));

    mBasicUserGUI->setContentsMargins(-10,-10,-5,-10);
    mImagesWidget = new QFrame();
    QVBoxLayout *mImagesWidgetLayout = new QVBoxLayout();

    mImagesWidgetLayout->addWidget(mPhotoViewer->getViewWidget());
    mPbAddImages = new QPushButton("Add images");
    connect(mPbAddImages,SIGNAL(clicked()),this,SLOT(addImages()));
    mPbAddImages->setVisible(false);
    mPbAddImages->setStyleSheet("Background-color:none;");
    mImagesWidgetLayout->addWidget(mPbAddImages);
    mImagesWidget->setLayout(mImagesWidgetLayout);
    mBasicUserGUI->addWidget(mImagesWidget);

    mTiePointsInfoView = new QWidget();
    QWidget *tiePointsInfoViewContainer = new QWidget();
    QVBoxLayout *tiePointsInfoViewContainerLayout = new QVBoxLayout();
    tiePointsInfoViewContainerLayout->addWidget(mTiePointsInfoView);
    mPbRecomputeTiePoints = new QPushButton("Tie points wizard");
    connect(mPbRecomputeTiePoints,SIGNAL(clicked()),this,SLOT(on_recomputeTiePointsTriggered()));
    mPbRecomputeTiePoints->setStyleSheet("Background-color:none;");
    tiePointsInfoViewContainerLayout->addWidget(mPbRecomputeTiePoints);
    tiePointsInfoViewContainer->setLayout(tiePointsInfoViewContainerLayout);
    mBasicUserGUI->addWidget(tiePointsInfoViewContainer);

    //Setup CC Viewer:
    mCCVW = new ccViewerWrapper();
    QVBoxLayout *orientationsLayout = new QVBoxLayout();
    orientationsLayout->addWidget((QWidget*)mCCVW->getGLWindow());
    mPbRecomputeOrientations = new QPushButton("Orientations wizard");
    connect(mPbRecomputeOrientations,SIGNAL(clicked()),this,SLOT(on_recomputeOrientationsTriggered()));
    orientationsLayout->addWidget(mPbRecomputeOrientations);
    mPbRecomputeOrientations->setStyleSheet("Background-color:none;");
    QWidget *widgetOrientations = new QWidget();
    widgetOrientations->setLayout(orientationsLayout);
    mBasicUserGUI->addWidget(widgetOrientations);


    mCCVW2 = new ccViewerWrapper();
    QVBoxLayout *densificationLayout = new QVBoxLayout();
    densificationLayout->addWidget((QWidget*)mCCVW2->getGLWindow());
    mPbRecomputeDensification =new QPushButton("Densification wizard");
    connect(mPbRecomputeDensification,SIGNAL(clicked()),this,SLOT(on_recomputeDensificationTriggered()));
    densificationLayout->addWidget(mPbRecomputeDensification);
    mPbRecomputeDensification->setStyleSheet("Background-color:none;");
    QWidget *widgetDensification = new QWidget();
    widgetDensification->setLayout(densificationLayout);
    mBasicUserGUI->addWidget(widgetDensification);

    //Setup matchings viewer
    mMatchingsView = new QWidget();
    QWidget *matchingsViewContainer = new QWidget();
    QVBoxLayout *matchingsViewContainerLayout = new QVBoxLayout();
    matchingsViewContainerLayout->addWidget(mMatchingsViewer->getView());
    mPbBackToTieImagesConnection = new QPushButton("Back to images connection");
    connect(mPbBackToTieImagesConnection,SIGNAL(clicked()),this,SLOT(on_BackToImagesConnectionTriggered()));
    mPbBackToTieImagesConnection->setStyleSheet("Background-color:none;");
    matchingsViewContainerLayout->addWidget(mPbBackToTieImagesConnection);
    matchingsViewContainer->setLayout(matchingsViewContainerLayout);
    mBasicUserGUI->addWidget(matchingsViewContainer);

    mBasicUserGUI->setCurrentIndex(0);

    mQStackedWidget->addWidget(mBasicUserGUI);
}

void MainWindowGRAPHOS::on_actionOrientationButton_triggered(){
    mBasicUserGUI->setCurrentIndex(2);
}
void MainWindowGRAPHOS::on_actionDensificationButton_triggered(){
    mBasicUserGUI->setCurrentIndex(3);
}

void MainWindowGRAPHOS::setWorkflowWidgetStatus(){
    QString nextStep="QPushButton:hover {background-color: qlineargradient(x1: 0, y1: 0, x2: 2, y2: 0,stop: 0 #77dd77, stop: 1 #f6f7fa);} QPushButton:pressed {background-color:qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #77dd77, stop: 1 #f6f7fa);} QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 5, y2: 0,stop: 0 #77dd77, stop: 1 #f6f7fa);border-style: outset;border-width: 0px;font-weight: bold;}";
    QString successfullStep="QPushButton:hover {background-color: qlineargradient(x1: 0, y1: 0, x2: 2, y2: 0,stop: 0 #5f8dd3, stop: 1 #f6f7fa);} QPushButton:pressed {background-color:qlineargradient(x1: 0, y1: 0, x2: 1, y2: 0,stop: 0 #5f8dd3, stop: 1 #f6f7fa);} QPushButton{background-color: qlineargradient(x1: 0, y1: 0, x2: 5, y2: 0,stop: 0 #5f8dd3, stop: 1 #f6f7fa);border-style: outset;border-width: 0px;font-weight: bold;}";

    QString dishabledStep="border-style: outset;border-width: 0px;font-weight: bold;background-color:qlineargradient(x1: 0, y1: 0, x2: 5, y2: 0,stop: 0 #e1e1e1, stop: 1 #f6f7fa);";
    QString endStepEnabled="border-style: outset;border-width: 0px;background-image: url(:/PW/icons/img/end.png);font-weight: bold;";


    if (!mProject->getDenseModelRelativePath().isEmpty()) {// || mState==4
                    mWorkflowButtonImages->setStyleSheet(successfullStep);
                    mWorkflowButtonTiePoints->setStyleSheet(successfullStep);
                    mWorkflowButtonOrientations->setStyleSheet(successfullStep);
                    mWorkflowButtonDensification->setStyleSheet(successfullStep);
                    mWorkflowButtonImages->setEnabled(true);
                    mWorkflowButtonTiePoints->setEnabled(true);
                    mWorkflowButtonOrientations->setEnabled(true);
                    mWorkflowButtonDensification->setEnabled(true);
                    mBasicUserGUI->setCurrentIndex(3);
    } else if(!mProject->getSparseModelRelativePath().isEmpty()){
                    mWorkflowButtonImages->setStyleSheet(successfullStep);
                    mWorkflowButtonTiePoints->setStyleSheet(successfullStep);
                    mWorkflowButtonOrientations->setStyleSheet(successfullStep);
                    mWorkflowButtonDensification->setStyleSheet(nextStep);
                    mWorkflowButtonImages->setEnabled(true);
                    mWorkflowButtonTiePoints->setEnabled(true);
                    mWorkflowButtonOrientations->setEnabled(true);
                    mWorkflowButtonDensification->setEnabled(true);
                    mBasicUserGUI->setCurrentIndex(2);
    } else if(mProject->getTiePointsSets().count()!=0){
                    mWorkflowButtonImages->setStyleSheet(successfullStep);
                    mWorkflowButtonTiePoints->setStyleSheet(successfullStep);
                    mWorkflowButtonOrientations->setStyleSheet(nextStep);
                    mWorkflowButtonDensification->setStyleSheet(dishabledStep);
                    mWorkflowButtonImages->setEnabled(true);
                    mWorkflowButtonTiePoints->setEnabled(true);
                    mWorkflowButtonOrientations->setEnabled(true);
                    mWorkflowButtonDensification->setEnabled(false);
                    mBasicUserGUI->setCurrentIndex(1);
    }else if(mProject->getImagesFileName().count()!=0){
                    mWorkflowButtonImages->setStyleSheet(successfullStep);
                    mWorkflowButtonTiePoints->setStyleSheet(nextStep);
                    mWorkflowButtonOrientations->setStyleSheet(dishabledStep);
                    mWorkflowButtonDensification->setStyleSheet(dishabledStep);
                    mWorkflowButtonImages->setEnabled(true);
                    mWorkflowButtonTiePoints->setEnabled(true);
                    mWorkflowButtonOrientations->setEnabled(false);
                    mWorkflowButtonDensification->setEnabled(false);
                    mBasicUserGUI->setCurrentIndex(0);
    }else{
                    mWorkflowButtonImages->setStyleSheet(nextStep);
                   mWorkflowButtonTiePoints->setStyleSheet(dishabledStep);
                   mWorkflowButtonOrientations->setStyleSheet(dishabledStep);
                   mWorkflowButtonDensification->setStyleSheet(dishabledStep);
                   mWorkflowButtonImages->setEnabled(true);
                   mWorkflowButtonTiePoints->setEnabled(false);
                   mWorkflowButtonOrientations->setEnabled(false);
                   mWorkflowButtonDensification->setEnabled(false);
                   mBasicUserGUI->setCurrentIndex(0);
    }
}



void MainWindowGRAPHOS::on_actionAdd_Images_triggered()
{
    if (mProject->getImagesFileName().count()!=0) {
        mPbAddImages->setVisible(true);
        mBasicUserGUI->setCurrentIndex(0);
        return;
    }
    addImages();
    setWorkflowWidgetStatus();
    mDockThumbs->setVisible(true);
}

void MainWindowGRAPHOS::addImages(){
    mFileNamesToLoad = new QStringList();

    QString initPath = mSettings->value("app/lastpath").toString();
        if (initPath.isEmpty())
            initPath = QDir::homePath();


    mImagesWizard = new ImagesWizard(this,mFileNamesToLoad,mProgressDialog);
    mImagesWizard->mInitPath=initPath;
    if (!mImagesWizard->exec()) {
        return;
    }


    if (!mFileNamesToLoad->isEmpty()) {
        mFileNamesToLoad->sort();
        //All images in the same directory?
        if (!mProject->getImages().isEmpty()){
            QString aFileName = mFileNamesToLoad->at(0);
            QString newFilesPath = aFileName.left(aFileName.lastIndexOf(QRegExp("/")));
            if(newFilesPath!=mImagesPath){
                QMessageBox::warning(this, tr("GRAPHOS"),
                                     tr("All images in the project must be in the same directory."));
                return;
            }
        }

        //All images taken whit same camera?
        int validationID = validateImages(*mFileNamesToLoad);
        if(validationID != 0){
            QString errorMessage = "";
            switch (validationID){
            case 1:
                errorMessage = tr("Not images selected.");
                break;
            case 2:
                errorMessage = tr("Invalid images path: \n The images path should not contain spaces, accents or other special characters.");
                break;
            case 3:
                errorMessage = tr("All images in the project must be taken with the same camera.");
                break;
            default:
                break;
            }

            QMessageBox::warning(this, tr("GRAPHOS"), errorMessage);
            return;
        }

        mImagesPath = mFileNamesToLoad->at(0).left(mFileNamesToLoad->at(0).lastIndexOf(QRegExp("/")));
        mProject->setBasePath(mImagesPath.left(mImagesPath.length()));
        mProject->setPreprocessingPath(mProject->getBasePath()+"/preprocessing");
        mSettings->setValue("app/lastpath", mImagesPath);

        QList<PWImage*> imagesList;
        PWImage* image = new PWImage(mFileNamesToLoad->at(0));

        // Read exif of first image:
        CameraMetadataIO exifIO(mFileNamesToLoad->at(0));
        Camera cameraEXIF;
        exifIO.read(&cameraEXIF);

        //Search the camera in project
        QString cameraKey = cameraEXIF.getName();
        if(!cameraEXIF.getLensName().isEmpty())
            cameraKey = cameraKey + " - " + cameraEXIF.getLensName();
        Camera *camera = mProject->getCamera(cameraKey);

        //Search the camera in project or data base:
        if(camera == NULL){
            camera = mPersistenceManager->readCamera(cameraEXIF.getName(), cameraEXIF.getLensName());
            if(camera==NULL){
                camera = mPersistenceManager->readCamera(cameraEXIF.getName());

                if(mCameraDefinitionDialog == NULL){
                    mCameraDefinitionDialog = new CameraDefinitionDialog(mPersistenceManager,this,image->getSize());
                }
                if(camera != NULL){
                    if(cameraEXIF.getDeclaredFocal() != 0){
                        camera->setDeclaredFocal(cameraEXIF.getDeclaredFocal());
                    }else{
                        Camera *cameraByLens = mPersistenceManager->readCameraByLens(cameraEXIF.getLensName());
                        if(cameraByLens != NULL){
                            camera->setLensName(cameraByLens->getLensName());
                            camera->setDeclaredFocal(cameraByLens->getDeclaredFocal());
                            delete cameraByLens;
                        }else{
                            mCameraDefinitionDialog->setCamera(&cameraEXIF);
                            if(image->getSize().width()>1 && image->getSize().height()>1)
                                mCameraDefinitionDialog->setAspectRatio((float)image->getSize().width()/(float)image->getSize().height());
                            else
                                mCameraDefinitionDialog->setAspectRatio(0);

                            if (!mCameraDefinitionDialog->exec()) {
                                return;
                            }
                            mPersistenceManager->writeCamera(&cameraEXIF);

                            camera = new Camera();
                            *camera = cameraEXIF; //******************* ¿Asignación miembro a miembro????  Comprobar!!!!!!!!!!!!!!!!
                        }
                    }
                }else{
                    mCameraDefinitionDialog->setCamera(&cameraEXIF);
                    if(image->getSize().width()>1 && image->getSize().height()>1)
                        mCameraDefinitionDialog->setAspectRatio((float)image->getSize().width()/(float)image->getSize().height());
                    else
                        mCameraDefinitionDialog->setAspectRatio(0);

                    if (!mCameraDefinitionDialog->exec()) {
                        return;
                    }

                    mPersistenceManager->writeCamera(&cameraEXIF);

                    camera = new Camera();
                    *camera = cameraEXIF; //******************* ¿Asignación miembro a miembro????  Comprobar!!!!!!!!!!!!!!!!
                }
            }
            mProject->addCamera(camera);
        }



        QVector<QString> currentImagesInProjectFullPath = mProject->getImagesFileName();
        for (int j = 0; j < currentImagesInProjectFullPath.count(); ++j) {
            currentImagesInProjectFullPath[j]=mProject->getBasePath().append("/").append(currentImagesInProjectFullPath[j]);
        }

        QVector<QString> repeatedImagesName;
        mHaveNewImages = false;
        for (int i=0; i<mFileNamesToLoad->count(); i++){
            PWImage* image = new PWImage(mFileNamesToLoad->at(i));
            if (!currentImagesInProjectFullPath.contains(mFileNamesToLoad->at(i))) {
                image->setCamera(camera);
                imagesList.append(image);
                mHaveNewImages=true;
            }else{
                QFileInfo fileInfo(mFileNamesToLoad->at(i));
                QString filename(fileInfo.fileName());
                repeatedImagesName.append(filename);
            }
        }


        if (repeatedImagesName.count()!=0) {
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Repeated images");
            QString repeatedImagesMessage = "The images ";
            for (int var = 0; var < repeatedImagesName.count(); ++var) {
                repeatedImagesMessage.append(repeatedImagesName.at(var));
                if (var!=repeatedImagesName.count()) {
                    repeatedImagesMessage.append(",");
                }
                repeatedImagesMessage.append(" ");

            }
            repeatedImagesMessage.append("already exists on the project.");
            msgBox.setText(repeatedImagesMessage);
            msgBox.exec();
        }


        mProject->addImputImages(imagesList);



        // *********** WRITE LeChantier... *******************//
        QFile chantierBaseFile(":/PW/MICMAC/LocalChantier");
        if (chantierBaseFile.exists()){
            QFile chantierFile(mProject->getBasePath() + "/MicMac-LocalChantierDescripteur.xml");
            chantierFile.remove();
            chantierBaseFile.copy(mProject->getBasePath() + "/MicMac-LocalChantierDescripteur.xml");
            QFile::setPermissions(mProject->getBasePath() + "/MicMac-LocalChantierDescripteur.xml", QFile::ReadOwner | QFile::WriteOwner);

            replace(&chantierFile, &chantierFile,"PW_SENSOR_WIDTH", QString::number(camera->getSensorWidth()));
            replace(&chantierFile, &chantierFile,"PW_SENSOR_HEIGHT", QString::number(camera->getSensorHeight()));
            replace(&chantierFile, &chantierFile,"PW_FOCAL", QString::number(camera->getDeclaredFocal()));
        }

        //Generate the mMapImages OK
        mMapImages = new QMap<QString, QImage>();
        QVector<QString> imageNamesList = mProject->getImagesFileName();
        mFileNamesToLoad->clear();
        for (int i = 0; i < imageNamesList.count(); ++i) {
            QString imageName = mProject->getBasePath()+"/"+imageNamesList[i];
            imageNamesList[i] = imageName;
            mFileNamesToLoad->append(imageName);
        }
        // Start the computation.
        mProgressDialog->setModal(true);
        mProgressDialog->setWindowTitle("Loading Images...");
        mProgressDialog->setStatusText("Loading Images...");
        mProgressDialog->setFinished(false);
        mProgressDialog->show();
        connect(this,SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));

        mImagesLoaderfutureWatcher2 = new QFutureWatcher<QImage>(this);
        connect(mImagesLoaderfutureWatcher2, SIGNAL(resultReadyAt(int)), SLOT(on_addImageToMap(int)));
        connect(mImagesLoaderfutureWatcher2, SIGNAL(finished()), SLOT(on_addImagesFinished()));
        mImagesLoaderfutureWatcher2->setFuture(QtConcurrent::mapped(imageNamesList, scaleIMG));

    }
}

void MainWindowGRAPHOS::on_actionCompute_Tie_Points_triggered()
{
    if (mProject->getTiePointsSets().count()!=0) {
        mBasicUserGUI->setCurrentIndex(1);
        return;
    }
    removePRJ_Files();
    mTiePointsWizard = new TiePointsWizard(this,mProject->getImageByName(mProject->getImagesFileName().first())->getSize(),mProject->getBasePath());
    if (!mTiePointsWizard->exec()) return;

    removePreviousOrientatios();
    mProject->clearTiePointsSets();
    //Preprocessing
    if (mTiePointsWizard->isWallisChecked()) {
        computeWallis();
    }else {
        computeCvDecolor();
    }
}

void MainWindowGRAPHOS::on_actionCompute_Orientations_triggered()
{
    if (!mProject->getSparseModelRelativePath().isEmpty()) {
        mBasicUserGUI->setCurrentIndex(2);
        return;
    }

    computeOrientations();
}

void MainWindowGRAPHOS::on_actionDense_Model_triggered()
{
    if (!mProject->getDenseModelRelativePath().isEmpty()) {
        mBasicUserGUI->setCurrentIndex(3);
        return;
    }

    computeDensification();
}

void MainWindowGRAPHOS::onComputeOrientationFinished()
{
    if(!mComputeOrientationProcess->isStopped()){

        QFileInfo orientationResultFile(mProject->getBasePath()+"/"+mSparseModelPath);
        if (!orientationResultFile.exists()) {mProgressDialog->setRange(0,1);
            mProgressDialog->setValue(1);
            mProgressDialog->setStatusText(tr("Orientation process failed."));
            mProgressDialog->setFinished(true);
            QString consoleOutput=mConsole->toPlainText().toAscii();
            if (consoleOutput.contains("Distortion Inversion by finite difference")) {
                if (mProject->getCurrentOrientation().contains("Fraser")||mProject->getCurrentOrientation().contains("Generic")) {
                    QMessageBox::critical(this,tr("Self-calibration error"),tr("Unable to compute self-calibration.\nPlease try recomputing the orientation process with the \"Basic calibration\" option."));
                }else {
                    QMessageBox::critical(this,tr("Self-calibration error"),tr("Unable to compute self-calibration.\nPlease try recomputing the tie points with a diferent algorithm."));
                }
            }
            return;
        }
        //Remove homol folder;
        QDir homolDir(mProject->getBasePath() + "/Homol");
        if(homolDir.exists())
            removeDir(homolDir.absolutePath());

        //Remove tmpFolder
        QString tmpMMFolder=mProject->getBasePath()+"/"+TAPIOCA_TMP_MM_PATH;
        QDir tmpMMdir(tmpMMFolder);
        if (tmpMMdir.exists()) {
            removeDir(tmpMMdir.absolutePath());
        }

        //Load Sparse model (ply)
        mProject->setSparseModelRelativePath(mSparseModelPath);
        QStringList modelsList;
        modelsList.append(mProject->getSparseModelFullPath());
        mCCVW->addToDB(modelsList);

        //Add orientations to the project.
        if (mProject->readOrientations(mImagesPath + "/Ori-" + mProject->getCurrentOrientation()))
        {
            QMessageBox::critical(this,tr("GRAPHOS error"),tr("Error reading images orientations"));
        }

        // Process metadata:
        mProject->removeProcessMetadata("Model");
        mProject->removeProcessMetadata("Orientation");
        mProject->setProcessMetadataElement("Orientation", "DistortionModel", mOrientationWizard->getOrientationMode());
        if (mOrientationWizard->getOrientationMode().contains("Generic")) {
            QString distortionParameters;
            if (!mOrientationWizard->isFocalParametersChecked()) distortionParameters.append(" f");
            if (!mOrientationWizard->isPrincipalPointParametersChecked()) distortionParameters.append(" x0 y0 ");
            if (!mOrientationWizard->isDistortionCenterParameterschecked()) distortionParameters.append(" x1 y1");
            if (!mOrientationWizard->isDecenteringParametersChecked()) distortionParameters.append(" p1 p2");
            if (!mOrientationWizard->isAffineParametersChecked()) distortionParameters.append(" b1 b2");
            mProject->setProcessMetadataElement("Orientation", "parameters", distortionParameters);
        }

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Orientation and sparse model finished."));
        mProgressDialog->setFinished(true);

        loadProjectMetadataOnProjectTree();
        updateImagesTree();
        loadModelsOnTree();
        updateTools();
        mBasicUserGUI->setCurrentIndex(2);

        setWorkflowWidgetStatus();
        //Save the project
        mPersistenceManager->updateProject(mProject);
    }

    //Remove Apero info files
    QFileInfo mm3dFile(mProject->getBasePath()+"/mm3d-LogFile.txt");
    if (mm3dFile.exists()) {
        QFile::remove(mm3dFile.absoluteFilePath());
    }
    QFileInfo sauvAperoFile(mProject->getBasePath()+"/sauvApero.xml");
    if (sauvAperoFile.exists()) {
        QFile::remove(sauvAperoFile.absoluteFilePath());
    }
    QFileInfo warnAperoFile(mProject->getBasePath()+"/WarnApero.txt");
    if (warnAperoFile.exists()) {
        QFile::remove(warnAperoFile.absoluteFilePath());
    }

    disconnect(mProgressDialog,SIGNAL(cancel()),mComputeOrientationProcess,SLOT(stop()));
}

void MainWindowGRAPHOS::onDenseModelFinished()
{
    if (!mDenseProcess->isStopped()){


        QDir tmpSlaves(mProject->getBasePath()+"/Ori-SlavesTMP");
        if (tmpSlaves.exists()) {
            removeDir(tmpSlaves.absolutePath());
        }
        QDir OriInterneScan(mProject->getBasePath()+"/Ori-InterneScan");
        if (OriInterneScan.exists()) {
            removeDir(OriInterneScan.absolutePath());
        }

        QDir tmpPly(mProject->getBasePath()+"/tmpPly");
        if (tmpPly.exists()) removeDir(tmpPly.absolutePath());

        QFileInfo targetPath(mProject->getBasePath()+"/MicMac.ply");

        if (!targetPath.exists()) {
            mProgressDialog->setRange(0,1);
            mProgressDialog->setValue(1);
            mProgressDialog->setStatusText(tr("MicMac dense matching failed."));
            mProgressDialog->setFinished(true);
            return;
        }
        //Load Dense model (ply)
        mProject->setDenseModelRelativePath(targetPath.fileName());
        QStringList modelsList;
        modelsList.append(mProject->getDenseModelFullPath());
        mCCVW2->addToDB(modelsList);

        // Process metadata:
        ccHObject* obj = mCCVW2->getGLWindow()->getSceneDB()->getFirstChild();
        ccPointCloud *cloud = static_cast<ccPointCloud*>(obj);
        unsigned cloudSize = cloud->size();

        mProject->removeProcessMetadata("Model");
        mProject->setProcessMetadataElement("Model", "CloudSize", QString::number(cloudSize)+" points");
        mProject->setProcessMetadataElement("Model", "Tool", "MICMAC");
        mProject->setProcessMetadataElement("Model", "Type", "Generic");
//        mProject->setProcessMetadataElement("Model", "InputOrientation", getBuildModelDialog()->getOrientation());
//        mProject->setProcessMetadataElement("Model", "MainImage", getBuildModelDialog()->getMainImgName());
//        if(getBuildModelDialog()->useMask())
//            mProject->setProcessMetadataElement("Model", "UseMask", "True");
//        else
//            mProject->setProcessMetadataElement("Model", "UseMask", "False");
//        if(getBuildModelDialog()->useGC())
//            mProject->setProcessMetadataElement("Model", "GC", "True");
//        else
//            mProject->setProcessMetadataElement("Model", "GC", "False");

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Dense model finished."));
        mProgressDialog->setFinished(true);

        mBasicUserGUI->setCurrentIndex(3);
        setWorkflowWidgetStatus();
        loadProjectMetadataOnProjectTree();
        loadModelsOnTree();
        updateTools();
        //Save the project
        mPersistenceManager->updateProject(mProject);
    }
    disconnect(mProgressDialog,SIGNAL(cancel()),mDenseProcess,SLOT(stop()));
}
void MainWindowGRAPHOS::on_actionOpen_Project_triggered()
{
    if(checkToSave() == QMessageBox::Cancel)
        return;

    mOpenProjectDialog->setNameVisible(false);
    mOpenProjectDialog->setForSave(false);
    mOpenProjectDialog->refreshData();
    mToSave = false;
    mOpenProjectDialog->open();
    if (!mOpenProjectDialog->exec()) {
        //Reset the latestProjects panel (some project could be deleted).
        setLatestProjectsLayout();
        return;
    }

    if (mProject->getID()!=0 && PW::LibPW::getCleanProjectAtClossingEvent()) {
        cleanProject();
    }

    mDockProject->setVisible(true);
    mDockWorkflow->setVisible(true);
    mDockThumbs->setVisible(true);
    mQStackedWidget->setStyleSheet("Background-color:transparent;");
    mQStackedWidget->setCurrentIndex(1);
    setWorkflowWidgetStatus();
    mTiePointsDescription=mProject->getActiveTiePointsSet(); //Trabajando solo con un conjunto de tie points posible.
    //Generate the mMapImages OK
    mMapImages = new QMap<QString, QImage>();
    QVector<QString> imageNamesList = mProject->getImagesFileName();
    mFileNamesToLoad = new QStringList();
    for (int i = 0; i < imageNamesList.count(); ++i) {
        mFileNamesToLoad->append(mProject->getBasePath()+"/"+imageNamesList[i]);
        imageNamesList[i]=mProject->getBasePath()+"/"+imageNamesList[i];
    }
    // Start the computation.
    mProgressDialog->setModal(true);
    mProgressDialog->setWindowTitle("Loading Images...");
    mProgressDialog->setStatusText("Loading Images...");
    mProgressDialog->setFinished(false);
    mProgressDialog->show();

    connect(this,SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));

    mImagesLoaderfutureWatcher2 = new QFutureWatcher<QImage>(this);
    connect(mImagesLoaderfutureWatcher2, SIGNAL(resultReadyAt(int)), SLOT(on_addImageToMap(int)));
    connect(mImagesLoaderfutureWatcher2, SIGNAL(finished()), SLOT(on_OpenProject_AddImagesToMapFinished()));
    connect(mProgressDialog,SIGNAL(cancel()),this, SLOT(on_imagesLoading_cancel()));
    mImagesLoaderfutureWatcher2->setFuture(QtConcurrent::mapped(imageNamesList, scaleIMG));
}

void MainWindowGRAPHOS::openLatestProject(QString projectName){


        mToSave=false;
        onProjectSelected(projectName);
        if(mProject->getTiePointsSets().count()!=0){
            mTiePointsDescription=mProject->getActiveTiePointsSet(); //Trabajando solo con un conjunto de tie points posible.
        }
            //Generate the mMapImages OK
            mMapImages = new QMap<QString, QImage>();
            QVector<QString> imageNamesList = mProject->getImagesFileName();
            mFileNamesToLoad = new QStringList();
            for (int i = 0; i < imageNamesList.count(); ++i) {
                mFileNamesToLoad->append(mProject->getBasePath()+"/"+imageNamesList[i]);
                imageNamesList[i]=mProject->getBasePath()+"/"+imageNamesList[i];
            }
            // Start the computation.
            mConsole->clear();
            mProgressDialog->setModal(true);
            mProgressDialog->setWindowTitle("Loading Images...");
            mProgressDialog->setStatusText("Loading Images...");
            mProgressDialog->setFinished(false);
            mProgressDialog->show();

            connect(this,SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));

            mImagesLoaderfutureWatcher2 = new QFutureWatcher<QImage>(this);
            connect(mImagesLoaderfutureWatcher2, SIGNAL(resultReadyAt(int)), SLOT(on_addImageToMap(int)));
            connect(mImagesLoaderfutureWatcher2, SIGNAL(finished()), SLOT(on_OpenProject_AddImagesToMapFinished()));
            connect(mProgressDialog,SIGNAL(cancel()),this, SLOT(on_imagesLoading_cancel()));

            mImagesLoaderfutureWatcher2->setFuture(QtConcurrent::mapped(imageNamesList, scaleIMG));

}

void MainWindowGRAPHOS::on_recomputeTiePointsTriggered(){

//      QMessageBox::StandardButton reply;
//      reply = QMessageBox::question(this, "Caution!", "Current tie points set, orientation and dense matching will be lost.<br>Continue?",
//                                    QMessageBox::Yes|QMessageBox::No);
//      if (reply == QMessageBox::No) {
//        return;
//      }
//      removePreviousOrientatios();

//      //Set new project status
//      mProject->setSparseModelRelativePath("");
//      mProject->setDenseModelRelativePath("");
//      mProject->clearTiePointsSets();
//      mProject->setActiveTiePointsSet("");
//      mProject->removeProcessMetadata("Model");
//      mProject->removeProcessMetadata("Orientation");
//      mProject->removeProcessMetadata("TiePoints");

//      //remove matches folder if was created
//      QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
//      if(MatchesDir.exists())
//          removeDir(MatchesDir.absolutePath());

//      mPersistenceManager->updateProject(mProject);
//      setWorkflowWidgetStatus();
//      mQStackedWidget->setCurrentIndex(1);
//      loadProjectMetadataOnProjectTree();
//      updateImagesTree();
//      updateTools();

      removePRJ_Files();
      mTiePointsWizard = new TiePointsWizard(this,mProject->getImageByName(mProject->getImagesFileName().first())->getSize(),mProject->getBasePath());
      if (!mTiePointsWizard->exec()) return;
            removePreviousOrientatios();

            //Set new project status
            mProject->setSparseModelRelativePath("");
            mProject->setDenseModelRelativePath("");
            mProject->clearTiePointsSets();
            mProject->setActiveTiePointsSet("");
            mProject->removeProcessMetadata("Model");
            mProject->removeProcessMetadata("Orientation");
            mProject->removeProcessMetadata("TiePoints");

            //remove matches folder if was created
            QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
            if(MatchesDir.exists())
                removeDir(MatchesDir.absolutePath());

            mPersistenceManager->updateProject(mProject);
            setWorkflowWidgetStatus();
            mQStackedWidget->setCurrentIndex(1);
            loadProjectMetadataOnProjectTree();
            updateImagesTree();
            updateTools();
      mProject->clearTiePointsSets();

      //preprocessing
      if (mTiePointsWizard->isWallisChecked()) {
          computeWallis();
      }else{
            computeCvDecolor();
      }
}

void MainWindowGRAPHOS::on_recomputeOrientationsTriggered(){

//    QMessageBox::StandardButton reply;
//    reply = QMessageBox::question(this, "Caution!", "Current orientation and dense matching will be lost.<br>Continue?",
//                                  QMessageBox::Yes|QMessageBox::No);
//    if (reply == QMessageBox::No) {
//      return;

//    }

//    if (!mProject->getSparseModelRelativePath().isEmpty()) {
//        mProject->setSparseModelRelativePath("");
//    }if (!mProject->getDenseModelRelativePath().isEmpty()) {
//        mProject->setDenseModelRelativePath("");
//    }
//    mProject->removeProcessMetadata("Model");
//    mProject->removeProcessMetadata("Orientation");

//    mProject->setCurrentOrientation("");
//    mPersistenceManager->updateProject(mProject);
//    loadProjectMetadataOnProjectTree();
//    updateImagesTree();
//    loadModelsOnTree();
//    updateTools();
//    mBasicUserGUI->setCurrentIndex(1);
//    setWorkflowWidgetStatus();

    computeOrientations();
}
void MainWindowGRAPHOS::on_recomputeDensificationTriggered(){


//      QMessageBox::StandardButton reply;
//      reply = QMessageBox::question(this, "Caution!", "Current dense matching will be lost.<br>Continue?",
//                                    QMessageBox::Yes|QMessageBox::No);
//      if (reply == QMessageBox::No) {
//        return;

//      }

//      removePreviousDensifications();

//      if (!mProject->getDenseModelRelativePath().isEmpty()) {
//          mProject->setDenseModelRelativePath("");
//      }

//      mProject->removeProcessMetadata("Model");

//      mPersistenceManager->updateProject(mProject);
//      loadProjectMetadataOnProjectTree();
//      updateImagesTree();
//      loadModelsOnTree();
//      updateTools();
//      mBasicUserGUI->setCurrentIndex(2);
//      setWorkflowWidgetStatus();
      computeDensification();
}

void MainWindowGRAPHOS::on_actionAbout_GRAPHOS_triggered(){
    AboutGraphos *aboutdialog = new AboutGraphos();
    aboutdialog->exec();
}

void MainWindowGRAPHOS::computeTapiocaHomol(QString pairsFileName)
{

    mProject->clearTiePointsSets();
    mTiePointsDescription="tapioca";

    QDir homolDir(mProject->getBasePath() + "/Homol");
    if(homolDir.exists())
        removeDir(homolDir.absolutePath());

    QDir matchesDir(mProject->getBasePath() + "/"+MATCHING_PATH);
    if(matchesDir.exists())
        removeDir(matchesDir.absolutePath());

    QString tapiocaMode;
    int tapiocaSize=0;
    int tapiocaRange=0;
    tapiocaMode = mTiePointsMethod.value("SearchMethod");
    if (tapiocaMode.contains("Line")) {
        tapiocaRange=mTiePointsMethod.value("Range").toInt();
    }
    int tapiocaMulScaleMin=0;
    if (tapiocaMode.contains("MulScale")) {
        tapiocaMulScaleMin=mTiePointsMethod.value("MulScaleMin").toInt();
        tapiocaSize=mTiePointsMethod.value("MulScaleMax").toInt();
    }else {
        tapiocaSize = mTiePointsMethod.value("ResizeValue").toInt();
        if (tapiocaSize==-1) {
            QSize imageSize=mProject->getImageByName(mProject->getImagesFileName().first())->getSize();
            if (imageSize.height()>=imageSize.width()) {
                tapiocaSize = (int)imageSize.height();
            }else {
                tapiocaSize = (int)imageSize.width();
            }
        }
    }
    mTiePointsMetadata="Tapioca;";
    mTiePointsMetadata+=("Mode:"+tapiocaMode+";");
    mTiePointsMetadata+=("Size:"+QString::number(tapiocaSize)+";");
    mTiePointsMetadata+=("Range:"+QString::number(tapiocaRange)+";");
    mTiePointsPath=mProject->getPreProcessingPath()+"/"+MATCHING_PATH+"/"+TAPIOCA_MATCHES_PATH;
    QVector<QString> imagesFileToProcess;
    QMap<QString,QVector<QString> > imagePairs;
    if(!pairsFileName.isEmpty())
    {
        QString pairsTapiocaFileName=mProject->getPreProcessingPath()+"/" + "MesCouples.xml";
        ImagePairsFileIO imagePairsFileIO;
        if(IMAGEPAIRSFILEIO_NO_ERROR!=imagePairsFileIO.readStandarAsciiFile(pairsFileName))
            return;
        if(IMAGEPAIRSFILEIO_NO_ERROR!=imagePairsFileIO.writeTapiocaPairsFile(pairsTapiocaFileName,0))
            return;
        if(IMAGEPAIRSFILEIO_ERROR==imagePairsFileIO.getImagePairs(imagePairs))
        {
            QString title="MainWindow::onComputeTiePointsAcepted";
            QString strError=tr("Error getting Tapioca image pairs from file:\n%1").arg(pairsFileName);
            QMessageBox::critical(this,title,strError);
            return;
        }
        QMap<QString,QVector<QString> >::const_iterator iter=imagePairs.constBegin();
        while(iter!=imagePairs.constEnd())
        {
            QString imageFile=iter.key();
            QVector<QString> imagePairsFile=iter.value();
            if(!imagesFileToProcess.contains(imageFile))
                imagesFileToProcess.push_back(imageFile);
            for(int nFile=0;nFile<imagePairsFile.size();nFile++)
            {
                QString auxFile=imagePairsFile[nFile];
                if(!imagesFileToProcess.contains(auxFile))
                    imagesFileToProcess.push_back(auxFile);
            }
            iter++;
        }
        // Test images on project
        for(int nFile=0;nFile<imagesFileToProcess.size();nFile++)
        {
            QString imageFileInPair=imagesFileToProcess[nFile];
            bool findImage=false;
            for(int i=0;i<mProject->getImages().count();i++)
            {
                QString imageFileInProject = mProject->getImages().at(i)->getFileName();
                if(imageFileInProject.compare(imageFileInPair,Qt::CaseInsensitive)==0)
                {
                    findImage=true;
                    break;
                }
            }
            if(!findImage)
            {
                QString title="MainWindow::onComputeTiePointsAcepted";
                QString strError=tr("Error Tapioca not found in project image %1 from image pairs file:\n%2").arg(imageFileInPair).arg(pairsFileName);
                QMessageBox::critical(this,title,strError);
                return;
            }
        }
    }
    else
    {
        for(int i=0;i< mProject->getImages().count();i++)
        {
            QString imageFileInProject = mProject->getImages().at(i)->getFileName();
            imagesFileToProcess.push_back(imageFileInProject.split(".").at(0)+".tif");

            if(i<(mProject->getImages().count()-1))
            {
                QVector<QString> pairs;
                for(int tt=i+1;tt<mProject->getImages().count();tt++)
                {
                    QString auxImageFileInProject = mProject->getImages().at(tt)->getFileName();
                    pairs.push_back(auxImageFileInProject);
                }
                imagePairs[imageFileInProject]=pairs;
            }
        }
    }

    //Generate Input Regular Expression:
    QString inputRegExp = QString("(");

    for(int i=0; i< imagesFileToProcess.size(); i++)
    {
        inputRegExp = inputRegExp + imagesFileToProcess.at(i) + QString("|");
    }

    inputRegExp.replace(inputRegExp.length()-1,1,")");
    inputRegExp=mProject->getPreProcessingPath()+"/"+inputRegExp;
    if(mTapiocaProcess)
        delete mTapiocaProcess;
    mTapiocaProcess = new TapiocaProcess(inputRegExp, mProject->getPreProcessingPath(), tapiocaMode,tapiocaRange, tapiocaSize,tapiocaMulScaleMin);
    mTapiocaProcess->setWorkingDir(mProject->getPreProcessingPath());

    connect(mTapiocaProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mTapiocaProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mTapiocaProcess, SIGNAL(finished()),this,SLOT(onTapiocaTiePointsFinished()));

    connect(mTapiocaProcess, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mTapiocaProcess,SLOT(stop()));

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle(mTapiocaProcess->getStartupMessage());
    mProgressDialog->setStatusText(mTapiocaProcess->getStartupMessage());
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
    mTapiocaProcess->start();
    qDebug() << QString("");
}

void MainWindowGRAPHOS::computeOrientations(){

//    removePreviousOrientatios();

    bool enableGC = true;
     if(mProject->getModelCPoints()->count()<3)
         enableGC = false;
     else if(mProject->getImages().count()>0){
         QString imagesPath = mProject->getImages().at(0)->getFullPath();
         imagesPath=imagesPath.left(imagesPath.lastIndexOf(QRegExp("/"))+1);
         QString outputName = mProject->getCurrentOrientation();
         if(outputName.isEmpty())
             // TODO: Eliminar. Si no hay, no hay.
             outputName = "PW";
         QDir oriDir(imagesPath+ "Ori-" + outputName);
         if(!oriDir.exists())
             enableGC = false;
     }
      QString projectName=mProject->getName();
        if(!projectName.isEmpty())
        {
            QStringList metadataMatchesCategories,descriptionMatchesCategories,timeCalculationMatchesCategories;
            QVector<bool> validityMatchesCategories;
            mProject->getMatchesCategoriesInformation(metadataMatchesCategories,
                                                      descriptionMatchesCategories,
                                                      timeCalculationMatchesCategories,
                                                      validityMatchesCategories);


            mOrientationWizard = new OrientationWizard(this,mProject->getBasePath());
            if (!mOrientationWizard->exec()) {
                return;
            }

                if (!mProject->getSparseModelRelativePath().isEmpty()) {
                    mProject->setSparseModelRelativePath("");
                }if (!mProject->getDenseModelRelativePath().isEmpty()) {
                    mProject->setDenseModelRelativePath("");
                }
                mProject->removeProcessMetadata("Model");
                mProject->removeProcessMetadata("Orientation");

                mProject->setCurrentOrientation("");
                mPersistenceManager->updateProject(mProject);
                loadProjectMetadataOnProjectTree();
                updateImagesTree();
                loadModelsOnTree();
                updateTools();
                mBasicUserGUI->setCurrentIndex(1);
                setWorkflowWidgetStatus();
            mProject->setDenseModelRelativePath("");

            QString orientationMode = mOrientationWizard->getOrientationMode();
            mProject->setCurrentOrientation(orientationMode);
            this->computeOnlyOrientations(orientationMode);
        }

}

void MainWindowGRAPHOS::computeDensification(){

//    removePreviousDensifications();
    mDensificationWizard = new DensificationWizard(this,mProject,mMapImages,mSettings);
    if (!mDensificationWizard->exec()) {
        return;
    }

          removePreviousDensifications();

          if (!mProject->getDenseModelRelativePath().isEmpty()) {
              mProject->setDenseModelRelativePath("");
          }

          mProject->removeProcessMetadata("Model");

          mPersistenceManager->updateProject(mProject);
          loadProjectMetadataOnProjectTree();
          updateImagesTree();
          loadModelsOnTree();
          updateTools();
          mBasicUserGUI->setCurrentIndex(2);
          setWorkflowWidgetStatus();

    if (mDensificationWizard->isSureSelected()) {

        buildModelSURECustom();
    }else{
        if (mDensificationWizard->getDensificationMode().contains("MicMac master image")) {

            computeMicMacSlaves();
        }else if (mDensificationWizard->getDensificationMode().contains("MicMac object space")) {
            buildMaltModel();

        }else if(mDensificationWizard->getDensificationMode().contains("QuickMac")){
            buildC3DCModel("QuickMac");
        }else if(mDensificationWizard->getDensificationMode().contains("Statue")){
            buildC3DCModel("Statue");
        }else if(mDensificationWizard->getDensificationMode().contains("BigMac")){
            buildC3DCModel("BigMac");
        }else{
            buildModelPMVS();
        }
    }
}

void MainWindowGRAPHOS::setLatestProjectsLayout(){
        //Clear latest projects layout
        QLayoutItem *item;
        while((item = mFrameRecentProjectsLayout->takeAt(0))) {

            if (item->widget()) {
                delete item->widget();
            }
            delete item;
        }

        //draw the layout
         mProjectDescriptors = mPersistenceManager->readProjectsDescriptors();

        QStringList latestProjects;
        mProjectsNames= new QStringList();
        mFrameRecentProjectsLayout->setContentsMargins(0,0,0,0);
        mFrameRecentProjectsLayout->setAlignment(Qt::AlignTop);
        if (mProjectDescriptors.length()!=0) {
            for (int i = mProjectDescriptors.length()-1, counter=0; i >= 0; --i,counter++) {
                if (counter<4) {
                    latestProjects.append(mProjectDescriptors[i].getName());
                }
                mProjectsNames->append(mProjectDescriptors[i].getName());
            }
        }else {
            QLabel *noProjectsLabel = new QLabel("No recent projects.");
            mFrameRecentProjectsLayout->addWidget(noProjectsLabel);
        }
        QSignalMapper* signalMapper = new QSignalMapper (this) ;


        QPushButton *pbLatestProject;

        foreach (QString latestProject, latestProjects) {
            pbLatestProject = new QPushButton(latestProject);
            pbLatestProject->setStyleSheet("background-color:none;");
            mFrameRecentProjectsLayout->addWidget(pbLatestProject);
            connect (pbLatestProject, SIGNAL(clicked()), signalMapper, SLOT(map())) ;
            signalMapper -> setMapping (pbLatestProject, latestProject) ;
        }
        mFrameRecentProjectsLayout->addStretch(1);
        connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(openLatestProject(QString))) ;

}

void MainWindowGRAPHOS::onPMVSFinished()
{
    if (!mPMVSMultiProcess->isStopped()){

        //Load Sparse model (ply)
        QStringList modelsList;

        QFileInfo sourceFilePath(mProject->getBasePath()+"/"+mDenseModelPath);
        QFileInfo targetFilePath(mProject->getBasePath()+"/PMVS.ply");
        QDir().rename(sourceFilePath.absoluteFilePath(),targetFilePath.absoluteFilePath());

        //Load Dense model (ply)
        mProject->setDenseModelRelativePath(targetFilePath.fileName());
        modelsList.clear();
        modelsList.append(mProject->getDenseModelFullPath());
        mCCVW2->addToDB(modelsList);

        // Process metadata:
        ccHObject* obj = mCCVW2->getGLWindow()->getSceneDB()->getFirstChild();
        ccPointCloud *cloud = static_cast<ccPointCloud*>(obj);
        unsigned cloudSize = cloud->size();

        mProject->removeProcessMetadata("Model");
        mProject->setProcessMetadataElement("Model", "CloudSize", QString::number(cloudSize)+" points");
        mProject->setProcessMetadataElement("Model", "Tool", "PMVS");
        mProject->setProcessMetadataElement("Model", "Level", QString::number(mDensificationWizard->getPMVSLevel()));
        mProject->setProcessMetadataElement("Model", "Min", QString::number(mDensificationWizard->getPMVSMin()));
        mProject->setProcessMetadataElement("Model", "CSize", QString::number(mDensificationWizard->getPMVSCSize()));
        mProject->setProcessMetadataElement("Model", "Threshold", QString::number(mDensificationWizard->getPMVSThreshold()));

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Ortho finished."));
        mProgressDialog->setFinished(true);

        mBasicUserGUI->setCurrentIndex(3);

        setWorkflowWidgetStatus();
        loadProjectMetadataOnProjectTree();
        loadModelsOnTree();
        updateTools();
        //Save the project
        mPersistenceManager->updateProject(mProject);
    }
    //Remove drunk folder if exists;
    QDir drunkDir(mProject->getBasePath()+"/DRUNK");
    if (drunkDir.exists()) {
        removeDir(drunkDir.absolutePath());
    }
    QDir tmpDir(mProject->getBasePath()+"/Tmp-MM-Dir");
    if (tmpDir.exists()) {
        removeDir(tmpDir.absolutePath());
    }
    disconnect(mProgressDialog,SIGNAL(cancel()),mPMVSMultiProcess,SLOT(stop()));
}

void MainWindowGRAPHOS::computeWallis(){

    // Eliminar la carpeta preprocessing previa
    QDir postprocessingDir(mProject->getPreProcessingPath());
    if(postprocessingDir.exists())
        removeDir(postprocessingDir.absolutePath());

    while (!postprocessingDir.exists()) {
        QDir().mkdir(postprocessingDir.absolutePath());
    }

    QVector<QString> imageNameList= mProject->getImagesFileName();
    QStringList imagePathList;
    foreach (QString imageName, imageNameList) {
        imagePathList.append(mProject->getBasePath()+"/"+imageName);
    }

    mWallisProcess = new WallisBatchProcess(imagePathList,mProject->getPreProcessingPath(),mTiePointsWizard->getWallisBrithness(),mTiePointsWizard->getWallisContrast(),mTiePointsWizard->getWallisKernell(),127,mTiePointsWizard->getWallisStdDeviation());

    connect(mWallisProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mWallisProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mWallisProcess, SIGNAL(finished()),this,SLOT(onWallisFinished()));

    connect(mWallisProcess, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mWallisProcess,SLOT(stop()));

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle("Wallis filter");
    mProgressDialog->setStatusText("Computing wallis filter...");
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
    mWallisProcess->start();
}

void MainWindowGRAPHOS::computeCvDecolor(){


    // Eliminar la carpeta preprocessing previa
    QDir postprocessingDir(mProject->getPreProcessingPath());
    if(postprocessingDir.exists())
        removeDir(postprocessingDir.absolutePath());

    while (!postprocessingDir.exists()) {
        QDir().mkdir(postprocessingDir.absolutePath());
    }
    QVector<QString> imageNameList= mProject->getImagesFileName();
    QStringList imagePathList;
    mCvDecolorMultiProcess = new MultiProcess(false);
    connect(mCvDecolorMultiProcess,SIGNAL(finished()),this,SLOT(onMultiDecolorFinished()));
    connect(mCvDecolorMultiProcess, SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));
    connect(mCvDecolorMultiProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mCvDecolorMultiProcess,SLOT(stop()));
    mCvDecolorMultiProcess->setSteps(imagePathList.count());
    foreach (QString imageName, imageNameList) {
        cvDecolorProcess *decolorProcess = new cvDecolorProcess(mImagesPath+"/"+imageName,mProject->getPreProcessingPath());
        mCvDecolorMultiProcess->appendProcess(decolorProcess);
    }
    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,mCvDecolorMultiProcess->getSteps());
    mProgressDialog->setWindowTitle("Preprocessing images (decolorization)...");
    mProgressDialog->setStatusText("Preprocessing images (decolorization)...");
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
    mCvDecolorMultiProcess->start();


}
void MainWindowGRAPHOS::onWallisFinished(){

    if (!mWallisProcess->isStopped()) {
            WallisResultViewer *Wviewer = new WallisResultViewer(this,mProject->getPreProcessingPath(),mProject->getImagesFileName());
            if (!Wviewer->exec()) {
                mProgressDialog->close();
                return;
            }
            mTiePointsMethod.clear();
            mTiePointsMethod = mTiePointsWizard->getTiePointsMethod();
            mProject->setCaptureType(mTiePointsWizard->getCaptureConfiguration());

            if (mTiePointsMethod.value("method").contains("Tapioca")) {
                computeTapiocaHomol("");
            }else if (mTiePointsMethod.value("method").contains("MSD+SIFT")) {
                QVector<QString> imgNames = mProject->getImagesFileName();
                QStringList imageNames;
                for (int i = 0; i < imgNames.count(); ++i) {
                    imageNames.append(mProject->getPreProcessingPath().append("/").append(imgNames[i].split(".").first().append(".tif")));
                }
                //remove previous matches
                QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                if(MatchesDir.exists())
                    removeDir(MatchesDir.absolutePath());

                //nos aseguramos de que se crean estas carpetas. ¿¿Alternativa para prevenir Infinite loop??
                while (!MatchesDir.exists()) {
                    QDir().mkdir(MatchesDir.absolutePath());
                }
                QDir msdDir(mProject->getBasePath() +"/"+ MATCHING_PATH+"/MSD");
                while (!msdDir.exists()) {
                    QDir().mkdir(msdDir.absolutePath());
                }

                mTiePointsDescription="MSD";
                mProject->setActiveTiePointsSet("MSD");
                mProgressDialog->writeinConsole("\n\nStarting MSD tiepoints detector ");
                mMsdProcess = new MSDProcess(mProject->getBasePath(),imageNames,mProject->getBasePath()+"/"+MATCHING_PATH,mTiePointsMethod,mTiePointsWizard->isMSDAffineChecked(),mTiePointsWizard->getMSDAffineTilts());
                connect(mMsdProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
                connect(mMsdProcess, SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));
                connect(mMsdProcess, SIGNAL(statusChangedNext()),mProgressDialog,SLOT(onSatutsChangedNext()));
                connect(mMsdProcess,SIGNAL(finished()),this,SLOT(onMSDTiePointsFinished()));
                connect(mProgressDialog,SIGNAL(cancel()),mMsdProcess,SLOT(stop()));

                mProgressDialog->setModal(true);
                int steps = mProject->getImages().count(); //tiepoints detection
                steps=steps*2; //tiepoints description
                for (int i = 1; i < mProject->getImagesFileName().count(); ++i) { //feature matching
                    int matchingSteps = mProject->getImagesFileName().count()-i;
                    steps+=matchingSteps;
                }
                steps+=2; //write matches to apero
                mProgressDialog->setRange(0,steps);
                mProgressDialog->setValue(1);
                mProgressDialog->setWindowTitle("Searching for tie points (MSD)...");
                mProgressDialog->setStatusText("Searching for tie points (MSD)...");
                mProgressDialog->setFinished(false);
                mProgressDialog->show();
                mMsdProcess->start();
            }else if (mTiePointsMethod.value("method").contains("ASIFT")) {
                QVector<QString> imgNames = mProject->getImagesFileName();
                QStringList imageNames;
                for (int i = 0; i < imgNames.count(); ++i) {
                    imageNames.append(mProject->getPreProcessingPath().append("/").append(imgNames[i].split(".").first().append(".tif")));
                }
                //remove previous matches
                QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                if(MatchesDir.exists())
                    removeDir(MatchesDir.absolutePath());

                while (!MatchesDir.exists()) {
                    QDir().mkdir(MatchesDir.absolutePath());
                }
                QDir asiftDir(mProject->getBasePath() +"/"+ MATCHING_PATH+"/ASIFT");
                while (!asiftDir.exists()) {
                       QDir().mkdir(asiftDir.absolutePath());
                }
                if (!mProject->getSparseModelRelativePath().isEmpty()) {
                    mProject->setSparseModelRelativePath("");
                }if (!mProject->getDenseModelRelativePath().isEmpty()) {
                    mProject->setDenseModelRelativePath("");
                }

                mTiePointsDescription="ASIFT";
                mProject->setActiveTiePointsSet("ASIFT");
                mProgressDialog->writeinConsole("\n\nStarting ASIFT tiepoints detector ");
                mASIFTUProcess = new ASIFTUProcess(mProject->getBasePath(),imageNames,mProject->getBasePath()+"/"+MATCHING_PATH,mTiePointsMethod);
                connect(mASIFTUProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
                connect(mASIFTUProcess, SIGNAL(statusChangedNext()),mProgressDialog,SLOT(onSatutsChangedNext()));
                connect(mASIFTUProcess,SIGNAL(finished()),this,SLOT(onASIFTUTiePointsFinished()));
                connect(mProgressDialog,SIGNAL(cancel()),mASIFTUProcess,SLOT(stop()));
                mProgressDialog->setModal(true);
                int steps = mProject->getImages().count(); //tiepoints detection
                steps=steps*2; //tiepoints description
                for (int i = 1; i < mProject->getImagesFileName().count(); ++i) { //feature matching
                    int matchingSteps = mProject->getImagesFileName().count()-i;
                    steps+=matchingSteps;
                }
                steps+=2; //write matches to apero
                mProgressDialog->setRange(0,steps);
                mProgressDialog->setValue(1);
                mProgressDialog->setWindowTitle("Searching for tie points (ASIFT)...");
                mProgressDialog->setStatusText("Searching for tie points (ASIFT)...");
                mProgressDialog->setFinished(false);
                mProgressDialog->show();
                mASIFTUProcess->start();
            }
    }
}

void MainWindowGRAPHOS::onTapiocaTiePointsFinished()
{
    if(!mTapiocaProcess->isStopped())
    {
        //Check results exists;
        QString sourceFolder=mProject->getPreProcessingPath()+"/"+TAPIOCA_MATCHES_ORIGINAL_PATH;
        QDir sourceDir(sourceFolder);
        if (!sourceDir.exists()) {
            mProgressDialog->setRange(0,1);
            mProgressDialog->setValue(1);
            mProgressDialog->setStatusText(tr("Tapioca tie points process failed."));
            mProgressDialog->setFinished(true);
            return;
        }


        QString strEngine="Tapioca-MicMac";// getTiePointsDialog()->getEngine();
        QString pairsFileName ="tapioca";
        bool isFileMode=false;
        if(!pairsFileName.isEmpty())
        {
            isFileMode=true;
        }
        // Process metadata:
        QString tapiocaMode;
        int tapiocaSize = 0;
        int tapiocaRange =0;

        tapiocaMode = mTiePointsMethod.value("SearchMethod");
        if (tapiocaMode.compare("Line")) {
            tapiocaRange=mTiePointsMethod.value("Range").toInt();
        }

        tapiocaSize = mTiePointsMethod.value("ResizeValue").toInt();

        mProject->removeProcessMetadata("Model");
        mProject->removeProcessMetadata("Orientation");
        mProject->removeProcessMetadata("TiePoints");
        if (mTiePointsWizard->isWallisChecked()) {
            mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Wallisfilter");
            mProject->setProcessMetadataElement("TiePoints", "WallisContrast", QString::number(mTiePointsWizard->getWallisContrast()));
            mProject->setProcessMetadataElement("TiePoints", "WallisBrightness", QString::number(mTiePointsWizard->getWallisBrithness()));
            mProject->setProcessMetadataElement("TiePoints", "WallisStdDev", QString::number(mTiePointsWizard->getWallisStdDeviation()));
            mProject->setProcessMetadataElement("TiePoints", "WallisKernelSize", QString::number(mTiePointsWizard->getWallisKernell()));
        }else {
            mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Contrast preserving decolorization");
        }

        mProject->setProcessMetadataElement("TiePoints", "Tool", "Tapioca");
        mProject->setProcessMetadataElement("TiePoints", "SearchMode", mTiePointsMethod.value("SearchMethod") );

        if(mTiePointsMethod.value("SearchMethod").compare("Line",Qt::CaseInsensitive)==0){
            mProject->setProcessMetadataElement("TiePoints", "Range", mTiePointsMethod.value("Range"));
            mProject->setProcessMetadataElement("TiePoints", "Size", mTiePointsMethod.value("ResizeValue"));
        }else if (mTiePointsMethod.value("SearchMethod").compare("MulScale",Qt::CaseInsensitive)==0) {
            mProject->setProcessMetadataElement("TiePoints", "MulScaleMax", mTiePointsMethod.value("MulScaleMax"));
            mProject->setProcessMetadataElement("TiePoints", "MulScaleMin", mTiePointsMethod.value("MulScaleMin"));
        }else {
            mProject->setProcessMetadataElement("TiePoints", "Size", mTiePointsMethod.value("ResizeValue"));
        }

        // Mover las carpetas
        QString matchesFolder=mProject->getBasePath()+"/"+MATCHING_PATH;
        QDir matchesDir(matchesFolder);

        // Eliminar las carpetas matches previos
        if(matchesDir.exists())
            removeDir(matchesDir.absolutePath());

        if(!matchesDir.exists())
        {
            if(!QDir().mkdir(matchesDir.absolutePath()))
            {
                QString title="MainWindow::onTiePointsFinished";
                QString strError=tr("Error making directory:\n %1").arg(matchesFolder);
                QMessageBox::critical(this,title,strError);
                return;
            }
        }
        QString targetFolder=mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription;
        QDir targetDir(targetFolder);
        if (!targetDir.exists()) {
            QDir().mkdir(targetDir.absolutePath());
        }

        if(!copyDir(sourceDir.absolutePath(),targetDir.absolutePath()))
        {
            QString title="MainWindow::onTiePointsFinished";
            QString strError=tr("Error moving Tapioca matching files");
            QMessageBox::critical(this,title,strError);
            return;
        }

        //Remove image conections under minimum matchings limit
        int minimumTapiocaMatches = mTiePointsWizard->getMinimumTapiocaMatches();

        QFileInfoList files = targetDir.entryInfoList(QDir::NoDotAndDotDot | QDir::AllDirs);
        foreach (QFileInfo file, files){
            if (file.isDir()){
                QDir pastisDir(file.absoluteFilePath());
                QFileInfoList matchesFiles = pastisDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
                foreach (QFileInfo matchesFileInfo, matchesFiles){
                    if (!matchesFileInfo.isDir()){
                        //Read the lines and remove the file if nLines<minimumTapiocaMatches
                        int points=0;
                        QFile matchesFile(matchesFileInfo.absoluteFilePath());
                        if (matchesFile.open(QIODevice::ReadOnly))
                        {
                           QTextStream in(&matchesFile);
                           while (!in.atEnd())
                           {
                                in.readLine();
                                points++;
                                if (points>=minimumTapiocaMatches) {
                                    matchesFile.close();
                                    break;
                                }
                           }
                           if (points<minimumTapiocaMatches) {
                               matchesFile.remove();
                           }
                        }
                    }
                }
            }
        }

        QString pastisFolder=mProject->getPreProcessingPath()+"/"+TAPIOCA_PASTIS_PATH;
        QDir pastisDir(pastisFolder);
        if(!removeDir(pastisDir.absolutePath()))
        {
            QString title="MainWindow::onTiePointsFinished";
            QString strError=tr("Error removing Tapioca pastis folder:\n%1").arg(pastisFolder);
            QMessageBox::critical(this,title,strError);
            return;
        }
        QString tmpMMFolder=mProject->getPreProcessingPath()+"/"+TAPIOCA_TMP_MM_PATH;
        QDir tmpMMDir(tmpMMFolder);
        if(!removeDir(tmpMMDir.absolutePath()))
        {
            QString title="MainWindow::onTiePointsFinished";
            QString strError=tr("Error removing Tapioca tmp-MM folder:\n%1").arg(tmpMMFolder);
            QMessageBox::critical(this,title,strError);
            return;
        }

        mProject->setMatchingFormat(MATCHING_FORMAT_APERO_TXT);
        mProject->appendTiePointsSet(mTiePointsDescription);
        mProject->setNeedToSave(true);

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Compute tie points finished."));
        mProgressDialog->setFinished(true);


        QDateTime dateTime=QDateTime::currentDateTime();
        QString timeCalculation=dateTime.toString(LIBPW_DATETIME_STRING_FORMAT);

        PWMatchesCategory * category = new PWMatchesCategory(mProject,
                              0,
                              mTiePointsDescription,
                              mTiePointsMetadata,
                              timeCalculation);

        QMap<QString, QVector<QString> > imagePairs;
        TapiocaIO tapiocaIO;

        QDir matchingsDir(mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription);
        tapiocaIO.readImagePairs(matchingsDir.absolutePath(), imagePairs);
        PWGraphImages* graphImages=new PWGraphImages();
            QVector<QString> wallisImageNames = mProject->getImagesFileName();
            for (int i = 0; i < wallisImageNames.count(); ++i) {
                wallisImageNames[i]=wallisImageNames[i].split(".").at(0)+".tif";
            }
            if(!graphImages->createGraph(wallisImageNames,
                                          imagePairs))
             {
                 //TODO: graphIsConnected=false; ¿Que hacer?
             }


        category->setGraphImages(graphImages);
        category->setImagePairs(imagePairs);

        mProject->insertMatchesCategory(category); //Comprobar categorie
        mProject->setActiveTiePointsSet(mTiePointsDescription);
        //Rename folders and files
        if (!QFileInfo(mProject->getImagesFileName().first()).suffix().contains("tif")) {

            QString matchesDirPath = mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription;
            QDir *matchesDir = new QDir(matchesDirPath);
            QFileInfoList infoList = matchesDir->entryInfoList();
            for (int j = 2; j < infoList.count(); ++j) {
                QString subfolderName = infoList[j].absoluteFilePath();
                subfolderName =subfolderName.split(".").at(0)+"."+mProject->getImagesFileName().at(0).split(".").at(1);
                copyDir(infoList[j].absoluteFilePath(),subfolderName);
                removeDir(infoList[j].absoluteFilePath());
                QDir *pastirDir = new QDir(subfolderName);
                QFileInfoList infoPastisList = pastirDir->entryInfoList();
                for (int k = 2; k < infoPastisList.count(); ++k) {
                    QString pastisFileName = infoPastisList[k].absoluteFilePath();
                    pastisFileName =pastisFileName.split(".tif.txt").at(0)+"."+mProject->getImagesFileName().at(0).split(".").at(1)+".txt";
                    QFile::rename(infoPastisList[k].absoluteFilePath(), pastisFileName);
                }
            }
        }

        if(!mProject->isValidMatchedCategory(mTiePointsMetadata) || !TIEPOINTS_VALIDATE_SETS){
            QString title;
            QStringList subgraphs;
            mProject->getInvalidMatchedCategoryExplanationByDescription(mTiePointsDescription,title, subgraphs);
            QString originalImageExtension= mProject->getImagesFileName().first().split(".").last();
            QList<QStringList> *subGraphsList = new QList<QStringList>();
            subGraphsList->clear();
            QStringList subgraph;
            subgraph.clear();
            for (int i = 0; i < subgraphs.count(); ++i) {

                //Parse subgraph and add items
                QStringList subgraphItems = subgraphs.at(i).split("}_-_{");
                if (subgraphItems.count()>3) {
                    subgraph.clear();
                    for (int j = 0; j < subgraphItems.count()-1; ++j) {
                        subgraph.append(subgraphItems[j].replace("tif",originalImageExtension));
                    }
                    subGraphsList->append(subgraph);
                }

           }
            if (subGraphsList->count()!=0) {
                SubgraphSelector *subgraphSelector = new SubgraphSelector(this,subGraphsList,mProject);
                if (!subgraphSelector->exec()) {
                    mProject->clearTiePointsSets();
                    mProject->setActiveTiePointsSet("");
                    mPersistenceManager->updateProject(mProject);
                    //remove matches folder if was created
                    QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                    if(MatchesDir.exists())
                        removeDir(MatchesDir.absolutePath());
                    return;
                }
                QStringList subgraphToProcess =subGraphsList->at(subgraphSelector->getSubgraphIndex());
                QStringList imageNamesToRemove;
                QList<int> imageIDsToRemove;
                foreach (PWImage *image, mProject->getImages()) {
                    QFileInfo projectImage(image->getFullPath());
                    if (!subgraphToProcess.contains(projectImage.fileName())) {
                        imageIDsToRemove.append(image->getID());
                        imageNamesToRemove.append(image->getFileName());
                    }
                }
                if (imageIDsToRemove.count()>0) {
                    mProject->removeImagesByName(imageNamesToRemove);
                    mPersistenceManager->deleteMatches(imageIDsToRemove);
                    if(!mProject->getImages().count()){
                        mProject->clearTiePointsSets();
                        mProject->setActiveTiePointsSet("");
                    }
                    emit projectChanged();
                    updateTools();
                    foreach (QString imageToRemovePastis, imageNamesToRemove) {
                        QDir pastisfolderToRemove(mProject->getBasePath()+"/Matches/tapioca/Pastis"+imageToRemovePastis);
                        if(pastisfolderToRemove.exists())
                            removeDir(pastisfolderToRemove.absolutePath());
                    }
                }

                //search ImagePairs again
                imagePairs.clear();
                tapiocaIO.readImagePairs(mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription, imagePairs);
                PWGraphImages* graphImages=new PWGraphImages();
                    QVector<QString> wallisImageNames = mProject->getImagesFileName();
                    for (int i = 0; i < wallisImageNames.count(); ++i) {
                        wallisImageNames[i]=wallisImageNames[i].split(".").at(0)+".tif";
                    }
                    if(!graphImages->createGraph(wallisImageNames,
                                                  imagePairs))
                     {
                         //TODO: graphIsConnected=false; ¿Que hacer?
                     }
                category->setGraphImages(graphImages);
                category->setImagePairs(imagePairs);

                mProject->insertMatchesCategory(category); //Comprobar categorie
                mProject->setActiveTiePointsSet(mTiePointsDescription);
            }else {
                QMessageBox msg(this);
                msg.setWindowTitle("Warning!");
                msg.setText("Not valid subgraph");
                msg.exec();
                mProject->clearTiePointsSets();
                mProject->setActiveTiePointsSet("");
                mPersistenceManager->updateProject(mProject);
                //remove matches folder if was created
                QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                if(MatchesDir.exists())
                    removeDir(MatchesDir.absolutePath());
                return;
            }

        }
        //tie point results;
        drawTiePointsInfoView(imagePairs);

        //Save the project
        mPersistenceManager->updateProject(mProject);
    }else {
        //remove matches folder if was created
        QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
        if(MatchesDir.exists())
            removeDir(MatchesDir.absolutePath());
    }

    setWorkflowWidgetStatus();
    mQStackedWidget->setCurrentIndex(1);
    loadProjectMetadataOnProjectTree();
    updateImagesTree();
    updateTools();

    disconnect(mProgressDialog,SIGNAL(cancel()),mTapiocaProcess,SLOT(stop()));
}



void MainWindowGRAPHOS::computeOnlyOrientations(QString calibrationModel)
{

    mProject->setCurrentOrientation(calibrationModel);
    if (mProject->getCurrentOrientation().isEmpty())
        mProject->setCurrentOrientation("PW");

    QString homolPath= mProject->getBasePath() + "/" + "Homol";
    QDir homolDir(homolPath);
    removeDir(homolDir.absolutePath());
    //Copy "Homol" to project directory:
    if(!homolDir.exists())
    {
        if(!homolDir.mkdir(homolDir.absolutePath()))
        {
            QMessageBox::critical(this,tr("GRAPHOS - Error"),tr("Error making homol dir"));
            return;
        }
    }
    QString sourceFolder=mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mProject->getActiveTiePointsSet();

    QString targetFolder=mProject->getBasePath()+"/"+TAPIOCA_MATCHES_ORIGINAL_PATH;
    QDir souceDir(sourceFolder);
    QDir targetDir(targetFolder);
    while (!targetDir.exists()) {
        QDir().mkdir(targetDir.absolutePath());
    }

    if(!copyDir(souceDir.absolutePath(),targetDir.absolutePath(),false))
    {
        QString title="MainWindow::onTiePointsFinished";
        QString strError=tr("Error moving matching files to Homol");
        QMessageBox::critical(this,title,strError);
        return;
    }


    if(mComputeOrientationProcess)
        delete mComputeOrientationProcess;
    mComputeOrientationProcess = new MultiProcess();
    mComputeOrientationProcess->setStartupMessage("Computing orientations...");

    QString inputRegExp = QString("(");

    TapasProcess *tapasProcess = new TapasProcess();
    tapasProcess->setWorkingDir(mImagesPath);

    QString distModel = calibrationModel;
    QStringList tapasInputs;

    //Generate Input Regular Expression:
    for(int i=0; i< mProject->getImages().count(); i++){
        inputRegExp = inputRegExp + mProject->getImages().at(i)->getFileName() + QString("|");
    }
    inputRegExp.replace(inputRegExp.length()-1,1,")");
    inputRegExp=mImagesPath+"/"+inputRegExp;

    if (distModel.contains("Generic")) {
        distModel = "Fraser";
        tapasInputs <<distModel<<inputRegExp<<"Out="+mProject->getCurrentOrientation();
        if (!mOrientationWizard->isAffineParametersChecked()) tapasInputs << "LibAff=false";
        if (!mOrientationWizard->isDecenteringParametersChecked()) tapasInputs << "LibDec=false";
        if (!mOrientationWizard->isDistortionCenterParameterschecked()) tapasInputs << "LibCP=false";
        if (!mOrientationWizard->isFocalParametersChecked()) tapasInputs << "LibFoc=false";
        if (!mOrientationWizard->isPrincipalPointParametersChecked()) tapasInputs << "LibPP=false";

    }else {
        tapasInputs <<distModel<<inputRegExp<<"Out="+mProject->getCurrentOrientation();
    }

    if(isTiePointsTxt(mProject->getBasePath()))
        tapasInputs << "ExpTxt=1";

    tapasProcess->addIntputs(tapasInputs);

    mComputeOrientationProcess->appendProcess(tapasProcess);


    AperiCloudProcess *aperiCloudProcess = new AperiCloudProcess();
    aperiCloudProcess->setWorkingDir(mProject->getBasePath());
    QStringList aperiCloudInputs;
    aperiCloudInputs <<inputRegExp<<mProject->getCurrentOrientation() <<
                       "Out="+mProject->getCurrentOrientation()+".ply";
    if(isTiePointsTxt(mProject->getBasePath()))
        aperiCloudInputs << "ExpTxt=1";
    aperiCloudProcess->addIntputs(aperiCloudInputs);
    mComputeOrientationProcess->appendProcess(aperiCloudProcess);

    connect(mComputeOrientationProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mComputeOrientationProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mComputeOrientationProcess, SIGNAL(finished()),this,SLOT(onComputeOrientationFinished()));
    connect(mComputeOrientationProcess, SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));
    mSparseModelPath = mProject->getCurrentOrientation()+".ply";
    connect(mComputeOrientationProcess, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mComputeOrientationProcess,SLOT(stop()));

    mSparseStopped = false;
    mComputeOrientationProcess->start();

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle(mComputeOrientationProcess->getStartupMessage());
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
}

void MainWindowGRAPHOS::drawTiePointsInfoView(QMap<QString, QVector<QString> > &imagesPairs){
    //remove the items of the layout
    if ( mTiePointsInfoView->layout() != NULL )
    {
        QLayoutItem* item;
        while ( ( item = mTiePointsInfoView->layout()->takeAt( 0 ) ) != NULL )
        {
            delete item->widget();
            delete item;
        }
        delete mTiePointsInfoView->layout();
    }

    //RenameImagePairs to original image extension if preprocesing methods were used.
    QVector<QString> ImageNamesList=mProject->getImagesFileName();
    QString originalImageExtension= ImageNamesList.at(0).split(".").last();
    QString preprocesedImageExtension = imagesPairs.keys().first().split(".").last();

    QScrollArea *scrollArea = new QScrollArea();
    scrollArea->setWidgetResizable(true);
    QWidget *mainFrame = new QWidget();
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);
    for (int i = 0; i < imagesPairs.keys().count(); ++i) {
        QFrame *connectionFrame = new QFrame();
        connectionFrame->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
        if (originalImageExtension.contains(preprocesedImageExtension)) {
            connectionFrame->setFixedHeight(mMapImages->value(imagesPairs.keys().at(i)).size().height()+60);

        }else {
            connectionFrame->setFixedHeight(mMapImages->value(imagesPairs.keys()[i].replace(preprocesedImageExtension,originalImageExtension)).size().height()+60);
        }
        QHBoxLayout *connectionFrameLayout = new QHBoxLayout();
        connectionFrameLayout->setContentsMargins(0,0,0,0);
        connectionFrameLayout->setAlignment(Qt::AlignLeft);
        QFrame *evaluatedImageFrame = new QFrame();
        QVBoxLayout *evaluatedImageFrameLayout = new QVBoxLayout();
        evaluatedImageFrameLayout->setContentsMargins(0,0,0,0);
        evaluatedImageFrameLayout->addWidget(new QLabel("Image:"));
        QListWidget *Image = new QListWidget();
        Image->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        Image->setStyleSheet("border: 0px;");
        Image->setViewMode(QListWidget::IconMode );
        Image->setIconSize(QSize(100,100));
        Image->setResizeMode(QListWidget::Adjust);
        QListWidgetItem *listItem;

        QString listItemWhatsThisFirstImage;
        if (originalImageExtension.contains(preprocesedImageExtension)) {
            listItem = new QListWidgetItem(QIcon(QPixmap::fromImage(mMapImages->value(imagesPairs.keys().at(i)))),imagesPairs.keys().at(i).mid(imagesPairs.keys().at(i).length()-15));
            evaluatedImageFrame->setFixedWidth(mMapImages->value(imagesPairs.keys().at(i)).size().width()+10);
            listItemWhatsThisFirstImage.append(imagesPairs.keys().at(i));
        }else {
            listItem = new QListWidgetItem(QIcon(QPixmap::fromImage(mMapImages->value(imagesPairs.keys()[i].replace(preprocesedImageExtension,originalImageExtension)))),imagesPairs.keys()[i].mid(imagesPairs.keys().at(i).length()-15).replace(preprocesedImageExtension,originalImageExtension));
            evaluatedImageFrame->setFixedWidth(mMapImages->value(imagesPairs.keys()[i].replace(preprocesedImageExtension,originalImageExtension)).size().width()+10);
            listItemWhatsThisFirstImage.append(imagesPairs.keys()[i].replace(preprocesedImageExtension,originalImageExtension));
        }

        listItemWhatsThisFirstImage.append("} , {");
        listItem->setFlags(Qt::ItemIsEnabled);
        Image->addItem(listItem);
        evaluatedImageFrameLayout->addWidget(Image);
        evaluatedImageFrame->setLayout(evaluatedImageFrameLayout);

        QFrame *connectedImagesFrame = new QFrame();
        connectedImagesFrame->setSizePolicy(QSizePolicy ::Expanding , QSizePolicy ::Expanding );
        QVBoxLayout *connectedImagesFrameLayout = new QVBoxLayout();
        connectedImagesFrameLayout->setContentsMargins(0,0,0,0);
        connectedImagesFrameLayout->addWidget(new QLabel("Connected with images:"));

        QListWidget *connectedWithImagesList = new QListWidget();
        connect(connectedWithImagesList,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(onImagesConnectionDoubleClicked(QListWidgetItem*)));
        connectedWithImagesList->setStyleSheet("border: 0px;");
        connectedWithImagesList->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        connectedWithImagesList->setWrapping(false);
        connectedWithImagesList->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        connectedWithImagesList->setViewMode(QListWidget::IconMode );
        connectedWithImagesList->setIconSize(QSize(100,100));
        connectedWithImagesList->setResizeMode(QListWidget::Adjust);
        QVector<QString> connectedImages = imagesPairs[imagesPairs.keys().at(i)];
        for (int j = 0; j < connectedImages.count(); ++j) {
            QListWidgetItem *listItem;
            QString listItemWhatsThisFull = listItemWhatsThisFirstImage;
            if (originalImageExtension.contains(preprocesedImageExtension)) {
                listItem = new QListWidgetItem(QIcon(QPixmap::fromImage(mMapImages->value(connectedImages.at(j)))),connectedImages.at(j).mid(connectedImages.at(j).length()-15));
                listItemWhatsThisFull.append(connectedImages.at(j));
            }else {
                listItem = new QListWidgetItem(QIcon(QPixmap::fromImage(mMapImages->value(connectedImages[j].replace(preprocesedImageExtension,originalImageExtension)))),connectedImages[j].mid(connectedImages.at(j).length()-15).replace(preprocesedImageExtension,originalImageExtension));
                listItemWhatsThisFull.append(connectedImages[j].replace(preprocesedImageExtension,originalImageExtension));
            }
            listItem->setWhatsThis(listItemWhatsThisFull);
            listItemWhatsThisFull.clear();
            listItem->setFlags(Qt::ItemIsEnabled);
            connectedWithImagesList->addItem(listItem);
        }

        connectedImagesFrameLayout->addWidget(connectedWithImagesList);
        connectedImagesFrame->setLayout(connectedImagesFrameLayout);
        connectionFrameLayout->addWidget(evaluatedImageFrame);
        connectionFrameLayout->addWidget(connectedImagesFrame);
        connectionFrame->setLayout(connectionFrameLayout);
        mainLayout->addWidget(connectionFrame);
    }

    mainLayout->addStretch();
    mainFrame->setLayout(mainLayout);
    scrollArea->setWidget(mainFrame);
    QVBoxLayout *auxLayout = new QVBoxLayout();
    auxLayout->setContentsMargins(1,1,1,0);
    auxLayout->addWidget(scrollArea);
    mTiePointsInfoView->setLayout(auxLayout);

}

int MainWindowGRAPHOS::addImageThumnailToMap(QVector<QString> imagesList){

    int numLoaded =0;

    QSize desiredSize(100,100);
    mProgressDialog->setRange(0,imagesList.count());
    foreach (QString img, imagesList) {
        if (QFileInfo(mProject->getBasePath()+"/"+img).exists()) {

            QImage orig(mProject->getBasePath()+"/"+img);
            QImage scaled = orig.scaled(
                        desiredSize,
                        Qt::KeepAspectRatio,
                        Qt::SmoothTransformation);

            mMapImages->insert(img,scaled);
            numLoaded++;
            QString consoleMessage = "Image "+img.toAscii()+" loaded." ;
            mProgressDialog->writeinConsole(consoleMessage);
            emit statusChanged(numLoaded, "Loading images...");
        }
    }
    return numLoaded;
}


void MainWindowGRAPHOS::on_imageLoadingOfExistingProjectFinished(){
    if (mProject->getTiePointsSets().count()!=0) {
        QDateTime dateTime=QDateTime::currentDateTime();
        QString timeCalculation=dateTime.toString(LIBPW_DATETIME_STRING_FORMAT);
        PWMatchesCategory * category = new PWMatchesCategory(mProject,
                              0,
                              mTiePointsDescription,
                              mTiePointsMetadata,
                              timeCalculation);


            QMap<QString, QVector<QString> > imagePairs;
            TapiocaIO tapiocaIO;
            tapiocaIO.readImagePairs(mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription, imagePairs);
            if (imagePairs.count()!=0) {
                drawTiePointsInfoView(imagePairs);
            }else {
                mProject->clearTiePointsSets();
            }

    }
    if (!mProject->getSparseModelFullPath().isEmpty()) {
        QFileInfo sparseModelPath(mProject->getSparseModelFullPath());
        if (!sparseModelPath.exists()) {
            mProject->setSparseModelRelativePath("");
            mProject->setDenseModelRelativePath("");

        }
    }
    if (!mProject->getDenseModelFullPath().isEmpty()) {
        QFileInfo denseModelPath(mProject->getDenseModelFullPath());
        if (!denseModelPath.exists()) {
            mProject->setDenseModelRelativePath("");
        }
    }
    mProgressDialog->close();
    mDockProject->setVisible(true);
    mDockWorkflow->setVisible(true);
    mDockThumbs->setVisible(true);
    mQStackedWidget->setStyleSheet("Background-color:transparent;");
    mQStackedWidget->setCurrentIndex(1);
    setWorkflowWidgetStatus();
    mPersistenceManager->updateProject(mProject);

}

void MainWindowGRAPHOS::on_imagesLoading_cancel(){
    mImagesLoaderfutureWatcher2->cancel();
    mProgressDialog->close();
}


void MainWindowGRAPHOS::onSureFinished(){
    if (!mCustomSureProcess->isStopped()) {

        //Merge sure output .las files
        QString SureLasPath = mProject->getBasePath()+"/SURE/3D_Points";
        QDir *SureLasDir = new QDir(SureLasPath);
        QFileInfoList infoList = SureLasDir->entryInfoList();

        QStringList sureCloudsToMerge;
        for (int j = 0; j < infoList.count(); ++j) {
            if (infoList.at(j).suffix().contains("las")) {
                sureCloudsToMerge.append(infoList[j].absoluteFilePath());
            }
        }
        if (sureCloudsToMerge.count()==0) {                QMessageBox msg(this);
            msg.setWindowTitle("Warning!");
            msg.setText("Unsuccessful dense matching process");
            msg.exec();
            return;
        }
        QString mergedLasFilePath =mProject->getBasePath()+"/SURE.las";
        if(mMergeLasResultsProcess)
            delete mMergeLasResultsProcess;
        mMergeLasResultsProcess = new MergeLasResultsProcess(sureCloudsToMerge,mergedLasFilePath);
        connect(mMergeLasResultsProcess, SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));
        connect(mMergeLasResultsProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
        connect(mMergeLasResultsProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
        connect(mMergeLasResultsProcess, SIGNAL(finished()),this,SLOT(onLasmergeFinished()));

        connect(mMergeLasResultsProcess, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
        connect(mProgressDialog,SIGNAL(cancel()),mMergeLasResultsProcess,SLOT(stop()));

        mProgressDialog->setModal(true);
        mProgressDialog->setRange(0,0);
        mProgressDialog->setValue(0);
        mProgressDialog->setWindowTitle(mMergeLasResultsProcess->getStartupMessage());
        mProgressDialog->setStatusText(mMergeLasResultsProcess->getStartupMessage());
        mProgressDialog->setFinished(false);
        mProgressDialog->show();

        mMergeLasResultsProcess->start();
    }
}

void MainWindowGRAPHOS::on_addImageToMap(int num)
{
    QSize desiredSize(100,100);
    mProgressDialog->setRange(0,mFileNamesToLoad->count());

        if (QFileInfo(mProject->getBasePath()+"/"+mFileNamesToLoad->at(num).split("/").last()).exists()) {
            mMapImages->insert(mFileNamesToLoad->at(num).split("/").last(),mImagesLoaderfutureWatcher2->resultAt(num));
            QString consoleMessage = "Image "+mFileNamesToLoad->at(num).split("/").last().toAscii()+" loaded.";
            mProgressDialog->writeinConsole(consoleMessage);
            emit statusChanged(num, "Loading images...");
        }

}


void MainWindowGRAPHOS::on_addImagesFinished()
{
    mProgressDialog->close();
    emit projectChanged();

    mPbAddImages->setVisible(true);
    updateTools();
    mPersistenceManager->updateProject(mProject);

}

void MainWindowGRAPHOS::on_OpenProject_AddImagesToMapFinished(){
        if (mProject->getTiePointsSets().count()!=0) {
            QDateTime dateTime=QDateTime::currentDateTime();
            QString timeCalculation=dateTime.toString(LIBPW_DATETIME_STRING_FORMAT);

            PWMatchesCategory * category = new PWMatchesCategory(mProject,
                                  0,
                                  mTiePointsDescription,
                                  mTiePointsMetadata,
                                  timeCalculation);

                QMap<QString, QVector<QString> > imagePairs;
                TapiocaIO tapiocaIO;
                tapiocaIO.readImagePairs(mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription, imagePairs);
                if (imagePairs.count()!=0) {
                    drawTiePointsInfoView(imagePairs);
                }else {
                    mProject->clearTiePointsSets();
                }

        }
        if (!mProject->getSparseModelFullPath().isEmpty()) {
            QFileInfo sparseModelPath(mProject->getSparseModelFullPath());
            if (!sparseModelPath.exists()) {
                mProject->setSparseModelRelativePath("");
                mProject->setDenseModelRelativePath("");
            }
        }
        if (!mProject->getDenseModelFullPath().isEmpty()) {
            QFileInfo denseModelPath(mProject->getDenseModelFullPath());
            if (!denseModelPath.exists()) {
                mProject->setDenseModelRelativePath("");
            }
        }
        mProgressDialog->close();
        mDockProject->setVisible(true);
        mDockWorkflow->setVisible(true);
        mDockThumbs->setVisible(true);
        mQStackedWidget->setStyleSheet("Background-color:transparent;");
        mQStackedWidget->setCurrentIndex(1);
        setWorkflowWidgetStatus();
        mPersistenceManager->updateProject(mProject);
        updateTools();
}

void MainWindowGRAPHOS::buildModelPMVS()
{
    if(mProject->getImages().count() > 0){

        //Generate Input Regular Expression:
        QString inputRegExp = QString("(");
        QString fileName;
        for(int i=0; i< mProject->getImages().count(); i++){
            fileName = mProject->getImages().at(i)->getFullPath();
            fileName = fileName.right(fileName.length()-fileName.lastIndexOf(QRegExp("/"))-1);
            inputRegExp = inputRegExp + fileName + QString("|");
        }
        inputRegExp.replace(inputRegExp.length()-1,1,")");
        QString fullInputRegExp = mImagesPath+"/"+inputRegExp;

        if(mApero2PMVSProcess)
            delete mApero2PMVSProcess;
        mApero2PMVSProcess = new PW::Apero2pmvs(fullInputRegExp, mProject->getCurrentOrientation());
        mApero2PMVSProcess->setWorkingDir(mImagesPath);
        if(mPMVSProcess)
            delete mPMVSProcess;
        QString pmvsDir = mProject->getBasePath()+"/pmvs-"+mProject->getCurrentOrientation() + "/";

        //****pmvs options: *******************

        QMap<QString, QString> options;
        options.insert("level",QString::number(mDensificationWizard->getPMVSLevel()));
        options.insert("csize",QString::number(mDensificationWizard->getPMVSCSize()));
        options.insert("minImageNum",QString::number(mDensificationWizard->getPMVSMin()));
        options.insert("threshold",QString::number(mDensificationWizard->getPMVSThreshold()));

        mPMVSProcess = new PW::PMVSProccess(pmvsDir, "pmvs_options.txt", options);
        if(mPMVSMultiProcess)
            delete mPMVSMultiProcess;
        mPMVSMultiProcess = new MultiProcess();

        mPMVSMultiProcess->appendProcess(mApero2PMVSProcess);
        mPMVSMultiProcess->appendProcess(mPMVSProcess);
        mPMVSMultiProcess->setStartupMessage("Generating PMVS dense model...");

        connect(mPMVSMultiProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
        connect(mPMVSMultiProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
        connect(mPMVSMultiProcess, SIGNAL(finished()), this, SLOT(onPMVSFinished()));
        connect(mProgressDialog,SIGNAL(cancel()),mPMVSMultiProcess,SLOT(stop()));
        connect(mPMVSMultiProcess, SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));
        connect(mPMVSMultiProcess, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));

        mPMVSMultiProcess->start();

        mConsole->clear();
        mProgressDialog->setModal(true);
        mProgressDialog->setRange(0,0);
        mProgressDialog->setWindowTitle(mPMVSMultiProcess->getStartupMessage());
        mProgressDialog->setFinished(false);
        mProgressDialog->show();

        mDenseModelPath = "pmvs-"+mProject->getCurrentOrientation() + "/models/pmvs_options.txt.ply";
    }
}

void MainWindowGRAPHOS::on_QStackedWidget_currentChanged(int currentIndex){
    ui->actionMask->setEnabled(false);
    ui->actionPointTool->setEnabled(false);
    ui->actionAngleTool->setEnabled(false);
    ui->actionDistance_Tool->setEnabled(false);
    ui->action_ActionPickRotationCenter->setEnabled(false);
    ui->actionFront_isometric_view->setEnabled(false);
    ui->actionBack_isometric_view->setEnabled(false);
    ui->actionFront_view->setEnabled(false);
    ui->actionBack_view->setEnabled(false);
    ui->actionLeft_view->setEnabled(false);
    ui->actionRight_view->setEnabled(false);
    ui->actionTop_view->setEnabled(false);
    ui->actionBottom_view->setEnabled(false);

    switch (currentIndex) {
    case 0:
        ui->actionMask->setEnabled(true);
        break;
    case 1:

        break;
    case 2:
        ui->actionPointTool->setEnabled(true);
        ui->actionAngleTool->setEnabled(true);
        ui->actionDistance_Tool->setEnabled(true);
        ui->action_ActionPickRotationCenter->setEnabled(true);
        ui->actionFront_isometric_view->setEnabled(true);
        ui->actionBack_isometric_view->setEnabled(true);
        ui->actionFront_view->setEnabled(true);
        ui->actionBack_view->setEnabled(true);
        ui->actionLeft_view->setEnabled(true);
        ui->actionRight_view->setEnabled(true);
        ui->actionTop_view->setEnabled(true);
        ui->actionBottom_view->setEnabled(true);
        break;
    case 3:
        ui->actionFront_isometric_view->setEnabled(true);
        ui->actionBack_isometric_view->setEnabled(true);
        ui->actionFront_view->setEnabled(true);
        ui->actionBack_view->setEnabled(true);
        ui->actionLeft_view->setEnabled(true);
        ui->actionRight_view->setEnabled(true);
        ui->actionTop_view->setEnabled(true);
        ui->actionBottom_view->setEnabled(true);
        ui->actionPointTool->setEnabled(true);
        ui->actionAngleTool->setEnabled(true);
        ui->actionDistance_Tool->setEnabled(true);
        ui->action_ActionPickRotationCenter->setEnabled(true);
        break;
    }

}

void MainWindowGRAPHOS::onMSDTiePointsFinished(){

    if(!mMsdProcess->isStopped())
    {

        mProject->setMatchingFormat(MATCHING_FORMAT_APERO_TXT);
        mProject->appendTiePointsSet(mTiePointsDescription);
        mProject->setNeedToSave(true);

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Compute tie points finished."));
        mProgressDialog->setFinished(true);
        mProgressDialog->writeinConsole("Compute tie points finished.");


        //Save metadata
        mProject->removeProcessMetadata("Model");
        mProject->removeProcessMetadata("Orientation");
        mProject->removeProcessMetadata("TiePoints");
        mProject->setProcessMetadataElement("TiePoints", "Tool", "MSD");
        if (mTiePointsWizard->isWallisChecked()) {
            mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Wallis filter");
            mProject->setProcessMetadataElement("TiePoints", "WallisContrast", QString::number(mTiePointsWizard->getWallisContrast()));
            mProject->setProcessMetadataElement("TiePoints", "WallisBrightness", QString::number(mTiePointsWizard->getWallisBrithness()));
            mProject->setProcessMetadataElement("TiePoints", "WallisStdDev", QString::number(mTiePointsWizard->getWallisStdDeviation()));
            mProject->setProcessMetadataElement("TiePoints", "WallisKernelSize", QString::number(mTiePointsWizard->getWallisKernell()));

        }else {
            mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Contrast preserving decolorization");
        }
        mProject->setProcessMetadataElement("TiePoints", "PatchRadius", mTiePointsMethod.value("PatchRadius") );
        mProject->setProcessMetadataElement("TiePoints", "SearchAreaRadius", mTiePointsMethod.value("SearchAreaRadius") );
        mProject->setProcessMetadataElement("TiePoints", "NMSRadius", mTiePointsMethod.value("NMSRadius") );
        mProject->setProcessMetadataElement("TiePoints", "NMSScaleRadius", mTiePointsMethod.value("NMSScaleRadius") );
        mProject->setProcessMetadataElement("TiePoints", "ThSaliency", mTiePointsMethod.value("ThSaliency") );
        mProject->setProcessMetadataElement("TiePoints", "KNN", mTiePointsMethod.value("KNN") );
        mProject->setProcessMetadataElement("TiePoints", "ScaleFactor", mTiePointsMethod.value("ScaleFactor") );
        mProject->setProcessMetadataElement("TiePoints", "NScales", mTiePointsMethod.value("NScales") );
        mProject->setProcessMetadataElement("TiePoints", "MaxTiepoints", mTiePointsMethod.value("MaxTiepoints") );

        mProject->setProcessMetadataElement("TiePoints", "Size", mTiePointsMethod.value("ResizeValue"));

        if(mTiePointsMethod.value("matchingMethod").compare("FLANN",Qt::CaseInsensitive)==0){
            mProject->setProcessMetadataElement("TiePoints", "MatchingMethod", "FLANN");
        }else{
            mProject->setProcessMetadataElement("TiePoints", "MatchingMethod", "Robust matcher (brute force)");
            mProject->setProcessMetadataElement("TiePoints", "RB_ratio", mTiePointsMethod.value("RB_ratio"));
            mProject->setProcessMetadataElement("TiePoints", "RB_threshold_K", mTiePointsMethod.value("RB_threshold_K"));
        }
        mProject->setProcessMetadataElement("TiePoints", "MinMatches", mTiePointsMethod.value("ResizeValue"));

        QDateTime dateTime=QDateTime::currentDateTime();
        QString timeCalculation=dateTime.toString(LIBPW_DATETIME_STRING_FORMAT);

        PWMatchesCategory * category = new PWMatchesCategory(mProject,
                              0,
                              mTiePointsDescription,
                              mTiePointsMetadata,
                              timeCalculation);

        QMap<QString, QVector<QString> > imagePairs;
        TapiocaIO tapiocaIO;
        tapiocaIO.readImagePairs(mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription, imagePairs);
        PWGraphImages* graphImages=new PWGraphImages();
            QVector<QString> wallisImageNames = mProject->getImagesFileName();
            for (int i = 0; i < wallisImageNames.count(); ++i) {
                wallisImageNames[i]=wallisImageNames[i].split(".").at(0)+".tif";
            }
            if(!graphImages->createGraph(wallisImageNames,
                                          imagePairs))
             {
                 //TODO: graphIsConnected=false; ¿Que hacer?
             }


        category->setGraphImages(graphImages);
        category->setImagePairs(imagePairs);

        mProject->insertMatchesCategory(category); //Comprobar categorie
        mProject->setActiveTiePointsSet(mTiePointsDescription);
        //Rename folders and files if necessary.

        if (!QFileInfo(mProject->getImagesFileName().first()).suffix().contains("tif")) {
            QString matchesDirPath = mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription;
            QDir *matchesDir = new QDir(matchesDirPath);
            QFileInfoList infoList = matchesDir->entryInfoList();
            for (int j = 2; j < infoList.count(); ++j) {
                QString subfolderName = infoList[j].absoluteFilePath();
                subfolderName =subfolderName.split(".").at(0)+"."+mProject->getImagesFileName().at(0).split(".").at(1);
                copyDir(infoList[j].absoluteFilePath(),subfolderName);
                removeDir(infoList[j].absoluteFilePath());
                QDir *pastirDir = new QDir(subfolderName);
                QFileInfoList infoPastisList = pastirDir->entryInfoList();
                for (int k = 2; k < infoPastisList.count(); ++k) {
                    QString pastisFileName = infoPastisList[k].absoluteFilePath();
                    pastisFileName =pastisFileName.split(".tif.txt").at(0)+"."+mProject->getImagesFileName().at(0).split(".").at(1)+".txt";
                    QFile::rename(infoPastisList[k].absoluteFilePath(), pastisFileName);
                }
            }
        }

        if(!mProject->isValidMatchedCategory(mTiePointsMetadata) || !TIEPOINTS_VALIDATE_SETS){
            QString title;
            QStringList subgraphs;
            mProject->getInvalidMatchedCategoryExplanationByDescription(mTiePointsDescription,title, subgraphs);
            QString originalImageExtension= mProject->getImagesFileName().first().split(".").last();
            QList<QStringList> *subGraphsList = new QList<QStringList>();
            subGraphsList->clear();
            QStringList subgraph;
            subgraph.clear();
            for (int i = 0; i < subgraphs.count(); ++i) {

                //Parse subgraph and add items
                QStringList subgraphItems = subgraphs.at(i).split("}_-_{");
                if (subgraphItems.count()>3) {
                    subgraph.clear();
                    for (int j = 0; j < subgraphItems.count()-1; ++j) {
                        subgraph.append(subgraphItems[j].replace("tif",originalImageExtension));
                    }
                    subGraphsList->append(subgraph);
                }

           }
            if (subGraphsList->count()!=0) {
                SubgraphSelector *subgraphSelector = new SubgraphSelector(this,subGraphsList,mProject);
                if (!subgraphSelector->exec()) {
                    mProject->clearTiePointsSets();
                    mProject->setActiveTiePointsSet("");
                    mPersistenceManager->updateProject(mProject);
                    //remove matches folder if was created
                    QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                    if(MatchesDir.exists())
                        removeDir(MatchesDir.absolutePath());
                    return;
                }
                QStringList subgraphToProcess =subGraphsList->at(subgraphSelector->getSubgraphIndex());
                QStringList imageNamesToRemove;
                QList<int> imageIDsToRemove;
                foreach (PWImage *image, mProject->getImages()) {
                    QFileInfo projectImage(image->getFullPath());
                    if (!subgraphToProcess.contains(projectImage.fileName())) {
                        imageIDsToRemove.append(image->getID());
                        imageNamesToRemove.append(image->getFileName());
                    }
                }
                if (imageIDsToRemove.count()>0) {
                    mProject->removeImagesByName(imageNamesToRemove);
                    mPersistenceManager->deleteMatches(imageIDsToRemove);
                    if(!mProject->getImages().count()){
                        mProject->clearTiePointsSets();
                        mProject->setActiveTiePointsSet("");
                    }
                    emit projectChanged();
                    updateTools();
                    foreach (QString imageToRemovePastis, imageNamesToRemove) {
                        QDir pastisfolderToRemove(mProject->getBasePath()+"/Matches/tapioca/Pastis"+imageToRemovePastis);
                        if(pastisfolderToRemove.exists())
                            removeDir(pastisfolderToRemove.absolutePath());
                    }
                }

                //search ImagePairs again
                imagePairs.clear();
                tapiocaIO.readImagePairs(mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription, imagePairs);
                PWGraphImages* graphImages=new PWGraphImages();
                    QVector<QString> wallisImageNames = mProject->getImagesFileName();
                    for (int i = 0; i < wallisImageNames.count(); ++i) {
                        wallisImageNames[i]=wallisImageNames[i].split(".").at(0)+".tif";
                    }
                    if(!graphImages->createGraph(wallisImageNames,
                                                  imagePairs))
                     {
                         //TODO: graphIsConnected=false; ¿Que hacer?
                     }
                category->setGraphImages(graphImages);
                category->setImagePairs(imagePairs);

                mProject->insertMatchesCategory(category); //Comprobar categorie
                mProject->setActiveTiePointsSet(mTiePointsDescription);
            }else {
                QMessageBox msg(this);
                msg.setWindowTitle("Warning!");
                msg.setText("Not valid subgraph");
                msg.exec();
                mProject->clearTiePointsSets();
                mProject->setActiveTiePointsSet("");
                mPersistenceManager->updateProject(mProject);
                //remove matches folder if was created
                QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                if(MatchesDir.exists())
                    removeDir(MatchesDir.absolutePath());
                return;
            }

        }


        //tie point results;
        drawTiePointsInfoView(imagePairs);

        //Save the project
        mPersistenceManager->updateProject(mProject);
    }else {
        //remove matches folder if was created
        QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
        if(MatchesDir.exists())
            removeDir(MatchesDir.absolutePath());
    }


    setWorkflowWidgetStatus();
    mQStackedWidget->setCurrentIndex(1);
    loadProjectMetadataOnProjectTree();
    updateImagesTree();
    updateTools();
    disconnect(mProgressDialog,SIGNAL(cancel()),mMsdProcess,SLOT(stop()));
}

void MainWindowGRAPHOS::onASIFTUTiePointsFinished(){

    if(!mASIFTUProcess->isStopped())
    {

        mProject->setMatchingFormat(MATCHING_FORMAT_APERO_TXT);
        mProject->appendTiePointsSet(mTiePointsDescription);
        mProject->setNeedToSave(true);

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Compute tie points finished."));
        mProgressDialog->setFinished(true);
        mProgressDialog->writeinConsole("Compute tie points finished.");

        //Save metadata
        mProject->removeProcessMetadata("Model");
        mProject->removeProcessMetadata("Orientation");
        mProject->removeProcessMetadata("TiePoints");
        mProject->setProcessMetadataElement("TiePoints", "Tool", "ASIFT");
        if (mTiePointsWizard->isWallisChecked()) {
            mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Wallis filter");
            mProject->setProcessMetadataElement("TiePoints", "WallisContrast", QString::number(mTiePointsWizard->getWallisContrast()));
            mProject->setProcessMetadataElement("TiePoints", "WallisBrightness", QString::number(mTiePointsWizard->getWallisBrithness()));
            mProject->setProcessMetadataElement("TiePoints", "WallisStdDev", QString::number(mTiePointsWizard->getWallisStdDeviation()));
            mProject->setProcessMetadataElement("TiePoints", "WallisKernelSize", QString::number(mTiePointsWizard->getWallisKernell()));

        }else {
            mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Contrast preserving decolorization");
        }
        mProject->setProcessMetadataElement("TiePoints", "PeakTh", mTiePointsMethod.value("PeakTh") );
        mProject->setProcessMetadataElement("TiePoints", "EdgeTh", mTiePointsMethod.value("EdgeTh") );
        mProject->setProcessMetadataElement("TiePoints", "Octaves", mTiePointsMethod.value("Octaves") );
        mProject->setProcessMetadataElement("TiePoints", "Tilts", mTiePointsMethod.value("Tilts") );
        mProject->setProcessMetadataElement("TiePoints", "MaxTiepoints", mTiePointsMethod.value("MaxTiepoints") );

        mProject->setProcessMetadataElement("TiePoints", "Size", mTiePointsMethod.value("ResizeValue"));

        if(mTiePointsMethod.value("matchingMethod").compare("FLANN",Qt::CaseInsensitive)==0){
            mProject->setProcessMetadataElement("TiePoints", "MatchingMethod", "FLANN");
        }else{
            mProject->setProcessMetadataElement("TiePoints", "MatchingMethod", "Robust matcher (brute force)");
            mProject->setProcessMetadataElement("TiePoints", "RB_ratio", mTiePointsMethod.value("RB_ratio"));
            mProject->setProcessMetadataElement("TiePoints", "RB_threshold_K", mTiePointsMethod.value("RB_threshold_K"));
        }
        mProject->setProcessMetadataElement("TiePoints", "MinMatches", mTiePointsMethod.value("ResizeValue"));


        QDateTime dateTime=QDateTime::currentDateTime();
        QString timeCalculation=dateTime.toString(LIBPW_DATETIME_STRING_FORMAT);

        PWMatchesCategory * category = new PWMatchesCategory(mProject,
                              0,
                              mTiePointsDescription,
                              mTiePointsMetadata,
                              timeCalculation);

        QMap<QString, QVector<QString> > imagePairs;
        TapiocaIO tapiocaIO;
        tapiocaIO.readImagePairs(mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription, imagePairs);
        PWGraphImages* graphImages=new PWGraphImages();
            QVector<QString> wallisImageNames = mProject->getImagesFileName();
            for (int i = 0; i < wallisImageNames.count(); ++i) {
                wallisImageNames[i]=wallisImageNames[i].split(".").at(0)+".tif";
            }
            if(!graphImages->createGraph(wallisImageNames,
                                          imagePairs))
             {
                 //TODO: graphIsConnected=false; ¿Que hacer?
             }


        category->setGraphImages(graphImages);
        category->setImagePairs(imagePairs);

        mProject->insertMatchesCategory(category); //Comprobar categorie
        mProject->setActiveTiePointsSet(mTiePointsDescription);
        //Rename folders and files if necessary.
        if (!QFileInfo(mProject->getImagesFileName().first()).suffix().contains("tif")) {
            QString matchesDirPath = mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription;
            QDir *matchesDir = new QDir(matchesDirPath);
            QFileInfoList infoList = matchesDir->entryInfoList();
            for (int j = 2; j < infoList.count(); ++j) {
                QString subfolderName = infoList[j].absoluteFilePath();
                subfolderName =subfolderName.split(".").at(0)+"."+mProject->getImagesFileName().at(0).split(".").at(1);
                copyDir(infoList[j].absoluteFilePath(),subfolderName);
                removeDir(infoList[j].absoluteFilePath());
                QDir *pastirDir = new QDir(subfolderName);
                QFileInfoList infoPastisList = pastirDir->entryInfoList();
                for (int k = 2; k < infoPastisList.count(); ++k) {
                    QString pastisFileName = infoPastisList[k].absoluteFilePath();
                    pastisFileName =pastisFileName.split(".tif.txt").at(0)+"."+mProject->getImagesFileName().at(0).split(".").at(1)+".txt";
                    QFile::rename(infoPastisList[k].absoluteFilePath(), pastisFileName);
                }
            }
        }
        if(!mProject->isValidMatchedCategory(mTiePointsMetadata) || !TIEPOINTS_VALIDATE_SETS){
            QString title;
            QStringList subgraphs;
            mProject->getInvalidMatchedCategoryExplanationByDescription(mTiePointsDescription,title, subgraphs);

            QString originalImageExtension= mProject->getImagesFileName().first().split(".").last();
            QList<QStringList> *subGraphsList = new QList<QStringList>();
            subGraphsList->clear();
            QStringList subgraph;
            subgraph.clear();
            for (int i = 0; i < subgraphs.count(); ++i) {

                //Parse subgraph and add items
                QStringList subgraphItems = subgraphs.at(i).split("}_-_{");
                if (subgraphItems.count()>3) {
                    subgraph.clear();
                    for (int j = 0; j < subgraphItems.count()-1; ++j) {
                        subgraph.append(subgraphItems[j].replace("tif",originalImageExtension));
                    }
                    subGraphsList->append(subgraph);
                }

           }
            if (subGraphsList->count()!=0) {
                SubgraphSelector *subgraphSelector = new SubgraphSelector(this,subGraphsList,mProject);
                if (!subgraphSelector->exec()) {
                    mProject->clearTiePointsSets();
                    mProject->setActiveTiePointsSet("");
                    mPersistenceManager->updateProject(mProject);
                    //remove matches folder if was created
                    QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                    if(MatchesDir.exists())
                        removeDir(MatchesDir.absolutePath());

                    mProgressDialog->close();
                    return;
                }
                QStringList subgraphToProcess =subGraphsList->at(subgraphSelector->getSubgraphIndex());
                QStringList imageNamesToRemove;
                QList<int> imageIDsToRemove;
                foreach (PWImage *image, mProject->getImages()) {
                    QFileInfo projectImage(image->getFullPath());
                    if (!subgraphToProcess.contains(projectImage.fileName())) {
                        imageIDsToRemove.append(image->getID());
                        imageNamesToRemove.append(image->getFileName());
                    }
                }
                if (imageIDsToRemove.count()>0) {
                    mProject->removeImagesByName(imageNamesToRemove);
                    mPersistenceManager->deleteMatches(imageIDsToRemove);
                    if(!mProject->getImages().count()){
                        mProject->clearTiePointsSets();
                        mProject->setActiveTiePointsSet("");
                    }
                    emit projectChanged();
                    updateTools();
                    foreach (QString imageToRemovePastis, imageNamesToRemove) {
                        QDir pastisfolderToRemove(mProject->getBasePath()+"/Matches/tapioca/Pastis"+imageToRemovePastis);
                        if(pastisfolderToRemove.exists())
                            removeDir(pastisfolderToRemove.absolutePath());
                    }
                }

                //search ImagePairs again
                imagePairs.clear();
                tapiocaIO.readImagePairs(mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mTiePointsDescription, imagePairs);
                PWGraphImages* graphImages=new PWGraphImages();
                    QVector<QString> wallisImageNames = mProject->getImagesFileName();
                    for (int i = 0; i < wallisImageNames.count(); ++i) {
                        wallisImageNames[i]=wallisImageNames[i].split(".").at(0)+".tif";
                    }
                    if(!graphImages->createGraph(wallisImageNames,
                                                  imagePairs))
                     {
                         //TODO: graphIsConnected=false; ¿Que hacer?
                     }
                category->setGraphImages(graphImages);
                category->setImagePairs(imagePairs);

                mProject->insertMatchesCategory(category); //Comprobar categorie
                mProject->setActiveTiePointsSet(mTiePointsDescription);
            }else {
                QMessageBox msg(this);
                msg.setWindowTitle("Warning!");
                msg.setText("Not valid subgraph");
                msg.exec();
                mProject->clearTiePointsSets();
                mProject->setActiveTiePointsSet("");
                mPersistenceManager->updateProject(mProject);
                //remove matches folder if was created
                QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                if(MatchesDir.exists())
                    removeDir(MatchesDir.absolutePath());

                mProgressDialog->close();
                return;
            }

        }

        //tie point results;
        drawTiePointsInfoView(imagePairs);

        //Save the project
        mPersistenceManager->updateProject(mProject);
    }else {
        //remove matches folder if was created
        QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
        if(MatchesDir.exists())
            removeDir(MatchesDir.absolutePath());
    }
    setWorkflowWidgetStatus();
    mQStackedWidget->setCurrentIndex(1);
    loadProjectMetadataOnProjectTree();
    updateImagesTree();
    updateTools();
    disconnect(mProgressDialog,SIGNAL(cancel()),mASIFTUProcess,SLOT(stop()));
}

void MainWindowGRAPHOS::onMultiDecolorFinished(){

    if (!mCvDecolorMultiProcess->isStopped()) {
        mTiePointsMethod.clear();
        mTiePointsMethod = mTiePointsWizard->getTiePointsMethod();
        mProject->setCaptureType(mTiePointsWizard->getCaptureConfiguration());
        if (mTiePointsMethod.value("method").contains("Tapioca")) {
            computeTapiocaHomol("");
        }else if (mTiePointsMethod.value("method").contains("MSD+SIFT")) {
            QVector<QString> imgNames = mProject->getImagesFileName();
            QStringList imageNames;
            for (int i = 0; i < imgNames.count(); ++i) {
                imageNames.append(mProject->getPreProcessingPath().append("/").append(imgNames[i].split(".").first().append(".tif")));
            }
            //remove previous matches
            QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
            if(MatchesDir.exists())
                removeDir(MatchesDir.absolutePath());

            while (!MatchesDir.exists()) {
                QDir().mkdir(MatchesDir.absolutePath());
            }
            QDir tapiocaDir(mProject->getBasePath() +"/"+ MATCHING_PATH+"/MSD");
            while (!tapiocaDir.exists()) {
                   QDir().mkdir(tapiocaDir.absolutePath());
            }
            if (!mProject->getSparseModelRelativePath().isEmpty()) {
                mProject->setSparseModelRelativePath("");
            }if (!mProject->getDenseModelRelativePath().isEmpty()) {
                mProject->setDenseModelRelativePath("");
            }

            mTiePointsDescription="MSD";
            mProject->setActiveTiePointsSet("MSD");
            mProgressDialog->writeinConsole("\n\nStarting MSD tiepoints detector ");
            mMsdProcess = new MSDProcess(mProject->getBasePath(),imageNames,mProject->getBasePath()+"/"+MATCHING_PATH,mTiePointsMethod,mTiePointsWizard->isMSDAffineChecked(),mTiePointsWizard->getMSDAffineTilts());
            connect(mMsdProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
            connect(mMsdProcess, SIGNAL(statusChangedNext()),mProgressDialog,SLOT(onSatutsChangedNext()));
            connect(mMsdProcess,SIGNAL(finished()),this,SLOT(onMSDTiePointsFinished()));
            connect(mProgressDialog,SIGNAL(cancel()),mMsdProcess,SLOT(stop()));
            mProgressDialog->setModal(true);
            int steps = mProject->getImages().count(); //tiepoints detection
            steps=steps*2; //tiepoints description
            for (int i = 1; i < mProject->getImagesFileName().count(); ++i) { //feature matching
                int matchingSteps = mProject->getImagesFileName().count()-i;
                steps+=matchingSteps;
            }
            steps+=2; //write matches to apero
            mProgressDialog->setRange(0,steps);
            mProgressDialog->setValue(1);
            mProgressDialog->setWindowTitle("Searching for tie points (MSD)...");
            mProgressDialog->setStatusText("Searching for tie points (MSD)...");
            mProgressDialog->setFinished(false);
            mProgressDialog->show();
            mMsdProcess->start();
        }else if (mTiePointsMethod.value("method").contains("ASIFT")) {
            QVector<QString> imgNames = mProject->getImagesFileName();
            QStringList imageNames;
            for (int i = 0; i < imgNames.count(); ++i) {
                imageNames.append(mProject->getPreProcessingPath().append("/").append(imgNames[i].split(".").first().append(".tif")));
            }
            //remove previous matches
            QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
            if(MatchesDir.exists())
                removeDir(MatchesDir.absolutePath());

            while (!MatchesDir.exists()) {
                QDir().mkdir(MatchesDir.absolutePath());
            }
            QDir tapiocaDir(mProject->getBasePath() +"/"+ MATCHING_PATH+"/ASIFT");
            while (!tapiocaDir.exists()) {
                   QDir().mkdir(tapiocaDir.absolutePath());
            }
            if (!mProject->getSparseModelRelativePath().isEmpty()) {
                mProject->setSparseModelRelativePath("");
            }if (!mProject->getDenseModelRelativePath().isEmpty()) {
                mProject->setDenseModelRelativePath("");
            }

            mTiePointsDescription="ASIFT";
            mProject->setActiveTiePointsSet("ASIFT");
            mProgressDialog->writeinConsole("\n\nStarting ASIFT tiepoints detector ");
            mASIFTUProcess = new ASIFTUProcess(mProject->getBasePath(),imageNames,mProject->getBasePath()+"/"+MATCHING_PATH,mTiePointsMethod);
            connect(mASIFTUProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
            connect(mASIFTUProcess, SIGNAL(statusChangedNext()),mProgressDialog,SLOT(onSatutsChangedNext()));
            connect(mASIFTUProcess,SIGNAL(finished()),this,SLOT(onASIFTUTiePointsFinished()));
            connect(mProgressDialog,SIGNAL(cancel()),mASIFTUProcess,SLOT(stop()));
            mProgressDialog->setModal(true);
            int steps = mProject->getImages().count(); //tiepoints detection
            steps=steps*2; //tiepoints description
            for (int i = 1; i < mProject->getImagesFileName().count(); ++i) { //feature matching
                int matchingSteps = mProject->getImagesFileName().count()-i;
                steps+=matchingSteps;
            }
            steps+=2; //write matches to apero
            mProgressDialog->setRange(0,steps);
            mProgressDialog->setValue(1);
            mProgressDialog->setWindowTitle("Searching for tie points (ASIFT)...");
            mProgressDialog->setStatusText("Searching for tie points (ASIFT)...");
            mProgressDialog->setFinished(false);
            mProgressDialog->show();
            mASIFTUProcess->start();
        }
    }
}

bool MainWindowGRAPHOS::onImagesConnectionDoubleClicked(QListWidgetItem *listWidget){
    QString data = listWidget->whatsThis();
    QStringList evaluatedImageNames = data.split("} , {");

    QFile matchingsPath(mProject->getBasePath()+"/Matches/"+mProject->getActiveTiePointsSet()+"/Pastis"+evaluatedImageNames.at(0)+"/"+evaluatedImageNames.at(1)+".txt");
    if (matchingsPath.open(QIODevice::ReadOnly)) {
        mMatchingsViewer->clearAll();
        QTextStream in(&matchingsPath);
        QList<QVector<float>> matching_coords;
        while(!in.atEnd()) {
            QString line = in.readLine();
            QStringList fields = line.split(" ");
            QVector<float> match;
            foreach (QString value, fields) {
                match.append(value.toFloat());
            }
            match.append(0);
            matching_coords.append(match);
            match.clear();
        }

        matchingsPath.close();
        QFileInfo imageLeftPath(mProject->getBasePath()+"/"+evaluatedImageNames.at(0));
        QFileInfo imageRightPath(mProject->getBasePath()+"/"+evaluatedImageNames.at(1));
        PW::PWImage *imageLeft = new PW::PWImage(imageLeftPath.absoluteFilePath());
        PW::PWImage *imageRight = new PW::PWImage(imageRightPath.absoluteFilePath());
        mBasicUserGUI->setCurrentIndex(4);
        mMatchingsViewer->loadImagesPair(imageLeft, imageRight,matching_coords);
        return true;
    }else {
        return false;
    }
}

void MainWindowGRAPHOS::on_BackToImagesConnectionTriggered(){
    mBasicUserGUI->setCurrentIndex(1);
}
void MainWindowGRAPHOS::onLasmergeFinished(){
    if (!mMergeLasResultsProcess->isStopped()) {

        mProject->setDenseModelRelativePath("SURE.las");

        QStringList modelsList;
        modelsList.append(mProject->getDenseModelFullPath());
        mCCVW2->addToDB(modelsList);


        // Process metadata:
        ccHObject* obj = mCCVW2->getGLWindow()->getSceneDB()->getFirstChild();
        ccPointCloud *cloud = static_cast<ccPointCloud*>(obj);
        unsigned cloudSize = cloud->size();

        mProject->removeProcessMetadata("Model");
        mProject->setProcessMetadataElement("Model", "CloudSize", QString::number(cloudSize)+" points");
        mProject->setProcessMetadataElement("Model", "Tool", "SURE");
        mProject->setProcessMetadataElement("Model", "Pyr", QString::number(mDensificationWizard->getSurePyrValue()));
        mProject->setProcessMetadataElement("Model", "Fold", QString::number(mDensificationWizard->getSureFoldValue()));
        mProject->setProcessMetadataElement("Model", "MaxModels", QString::number(mDensificationWizard->getSureMaxModelsValue()));


        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("SURE densification finished."));
        mProgressDialog->setFinished(true);

        mBasicUserGUI->setCurrentIndex(3);
        setWorkflowWidgetStatus();
        loadProjectMetadataOnProjectTree();
        loadModelsOnTree();
        updateTools();
        //Save the project
        mPersistenceManager->updateProject(mProject);
    }
}
void MainWindowGRAPHOS::onTreeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous){
    if(current != NULL && current->parent() != NULL ){
        if (current->parent()->text(0).contains(tr("Images"))) {
            QString imagePath = current->data(0,Qt::ToolTipRole).toString();
            mPhotoViewer->loadNewImg(imagePath,0);
            mBasicUserGUI->setCurrentIndex(0);
            updatePhotoViewerGraphics();
        }else if (current->parent()->text(0).contains(tr("Image Matchings"))) {
            QFileInfo matchingsFileInfo(mProject->getBasePath()+"/Matches/"+mProject->getActiveTiePointsSet()+"/Pastis"+current->parent()->parent()->text(0)+"/"+current->text(0)+".txt");
            QFile matchingsPath(matchingsFileInfo.absoluteFilePath());
            if (matchingsPath.open(QIODevice::ReadOnly)) {
                mMatchingsViewer->clearAll();
                QTextStream in(&matchingsPath);
                QList<QVector<float>> matching_coords;
                while(!in.atEnd()) {
                    QString line = in.readLine();
                    QStringList fields = line.split(" ");
                    QVector<float> match;
                    foreach (QString value, fields) {
                        match.append(value.toFloat());
                    }
                    match.append(0);
                    matching_coords.append(match);
                    match.clear();
                }

                matchingsPath.close();
                QFileInfo imageLeftPath(mProject->getBasePath()+"/"+current->parent()->parent()->text(0));
                QFileInfo imageRightPath(mProject->getBasePath()+"/"+current->text(0));
                PW::PWImage *imageLeft = new PW::PWImage(imageLeftPath.absoluteFilePath());
                PW::PWImage *imageRight = new PW::PWImage(imageRightPath.absoluteFilePath());
                mBasicUserGUI->setCurrentIndex(4);
                mMatchingsViewer->loadImagesPair(imageLeft, imageRight,matching_coords);
            }
        }else if (current->text(0).contains(tr("Dense Model"))) {
            mBasicUserGUI->setCurrentIndex(3);

        }else if (current->text(0).contains(tr("Sparse Model"))) {
            mBasicUserGUI->setCurrentIndex(2);

        }
    }
}

void MainWindowGRAPHOS::removePreviousDensifications(){
    //Remove previous SURE dir if exists
    QDir sureDir(mProject->getBasePath()+"/SURE");
    if (sureDir.exists()) {
        removeDir(sureDir.absolutePath());
    }
    QFileInfo sureDenseFile(mProject->getBasePath()+"/SURE.las");
    if (sureDenseFile.exists()) {
        QFile::remove(sureDenseFile.absoluteFilePath());
    }
    QFileInfo sureDenseTmpFile(mProject->getBasePath()+"/tempLas.las");
    if (sureDenseTmpFile.exists()) {
        QFile::remove(sureDenseTmpFile.absoluteFilePath());
    }

    QFileInfo MicMacDenseFile(mProject->getBasePath()+"/MicMac.ply");
    if (MicMacDenseFile.exists()) {
        QFile::remove(MicMacDenseFile.absoluteFilePath());
    }
    //remove previous PMVS results if exists
    QDir PMVS_FB(mProject->getBasePath()+"/pmvs-FraserBasic");
    if (PMVS_FB.exists()) {
        removeDir(PMVS_FB.absolutePath());
    }

    QDir PMVS_F(mProject->getBasePath()+"/pmvs-Fraser");
    if (PMVS_F.exists()) {
        removeDir(PMVS_F.absolutePath());
    }

    QDir PMVS_RE(mProject->getBasePath()+"/pmvs-RadialExtended");
    if (PMVS_RE.exists()) {
        removeDir(PMVS_RE.absolutePath());
    }
    QFileInfo pmvsDenseFile(mProject->getBasePath()+"/PMVS.ply");
    if (pmvsDenseFile.exists()) {
        QFile::remove(pmvsDenseFile.absoluteFilePath());
    }
}
void MainWindowGRAPHOS::removePreviousOrientatios(){
    removePreviousDensifications();
    QDir OriFB(mProject->getBasePath()+"/Ori-FraserBasic");
    if (OriFB.exists()) {
        removeDir(OriFB.absolutePath());
    }
    QDir OriF(mProject->getBasePath()+"/Ori-Fraser");
    if (OriF.exists()) {
        removeDir(OriF.absolutePath());
    }
    QDir OriRE(mProject->getBasePath()+"/Ori-RadialExtended");
    if (OriRE.exists()) {
        removeDir(OriRE.absolutePath());
    }
    QDir OriRB(mProject->getBasePath()+"/Ori-RadialBasic");
    if (OriRB.exists()) {
        removeDir(OriRB.absolutePath());
    }

    QFileInfo plyFB(mProject->getBasePath()+"/FraserBasic.ply");
    if (plyFB.exists()) {
        QFile::remove(plyFB.absoluteFilePath());
    }
    QFileInfo plyF(mProject->getBasePath()+"/Fraser.ply");
    if (plyF.exists()) {
        QFile::remove(plyF.absoluteFilePath());
    }
    QFileInfo plyRE(mProject->getBasePath()+"/RadialExtended.ply");
    if (plyRE.exists()) {
        QFile::remove(plyRE.absoluteFilePath());
    }
    QFileInfo plyRB(mProject->getBasePath()+"/RadialBasic.ply");
    if (plyRB.exists()) {
        QFile::remove(plyRB.absoluteFilePath());
    }
}

void MainWindowGRAPHOS::cleanProject(){
    //remove preprocessing path
    QDir preprocessingPath(mProject->getPreProcessingPath());
    if (preprocessingPath.exists()) {
        removeDir(preprocessingPath.absolutePath());
    }

    //MICMAC

    QDir tmpSlaves(mProject->getBasePath()+"/Ori-SlavesTMP");
    if (tmpSlaves.exists()) {
        removeDir(tmpSlaves.absolutePath());
    }
    QDir OriInterneScan(mProject->getBasePath()+"/Ori-InterneScan");
    if (OriInterneScan.exists()) {
        removeDir(OriInterneScan.absolutePath());
    }

    //Remove TMP folder
    QDir TmpDir(mProject->getBasePath() + "/Tmp-MM-Dir");
    if(TmpDir.exists())
        removeDir(TmpDir.absolutePath());
    //Remove tmpPly folder
    QDir tmpPly(mProject->getBasePath()+"/tmpPly");
    if (tmpPly.exists()) removeDir(tmpPly.absolutePath());
    //Remove pyr dir
    QDir pyramDir(mProject->getBasePath() + "/Pyram-PW");
    if(pyramDir.exists())
        removeDir(pyramDir.absolutePath());

    QDir pyramTerDir(mProject->getBasePath() + "/Pyram-Ter");
    if(pyramTerDir.exists())
        removeDir(pyramTerDir.absolutePath());

    //Remove previous MICMAC dir if exists
    QDir MicMacDir(mProject->getBasePath()+"/MEC-0-PW");
    if (MicMacDir.exists()) {
        removeDir(MicMacDir.absolutePath());
    }

    //Remove previous ORTHO dir if exists
    QDir orthoDir(mProject->getBasePath()+"/ORTHO");
    if (orthoDir.exists()) {
        removeDir(orthoDir.absolutePath());
    }

    //Remove MicMac info files
    QFileInfo paramFile(mProject->getBasePath()+"/paramMICMAC1.xml");
    if (paramFile.exists()) {
        QFile::remove(paramFile.absoluteFilePath());
    }

    QFileInfo warnFile(mProject->getBasePath()+"/WarnMICMAC.txt");
    if (warnFile.exists()) {
        QFile::remove(warnFile.absoluteFilePath());
    }

    //SURE
    //Remove drunk folder if exists;
    QDir drunkDir(mProject->getBasePath()+"/DRUNK");
    if (drunkDir.exists()) {
        removeDir(drunkDir.absolutePath());
    }
    QDir tmpDir(mProject->getBasePath()+"/Tmp-MM-Dir");
    if (tmpDir.exists()) {
        removeDir(tmpDir.absolutePath());
    }
    //Remove SURE folder
    QDir surePath(mProject->getBasePath()+"/SURE");
    if (surePath.exists()) {
        removeDir(surePath.absolutePath());
    }

    //PMVS
    //delete PMVS folder
    //remove previous PMVS results if exists
    QDir PMVS_FB(mProject->getBasePath()+"/pmvs-FraserBasic");
    if (PMVS_FB.exists()) {
        removeDir(PMVS_FB.absolutePath());
    }

    QDir PMVS_F(mProject->getBasePath()+"/pmvs-Fraser");
    if (PMVS_F.exists()) {
        removeDir(PMVS_F.absolutePath());
    }

    QDir PMVS_RE(mProject->getBasePath()+"/pmvs-RadialExtended");
    if (PMVS_RE.exists()) {
        removeDir(PMVS_RE.absolutePath());
    }

    //tmpFiles
    QDir projectBasePath(mProject->getBasePath());
    projectBasePath.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);

    projectBasePath.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QStringList dirList = projectBasePath.entryList();
    for (int i=0; i<dirList.size(); ++i)
    {
        QFileInfo fileToEvaluate(QString("%1/%2").arg(projectBasePath.absolutePath()).arg(dirList.at(i)));
        if (fileToEvaluate.baseName().contains("paramMICMAC")||fileToEvaluate.baseName().contains("mm3d")||fileToEvaluate.baseName().contains("Warn")||fileToEvaluate.baseName().contains("Sauv")||fileToEvaluate.baseName().contains("MkStdMM")) {
            QFile(fileToEvaluate.absoluteFilePath()).remove();
        }
    }

    //Malt files
    QDir PyramDir(mProject->getBasePath()+"/Pyram");
    if (PyramDir.exists()) removeDir(PyramDir.absolutePath());


    QDirIterator directories(mProject->getBasePath(), QDir::Dirs | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    while(directories.hasNext()){
        directories.next();
        if (directories.fileName().contains("MEC-Malt") || directories.fileName().contains("MM-Malt-Img") || directories.fileName().contains("MTD-Image")) {
            removeDir(QDir(mProject->getBasePath()+"/"+directories.fileName()).absolutePath());
        }
    }
}

void MainWindowGRAPHOS::buildModelSURECustom(){

    //Remove previous sure path from sure dir if exists
    QDir originalDir(mProject->getBasePath()+"/SURE");
    if (originalDir.exists()) {
        removeDir(originalDir.absolutePath());
    }

    mCustomSureProcess = new PW::CustomSureProcess(mProject,mDensificationWizard->getSurePyrValue(),mDensificationWizard->getSureFoldValue(),mDensificationWizard->getSureMaxModelsValue(),CUDA_ENABLED);
    connect(mCustomSureProcess, SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));
    connect(mCustomSureProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mCustomSureProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mCustomSureProcess, SIGNAL(finished()),this,SLOT(onSureFinished()));
    connect(mCustomSureProcess, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mCustomSureProcess,SLOT(stop()));
    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setValue(0);
    mProgressDialog->setWindowTitle(mCustomSureProcess->getStartupMessage());
    mProgressDialog->setStatusText(mCustomSureProcess->getStartupMessage());
    mProgressDialog->setFinished(false);
    mProgressDialog->show();


    mCustomSureProcess->start();

}
void MainWindowGRAPHOS::on_actionExport_UndistortedImages_triggered(){
    QString initPath = mSettings->value("app/lastoutputpath").toString();
    if (initPath.isEmpty())
        initPath = QDir::homePath();

    mExportPath = QFileDialog::getExistingDirectory(this,"Select folder to save undistorted images",initPath);


    if (mExportPath.isEmpty()){
        return;
    }

    //DRUNK
    QString drunkInputRegExp = QString("(");
    QString fileName;
    for(int i=0; i< mProject->getImages().count(); i++){
        fileName = mProject->getImages().at(i)->getFullPath();
        fileName = fileName.right(fileName.length()-fileName.lastIndexOf(QRegExp("/"))-1);
        drunkInputRegExp = drunkInputRegExp + fileName + QString("|");
    }
    drunkInputRegExp.replace(drunkInputRegExp.length()-1,1,")");
    drunkInputRegExp =mProject->getBasePath()+"/"+drunkInputRegExp;
    if (mDrunkProcess) {
        delete mDrunkProcess;
    }
    mDrunkProcess = new PW::DrunkProcess(drunkInputRegExp,mProject->getCurrentOrientation());
    mDrunkProcess->setWorkingDir(mProject->getBasePath());
    connect(mDrunkProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mDrunkProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mDrunkProcess, SIGNAL(finished()),this,SLOT(onExportUndistortedImagesFinished()));

    connect(mDrunkProcess, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mDrunkProcess,SLOT(stop()));

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle(mDrunkProcess->getStartupMessage());
    mProgressDialog->setStatusText(mDrunkProcess->getStartupMessage());
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
    mDrunkProcess->start();
}

void MainWindowGRAPHOS::onExportUndistortedImagesFinished(){
    //Move results to target path
    QDir sourceDir(mProject->getBasePath()+"/DRUNK");
    QDir targetDir(mExportPath+"/DRUNK_UndistortedImages");
    copyDir(sourceDir.absolutePath(),targetDir.absolutePath());
    mProgressDialog->setRange(0,1);
    mProgressDialog->setValue(1);
    mProgressDialog->setStatusText(tr("Undistorted images exported."));
    mProgressDialog->setFinished(true);
}

void MainWindowGRAPHOS::on_actionExport_AgisoftDistortion(){

    QString initPath = mSettings->value("app/lastoutputpath").toString();
    if (initPath.isEmpty())
        initPath = QDir::homePath();

    QString fileXMLAgisoft = "";
    QString filters("XML file (*.xml)");
    QString defaultFilter="XML file (*.xml)";

    fileXMLAgisoft = QFileDialog::getSaveFileName(this, tr("Dense Model"),
                                                initPath,
                                                filters, &defaultFilter);
    if (fileXMLAgisoft.isEmpty()) {
        return;
    }

    GraphosCalib IoGraphos  = {}; //Inicializar {y poner a cero}
    QString temporal;


    std::cout << "Inicializacion de la herramienta..." << std::endl;

    //Leer el archivo XML
    QFileInfo graphosDistFileInfo(mProject->getBasePath()+"/Ori-"+mProject->getCurrentOrientation()+"/AutoCal_Foc-17000_Cam-TheCamera.xml");

    //The QDomDocument class represents an XML document.
    QDomDocument xmlBOM;
    // Load xml file as raw data
    QFile f(graphosDistFileInfo.absoluteFilePath());
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        std::cerr << "Error while loading file" << std::endl;
        return; // return 1;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f);
    f.close();


    std::cout << "Inicio de la lectura del archivo de Apero..." << std::endl;


    // Extract the root markup
    QDomElement root=xmlBOM.documentElement();

    // Display root data
    std::cout << "Type = " << root.tagName().toStdString() << std::endl;

    int RadialCount=0;

    // Get the first child of the root (Markup COMPONENT is expected)
    QDomElement Component=root.firstChild().toElement();

    // Loop while there is a child
    while(!Component.isNull())
    {
        // Check if the child tag name is "CalibrationInternConique"
        if (Component.tagName()=="CalibrationInternConique")
        {
            // Get the first child of the component
            QDomElement Child=Component.firstChild().toElement();


            // Read each child of the component node
            while (!Child.isNull())
            {
                // Leer la CABECERA
                if (Child.tagName()=="KnownConv") IoGraphos.KnownConv=Child.firstChild().toText().data();
                if (Child.tagName()=="F") IoGraphos.F=Child.firstChild().toText().data().toDouble();
                if (Child.tagName()=="PP") {
                    temporal=Child.firstChild().toText().data(); //leer como string para luego cortar
                    IoGraphos.PPx=temporal.split(" ").at(0).toDouble();
                    IoGraphos.PPy=temporal.split(" ").at(1).toDouble();
                    temporal="";}
                if (Child.tagName()=="SzIm") {
                    temporal=Child.firstChild().toText().data(); //leer como string para luego cortar
                    IoGraphos.SzImx=temporal.split(" ").at(0).toInt();
                    IoGraphos.SzImy=temporal.split(" ").at(1).toInt();
                    temporal="";}




                if (Child.tagName()=="CalibDistortion") {

                    QDomElement Component2=Child.toElement();
                    QDomElement Child2=Component2.firstChild().toElement();

                    while (!Child2.isNull()) {

                        if (Child2.tagName()=="ModPhgrStd") {

                            QDomElement Component3=Child2.toElement();
                            QDomElement Child3=Component3.firstChild().toElement();

                            while (!Child3.isNull()) {


                                if (Child3.tagName()=="P1") IoGraphos.P1=Child3.firstChild().toText().data().toDouble();
                                if (Child3.tagName()=="P2") IoGraphos.P2=Child3.firstChild().toText().data().toDouble();
                                if (Child3.tagName()=="b1") IoGraphos.b1=Child3.firstChild().toText().data().toDouble();
                                if (Child3.tagName()=="b2") IoGraphos.b2=Child3.firstChild().toText().data().toDouble();

                                if (Child3.tagName()=="RadialePart") {
                                    QDomElement Component4=Child3.toElement();
                                    QDomElement Child4=Component4.firstChild().toElement();

                                    while (!Child4.isNull()) {


                                        if (Child4.tagName()=="CDist") {
                                            temporal=Child4.firstChild().toText().data(); //leer como string para luego cortar
                                            IoGraphos.CDistx=temporal.split(" ").at(0).toDouble();
                                            IoGraphos.CDisty=temporal.split(" ").at(1).toDouble();
                                            temporal="";}

                                        if (Child4.tagName()=="CoeffDist") {

                                            RadialCount=RadialCount+1;

                                            if (RadialCount==1) IoGraphos.K1=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==2) IoGraphos.K2=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==3) IoGraphos.K3=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==4) IoGraphos.K4=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==5) IoGraphos.K5=Child4.firstChild().toText().data().toDouble();

                                        }

                                        Child4 = Child4.nextSibling().toElement();
                                    }
                                }

                                Child3 = Child3.nextSibling().toElement();
                            }
                        } else {
                            // Caso de la Radial BASIC y EXTENDED
                            if (Child2.tagName()=="ModRad") {

                                QDomElement Component3b=Child2.toElement();
                                QDomElement Child3b=Component3b.firstChild().toElement();

                                while (!Child3b.isNull()) {

                                    if (Child3b.tagName()=="CDist") {
                                        temporal=Child3b.firstChild().toText().data(); //leer como string para luego cortar
                                        IoGraphos.CDistx=temporal.split(" ").at(0).toDouble();
                                        IoGraphos.CDisty=temporal.split(" ").at(1).toDouble();
                                        temporal="";}

                                    if (Child3b.tagName()=="CoeffDist") {
                                        RadialCount=RadialCount+1;

                                        if (RadialCount==1) IoGraphos.K1=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==2) IoGraphos.K2=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==3) IoGraphos.K3=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==4) IoGraphos.K4=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==5) IoGraphos.K5=Child3b.firstChild().toText().data().toDouble();
                                    }
                                    Child3b = Child3b.nextSibling().toElement();
                                }
                            }
                        }
                        Child2 = Child2.nextSibling().toElement();
                    }
                }
                // Next child
                Child = Child.nextSibling().toElement();
            }

        }

        // Next component
        Component = Component.nextSibling().toElement();
    }

    // Escritura de los valores leidos
    std::cout << "Parametros de orientacion leidos..." << std::endl;

    // IMPORTANTE, SON NECESARIOS LOS DATOS DE LA CÁMARA PARA PODER CONTINUAR LA CONVERSIÓN
    // Búsqueda del Chantier
    QString fileChantier = "";
    QStringList parts = graphosDistFileInfo.absoluteFilePath().split("Ori-");
    fileChantier = parts.at(0);
    fileChantier =fileChantier + "MicMac-LocalChantierDescripteur.xml";


    // Load xml file as raw data
    QFile f2(fileChantier);
    if (!f2.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        std::cerr << "Error while loading Chantier file" << std::endl;


        // Si no hay archivo, hay que introducir la info de la cámara
        int ret = QMessageBox::warning(this, tr("PRG"),
        tr("There is not Chantier file.\n"
        "Necessary insert the camera parameters to carry on the conversion"),
        QMessageBox::Ok);

        return;
    }else{
        std::cout << "Chantier file detected..." << std::endl;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f2);
    f2.close();

    bool isNumeric = false;

    QDomElement rootCH=xmlBOM.documentElement();// Extract the root markup
    QDomElement ComponentCH=rootCH.firstChild().toElement();// Get the first child of the root
    while(!ComponentCH.isNull()) {// Loop while there is a child

        std::cout << "Chantier file read..." << ComponentCH.tagName().toStdString() << std::endl;

        if (ComponentCH.tagName()=="ChantierDescripteur") {
            QDomElement ChildCH=ComponentCH.firstChild().toElement();// Get the first child of the component

            while(!ChildCH.isNull()) {// Loop while there is a child

                if (ChildCH.tagName()=="LocCamDataBase") {
                    QDomElement ChildCH2=ChildCH.firstChild().toElement();// Get the first child of the component

                    while(!ChildCH2.isNull()) {
                        if (ChildCH2.tagName()=="CameraEntry") {
                            QDomElement ChildCH3=ChildCH2.firstChild().toElement();
                            while(!ChildCH3.isNull()) {
                                if (ChildCH3.tagName()=="Name") IoGraphos.Name=ChildCH3.firstChild().toText().data().simplified();

                                if (ChildCH3.tagName()=="SzCaptMm") {
                                    temporal=ChildCH3.firstChild().toText().data().simplified();
                                    IoGraphos.SzCaptMmx=temporal.split(" ").at(0).toDouble();
                                    IoGraphos.SzCaptMmy=temporal.split(" ").at(1).toDouble();
                                    temporal="";}
                                ChildCH3 = ChildCH3.nextSibling().toElement();
                            }
                        }
                        ChildCH2 = ChildCH2.nextSibling().toElement();
                    }
                } else if (ChildCH.tagName()=="KeyedNamesAssociations") {
                    // Búsqueda de la focal teórica
                    QDomElement ChildCH2b=ChildCH.firstChild().toElement();
                    while(!ChildCH2b.isNull()) {
                        if (ChildCH2b.tagName()=="Calcs") {
                            QDomElement ChildCH3b=ChildCH2b.firstChild().toElement();
                            while(!ChildCH3b.isNull()) {
                            if (ChildCH3b.tagName()=="Direct") {
                                    QDomElement ChildCH4b=ChildCH3b.firstChild().toElement();
                                    while(!ChildCH4b.isNull()) {
                                        if (ChildCH4b.tagName()=="CalcName") {
                                            //Como hay dos nodos con el mismo nombre y jerarquía, la única forma de distinguirlos en pq uno es texto y el otro número
                                            ChildCH4b.firstChild().toText().data().toDouble(&isNumeric);
                                            if(isNumeric == true) IoGraphos.focalMm=ChildCH4b.firstChild().toText().data().toDouble();

                                        }
                                    ChildCH4b = ChildCH4b.nextSibling().toElement();
                                    }
                                }
                            ChildCH3b = ChildCH3b.nextSibling().toElement();
                            }
                        }
                    ChildCH2b = ChildCH2b.nextSibling().toElement();
                    }
                }
                ChildCH = ChildCH.nextSibling().toElement();
            }
        }
        ComponentCH = ComponentCH.nextSibling().toElement();// Next component
    }

    //Inicialización de las estructuras básicas
    AgisoftCalib IoAgisoft = {}; //Inicializar {y poner a cero}
    PhotomodelerCalib IoPhotomodeler = {};
    BalancedCalib IoBalanced = {};

    int control_Apero2X=0;
    control_Apero2X = Apero2X(IoGraphos, IoAgisoft,IoPhotomodeler, IoBalanced);

    //3. LLamar al escritor
    AgisoftXMLWriter(fileXMLAgisoft, IoAgisoft);
}

void MainWindowGRAPHOS::on_actionExport_BalancedDistortion(){
    QString initPath = mSettings->value("app/lastoutputpath").toString();
    if (initPath.isEmpty())
        initPath = QDir::homePath();

    QString fileOut = "";
    QString filters("txt file (*.txt)");
    QString defaultFilter="txt file (*.txt)";

    fileOut = QFileDialog::getSaveFileName(this, tr("Dense Model"),
                                                initPath,
                                                filters, &defaultFilter);
    if (fileOut.isEmpty()) {
        return;
    }

    GraphosCalib IoGraphos  = {}; //Inicializar {y poner a cero}
    QString temporal;


    std::cout << "Inicializacion de la herramienta..." << std::endl;

    //Leer el archivo XML
    QFileInfo graphosDistFileInfo(mProject->getBasePath()+"/Ori-"+mProject->getCurrentOrientation()+"/AutoCal_Foc-17000_Cam-TheCamera.xml");

    //The QDomDocument class represents an XML document.
    QDomDocument xmlBOM;
    // Load xml file as raw data
    QFile f(graphosDistFileInfo.absoluteFilePath());
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        std::cerr << "Error while loading file" << std::endl;
        return; // return 1;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f);
    f.close();


    std::cout << "Inicio de la lectura del archivo de Apero..." << std::endl;


    // Extract the root markup
    QDomElement root=xmlBOM.documentElement();

    // Display root data
    std::cout << "Type = " << root.tagName().toStdString() << std::endl;

    int RadialCount=0;

    // Get the first child of the root (Markup COMPONENT is expected)
    QDomElement Component=root.firstChild().toElement();

    // Loop while there is a child
    while(!Component.isNull())
    {
        // Check if the child tag name is "CalibrationInternConique"
        if (Component.tagName()=="CalibrationInternConique")
        {
            // Get the first child of the component
            QDomElement Child=Component.firstChild().toElement();


            // Read each child of the component node
            while (!Child.isNull())
            {
                // Leer la CABECERA
                if (Child.tagName()=="KnownConv") IoGraphos.KnownConv=Child.firstChild().toText().data();
                if (Child.tagName()=="F") IoGraphos.F=Child.firstChild().toText().data().toDouble();
                if (Child.tagName()=="PP") {
                    temporal=Child.firstChild().toText().data(); //leer como string para luego cortar
                    IoGraphos.PPx=temporal.split(" ").at(0).toDouble();
                    IoGraphos.PPy=temporal.split(" ").at(1).toDouble();
                    temporal="";}
                if (Child.tagName()=="SzIm") {
                    temporal=Child.firstChild().toText().data(); //leer como string para luego cortar
                    IoGraphos.SzImx=temporal.split(" ").at(0).toInt();
                    IoGraphos.SzImy=temporal.split(" ").at(1).toInt();
                    temporal="";}




                if (Child.tagName()=="CalibDistortion") {

                    QDomElement Component2=Child.toElement();
                    QDomElement Child2=Component2.firstChild().toElement();

                    while (!Child2.isNull()) {

                        if (Child2.tagName()=="ModPhgrStd") {

                            QDomElement Component3=Child2.toElement();
                            QDomElement Child3=Component3.firstChild().toElement();

                            while (!Child3.isNull()) {


                                if (Child3.tagName()=="P1") IoGraphos.P1=Child3.firstChild().toText().data().toDouble();
                                if (Child3.tagName()=="P2") IoGraphos.P2=Child3.firstChild().toText().data().toDouble();
                                if (Child3.tagName()=="b1") IoGraphos.b1=Child3.firstChild().toText().data().toDouble();
                                if (Child3.tagName()=="b2") IoGraphos.b2=Child3.firstChild().toText().data().toDouble();

                                if (Child3.tagName()=="RadialePart") {
                                    QDomElement Component4=Child3.toElement();
                                    QDomElement Child4=Component4.firstChild().toElement();

                                    while (!Child4.isNull()) {


                                        if (Child4.tagName()=="CDist") {
                                            temporal=Child4.firstChild().toText().data(); //leer como string para luego cortar
                                            IoGraphos.CDistx=temporal.split(" ").at(0).toDouble();
                                            IoGraphos.CDisty=temporal.split(" ").at(1).toDouble();
                                            temporal="";}

                                        if (Child4.tagName()=="CoeffDist") {

                                            RadialCount=RadialCount+1;

                                            if (RadialCount==1) IoGraphos.K1=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==2) IoGraphos.K2=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==3) IoGraphos.K3=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==4) IoGraphos.K4=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==5) IoGraphos.K5=Child4.firstChild().toText().data().toDouble();

                                        }

                                        Child4 = Child4.nextSibling().toElement();
                                    }
                                }

                                Child3 = Child3.nextSibling().toElement();
                            }
                        } else {
                            // Caso de la Radial BASIC y EXTENDED
                            if (Child2.tagName()=="ModRad") {

                                QDomElement Component3b=Child2.toElement();
                                QDomElement Child3b=Component3b.firstChild().toElement();

                                while (!Child3b.isNull()) {

                                    if (Child3b.tagName()=="CDist") {
                                        temporal=Child3b.firstChild().toText().data(); //leer como string para luego cortar
                                        IoGraphos.CDistx=temporal.split(" ").at(0).toDouble();
                                        IoGraphos.CDisty=temporal.split(" ").at(1).toDouble();
                                        temporal="";}

                                    if (Child3b.tagName()=="CoeffDist") {
                                        RadialCount=RadialCount+1;

                                        if (RadialCount==1) IoGraphos.K1=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==2) IoGraphos.K2=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==3) IoGraphos.K3=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==4) IoGraphos.K4=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==5) IoGraphos.K5=Child3b.firstChild().toText().data().toDouble();
                                    }
                                    Child3b = Child3b.nextSibling().toElement();
                                }
                            }
                        }
                        Child2 = Child2.nextSibling().toElement();
                    }
                }
                // Next child
                Child = Child.nextSibling().toElement();
            }

        }

        // Next component
        Component = Component.nextSibling().toElement();
    }

    // Escritura de los valores leidos
    std::cout << "Parametros de orientacion leidos..." << std::endl;

    // IMPORTANTE, SON NECESARIOS LOS DATOS DE LA CÁMARA PARA PODER CONTINUAR LA CONVERSIÓN
    // Búsqueda del Chantier
    QString fileChantier = "";
    QStringList parts = graphosDistFileInfo.absoluteFilePath().split("Ori-");
    fileChantier = parts.at(0);
    fileChantier =fileChantier + "MicMac-LocalChantierDescripteur.xml";


    // Load xml file as raw data
    QFile f2(fileChantier);
    if (!f2.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        std::cerr << "Error while loading Chantier file" << std::endl;


        // Si no hay archivo, hay que introducir la info de la cámara
        int ret = QMessageBox::warning(this, tr("PRG"),
        tr("There is not Chantier file.\n"
        "Necessary insert the camera parameters to carry on the conversion"),
        QMessageBox::Ok);

        return;
    }else{
        std::cout << "Chantier file detected..." << std::endl;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f2);
    f2.close();

    bool isNumeric = false;

    QDomElement rootCH=xmlBOM.documentElement();// Extract the root markup
    QDomElement ComponentCH=rootCH.firstChild().toElement();// Get the first child of the root
    while(!ComponentCH.isNull()) {// Loop while there is a child

        std::cout << "Chantier file read..." << ComponentCH.tagName().toStdString() << std::endl;

        if (ComponentCH.tagName()=="ChantierDescripteur") {
            QDomElement ChildCH=ComponentCH.firstChild().toElement();// Get the first child of the component

            while(!ChildCH.isNull()) {// Loop while there is a child

                if (ChildCH.tagName()=="LocCamDataBase") {
                    QDomElement ChildCH2=ChildCH.firstChild().toElement();// Get the first child of the component

                    while(!ChildCH2.isNull()) {
                        if (ChildCH2.tagName()=="CameraEntry") {
                            QDomElement ChildCH3=ChildCH2.firstChild().toElement();
                            while(!ChildCH3.isNull()) {
                                if (ChildCH3.tagName()=="Name") IoGraphos.Name=ChildCH3.firstChild().toText().data().simplified();

                                if (ChildCH3.tagName()=="SzCaptMm") {
                                    temporal=ChildCH3.firstChild().toText().data().simplified();
                                    IoGraphos.SzCaptMmx=temporal.split(" ").at(0).toDouble();
                                    IoGraphos.SzCaptMmy=temporal.split(" ").at(1).toDouble();
                                    temporal="";}
                                ChildCH3 = ChildCH3.nextSibling().toElement();
                            }
                        }
                        ChildCH2 = ChildCH2.nextSibling().toElement();
                    }
                } else if (ChildCH.tagName()=="KeyedNamesAssociations") {
                    // Búsqueda de la focal teórica
                    QDomElement ChildCH2b=ChildCH.firstChild().toElement();
                    while(!ChildCH2b.isNull()) {
                        if (ChildCH2b.tagName()=="Calcs") {
                            QDomElement ChildCH3b=ChildCH2b.firstChild().toElement();
                            while(!ChildCH3b.isNull()) {
                            if (ChildCH3b.tagName()=="Direct") {
                                    QDomElement ChildCH4b=ChildCH3b.firstChild().toElement();
                                    while(!ChildCH4b.isNull()) {
                                        if (ChildCH4b.tagName()=="CalcName") {
                                            //Como hay dos nodos con el mismo nombre y jerarquía, la única forma de distinguirlos en pq uno es texto y el otro número
                                            ChildCH4b.firstChild().toText().data().toDouble(&isNumeric);
                                            if(isNumeric == true) IoGraphos.focalMm=ChildCH4b.firstChild().toText().data().toDouble();

                                        }
                                    ChildCH4b = ChildCH4b.nextSibling().toElement();
                                    }
                                }
                            ChildCH3b = ChildCH3b.nextSibling().toElement();
                            }
                        }
                    ChildCH2b = ChildCH2b.nextSibling().toElement();
                    }
                }
                ChildCH = ChildCH.nextSibling().toElement();
            }
        }
        ComponentCH = ComponentCH.nextSibling().toElement();// Next component
    }

    //Inicialización de las estructuras básicas
    AgisoftCalib IoAgisoft = {}; //Inicializar {y poner a cero}
    PhotomodelerCalib IoPhotomodeler = {};
    BalancedCalib IoBalanced = {};

    int control_Apero2X=0;
    control_Apero2X = Apero2X(IoGraphos, IoAgisoft,IoPhotomodeler, IoBalanced);

    BalancedTxtWriter(fileOut,IoBalanced);
}

void MainWindowGRAPHOS::on_actionExport_GRAPHOSDistortion(){
    QString initPath = mSettings->value("app/lastoutputpath").toString();
    if (initPath.isEmpty())
        initPath = QDir::homePath();

    QString fileXMLGRAPHOS = "";
    QString filters("XML file (*.xml)");
    QString defaultFilter="XML file (*.xml)";

    fileXMLGRAPHOS = QFileDialog::getSaveFileName(this, tr("Dense Model"),
                                                initPath,
                                                filters, &defaultFilter);
    if (fileXMLGRAPHOS.isEmpty()) {
        return;
    }

    QFileInfo graphosDistFileInfo(mProject->getBasePath()+"/Ori-"+mProject->getCurrentOrientation()+"/AutoCal_Foc-17000_Cam-TheCamera.xml");

    QFile(graphosDistFileInfo.absoluteFilePath()).copy(fileXMLGRAPHOS);

}

void MainWindowGRAPHOS::on_actionExport_PhotomodellerDistortion(){
    QString initPath = mSettings->value("app/lastoutputpath").toString();
    if (initPath.isEmpty())
        initPath = QDir::homePath();

    QString fileOut = "";
    QString filters("txt file (*.txt)");
    QString defaultFilter="txt file (*.txt)";

    fileOut = QFileDialog::getSaveFileName(this, tr("Dense Model"),
                                                initPath,
                                                filters, &defaultFilter);
    if (fileOut.isEmpty()) {
        return;
    }

    GraphosCalib IoGraphos  = {}; //Inicializar {y poner a cero}
    QString temporal;


    std::cout << "Inicializacion de la herramienta..." << std::endl;

    //Leer el archivo XML
    QFileInfo graphosDistFileInfo(mProject->getBasePath()+"/Ori-"+mProject->getCurrentOrientation()+"/AutoCal_Foc-17000_Cam-TheCamera.xml");

    //The QDomDocument class represents an XML document.
    QDomDocument xmlBOM;
    // Load xml file as raw data
    QFile f(graphosDistFileInfo.absoluteFilePath());
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        std::cerr << "Error while loading file" << std::endl;
        return; // return 1;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f);
    f.close();


    std::cout << "Inicio de la lectura del archivo de Apero..." << std::endl;


    // Extract the root markup
    QDomElement root=xmlBOM.documentElement();

    // Display root data
    std::cout << "Type = " << root.tagName().toStdString() << std::endl;

    int RadialCount=0;

    // Get the first child of the root (Markup COMPONENT is expected)
    QDomElement Component=root.firstChild().toElement();

    // Loop while there is a child
    while(!Component.isNull())
    {
        // Check if the child tag name is "CalibrationInternConique"
        if (Component.tagName()=="CalibrationInternConique")
        {
            // Get the first child of the component
            QDomElement Child=Component.firstChild().toElement();


            // Read each child of the component node
            while (!Child.isNull())
            {
                // Leer la CABECERA
                if (Child.tagName()=="KnownConv") IoGraphos.KnownConv=Child.firstChild().toText().data();
                if (Child.tagName()=="F") IoGraphos.F=Child.firstChild().toText().data().toDouble();
                if (Child.tagName()=="PP") {
                    temporal=Child.firstChild().toText().data(); //leer como string para luego cortar
                    IoGraphos.PPx=temporal.split(" ").at(0).toDouble();
                    IoGraphos.PPy=temporal.split(" ").at(1).toDouble();
                    temporal="";}
                if (Child.tagName()=="SzIm") {
                    temporal=Child.firstChild().toText().data(); //leer como string para luego cortar
                    IoGraphos.SzImx=temporal.split(" ").at(0).toInt();
                    IoGraphos.SzImy=temporal.split(" ").at(1).toInt();
                    temporal="";}




                if (Child.tagName()=="CalibDistortion") {

                    QDomElement Component2=Child.toElement();
                    QDomElement Child2=Component2.firstChild().toElement();

                    while (!Child2.isNull()) {

                        if (Child2.tagName()=="ModPhgrStd") {

                            QDomElement Component3=Child2.toElement();
                            QDomElement Child3=Component3.firstChild().toElement();

                            while (!Child3.isNull()) {


                                if (Child3.tagName()=="P1") IoGraphos.P1=Child3.firstChild().toText().data().toDouble();
                                if (Child3.tagName()=="P2") IoGraphos.P2=Child3.firstChild().toText().data().toDouble();
                                if (Child3.tagName()=="b1") IoGraphos.b1=Child3.firstChild().toText().data().toDouble();
                                if (Child3.tagName()=="b2") IoGraphos.b2=Child3.firstChild().toText().data().toDouble();

                                if (Child3.tagName()=="RadialePart") {
                                    QDomElement Component4=Child3.toElement();
                                    QDomElement Child4=Component4.firstChild().toElement();

                                    while (!Child4.isNull()) {


                                        if (Child4.tagName()=="CDist") {
                                            temporal=Child4.firstChild().toText().data(); //leer como string para luego cortar
                                            IoGraphos.CDistx=temporal.split(" ").at(0).toDouble();
                                            IoGraphos.CDisty=temporal.split(" ").at(1).toDouble();
                                            temporal="";}

                                        if (Child4.tagName()=="CoeffDist") {

                                            RadialCount=RadialCount+1;

                                            if (RadialCount==1) IoGraphos.K1=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==2) IoGraphos.K2=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==3) IoGraphos.K3=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==4) IoGraphos.K4=Child4.firstChild().toText().data().toDouble();
                                            if (RadialCount==5) IoGraphos.K5=Child4.firstChild().toText().data().toDouble();

                                        }

                                        Child4 = Child4.nextSibling().toElement();
                                    }
                                }

                                Child3 = Child3.nextSibling().toElement();
                            }
                        } else {
                            // Caso de la Radial BASIC y EXTENDED
                            if (Child2.tagName()=="ModRad") {

                                QDomElement Component3b=Child2.toElement();
                                QDomElement Child3b=Component3b.firstChild().toElement();

                                while (!Child3b.isNull()) {

                                    if (Child3b.tagName()=="CDist") {
                                        temporal=Child3b.firstChild().toText().data(); //leer como string para luego cortar
                                        IoGraphos.CDistx=temporal.split(" ").at(0).toDouble();
                                        IoGraphos.CDisty=temporal.split(" ").at(1).toDouble();
                                        temporal="";}

                                    if (Child3b.tagName()=="CoeffDist") {
                                        RadialCount=RadialCount+1;

                                        if (RadialCount==1) IoGraphos.K1=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==2) IoGraphos.K2=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==3) IoGraphos.K3=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==4) IoGraphos.K4=Child3b.firstChild().toText().data().toDouble();
                                        if (RadialCount==5) IoGraphos.K5=Child3b.firstChild().toText().data().toDouble();
                                    }
                                    Child3b = Child3b.nextSibling().toElement();
                                }
                            }
                        }
                        Child2 = Child2.nextSibling().toElement();
                    }
                }
                // Next child
                Child = Child.nextSibling().toElement();
            }

        }

        // Next component
        Component = Component.nextSibling().toElement();
    }

    // Escritura de los valores leidos
    std::cout << "Parametros de orientacion leidos..." << std::endl;

    // IMPORTANTE, SON NECESARIOS LOS DATOS DE LA CÁMARA PARA PODER CONTINUAR LA CONVERSIÓN
    // Búsqueda del Chantier
    QString fileChantier = "";
    QStringList parts = graphosDistFileInfo.absoluteFilePath().split("Ori-");
    fileChantier = parts.at(0);
    fileChantier =fileChantier + "MicMac-LocalChantierDescripteur.xml";


    // Load xml file as raw data
    QFile f2(fileChantier);
    if (!f2.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        std::cerr << "Error while loading Chantier file" << std::endl;


        // Si no hay archivo, hay que introducir la info de la cámara
        int ret = QMessageBox::warning(this, tr("PRG"),
        tr("There is not Chantier file.\n"
        "Necessary insert the camera parameters to carry on the conversion"),
        QMessageBox::Ok);

        return;
    }else{
        std::cout << "Chantier file detected..." << std::endl;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f2);
    f2.close();

    bool isNumeric = false;

    QDomElement rootCH=xmlBOM.documentElement();// Extract the root markup
    QDomElement ComponentCH=rootCH.firstChild().toElement();// Get the first child of the root
    while(!ComponentCH.isNull()) {// Loop while there is a child

        std::cout << "Chantier file read..." << ComponentCH.tagName().toStdString() << std::endl;

        if (ComponentCH.tagName()=="ChantierDescripteur") {
            QDomElement ChildCH=ComponentCH.firstChild().toElement();// Get the first child of the component

            while(!ChildCH.isNull()) {// Loop while there is a child

                if (ChildCH.tagName()=="LocCamDataBase") {
                    QDomElement ChildCH2=ChildCH.firstChild().toElement();// Get the first child of the component

                    while(!ChildCH2.isNull()) {
                        if (ChildCH2.tagName()=="CameraEntry") {
                            QDomElement ChildCH3=ChildCH2.firstChild().toElement();
                            while(!ChildCH3.isNull()) {
                                if (ChildCH3.tagName()=="Name") IoGraphos.Name=ChildCH3.firstChild().toText().data().simplified();

                                if (ChildCH3.tagName()=="SzCaptMm") {
                                    temporal=ChildCH3.firstChild().toText().data().simplified();
                                    IoGraphos.SzCaptMmx=temporal.split(" ").at(0).toDouble();
                                    IoGraphos.SzCaptMmy=temporal.split(" ").at(1).toDouble();
                                    temporal="";}
                                ChildCH3 = ChildCH3.nextSibling().toElement();
                            }
                        }
                        ChildCH2 = ChildCH2.nextSibling().toElement();
                    }
                } else if (ChildCH.tagName()=="KeyedNamesAssociations") {
                    // Búsqueda de la focal teórica
                    QDomElement ChildCH2b=ChildCH.firstChild().toElement();
                    while(!ChildCH2b.isNull()) {
                        if (ChildCH2b.tagName()=="Calcs") {
                            QDomElement ChildCH3b=ChildCH2b.firstChild().toElement();
                            while(!ChildCH3b.isNull()) {
                            if (ChildCH3b.tagName()=="Direct") {
                                    QDomElement ChildCH4b=ChildCH3b.firstChild().toElement();
                                    while(!ChildCH4b.isNull()) {
                                        if (ChildCH4b.tagName()=="CalcName") {
                                            //Como hay dos nodos con el mismo nombre y jerarquía, la única forma de distinguirlos en pq uno es texto y el otro número
                                            ChildCH4b.firstChild().toText().data().toDouble(&isNumeric);
                                            if(isNumeric == true) IoGraphos.focalMm=ChildCH4b.firstChild().toText().data().toDouble();

                                        }
                                    ChildCH4b = ChildCH4b.nextSibling().toElement();
                                    }
                                }
                            ChildCH3b = ChildCH3b.nextSibling().toElement();
                            }
                        }
                    ChildCH2b = ChildCH2b.nextSibling().toElement();
                    }
                }
                ChildCH = ChildCH.nextSibling().toElement();
            }
        }
        ComponentCH = ComponentCH.nextSibling().toElement();// Next component
    }

    //Inicialización de las estructuras básicas
    AgisoftCalib IoAgisoft = {}; //Inicializar {y poner a cero}
    PhotomodelerCalib IoPhotomodeler = {};
    BalancedCalib IoBalanced = {};

    int control_Apero2X=0;
    control_Apero2X = Apero2X(IoGraphos, IoAgisoft,IoPhotomodeler, IoBalanced);

    PhotomodellerTxtWriter(fileOut, IoPhotomodeler);
}

void MainWindowGRAPHOS::AgisoftXMLWriter(QString fileXMLAgisoft, MainWindowGRAPHOS::AgisoftCalib IoAgisoft)
{
    QFile f_out(fileXMLAgisoft);
    QTextStream out(&f_out);
    out.setCodec("UTF-8");
    f_out.open(QIODevice::WriteOnly);
    out << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
        << "<calibration>\n"
        << "  <projection>" << IoAgisoft.projection << "</projection>\n"
        << "  <width>" << IoAgisoft.width << "</width>\n"
        << "  <height>" << IoAgisoft.height << "</height>\n"
        << "  <fx>" << QString::number(IoAgisoft.fx,'e',16) << "</fx>\n"
        << "  <fy>" << QString::number(IoAgisoft.fy,'e',16) << "</fy>\n"
        << "  <cx>" << QString::number(IoAgisoft.cx,'e',16) << "</cx>\n"
        << "  <cy>" << QString::number(IoAgisoft.cy,'e',16) << "</cy>\n"
        << "  <skew>" << QString::number(IoAgisoft.skew,'e',16) << "</skew>\n"
        << "  <k1>" << QString::number(IoAgisoft.K1,'e',16) << "</k1>\n"
        << "  <k2>" << QString::number(IoAgisoft.K2,'e',16) << "</k2>\n"
        << "  <k3>" << QString::number(IoAgisoft.K3,'e',16) << "</k3>\n"
        << "  <k4>" << QString::number(IoAgisoft.K4,'e',16) << "</k4>\n"
        << "  <p1>" << QString::number(IoAgisoft.P1,'e',16) << "</p1>\n"
        << "  <p2>" << QString::number(IoAgisoft.P2,'e',16) << "</p2>\n"
        << "  <date>" << IoAgisoft.date << "</date>\n"
        << "</calibration>\n";
    f_out.close();
}

void MainWindowGRAPHOS::PhotomodellerTxtWriter(QString destfile, MainWindowGRAPHOS::PhotomodelerCalib IoPhotomodeller)
{
    QFile f_out(destfile);
    QTextStream out(&f_out);
    out.setCodec("UTF-8");
    f_out.open(QIODevice::WriteOnly);
    out << "Photomodeller calibration\n"
        << "Focal (mm): " << IoPhotomodeller.F << "\n"
        << "Xp (mm): " << QString::number(IoPhotomodeller.Xp) << "\n"
        << "Xy (mm): " << QString::number(IoPhotomodeller.Yp) << "\n"
        << "Fw (mm): " << QString::number(IoPhotomodeller.Fw,'e',16) << "\n"
        << "Fh (mm): " << QString::number(IoPhotomodeller.Fh,'e',16) << "\n"
        << "K1 (mm-2): " << QString::number(IoPhotomodeller.K1,'e',16) << "\n"
        << "K2 (mm-4): " << QString::number(IoPhotomodeller.K2,'e',16) << "\n"
        << "K3 (mm-6): " << QString::number(IoPhotomodeller.K3,'e',16) << "\n"
        << "P1 (mm-1): " << QString::number(IoPhotomodeller.P1,'e',16) << "\n"
        << "P2 (mm-1): " << QString::number(IoPhotomodeller.P2,'e',16);

    f_out.close();
}

void MainWindowGRAPHOS::BalancedTxtWriter(QString destfile, MainWindowGRAPHOS::BalancedCalib IoBalanced)
{
    QFile f_out(destfile);
    QTextStream out(&f_out);
    out.setCodec("UTF-8");
    f_out.open(QIODevice::WriteOnly);
    out << "Balanced calibration\n"
        << "Fb (mm): " << QString::number(IoBalanced.fb,'e',16) << "\n"
        << "a0: " << QString::number(IoBalanced.a0,'e',16) << "\n"
        << "a1 (mm-2): " << QString::number(IoBalanced.a1,'e',16) << "\n"
        << "a2 (mm-4): " << QString::number(IoBalanced.a2,'e',16);

    f_out.close();
}

int MainWindowGRAPHOS::Apero2X(MainWindowGRAPHOS::GraphosCalib IoGraphos, MainWindowGRAPHOS::AgisoftCalib &IoAgisoft,MainWindowGRAPHOS::PhotomodelerCalib &IoPhotomodeler,MainWindowGRAPHOS::BalancedCalib &IoBalanced)
{
    //1. Calcular el pixel size
    double pix_size_x=IoGraphos.SzCaptMmx/IoGraphos.SzImx;
    double pix_size_y=IoGraphos.SzCaptMmy/IoGraphos.SzImy;

    //1.b. Elegir el valor medio
    double pix_size=(pix_size_x+pix_size_y)/2;

    std::cout << "Pixel size = " << pix_size << std::endl;

    //2. Conversión a Agisoft
    IoAgisoft.projection = "frame"; // Porque es el único modelo que soporta este conversor
    IoAgisoft.width=IoGraphos.SzImx;
    IoAgisoft.height=IoGraphos.SzImy;
    // La focal se mantiene porque son las misma unidades
    IoAgisoft.fx = IoGraphos.F*(1+IoGraphos.b1); //En la ecuación de fraser b1 multiplica a X unicamente
    IoAgisoft.fy = IoGraphos.F;
    IoAgisoft.cx= IoGraphos.PPx;
    IoAgisoft.cy=IoGraphos.PPy;

    // Disclaimer de la conversión
    std::cout << "Skew = " <<  qAtan(1/IoGraphos.b2)/(qAtan(1)*4)*180 << std::endl;

    IoAgisoft.skew=-IoAgisoft.fx*IoGraphos.b2; //En Graphos el Skew viene dado por B2, pero en el ruso lee el valor de A[0,1]
    IoAgisoft.K1=IoGraphos.K1*pow(IoGraphos.F,2);
    IoAgisoft.K2=IoGraphos.K2*pow(IoGraphos.F,4);
    IoAgisoft.K3=IoGraphos.K3*pow(IoGraphos.F,6);
    IoAgisoft.K4=IoGraphos.K4*pow(IoGraphos.F,8);
    IoAgisoft.P1=IoGraphos.P2*IoGraphos.F;//Ojo están intercambiados
    IoAgisoft.P2=IoGraphos.P1*IoGraphos.F;

    //Hora de la conversión (por poner algo)
    QDateTime dateTime = dateTime.currentDateTime();
    QString dateTimeString = dateTime.toString("yyyy-MM-ddThh:mm:ssZ");
    IoAgisoft.date=dateTimeString;


    IoPhotomodeler.F=IoGraphos.F*pix_size; //pixel*(mm/pix)
    //se podría usar promedio(f*b1,f)¿pero como afectaría a la relación de aspecto

    IoPhotomodeler.Xp=IoGraphos.PPx*pix_size_x;
    IoPhotomodeler.Yp=IoGraphos.PPy*pix_size_y;

    IoPhotomodeler.Fw=IoGraphos.SzCaptMmx; //Ancho en mm
    IoPhotomodeler.Fh=IoGraphos.SzCaptMmy;

    // Inversión del signo
    IoPhotomodeler.K1=-IoGraphos.K1*pow(1/pix_size,2);
    IoPhotomodeler.K2=-IoGraphos.K2*pow(1/pix_size,4);
    IoPhotomodeler.K3=-IoGraphos.K3*pow(1/pix_size,6);
    IoPhotomodeler.P1=-IoGraphos.P1/pix_size;
    IoPhotomodeler.P2=-IoGraphos.P2/pix_size;
    IoPhotomodeler.date=QDateTime::currentDateTime().toString("ddd MMM dd hh:mm:ss yyyy");

    //Modelo balanceado
    double rmax=pow(pow(IoGraphos.SzCaptMmx,2)+pow(IoGraphos.SzCaptMmy,2),0.5)/2;
    double r0=rmax*2/3;

     IoBalanced.a0=-IoPhotomodeler.K1*pow(r0,2)-IoPhotomodeler.K2*pow(r0,4);
     IoBalanced.a1=IoPhotomodeler.K1*(1-IoBalanced.a0);
     IoBalanced.a2=IoPhotomodeler.K2*(1-IoBalanced.a0);
     IoBalanced.fb=IoPhotomodeler.F/(1-IoBalanced.a0);

    //Programa ejecutado de forma correcta
    return 0;
}

void MainWindowGRAPHOS::computeMicMacSlaves(){

    QString homolPath= mProject->getBasePath() + "/" + "Homol";
    QDir homolDir(homolPath);
    removeDir(homolDir.absolutePath());
    //Copy "Homol" to project directory:
    if(!homolDir.exists())
    {
        if(!homolDir.mkdir(homolDir.absolutePath()))
        {
            QMessageBox::critical(this,tr("GRAPHOS - Error"),tr("Error making homol dir"));
            return;
        }
    }
    QString sourceFolder=mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mProject->getActiveTiePointsSet();

    QString targetFolder=mProject->getBasePath()+"/"+TAPIOCA_MATCHES_ORIGINAL_PATH;
    QDir souceDir(sourceFolder);
    QDir targetDir(targetFolder);
    while (!targetDir.exists()) {
        QDir().mkdir(targetDir.absolutePath());
    }

    if(!copyDir(souceDir.absolutePath(),targetDir.absolutePath(),false))
    {
        QString title="MainWindow::onTiePointsFinished";
        QString strError=tr("Error moving matching files to Homol");
        QMessageBox::critical(this,title,strError);
        return;
    }

    QDir slavesDir(mProject->getBasePath()+"/Ori-SlavesTMP");
    if (slavesDir.exists()) {
        removeDir(slavesDir.absolutePath());
    }
    QDir().mkdir(slavesDir.absolutePath());

    QVector<QString> projectImages = mProject->getImagesFileName();


    //Generate Input Regular Expression:
    QString inputRegExp = QString("(");

    for(int i=0; i< projectImages.size(); i++)
    {
        inputRegExp = inputRegExp + projectImages.at(i) + QString("|");
    }

    inputRegExp.replace(inputRegExp.length()-1,1,")");
    inputRegExp=mProject->getBasePath()+"/"+inputRegExp;
    //MICMAC Process:
    if(mMicMacSlavesProcess)
        delete (mMicMacSlavesProcess);
    mMicMacSlavesProcess = new MicMacComputeSlavesProcess(inputRegExp,mProject->getCurrentOrientation(),"SlavesTMP");

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setFinished(false);
    mMicMacSlavesProcess->setWorkingDir(mProject->getBasePath());
    connect(mMicMacSlavesProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mMicMacSlavesProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mMicMacSlavesProcess, SIGNAL(finished()), this, SLOT(buildMaltMultiMainImageModel()));
    connect(mProgressDialog,SIGNAL(cancel()),mMicMacSlavesProcess,SLOT(stop()));
    mMicMacSlavesProcess->start();

    mProgressDialog->show();
}

QStringList MainWindowGRAPHOS::getMicMacSlavesForMainImage(QString mainImage){
    QStringList slaveImages;
    QStringList tmpList;

    slaveImages.clear();
    double currentCoverage =0.0;
    QFileInfo MicMacSlavesFileInfo(mProject->getBasePath()+"/Ori-SlavesTMP/ImSec-"+mainImage+".xml");


    //The QDomDocument class represents an XML document.
    QDomDocument xmlBOM;
    // Load xml file as raw data
    QFile f(MicMacSlavesFileInfo.absoluteFilePath());
    if (!f.open(QIODevice::ReadOnly ))
    {
        // Error while loading file
        std::cerr << "Error while loading file" << std::endl;
    }
    // Set data into the QDomDocument before processing
    xmlBOM.setContent(&f);
    f.close();

    // Extract the root markup
    QDomElement root=xmlBOM.documentElement();

    // Get the first child of the root (Markup COMPONENT is expected)
    QDomElement Component=root.firstChild().toElement();
    // Loop while there is a child
    while(!Component.isNull())
    {
        // evaluate sols
        if (Component.tagName()=="Sols")
        {
            tmpList.clear();
//          Get the first child of the component
            QDomElement Child=Component.firstChild().toElement();

            // Read each child of the component node
            while (!Child.isNull())
            {

                if (Child.tagName()=="Images") {
                    tmpList.append(Child.text());
                }else if (Child.tagName()=="Coverage") {
                    if (Child.text().toDouble()>currentCoverage) {
                        currentCoverage = Child.text().toDouble();
                        slaveImages.clear();
                        slaveImages.append(tmpList);
                        break;
                    }
                }
                // Next child
                Child = Child.nextSibling().toElement();
            }

        }

        // Next component
        Component = Component.nextSibling().toElement();
    }
    return slaveImages;
}

void MainWindowGRAPHOS::buildMaltModel(){
    if(mProject->getImages().count() > 0){

        //Generate Input Regular Expression:
        QString inputRegExp = QString("(");
        QString fileName;
        for(int i=0; i< mProject->getImages().count(); i++){
            fileName = mProject->getImages().at(i)->getFullPath();
            fileName = fileName.right(fileName.length()-fileName.lastIndexOf(QRegExp("/"))-1);
            inputRegExp = inputRegExp + fileName + QString("|");
        }
        inputRegExp.replace(inputRegExp.length()-1,1,")");

        inputRegExp = mProject->getBasePath()+"/"+inputRegExp;

        QFileInfo nuageFile;

        switch (mDensificationWizard->getMicMacDeZoomValue()) {
        case 1:
            mDenseModelPath = "MEC-Malt/NuageImProf_STD-MALT_Etape_8.ply";
            nuageFile.setFile(mProject->getBasePath()+"/MEC-Malt/NuageImProf_STD-MALT_Etape_8.xml");
            break;
        case 2:
            mDenseModelPath = "MEC-Malt/NuageImProf_STD-MALT_Etape_7.ply";
            nuageFile.setFile(mProject->getBasePath()+"/MEC-Malt/NuageImProf_STD-MALT_Etape_7.xml");
            break;
        case 4:
            mDenseModelPath = "MEC-Malt/NuageImProf_STD-MALT_Etape_6.ply";
            nuageFile.setFile(mProject->getBasePath()+"/MEC-Malt/NuageImProf_STD-MALT_Etape_6.xml");
            break;
        default:
            mDenseModelPath = "MEC-Malt/NuageImProf_STD-MALT_Etape_7.ply";
            nuageFile.setFile(mProject->getBasePath()+"/MEC-Malt/NuageImProf_STD-MALT_Etape_7.xml");
            break;
        }



        //MICMAC Process:
        if(mMaltDensificationProcess)
            delete (mMaltDensificationProcess);
        mMaltDensificationProcess = new PW::MultiProcess(true);

        MaltProcess *densificationProcess= new MaltProcess();
        QStringList densificationInputs;
        densificationInputs.append("UrbanMNE");
        densificationInputs.append(inputRegExp);
        densificationInputs.append(mProject->getCurrentOrientation());
        if (CUDA_ENABLED) {
           densificationInputs.append("UseGpu=true");
        }

        densificationInputs.append("HrOr=true");
        densificationInputs.append("ZoomF="+QString::number(mDensificationWizard->getMicMacDeZoomValue()));
        densificationInputs.append("Regul="+QString::number(mDensificationWizard->getMicMacZRegulValue()));
        densificationInputs.append("ZPas="+QString::number(mDensificationWizard->getMicMacZPasValue()));
        densificationProcess->addIntputs(densificationInputs);

        mMaltDensificationProcess->appendProcess(densificationProcess);

        TawnyProcess *orthoProcess = new TawnyProcess();

        QDir orthoDir(mProject->getBasePath()+"/Ortho-MEC-Malt");
        orthoProcess->addIntputs(QStringList() << orthoDir.absolutePath());

        mMaltDensificationProcess->appendProcess(orthoProcess);

        Nuage2PlyProcess *plyProcess= new Nuage2PlyProcess();

        QFileInfo orthoFile(orthoDir.absolutePath()+"/Orthophotomosaic.tif");

        plyProcess->addIntputs(QStringList() << nuageFile.absoluteFilePath() << "Attr="+orthoFile.absoluteFilePath() << "Scale="+QString::number(mDensificationWizard->getMicMacDeZoomValue()));

        mMaltDensificationProcess->appendProcess(plyProcess);
        mConsole->clear();
        mProgressDialog->setModal(true);
        mProgressDialog->setRange(0,0);
        mProgressDialog->setWindowTitle("Generating Dense Model...");
        mProgressDialog->setStatusText("Generating Dense Model...");
        mProgressDialog->setFinished(false);
        mMaltDensificationProcess->start();

        connect(mMaltDensificationProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
        connect(mMaltDensificationProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
        connect(mMaltDensificationProcess, SIGNAL(finished()), this, SLOT(onMaltProcessFinished()));
        connect(mProgressDialog,SIGNAL(cancel()),mMaltDensificationProcess,SLOT(stop()));
        mProgressDialog->show();
    }

}

void MainWindowGRAPHOS::onMaltProcessFinished()
{
    QDir PyramDir(mProject->getBasePath()+"/Pyram");
    if (PyramDir.exists()) removeDir(PyramDir.absolutePath());

    if (!mMaltDensificationProcess->isStopped()){

        //Move micmac result
        QFileInfo sourcePath(mProject->getBasePath()+"/"+mDenseModelPath);


        if (!sourcePath.exists()) {
            mProgressDialog->setRange(0,1);
            mProgressDialog->setValue(1);
            mProgressDialog->setStatusText(tr("MicMac dense matching failed."));
            mProgressDialog->setFinished(true);
            return;
        }
        QFileInfo targetPath(mProject->getBasePath()+"/MicMac.ply");

        QDir().rename(sourcePath.absoluteFilePath(),targetPath.absoluteFilePath());

        //Load Dense model (ply)
        mProject->setDenseModelRelativePath(targetPath.fileName());
        QStringList modelsList;
        modelsList.append(mProject->getDenseModelFullPath());
        mCCVW2->addToDB(modelsList);

        // Process metadata:
        ccHObject* obj = mCCVW2->getGLWindow()->getSceneDB()->getFirstChild();
        ccPointCloud *cloud = static_cast<ccPointCloud*>(obj);
        unsigned cloudSize = cloud->size();

        mProject->removeProcessMetadata("Model");
        mProject->setProcessMetadataElement("Model", "CloudSize", QString::number(cloudSize)+" points");
        mProject->setProcessMetadataElement("Model", "Tool", mDensificationWizard->getDensificationMode());
        if(mDensificationWizard->getDensificationMode().contains("master"))
        {
            QString mainImages;
            QStringList mainImgNames = mDensificationWizard->getMainImages();
            foreach (QString name, mainImgNames) {
                mainImages.append(" ").append(name);
            }
            mProject->setProcessMetadataElement("Model", "MainImageNames", mainImages);
        }
        mProject->setProcessMetadataElement("Model", "DeZoom", QString::number(mDensificationWizard->getMicMacDeZoomValue()));
        mProject->setProcessMetadataElement("Model", "ZRegul", QString::number(mDensificationWizard->getMicMacZRegulValue()));
        mProject->setProcessMetadataElement("Model", "ZPas", QString::number(mDensificationWizard->getMicMacZPasValue()));


        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Dense model finished."));
        mProgressDialog->setFinished(true);

        mBasicUserGUI->setCurrentIndex(3);
        setWorkflowWidgetStatus();
        loadProjectMetadataOnProjectTree();
        loadModelsOnTree();
        updateTools();
        //Save the project
        mPersistenceManager->updateProject(mProject);
    }
    disconnect(mProgressDialog,SIGNAL(cancel()),mMaltDensificationProcess,SLOT(stop()));
}

void MainWindowGRAPHOS::buildMaltMultiMainImageModel(){
    QString homolPath= mProject->getBasePath() + "/" + "Homol";
    QDir homolDir(homolPath);
    if (homolDir.exists()) {
        removeDir(homolDir.absolutePath());
    }

    QStringList mainImgNames = mDensificationWizard->getMainImages();

    if(mainImgNames.count() > 0){

        //Create temp .ply folder
        QDir tmpPly(mProject->getBasePath()+"/tmpPLY");
        if (tmpPly.exists()) {
            removeDir(tmpPly.absolutePath());
        }
        QDir().mkdir(tmpPly.absolutePath());

        if(mMaltDensificationProcess)
            delete (mMaltDensificationProcess);
        mMaltDensificationProcess = new MultiProcess(true);

        foreach (QString mainImage, mainImgNames) {
            QStringList nNearestImages = getMicMacSlavesForMainImage(mainImage);

            //Generate Input Regular Expression:
            QString inputRegExp = QString("(");

            for(int i=0; i< nNearestImages.count(); i++){
                inputRegExp = inputRegExp + nNearestImages.at(i) + QString("|");
            }
            inputRegExp.replace(inputRegExp.length()-1,1,")");

            inputRegExp=mProject->getBasePath()+"/"+inputRegExp;
            MaltProcess *densificationProcess= new MaltProcess();
            densificationProcess->setWorkingDir(mProject->getBasePath());
            QStringList densificationInputs;
            densificationInputs.append("GeomImage");
            densificationInputs.append(inputRegExp);
            densificationInputs.append(mProject->getCurrentOrientation());
            densificationInputs.append("Master="+mainImage);
            if (CUDA_ENABLED) {
               densificationInputs.append("UseGpu=true");
            }
            densificationInputs.append("ZoomF="+QString::number(mDensificationWizard->getMicMacDeZoomValue()));
            densificationInputs.append("Regul="+QString::number(mDensificationWizard->getMicMacZRegulValue()));
            densificationInputs.append("ZPas="+QString::number(mDensificationWizard->getMicMacZPasValue()));
            densificationProcess->addIntputs(densificationInputs);

            mMaltDensificationProcess->appendProcess(densificationProcess);

            Nuage2PlyProcess *plyProcess= new Nuage2PlyProcess();

            QFileInfo mainImageFile(mProject->getBasePath()+"/"+mainImage);

            QFileInfo nuageFile;

            switch (mDensificationWizard->getMicMacDeZoomValue()) {
            case 1:
                nuageFile.setFile(mProject->getBasePath()+"/MM-Malt-Img-"+mainImageFile.baseName()+"/NuageImProf_STD-MALT_Etape_8.xml");
                break;
            case 2:
                nuageFile.setFile(mProject->getBasePath()+"/MM-Malt-Img-"+mainImageFile.baseName()+"/NuageImProf_STD-MALT_Etape_7.xml");
                break;
            case 4:
                nuageFile.setFile(mProject->getBasePath()+"/MM-Malt-Img-"+mainImageFile.baseName()+"/NuageImProf_STD-MALT_Etape_6.xml");
                break;
            default:
                nuageFile.setFile(mProject->getBasePath()+"/MM-Malt-Img-"+mainImageFile.baseName()+"/NuageImProf_STD-MALT_Etape_7.xml");
                break;
            }

            plyProcess->addIntputs(QStringList() << nuageFile.absoluteFilePath() << "Attr="+mainImageFile.absoluteFilePath() << "Scale="+QString::number(mDensificationWizard->getMicMacDeZoomValue()) << "Out="+mProject->getBasePath()+"/tmpPLY/"+mainImageFile.baseName()+".ply");

            mMaltDensificationProcess->appendProcess(plyProcess);

        }


        QStringList mergePlyInputs;
        QFileInfo plyfiles(mProject->getBasePath()+"/tmpPly/.*.ply");
        mergePlyInputs<<"MergePly" <<plyfiles.absoluteFilePath()<<"Out=MicMac.ply";

        PlyMergeProcess *mergePlyProcess= new PlyMergeProcess();
        mergePlyProcess->addIntputs(mergePlyInputs);
        mergePlyProcess->setWorkingDir(mProject->getBasePath());
        mMaltDensificationProcess->appendProcess(mergePlyProcess);

        mDenseModelPath = "MicMac.ply";

        mConsole->clear();
        mProgressDialog->setModal(true);
        mProgressDialog->setRange(0,0);
        mProgressDialog->setWindowTitle("Generating Dense Model...");
        mProgressDialog->setStatusText("Generating Dense Model...");
        mProgressDialog->setFinished(false);
        mMaltDensificationProcess->start();

        connect(mMaltDensificationProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
        connect(mMaltDensificationProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
        connect(mMaltDensificationProcess, SIGNAL(finished()), this, SLOT(onMaltProcessFinished()));
        connect(mProgressDialog,SIGNAL(cancel()),mMaltDensificationProcess,SLOT(stop()));
        mProgressDialog->show();
    }
}

void MainWindowGRAPHOS::buildC3DCModel(QString type){
    if(mProject->getImages().count() > 0){

        writeMatchesInDatFormat();

        //Generate Input Regular Expression:
        QString inputRegExp = QString("(");
        QString fileName;
        for(int i=0; i< mProject->getImages().count(); i++){
            fileName = mProject->getImages().at(i)->getFullPath();
            fileName = fileName.right(fileName.length()-fileName.lastIndexOf(QRegExp("/"))-1);
            inputRegExp = inputRegExp + fileName + QString("|");
        }
        inputRegExp.replace(inputRegExp.length()-1,1,")");

        inputRegExp = mProject->getBasePath()+"/"+inputRegExp;

        mDenseModelPath = "MicMAc.ply";

        //C3DC Process:
        if(mC3DCProcess)
            delete (mC3DCProcess);
        mC3DCProcess = new PW::C3DCProcess;
        mC3DCProcess->setWorkingDir(mProject->getBasePath());
        QStringList densificationInputs;
        densificationInputs.append("C3DC");
        densificationInputs.append(type);
        densificationInputs.append(inputRegExp);
        densificationInputs.append(mProject->getCurrentOrientation());
        if (CUDA_ENABLED) {
           densificationInputs.append("UseGpu=true");
        }
        densificationInputs.append("Out=MicMac.ply");
        densificationInputs.append("SzNorm=-1");

        mC3DCProcess->addIntputs(densificationInputs);


        mConsole->clear();
        mProgressDialog->setModal(true);
        mProgressDialog->setRange(0,0);
        mProgressDialog->setWindowTitle("Generating Dense Model...");
        mProgressDialog->setStatusText("Generating Dense Model...");
        mProgressDialog->setFinished(false);
        mC3DCProcess->start();

        connect(mC3DCProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
        connect(mC3DCProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
        connect(mC3DCProcess, SIGNAL(finished()), this, SLOT(onC3DCProcessFinished()));
        connect(mProgressDialog,SIGNAL(cancel()),mC3DCProcess,SLOT(stop()));
        mProgressDialog->show();
    }
}

void MainWindowGRAPHOS::onC3DCProcessFinished(){
    QDir PyramDir(mProject->getBasePath()+"/Pyram");
    if (PyramDir.exists()) removeDir(PyramDir.absolutePath());

    if (!mC3DCProcess->isStopped()){

        //Move micmac result
        QFileInfo sourcePath(mProject->getBasePath()+"/"+mDenseModelPath);

        if (!sourcePath.exists()) {
            mProgressDialog->setRange(0,1);
            mProgressDialog->setValue(1);
            mProgressDialog->setStatusText(tr("MicMac dense matching failed."));
            mProgressDialog->setFinished(true);
            return;
        }
        QFileInfo targetPath(mProject->getBasePath()+"/MicMac.ply");

        QDir().rename(sourcePath.absoluteFilePath(),targetPath.absoluteFilePath());

        //Load Dense model (ply)
        mProject->setDenseModelRelativePath(targetPath.fileName());
        QStringList modelsList;
        modelsList.append(mProject->getDenseModelFullPath());
        mCCVW2->addToDB(modelsList);

        // Process metadata:
        ccHObject* obj = mCCVW2->getGLWindow()->getSceneDB()->getFirstChild();
        ccPointCloud *cloud = static_cast<ccPointCloud*>(obj);
        unsigned cloudSize = cloud->size();

        mProject->removeProcessMetadata("Model");
        mProject->setProcessMetadataElement("Model", "CloudSize", QString::number(cloudSize)+" points");
        mProject->setProcessMetadataElement("Model", "Tool", mDensificationWizard->getDensificationMode());

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Dense model finished."));
        mProgressDialog->setFinished(true);

        mBasicUserGUI->setCurrentIndex(3);
        setWorkflowWidgetStatus();
        loadProjectMetadataOnProjectTree();
        loadModelsOnTree();
        updateTools();
        //Save the project
        mPersistenceManager->updateProject(mProject);
    }
    disconnect(mProgressDialog,SIGNAL(cancel()),mC3DCProcess,SLOT(stop()));
}

void MainWindowGRAPHOS::writeMatchesInDatFormat(){

    QDir homolDir(mProject->getBasePath()+"/Homol");
    if (homolDir.exists()) removeDir(homolDir.absolutePath());
    QDir().mkdir(homolDir.absolutePath());

    QVector<double> firstImagePixelsColumn;
    QVector<double> firstImagePixelsRow;
    QVector<double> secondImagePixelsColumn;
    QVector<double> secondImagePixelsRow;
    QString error;
    QVector<QString> imageslist=mProject->getImagesFileName();
    foreach (QString imageName, imageslist) {
        QFileInfo imageFile(mProject->getBasePath()+imageName);
        QDir PastisDir(mProject->getBasePath()+"/Homol/Pastis"+imageName);
        if (!PastisDir.exists()) QDir().mkdir(PastisDir.absolutePath());

        QDir matchesDir(mProject->getBasePath()+"/Matches/"+mProject->getActiveTiePointsSet()+"/Pastis"+imageName);
        QDirIterator it(matchesDir.absolutePath(), QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
        while (it.hasNext()) {
            firstImagePixelsColumn.clear();
            firstImagePixelsRow.clear();
            secondImagePixelsColumn.clear();
            secondImagePixelsRow.clear();

            it.next();
            QFileInfo matchingsInputFileTxt = it.fileInfo();
            QFileInfo matchingsOutputFileDat(mProject->getBasePath()+"/Homol/Pastis"+imageName+"/"+matchingsInputFileTxt.baseName()+"."+imageFile.suffix()+".dat");
            TiePointsIO().readTiePointsFile(matchingsInputFileTxt.absoluteFilePath(),firstImagePixelsColumn,firstImagePixelsRow,secondImagePixelsColumn,secondImagePixelsRow,error);
            TiePointsIO().WriteDatTiePoints(matchingsOutputFileDat.absoluteFilePath(),firstImagePixelsColumn,firstImagePixelsRow,secondImagePixelsColumn,secondImagePixelsRow,error);
        }
    }

}

void MainWindowGRAPHOS::on_actionBatch_ProcessTriggered(){
    removePRJ_Files();
    mTiePointsWizard = new TiePointsWizard(this,mProject->getImageByName(mProject->getImagesFileName().first())->getSize(),mProject->getBasePath());
    mDensificationWizard = new DensificationWizard(this,mProject,mMapImages,mSettings);
    mOrientationWizard = new OrientationWizard(this,mProject->getBasePath());

    mBatchProcessWizard= new BatchProcessWizard(this,mProject,mMapImages,mSettings,mTiePointsWizard,mOrientationWizard,mDensificationWizard);
    if (!mBatchProcessWizard->exec()) return;

    mBatchProcess = new PW::MultiProcess(true);



    if (mBatchProcessWizard->isComputeTiePointsChecked()) {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Caution!", "Current tie points set, orientation and dense matching will be lost.<br>Continue?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
          return;
        }
        removePreviousOrientatios();
        removePreviousDensifications();
        mProject->setSparseModelRelativePath("");
        mProject->setDenseModelRelativePath("");
        mProject->clearTiePointsSets();
        mProject->setActiveTiePointsSet("");
        mPersistenceManager->updateProject(mProject);

    }else if (mBatchProcessWizard->isComputeOrientationsChecked()) {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Caution!", "Current orientation and dense matching will be lost.<br>Continue?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
          return;

        }
        removePreviousOrientatios();
        removePreviousDensifications();
        mProject->setSparseModelRelativePath("");
        mProject->setDenseModelRelativePath("");
        mPersistenceManager->updateProject(mProject);
    }else if (mBatchProcessWizard->isComputeDenseMatchingChecked()) {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Caution!", "Current dense matching will be lost.<br>Continue?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
          return;
          mProject->setDenseModelRelativePath("");
          mPersistenceManager->updateProject(mProject);
        }
        removePreviousDensifications();
    }
        setWorkflowWidgetStatus();
        mQStackedWidget->setCurrentIndex(1);
        loadProjectMetadataOnProjectTree();
        updateImagesTree();
        updateTools();
    //////////////////// TIE POITNS PROCESS ///////////////////

    if (mBatchProcessWizard->isComputeTiePointsChecked()) {

        //remove matches folder if was created
        QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
        if(MatchesDir.exists())
            removeDir(MatchesDir.absolutePath());

        //preprocessing
        if (mTiePointsWizard->isWallisChecked()) {
            // Eliminar la carpeta preprocessing previa
            QDir postprocessingDir(mProject->getPreProcessingPath());
            if(postprocessingDir.exists())
                removeDir(postprocessingDir.absolutePath());

            while (!postprocessingDir.exists()) {
                QDir().mkdir(postprocessingDir.absolutePath());
            }

            QVector<QString> imageNameList= mProject->getImagesFileName();
            QStringList imagePathList;
            foreach (QString imageName, imageNameList) {
                imagePathList.append(mProject->getBasePath()+"/"+imageName);
            }

            mWallisProcess = new WallisBatchProcess(imagePathList,mProject->getPreProcessingPath(),mTiePointsWizard->getWallisBrithness(),mTiePointsWizard->getWallisContrast(),mTiePointsWizard->getWallisKernell(),127,mTiePointsWizard->getWallisStdDeviation());

            mBatchProcess->appendProcess(mWallisProcess);


            mTiePointsMethod.clear();
            mTiePointsMethod = mTiePointsWizard->getTiePointsMethod();
            mProject->setCaptureType(mTiePointsWizard->getCaptureConfiguration());

            if (mTiePointsMethod.value("method").contains("Tapioca")) {
                mProject->clearTiePointsSets();
                mTiePointsDescription="tapioca";
                mProject->setActiveTiePointsSet("tapioca");
                QDir homolDir(mProject->getBasePath() + "/Homol");
                if(homolDir.exists())
                    removeDir(homolDir.absolutePath());

                QDir matchesDir(mProject->getBasePath() + "/"+MATCHING_PATH);
                if(matchesDir.exists())
                    removeDir(matchesDir.absolutePath());

                QString tapiocaMode;
                int tapiocaSize=0;
                int tapiocaRange=0;
                tapiocaMode = mTiePointsMethod.value("SearchMethod");
                if (tapiocaMode.contains("Line")) {
                    tapiocaRange=mTiePointsMethod.value("Range").toInt();
                }
                int tapiocaMulScaleMin=0;
                if (tapiocaMode.contains("MulScale")) {
                    tapiocaMulScaleMin=mTiePointsMethod.value("MulScaleMin").toInt();
                    tapiocaSize=mTiePointsMethod.value("MulScaleMax").toInt();
                }else {
                    tapiocaSize = mTiePointsMethod.value("ResizeValue").toInt();
                    if (tapiocaSize==-1) {
                        QSize imageSize=mProject->getImageByName(mProject->getImagesFileName().first())->getSize();
                        if (imageSize.height()>=imageSize.width()) {
                            tapiocaSize = (int)imageSize.height();
                        }else {
                            tapiocaSize = (int)imageSize.width();
                        }
                    }
                }

                mTiePointsPath=mProject->getPreProcessingPath()+"/"+MATCHING_PATH+"/"+TAPIOCA_MATCHES_PATH;
                QVector<QString> imagesFileToProcess;
                QMap<QString,QVector<QString> > imagePairs;

                for(int i=0;i< mProject->getImages().count();i++)
                {
                    QString imageFileInProject = mProject->getImages().at(i)->getFileName();
                    imagesFileToProcess.push_back(imageFileInProject.split(".").at(0)+".tif");

                    if(i<(mProject->getImages().count()-1))
                    {
                        QVector<QString> pairs;
                        for(int tt=i+1;tt<mProject->getImages().count();tt++)
                        {
                            QString auxImageFileInProject = mProject->getImages().at(tt)->getFileName();
                            pairs.push_back(auxImageFileInProject);
                        }
                        imagePairs[imageFileInProject]=pairs;
                    }
                }


                //Generate Input Regular Expression:
                QString inputRegExp = QString("(");

                for(int i=0; i< imagesFileToProcess.size(); i++)
                {
                    inputRegExp = inputRegExp + imagesFileToProcess.at(i) + QString("|");
                }

                inputRegExp.replace(inputRegExp.length()-1,1,")");
                inputRegExp=mProject->getPreProcessingPath()+"/"+inputRegExp;
                if(mTapiocaProcess)
                    delete mTapiocaProcess;
                mTapiocaProcess = new TapiocaProcess(inputRegExp, mProject->getPreProcessingPath(), tapiocaMode,tapiocaRange, tapiocaSize,tapiocaMulScaleMin);
                mTapiocaProcess->setWorkingDir(mProject->getPreProcessingPath());

                mBatchProcess->appendProcess(mTapiocaProcess);

                TapiocaFinishedProcess *tapiocaFinished= new TapiocaFinishedProcess(mProject,mTiePointsWizard->getMinimumTapiocaMatches(),mTiePointsMetadata);
                mBatchProcess->appendProcess(tapiocaFinished);

            }else if (mTiePointsMethod.value("method").contains("MSD+SIFT")) {
                QVector<QString> imgNames = mProject->getImagesFileName();
                QStringList imageNames;
                for (int i = 0; i < imgNames.count(); ++i) {
                    imageNames.append(mProject->getPreProcessingPath().append("/").append(imgNames[i].split(".").first().append(".tif")));
                }
                //remove previous matches
                QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                if(MatchesDir.exists())
                    removeDir(MatchesDir.absolutePath());

                //nos aseguramos de que se crean estas carpetas. ¿¿Alternativa para prevenir Infinite loop??
                while (!MatchesDir.exists()) {
                    QDir().mkdir(MatchesDir.absolutePath());
                }
                QDir msdDir(mProject->getBasePath() +"/"+ MATCHING_PATH+"/MSD");
                while (!msdDir.exists()) {
                    QDir().mkdir(msdDir.absolutePath());
                }

                mTiePointsDescription="MSD";
                mProject->setActiveTiePointsSet("MSD");
                mProgressDialog->writeinConsole("\n\nStarting MSD tiepoints detector ");
                mMsdProcess = new MSDProcess(mProject->getBasePath(),imageNames,mProject->getBasePath()+"/"+MATCHING_PATH,mTiePointsMethod,mTiePointsWizard->isMSDAffineChecked(),mTiePointsWizard->getMSDAffineTilts());

                mBatchProcess->appendProcess(mMsdProcess);

                MSDFinishedProcess *MSDFinished= new MSDFinishedProcess(mProject,mTiePointsMetadata);
                mBatchProcess->appendProcess(MSDFinished);
            }else if (mTiePointsMethod.value("method").contains("ASIFT")) {
                QVector<QString> imgNames = mProject->getImagesFileName();
                QStringList imageNames;
                for (int i = 0; i < imgNames.count(); ++i) {
                    imageNames.append(mProject->getPreProcessingPath().append("/").append(imgNames[i].split(".").first().append(".tif")));
                }
                //remove previous matches
                QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                if(MatchesDir.exists())
                    removeDir(MatchesDir.absolutePath());

                while (!MatchesDir.exists()) {
                    QDir().mkdir(MatchesDir.absolutePath());
                }
                QDir asiftDir(mProject->getBasePath() +"/"+ MATCHING_PATH+"/ASIFT");
                while (!asiftDir.exists()) {
                       QDir().mkdir(asiftDir.absolutePath());
                }
                if (!mProject->getSparseModelRelativePath().isEmpty()) {
                    mProject->setSparseModelRelativePath("");
                }if (!mProject->getDenseModelRelativePath().isEmpty()) {
                    mProject->setDenseModelRelativePath("");
                }

                mTiePointsDescription="ASIFT";
                mProject->setActiveTiePointsSet("ASIFT");
                mProgressDialog->writeinConsole("\n\nStarting ASIFT tiepoints detector ");
                mASIFTUProcess = new ASIFTUProcess(mProject->getBasePath(),imageNames,mProject->getBasePath()+"/"+MATCHING_PATH,mTiePointsMethod);
                mBatchProcess->appendProcess(mASIFTUProcess);

                ASIFTFinishedProcess *ASIFTFinished= new ASIFTFinishedProcess(mProject,mTiePointsMetadata);
                mBatchProcess->appendProcess(ASIFTFinished);
            }
        }else{
            // Eliminar la carpeta preprocessing previa
            QDir postprocessingDir(mProject->getPreProcessingPath());
            if(postprocessingDir.exists())
                removeDir(postprocessingDir.absolutePath());

            while (!postprocessingDir.exists()) {
                QDir().mkdir(postprocessingDir.absolutePath());
            }
            QVector<QString> imageNameList= mProject->getImagesFileName();
            QStringList imagePathList;

            mCvDecolorMultiProcess = new MultiProcess(false);
            mCvDecolorMultiProcess->setSteps(imagePathList.count());
            foreach (QString imageName, imageNameList) {
                cvDecolorProcess *decolorProcess = new cvDecolorProcess(mImagesPath+"/"+imageName,mProject->getPreProcessingPath());
                mCvDecolorMultiProcess->appendProcess(decolorProcess);
            }
            mBatchProcess->appendProcess(mCvDecolorMultiProcess);


            mTiePointsMethod.clear();
            mTiePointsMethod = mTiePointsWizard->getTiePointsMethod();
            mProject->setCaptureType(mTiePointsWizard->getCaptureConfiguration());

            if (mTiePointsMethod.value("method").contains("Tapioca")) {
                mProject->clearTiePointsSets();
                mTiePointsDescription="tapioca";
                mProject->setActiveTiePointsSet("tapioca");
                QDir homolDir(mProject->getBasePath() + "/Homol");
                if(homolDir.exists())
                    removeDir(homolDir.absolutePath());

                QDir matchesDir(mProject->getBasePath() + "/"+MATCHING_PATH);
                if(matchesDir.exists())
                    removeDir(matchesDir.absolutePath());

                QString tapiocaMode;
                int tapiocaSize=0;
                int tapiocaRange=0;
                tapiocaMode = mTiePointsMethod.value("SearchMethod");
                if (tapiocaMode.contains("Line")) {
                    tapiocaRange=mTiePointsMethod.value("Range").toInt();
                }
                int tapiocaMulScaleMin=0;
                if (tapiocaMode.contains("MulScale")) {
                    tapiocaMulScaleMin=mTiePointsMethod.value("MulScaleMin").toInt();
                    tapiocaSize=mTiePointsMethod.value("MulScaleMax").toInt();
                }else {
                    tapiocaSize = mTiePointsMethod.value("ResizeValue").toInt();
                    if (tapiocaSize==-1) {
                        QSize imageSize=mProject->getImageByName(mProject->getImagesFileName().first())->getSize();
                        if (imageSize.height()>=imageSize.width()) {
                            tapiocaSize = (int)imageSize.height();
                        }else {
                            tapiocaSize = (int)imageSize.width();
                        }
                    }
                }
                mTiePointsPath=mProject->getPreProcessingPath()+"/"+MATCHING_PATH+"/"+TAPIOCA_MATCHES_PATH;
                QVector<QString> imagesFileToProcess;
                QMap<QString,QVector<QString> > imagePairs;

                for(int i=0;i< mProject->getImages().count();i++)
                {
                    QString imageFileInProject = mProject->getImages().at(i)->getFileName();
                    imagesFileToProcess.push_back(imageFileInProject.split(".").at(0)+".tif");

                    if(i<(mProject->getImages().count()-1))
                    {
                        QVector<QString> pairs;
                        for(int tt=i+1;tt<mProject->getImages().count();tt++)
                        {
                            QString auxImageFileInProject = mProject->getImages().at(tt)->getFileName();
                            pairs.push_back(auxImageFileInProject);
                        }
                        imagePairs[imageFileInProject]=pairs;
                    }
                }


                //Generate Input Regular Expression:
                QString inputRegExp = QString("(");

                for(int i=0; i< imagesFileToProcess.size(); i++)
                {
                    inputRegExp = inputRegExp + imagesFileToProcess.at(i) + QString("|");
                }

                inputRegExp.replace(inputRegExp.length()-1,1,")");
                inputRegExp=mProject->getPreProcessingPath()+"/"+inputRegExp;
                if(mTapiocaProcess)
                    delete mTapiocaProcess;
                mTapiocaProcess = new TapiocaProcess(inputRegExp, mProject->getPreProcessingPath(), tapiocaMode,tapiocaRange, tapiocaSize,tapiocaMulScaleMin);
                mTapiocaProcess->setWorkingDir(mProject->getPreProcessingPath());

                mBatchProcess->appendProcess(mTapiocaProcess);

                TapiocaFinishedProcess *tapiocaFinished= new TapiocaFinishedProcess(mProject,mTiePointsWizard->getMinimumTapiocaMatches(),mTiePointsMetadata);
                mBatchProcess->appendProcess(tapiocaFinished);

            }else if (mTiePointsMethod.value("method").contains("MSD+SIFT")) {
                QVector<QString> imgNames = mProject->getImagesFileName();
                QStringList imageNames;
                for (int i = 0; i < imgNames.count(); ++i) {
                    imageNames.append(mProject->getPreProcessingPath().append("/").append(imgNames[i].split(".").first().append(".tif")));
                }
                //remove previous matches
                QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                if(MatchesDir.exists())
                    removeDir(MatchesDir.absolutePath());

                //nos aseguramos de que se crean estas carpetas. ¿¿Alternativa para prevenir Infinite loop??
                while (!MatchesDir.exists()) {
                    QDir().mkdir(MatchesDir.absolutePath());
                }
                QDir msdDir(mProject->getBasePath() +"/"+ MATCHING_PATH+"/MSD");
                while (!msdDir.exists()) {
                    QDir().mkdir(msdDir.absolutePath());
                }

                mTiePointsDescription="MSD";
                mProject->setActiveTiePointsSet("MSD");
                mProgressDialog->writeinConsole("\n\nStarting MSD tiepoints detector ");
                mMsdProcess = new MSDProcess(mProject->getBasePath(),imageNames,mProject->getBasePath()+"/"+MATCHING_PATH,mTiePointsMethod,mTiePointsWizard->isMSDAffineChecked(),mTiePointsWizard->getMSDAffineTilts());

                mBatchProcess->appendProcess(mMsdProcess);

                MSDFinishedProcess *MSDFinished= new MSDFinishedProcess(mProject,mTiePointsMetadata);
                mBatchProcess->appendProcess(MSDFinished);
            }else if (mTiePointsMethod.value("method").contains("ASIFT")) {
                QVector<QString> imgNames = mProject->getImagesFileName();
                QStringList imageNames;
                for (int i = 0; i < imgNames.count(); ++i) {
                    imageNames.append(mProject->getPreProcessingPath().append("/").append(imgNames[i].split(".").first().append(".tif")));
                }
                //remove previous matches
                QDir MatchesDir(mProject->getBasePath() +"/"+ MATCHING_PATH);
                if(MatchesDir.exists())
                    removeDir(MatchesDir.absolutePath());

                while (!MatchesDir.exists()) {
                    QDir().mkdir(MatchesDir.absolutePath());
                }
                QDir asiftDir(mProject->getBasePath() +"/"+ MATCHING_PATH+"/ASIFT");
                while (!asiftDir.exists()) {
                       QDir().mkdir(asiftDir.absolutePath());
                }
                if (!mProject->getSparseModelRelativePath().isEmpty()) {
                    mProject->setSparseModelRelativePath("");
                }if (!mProject->getDenseModelRelativePath().isEmpty()) {
                    mProject->setDenseModelRelativePath("");
                }

                mTiePointsDescription="ASIFT";
                mProject->setActiveTiePointsSet("ASIFT");
                mProgressDialog->writeinConsole("\n\nStarting ASIFT tiepoints detector ");
                mASIFTUProcess = new ASIFTUProcess(mProject->getBasePath(),imageNames,mProject->getBasePath()+"/"+MATCHING_PATH,mTiePointsMethod);
                mBatchProcess->appendProcess(mASIFTUProcess);

                ASIFTFinishedProcess *ASIFTFinished= new ASIFTFinishedProcess(mProject,mTiePointsMetadata);
                mBatchProcess->appendProcess(ASIFTFinished);
            }
        }
    }

    //////////////////// ORIENTATION PROCESS ///////////////////

    if (mBatchProcessWizard->isComputeOrientationsChecked()) {

        if (!mBatchProcessWizard->isComputeTiePointsChecked()) {
            QString homolPath= mProject->getBasePath() + "/" + "Homol";
            QDir homolDir(homolPath);
            LibPW::removeDir(homolDir.absolutePath());
            //Copy "Homol" to project directory:
            if(!homolDir.exists())
            {
                if(!homolDir.mkdir(homolDir.absolutePath()))
                {
        //            QMessageBox::critical(this,tr("GRAPHOS - Error"),tr("Error making homol dir"));
                    return;
                }
            }
            QString sourceMatchesFolder=mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mProject->getActiveTiePointsSet();

            QString targetMatchesFolder=mProject->getBasePath()+"/"+TAPIOCA_MATCHES_ORIGINAL_PATH;
            QDir souceMatchesDir(sourceMatchesFolder);
            QDir targetMatchesDir(targetMatchesFolder);
            while (!targetMatchesDir.exists()) {
                QDir().mkdir(targetMatchesDir.absolutePath());
            }

            if(!LibPW::copyDir(souceMatchesDir.absolutePath(),targetMatchesDir.absolutePath(),false))
            {
                QString title="MainWindow::onTiePointsFinished";
                QString strError=tr("Error moving matching files to Homol");
                QMessageBox::critical(this,title,strError);
                return;
            }
        }
            QString projectName=mProject->getName();
            if(!projectName.isEmpty())
            {
                QStringList metadataMatchesCategories,descriptionMatchesCategories,timeCalculationMatchesCategories;
                QVector<bool> validityMatchesCategories;
                mProject->getMatchesCategoriesInformation(metadataMatchesCategories,
                                                          descriptionMatchesCategories,
                                                          timeCalculationMatchesCategories,
                                                          validityMatchesCategories);


                QString orientationMode = mOrientationWizard->getOrientationMode();
                mProject->setCurrentOrientation(orientationMode);


                if(mComputeOrientationProcess)
                    delete mComputeOrientationProcess;
                mComputeOrientationProcess = new MultiProcess();
                mComputeOrientationProcess->setStartupMessage("Computing orientations...");

                QString inputRegExp = QString("(");

                TapasProcess *tapasProcess = new TapasProcess();
                tapasProcess->setWorkingDir(mImagesPath);

                QString distModel = orientationMode;

                QStringList tapasInputs;

                //Generate Input Regular Expression:
                for(int i=0; i< mProject->getImages().count(); i++){
                    inputRegExp = inputRegExp + mProject->getImages().at(i)->getFileName() + QString("|");
                }
                inputRegExp.replace(inputRegExp.length()-1,1,")");
                inputRegExp=mImagesPath+"/"+inputRegExp;

                if (distModel.contains("Generic")) {
                    distModel = "Fraser";
                    tapasInputs <<distModel<<inputRegExp<<"Out="+mProject->getCurrentOrientation();
                    if (!mOrientationWizard->isAffineParametersChecked()) tapasInputs << "LibAff=false";
                    if (!mOrientationWizard->isDecenteringParametersChecked()) tapasInputs << "LibDec=false";
                    if (!mOrientationWizard->isDistortionCenterParameterschecked()) tapasInputs << "LibCP=false";
                    if (!mOrientationWizard->isFocalParametersChecked()) tapasInputs << "LibFoc=false";
                    if (!mOrientationWizard->isPrincipalPointParametersChecked()) tapasInputs << "LibPP=false";

                }else {
                    tapasInputs <<distModel<<inputRegExp<<"Out="+mProject->getCurrentOrientation();
                }

                tapasInputs << "ExpTxt=1";

                tapasProcess->addIntputs(tapasInputs);

                mComputeOrientationProcess->appendProcess(tapasProcess);


                AperiCloudProcess *aperiCloudProcess = new AperiCloudProcess();
                aperiCloudProcess->setWorkingDir(mProject->getBasePath());
                QStringList aperiCloudInputs;
                aperiCloudInputs <<inputRegExp<<mProject->getCurrentOrientation() <<
                                   "Out="+mProject->getCurrentOrientation()+".ply";
                aperiCloudInputs << "ExpTxt=1";
                aperiCloudProcess->addIntputs(aperiCloudInputs);
                mComputeOrientationProcess->appendProcess(aperiCloudProcess);


                mSparseModelPath = mProject->getCurrentOrientation()+".ply";
                mProject->setSparseModelRelativePath(mSparseModelPath);
                mSparseStopped = false;
                mBatchProcess->appendProcess(mComputeOrientationProcess);

                bool writeToDat = false;
                bool cleanOri=false;

                if (mDensificationWizard->getDensificationMode().contains("QuickMac")||
                        mDensificationWizard->getDensificationMode().contains("Statue")||
                        mDensificationWizard->getDensificationMode().contains("BigMac")) {
                    writeToDat=true;
                }
                if (mDensificationWizard->isSureSelected()) {
                    cleanOri=true;
                }
                AperoFinishedProcess *aperoFinished= new AperoFinishedProcess(mProject,writeToDat,cleanOri);
                mBatchProcess->appendProcess(aperoFinished);
            }

    }

    //////////////////// DENSE MATCHING PROCESS ///////////////////

    if (mBatchProcessWizard->isComputeDenseMatchingChecked()) {

        if (mDensificationWizard->isSureSelected()) {
            //Remove previous sure path from sure dir if exists
            QDir originalDir(mProject->getBasePath()+"/SURE");
            if (originalDir.exists()) {
                removeDir(originalDir.absolutePath());
            }

            //apero2SURE
            QDir aperoOriDir(mProject->getBasePath()+"/Ori-"+mProject->getCurrentOrientation());
            PW::Apero2SureProcess *apero2sure = new PW::Apero2SureProcess(aperoOriDir.absolutePath(),true);
            apero2sure->setWorkingDir(aperoOriDir.absolutePath());
            mBatchProcess->appendProcess(apero2sure);

            //DRUNK
            QString drunkInputRegExp = QString("(");
            QString fileName;
            for(int i=0; i< mProject->getImages().count(); i++){
                fileName = mProject->getImages().at(i)->getFullPath();
                fileName = fileName.right(fileName.length()-fileName.lastIndexOf(QRegExp("/"))-1);
                drunkInputRegExp = drunkInputRegExp + fileName + QString("|");
            }
            drunkInputRegExp.replace(drunkInputRegExp.length()-1,1,")");
            drunkInputRegExp =mProject->getBasePath()+"/"+drunkInputRegExp;
            QDir drunkImagesPath =mProject->getBasePath()+"/DRUNK";
            PW::DrunkProcess *mDrunkProcess = new PW::DrunkProcess(drunkInputRegExp,mProject->getCurrentOrientation());
            mDrunkProcess->setWorkingDir(mProject->getBasePath());
            mBatchProcess->appendProcess(mDrunkProcess);
            //Sure prep process
            QString prjPath =mProject->getBasePath()+"/Ori-"+ mProject->getCurrentOrientation()+"/conversion.prj";
            QFileInfo prjFileInfo(prjPath);
            SUREProcess *mSureProcess = new PW::SUREProcess(prjFileInfo.absoluteFilePath(),drunkImagesPath.absolutePath(),mDensificationWizard->getSurePyrValue(),mDensificationWizard->getSureFoldValue(),mDensificationWizard->getSureMaxModelsValue(),CUDA_ENABLED);
            mSureProcess->setWorkingDir(mProject->getBasePath());
            mBatchProcess->appendProcess(mSureProcess);
            //Merge sure output .las files
            QFileInfo SURELasExp(mProject->getBasePath()+"/SURE/3D_Points/*.las");

            QString mergedLasFilePath =mProject->getBasePath()+"/SURE.las";
            if(mMergeLasResultsProcess)
                delete mMergeLasResultsProcess;
            mMergeLasResultsProcess = new MergeLasResultsProcess(QStringList()<< SURELasExp.absoluteFilePath() ,mergedLasFilePath);

            mBatchProcess->appendProcess(mMergeLasResultsProcess);
        }else{
            if (mDensificationWizard->getDensificationMode().contains("MicMac master image")) {

                QDir slavesDir(mProject->getBasePath()+"/Ori-SlavesTMP");
                if (slavesDir.exists()) {
                    removeDir(slavesDir.absolutePath());
                }
                QDir().mkdir(slavesDir.absolutePath());

                QVector<QString> projectImages = mProject->getImagesFileName();


                //Generate Input Regular Expression:
                QString inputRegExp = QString("(");

                for(int i=0; i< projectImages.size(); i++)
                {
                    inputRegExp = inputRegExp + projectImages.at(i) + QString("|");
                }

                inputRegExp.replace(inputRegExp.length()-1,1,")");
                inputRegExp=mProject->getBasePath()+"/"+inputRegExp;
                //MICMAC slaves Process:

                if(mMicMacSlavesProcess)
                    delete (mMicMacSlavesProcess);
                mMicMacSlavesProcess = new MicMacComputeSlavesProcess(inputRegExp,mProject->getCurrentOrientation(),"SlavesTMP");
                mMicMacSlavesProcess->setWorkingDir(mProject->getBasePath());
                mBatchProcess->appendProcess(mMicMacSlavesProcess);

                mConsole->clear();
                mProgressDialog->setModal(true);
                mProgressDialog->setRange(0,0);
                mProgressDialog->setWindowTitle("Generating Dense Model...");
                mProgressDialog->setStatusText("Generating Dense Model...");
                mProgressDialog->setFinished(false);
                mBatchProcess->start();

                connect(mBatchProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
                connect(mBatchProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
                connect(mBatchProcess, SIGNAL(finished()), this, SLOT(on_LaunchMaltMultiMainImageForBatchProcess()));
                connect(mProgressDialog,SIGNAL(cancel()),mBatchProcess,SLOT(stop()));
                mProgressDialog->show();
                return;

            }else if (mDensificationWizard->getDensificationMode().contains("MicMac object space")) {
                //Generate Input Regular Expression:
                QString inputRegExp = QString("(");
                QString fileName;
                for(int i=0; i< mProject->getImages().count(); i++){
                    fileName = mProject->getImages().at(i)->getFullPath();
                    fileName = fileName.right(fileName.length()-fileName.lastIndexOf(QRegExp("/"))-1);
                    inputRegExp = inputRegExp + fileName + QString("|");
                }
                inputRegExp.replace(inputRegExp.length()-1,1,")");

                inputRegExp = mProject->getBasePath()+"/"+inputRegExp;

                QFileInfo nuageFile;

                switch (mDensificationWizard->getMicMacDeZoomValue()) {
                case 1:
                    mDenseModelPath = "MEC-Malt/NuageImProf_STD-MALT_Etape_8.ply";
                    nuageFile.setFile(mProject->getBasePath()+"/MEC-Malt/NuageImProf_STD-MALT_Etape_8.xml");
                    break;
                case 2:
                    mDenseModelPath = "MEC-Malt/NuageImProf_STD-MALT_Etape_7.ply";
                    nuageFile.setFile(mProject->getBasePath()+"/MEC-Malt/NuageImProf_STD-MALT_Etape_7.xml");
                    break;
                case 4:
                    mDenseModelPath = "MEC-Malt/NuageImProf_STD-MALT_Etape_6.ply";
                    nuageFile.setFile(mProject->getBasePath()+"/MEC-Malt/NuageImProf_STD-MALT_Etape_6.xml");
                    break;
                default:
                    mDenseModelPath = "MEC-Malt/NuageImProf_STD-MALT_Etape_7.ply";
                    nuageFile.setFile(mProject->getBasePath()+"/MEC-Malt/NuageImProf_STD-MALT_Etape_7.xml");
                    break;
                }

                MaltProcess *densificationProcess= new MaltProcess();
                QStringList densificationInputs;
                densificationInputs.append("UrbanMNE");
                densificationInputs.append(inputRegExp);
                densificationInputs.append(mProject->getCurrentOrientation());
                if (CUDA_ENABLED) {
                   densificationInputs.append("UseGpu=true");
                }

                densificationInputs.append("HrOr=true");
                densificationInputs.append("ZoomF="+QString::number(mDensificationWizard->getMicMacDeZoomValue()));
                densificationInputs.append("Regul="+QString::number(mDensificationWizard->getMicMacZRegulValue()));
                densificationInputs.append("ZPas="+QString::number(mDensificationWizard->getMicMacZPasValue()));
                densificationProcess->addIntputs(densificationInputs);

                mBatchProcess->appendProcess(densificationProcess);

                TawnyProcess *orthoProcess = new TawnyProcess();

                QDir orthoDir(mProject->getBasePath()+"/Ortho-MEC-Malt");
                orthoProcess->addIntputs(QStringList() << orthoDir.absolutePath());

                mBatchProcess->appendProcess(orthoProcess);

                Nuage2PlyProcess *plyProcess= new Nuage2PlyProcess();

                QFileInfo orthoFile(orthoDir.absolutePath()+"/Orthophotomosaic.tif");

                plyProcess->addIntputs(QStringList() << nuageFile.absoluteFilePath() << "Attr="+orthoFile.absoluteFilePath() << "Scale="+QString::number(mDensificationWizard->getMicMacDeZoomValue()));

                mBatchProcess->appendProcess(plyProcess);

            }else if(mDensificationWizard->getDensificationMode().contains("QuickMac")||
                mDensificationWizard->getDensificationMode().contains("Statue")||
                mDensificationWizard->getDensificationMode().contains("Statue")){
                //Generate Input Regular Expression:
                QString inputRegExp = QString("(");
                QString fileName;
                for(int i=0; i< mProject->getImages().count(); i++){
                    fileName = mProject->getImages().at(i)->getFullPath();
                    fileName = fileName.right(fileName.length()-fileName.lastIndexOf(QRegExp("/"))-1);
                    inputRegExp = inputRegExp + fileName + QString("|");
                }
                inputRegExp.replace(inputRegExp.length()-1,1,")");

                inputRegExp = mProject->getBasePath()+"/"+inputRegExp;

                mDenseModelPath = "MicMAc.ply";

                //C3DC Process:
                if(mC3DCProcess)
                    delete (mC3DCProcess);
                mC3DCProcess = new PW::C3DCProcess;
                mC3DCProcess->setWorkingDir(mProject->getBasePath());
                QStringList densificationInputs;
                densificationInputs.append("C3DC");
                if (mDensificationWizard->getDensificationMode().contains("QuickMac")) {
                    densificationInputs.append("QuickMac");
                }else if(mDensificationWizard->getDensificationMode().contains("Statue")){
                    densificationInputs.append("Statue");
                }else if(mDensificationWizard->getDensificationMode().contains("BigMac")){
                    densificationInputs.append("BigMac");
                }
                densificationInputs.append(inputRegExp);
                densificationInputs.append(mProject->getCurrentOrientation());
                if (CUDA_ENABLED) {
                   densificationInputs.append("UseGpu=true");
                }
                densificationInputs.append("Out=MicMac.ply");
                densificationInputs.append("SzNorm=-1");

                mC3DCProcess->addIntputs(densificationInputs);
                mBatchProcess->appendProcess(mC3DCProcess);
            }else{
                //Generate Input Regular Expression:
                QString inputRegExp = QString("(");
                QString fileName;
                for(int i=0; i< mProject->getImages().count(); i++){
                    fileName = mProject->getImages().at(i)->getFullPath();
                    fileName = fileName.right(fileName.length()-fileName.lastIndexOf(QRegExp("/"))-1);
                    inputRegExp = inputRegExp + fileName + QString("|");
                }
                inputRegExp.replace(inputRegExp.length()-1,1,")");
                QString fullInputRegExp = mImagesPath+"/"+inputRegExp;

                if(mApero2PMVSProcess)
                    delete mApero2PMVSProcess;
                mApero2PMVSProcess = new PW::Apero2pmvs(fullInputRegExp, mProject->getCurrentOrientation());
                mApero2PMVSProcess->setWorkingDir(mImagesPath);
                if(mPMVSProcess)
                    delete mPMVSProcess;
                QString pmvsDir = mProject->getBasePath()+"/pmvs-"+mProject->getCurrentOrientation() + "/";

                //****pmvs options: *******************

                QMap<QString, QString> options;
                options.insert("level",QString::number(mDensificationWizard->getPMVSLevel()));
                options.insert("csize",QString::number(mDensificationWizard->getPMVSCSize()));
                options.insert("minImageNum",QString::number(mDensificationWizard->getPMVSMin()));
                options.insert("threshold",QString::number(mDensificationWizard->getPMVSThreshold()));

                mPMVSProcess = new PW::PMVSProccess(pmvsDir, "pmvs_options.txt", options);
                mBatchProcess->appendProcess(mApero2PMVSProcess);
                mBatchProcess->appendProcess(mPMVSProcess);

                mDenseModelPath ="PMVS.ply";
            }
        }
    }

    mPersistenceManager->updateProject(mProject);

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle("Generating Dense Model...");
    mProgressDialog->setStatusText("Generating Dense Model...");
    mProgressDialog->setFinished(false);
    mBatchProcess->start();

    connect(mBatchProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mBatchProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mBatchProcess, SIGNAL(finished()), this, SLOT(on_BatchProcess_Finished()));
    connect(mProgressDialog,SIGNAL(cancel()),mBatchProcess,SLOT(stop()));
    mProgressDialog->show();

}

void MainWindowGRAPHOS::on_BatchProcess_Finished(){

    if (!mBatchProcess->isStopped()) {
        if (mBatchProcessWizard->isComputeTiePointsChecked()) {
                //Check results exists;
                QString sourceFolder=mProject->getBasePath()+"/Matches/"+mProject->getActiveTiePointsSet();
                QDir sourceDir(sourceFolder);
                if (!sourceDir.exists()) {
                    mProgressDialog->setRange(0,1);
                    mProgressDialog->setValue(1);
                    mProgressDialog->setStatusText(tr("Tiepoints process failed."));
                    mProgressDialog->setFinished(true);
                    mProject->clearTiePointsSets();
                    return;
                }

                mProject->removeProcessMetadata("Model");
                mProject->removeProcessMetadata("Orientation");
                mProject->removeProcessMetadata("TiePoints");

                if (mProject->getActiveTiePointsSet().compare("Tapioca",Qt::CaseInsensitive)==0) {

                    if (mTiePointsWizard->isWallisChecked()) {
                        mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Wallisfilter");
                        mProject->setProcessMetadataElement("TiePoints", "WallisContrast", QString::number(mTiePointsWizard->getWallisContrast()));
                        mProject->setProcessMetadataElement("TiePoints", "WallisBrightness", QString::number(mTiePointsWizard->getWallisBrithness()));
                        mProject->setProcessMetadataElement("TiePoints", "WallisStdDev", QString::number(mTiePointsWizard->getWallisStdDeviation()));
                        mProject->setProcessMetadataElement("TiePoints", "WallisKernelSize", QString::number(mTiePointsWizard->getWallisKernell()));
                    }else {
                        mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Contrast preserving decolorization");
                    }

                    mProject->setProcessMetadataElement("TiePoints", "Tool", "Tapioca");
                    mProject->setProcessMetadataElement("TiePoints", "SearchMode", mTiePointsMethod.value("SearchMethod") );

                    if(mTiePointsMethod.value("SearchMethod").compare("Line",Qt::CaseInsensitive)==0){
                        mProject->setProcessMetadataElement("TiePoints", "Range", mTiePointsMethod.value("Range"));
                        mProject->setProcessMetadataElement("TiePoints", "Size", mTiePointsMethod.value("ResizeValue"));
                    }else if (mTiePointsMethod.value("SearchMethod").compare("MulScale",Qt::CaseInsensitive)==0) {
                        mProject->setProcessMetadataElement("TiePoints", "MulScaleMax", mTiePointsMethod.value("MulScaleMax"));
                        mProject->setProcessMetadataElement("TiePoints", "MulScaleMin", mTiePointsMethod.value("MulScaleMin"));
                    }else {
                        mProject->setProcessMetadataElement("TiePoints", "Size", mTiePointsMethod.value("ResizeValue"));
                    }
                }else if (mProject->getActiveTiePointsSet().compare("MSD",Qt::CaseInsensitive)==0) {
                    //Save metadata
                    mProject->setProcessMetadataElement("TiePoints", "Tool", "MSD");
                    if (mTiePointsWizard->isWallisChecked()) {
                        mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Wallis filter");
                        mProject->setProcessMetadataElement("TiePoints", "WallisContrast", QString::number(mTiePointsWizard->getWallisContrast()));
                        mProject->setProcessMetadataElement("TiePoints", "WallisBrightness", QString::number(mTiePointsWizard->getWallisBrithness()));
                        mProject->setProcessMetadataElement("TiePoints", "WallisStdDev", QString::number(mTiePointsWizard->getWallisStdDeviation()));
                        mProject->setProcessMetadataElement("TiePoints", "WallisKernelSize", QString::number(mTiePointsWizard->getWallisKernell()));

                    }else {
                        mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Contrast preserving decolorization");
                    }
                    mProject->setProcessMetadataElement("TiePoints", "PatchRadius", mTiePointsMethod.value("PatchRadius") );
                    mProject->setProcessMetadataElement("TiePoints", "SearchAreaRadius", mTiePointsMethod.value("SearchAreaRadius") );
                    mProject->setProcessMetadataElement("TiePoints", "NMSRadius", mTiePointsMethod.value("NMSRadius") );
                    mProject->setProcessMetadataElement("TiePoints", "NMSScaleRadius", mTiePointsMethod.value("NMSScaleRadius") );
                    mProject->setProcessMetadataElement("TiePoints", "ThSaliency", mTiePointsMethod.value("ThSaliency") );
                    mProject->setProcessMetadataElement("TiePoints", "KNN", mTiePointsMethod.value("KNN") );
                    mProject->setProcessMetadataElement("TiePoints", "ScaleFactor", mTiePointsMethod.value("ScaleFactor") );
                    mProject->setProcessMetadataElement("TiePoints", "NScales", mTiePointsMethod.value("NScales") );
                    mProject->setProcessMetadataElement("TiePoints", "MaxTiepoints", mTiePointsMethod.value("MaxTiepoints") );

                    mProject->setProcessMetadataElement("TiePoints", "Size", mTiePointsMethod.value("ResizeValue"));

                    if(mTiePointsMethod.value("matchingMethod").compare("FLANN",Qt::CaseInsensitive)==0){
                        mProject->setProcessMetadataElement("TiePoints", "MatchingMethod", "FLANN");
                    }else{
                        mProject->setProcessMetadataElement("TiePoints", "MatchingMethod", "Robust matcher (brute force)");
                        mProject->setProcessMetadataElement("TiePoints", "RB_ratio", mTiePointsMethod.value("RB_ratio"));
                        mProject->setProcessMetadataElement("TiePoints", "RB_threshold_K", mTiePointsMethod.value("RB_threshold_K"));
                    }
                    mProject->setProcessMetadataElement("TiePoints", "MinMatches", mTiePointsMethod.value("ResizeValue"));
                }else if (mProject->getActiveTiePointsSet().compare("ASIFT",Qt::CaseInsensitive)==0) {
                    mProject->setProcessMetadataElement("TiePoints", "Tool", "ASIFT");
                    if (mTiePointsWizard->isWallisChecked()) {
                        mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Wallis filter");
                        mProject->setProcessMetadataElement("TiePoints", "WallisContrast", QString::number(mTiePointsWizard->getWallisContrast()));
                        mProject->setProcessMetadataElement("TiePoints", "WallisBrightness", QString::number(mTiePointsWizard->getWallisBrithness()));
                        mProject->setProcessMetadataElement("TiePoints", "WallisStdDev", QString::number(mTiePointsWizard->getWallisStdDeviation()));
                        mProject->setProcessMetadataElement("TiePoints", "WallisKernelSize", QString::number(mTiePointsWizard->getWallisKernell()));

                    }else {
                        mProject->setProcessMetadataElement("TiePoints", "Proprocessing", "Contrast preserving decolorization");
                    }
                    mProject->setProcessMetadataElement("TiePoints", "PeakTh", mTiePointsMethod.value("PeakTh") );
                    mProject->setProcessMetadataElement("TiePoints", "EdgeTh", mTiePointsMethod.value("EdgeTh") );
                    mProject->setProcessMetadataElement("TiePoints", "Octaves", mTiePointsMethod.value("Octaves") );
                    mProject->setProcessMetadataElement("TiePoints", "Tilts", mTiePointsMethod.value("Tilts") );
                    mProject->setProcessMetadataElement("TiePoints", "MaxTiepoints", mTiePointsMethod.value("MaxTiepoints") );

                    mProject->setProcessMetadataElement("TiePoints", "Size", mTiePointsMethod.value("ResizeValue"));

                    if(mTiePointsMethod.value("matchingMethod").compare("FLANN",Qt::CaseInsensitive)==0){
                        mProject->setProcessMetadataElement("TiePoints", "MatchingMethod", "FLANN");
                    }else{
                        mProject->setProcessMetadataElement("TiePoints", "MatchingMethod", "Robust matcher (brute force)");
                        mProject->setProcessMetadataElement("TiePoints", "RB_ratio", mTiePointsMethod.value("RB_ratio"));
                        mProject->setProcessMetadataElement("TiePoints", "RB_threshold_K", mTiePointsMethod.value("RB_threshold_K"));
                    }
                    mProject->setProcessMetadataElement("TiePoints", "MinMatches", mTiePointsMethod.value("ResizeValue"));
                }
                QDateTime dateTime=QDateTime::currentDateTime();
                QString timeCalculation=dateTime.toString(LIBPW_DATETIME_STRING_FORMAT);

                PWMatchesCategory * category = new PWMatchesCategory(mProject,
                                      0,
                                      mProject->getActiveTiePointsSet(),
                                      mTiePointsMetadata,
                                      timeCalculation);

                QMap<QString, QVector<QString> > imagePairs;
                TapiocaIO tapiocaIO;

                QDir matchingsDir(mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mProject->getActiveTiePointsSet());
                tapiocaIO.readImagePairs(matchingsDir.absolutePath(), imagePairs);
                PWGraphImages* graphImages=new PWGraphImages();
                    QVector<QString> wallisImageNames = mProject->getImagesFileName();
                    for (int i = 0; i < wallisImageNames.count(); ++i) {
                        wallisImageNames[i]=wallisImageNames[i].split(".").at(0)+".tif";
                    }
                    if(!graphImages->createGraph(wallisImageNames,
                                                  imagePairs))
                     {
                         //TODO: graphIsConnected=false; ¿Que hacer?
                     }


                category->setGraphImages(graphImages);
                category->setImagePairs(imagePairs);

                mProject->insertMatchesCategory(category); //Comprobar categorie

                //tie point results;
                drawTiePointsInfoView(imagePairs);
                mBasicUserGUI->setCurrentIndex(1);
        }
        if (mBatchProcessWizard->isComputeOrientationsChecked()) {
            QFileInfo orientationResultFile(mProject->getBasePath()+"/"+mSparseModelPath);
            if (!orientationResultFile.exists()) {
                mProgressDialog->setRange(0,1);
                mProgressDialog->setValue(1);
                mProgressDialog->setStatusText(tr("Orientation process failed."));
                mProgressDialog->setFinished(true);
                mProject->setSparseModelRelativePath("");
                mProject->setCurrentOrientation("");
                return;
            }

            // Process metadata:
            mProject->removeProcessMetadata("Model");
            mProject->removeProcessMetadata("Orientation");
            mProject->setProcessMetadataElement("Orientation", "DistortionModel", mOrientationWizard->getOrientationMode());
            if (mOrientationWizard->getOrientationMode().contains("Generic")) {
                QString distortionParameters;
                if (!mOrientationWizard->isFocalParametersChecked()) distortionParameters.append(" f");
                if (!mOrientationWizard->isPrincipalPointParametersChecked()) distortionParameters.append(" x0 y0 ");
                if (!mOrientationWizard->isDistortionCenterParameterschecked()) distortionParameters.append(" x1 y1");
                if (!mOrientationWizard->isDecenteringParametersChecked()) distortionParameters.append(" p1 p2");
                if (!mOrientationWizard->isAffineParametersChecked()) distortionParameters.append(" b1 b2");
                mProject->setProcessMetadataElement("Orientation", "parameters", distortionParameters);
            }

            //Remove homol folder;
            QDir homolDir(mProject->getBasePath() + "/Homol");
            if(homolDir.exists())
                removeDir(homolDir.absolutePath());

            //Remove tmpFolder
            QString tmpMMFolder=mProject->getBasePath()+"/"+TAPIOCA_TMP_MM_PATH;
            QDir tmpMMdir(tmpMMFolder);
            if (tmpMMdir.exists()) {
                removeDir(tmpMMdir.absolutePath());
            }

            //Load Sparse model (ply)
            mProject->setSparseModelRelativePath(mSparseModelPath);
            QStringList modelsList;
            modelsList.append(mProject->getSparseModelFullPath());
            mCCVW->addToDB(modelsList);

            //Add orientations to the project.
            if (mProject->readOrientations(mImagesPath + "/Ori-" + mProject->getCurrentOrientation()))
            {
                QMessageBox::critical(this,tr("GRAPHOS error"),tr("Error reading images orientations"));
            }


            loadProjectMetadataOnProjectTree();
            updateImagesTree();
            loadModelsOnTree();
            updateTools();
            mBasicUserGUI->setCurrentIndex(2);

            setWorkflowWidgetStatus();
        }
        if (mBatchProcessWizard->isComputeDenseMatchingChecked()) {
            if (mDensificationWizard->isSureSelected()) {
                mProject->setDenseModelRelativePath("SURE.las");

            }else {
                if (mDensificationWizard->getDensificationMode().contains("MicMac object space")||
                        mDensificationWizard->getDensificationMode().contains("MicMac master image")||
                        mDensificationWizard->getDensificationMode().contains("QuickMac")||
                        mDensificationWizard->getDensificationMode().contains("Statue")||
                        mDensificationWizard->getDensificationMode().contains("BigMac")) {
                    QFileInfo sourceFile(mProject->getBasePath()+"/"+mDenseModelPath);
                    QFileInfo targetFile(mProject->getBasePath()+"/MicMac.ply");
                    if (sourceFile.exists()) {
                        QFile(sourceFile.absoluteFilePath()).rename(targetFile.absoluteFilePath());
                        mProject->setDenseModelRelativePath("MicMac.ply");
                    }
                }else if (mDensificationWizard->getDensificationMode().contains("PMVS")) {
                    QFileInfo sourceFile(mProject->getBasePath()+"/pmvs-"+mProject->getCurrentOrientation() + "/models/pmvs_options.txt.ply");
                    QFileInfo targetFile(mProject->getBasePath()+"/PMVS.ply");
                    if (sourceFile.exists()) {
                        QFile(sourceFile.absoluteFilePath()).rename(targetFile.absoluteFilePath());
                        mProject->setDenseModelRelativePath("PMVS.ply");
                    }
                }
            }
            QFileInfo denseMatchingResultFile(mProject->getDenseModelFullPath());
            if (!denseMatchingResultFile.exists()) {
                mProgressDialog->setRange(0,1);
                mProgressDialog->setValue(1);
                mProgressDialog->setStatusText(tr("Dense matching process failed."));
                mProgressDialog->setFinished(true);
                mProject->setDenseModelRelativePath("");
                return;
            }
            //Load Dense model (ply)
            QStringList modelsList;
            modelsList.append(mProject->getDenseModelFullPath());
            mCCVW2->addToDB(modelsList);
            // Process metadata:
            ccHObject* obj = mCCVW2->getGLWindow()->getSceneDB()->getFirstChild();
            ccPointCloud *cloud = static_cast<ccPointCloud*>(obj);
            unsigned cloudSize = cloud->size();

            //Save project metadata
            mProject->removeProcessMetadata("Model");

            if (mDensificationWizard->isSureSelected()) {
                mProject->setProcessMetadataElement("Model", "CloudSize", QString::number(cloudSize)+" points");
                mProject->setProcessMetadataElement("Model", "Tool", "SURE");
                mProject->setProcessMetadataElement("Model", "Pyr", QString::number(mDensificationWizard->getSurePyrValue()));
                mProject->setProcessMetadataElement("Model", "Fold", QString::number(mDensificationWizard->getSureFoldValue()));
                mProject->setProcessMetadataElement("Model", "MaxModels", QString::number(mDensificationWizard->getSureMaxModelsValue()));

            }else if (mDensificationWizard->getDensificationMode().contains("MicMac object space")||
                        mDensificationWizard->getDensificationMode().contains("MicMac master image")) {
                mProject->setProcessMetadataElement("Model", "CloudSize", QString::number(cloudSize)+" points");
                mProject->setProcessMetadataElement("Model", "Tool", mDensificationWizard->getDensificationMode());
                if(mDensificationWizard->getDensificationMode().contains("master"))
                {
                    QString mainImages;
                    QStringList mainImgNames = mDensificationWizard->getMainImages();
                    foreach (QString name, mainImgNames) {
                        mainImages.append(" ").append(name);
                    }
                    mProject->setProcessMetadataElement("Model", "MainImageNames", mainImages);
                }
                mProject->setProcessMetadataElement("Model", "DeZoom", QString::number(mDensificationWizard->getMicMacDeZoomValue()));
                mProject->setProcessMetadataElement("Model", "ZRegul", QString::number(mDensificationWizard->getMicMacZRegulValue()));
                mProject->setProcessMetadataElement("Model", "ZPas", QString::number(mDensificationWizard->getMicMacZPasValue()));

            }else if (mDensificationWizard->getDensificationMode().contains("QuickMac")||
                      mDensificationWizard->getDensificationMode().contains("Statue")||
                      mDensificationWizard->getDensificationMode().contains("BigMac")) {
                mProject->setProcessMetadataElement("Model", "CloudSize", QString::number(cloudSize)+" points");
                mProject->setProcessMetadataElement("Model", "Tool", mDensificationWizard->getDensificationMode());
            }else if (mDensificationWizard->getDensificationMode().contains("PMVS")) {
                mProject->setProcessMetadataElement("Model", "CloudSize", QString::number(cloudSize)+" points");
                mProject->setProcessMetadataElement("Model", "Tool", "PMVS");
                mProject->setProcessMetadataElement("Model", "Level", QString::number(mDensificationWizard->getPMVSLevel()));
                mProject->setProcessMetadataElement("Model", "Min", QString::number(mDensificationWizard->getPMVSMin()));
                mProject->setProcessMetadataElement("Model", "CSize", QString::number(mDensificationWizard->getPMVSCSize()));
                mProject->setProcessMetadataElement("Model", "Threshold", QString::number(mDensificationWizard->getPMVSThreshold()));
            }


            mBasicUserGUI->setCurrentIndex(3);
            setWorkflowWidgetStatus();
            loadProjectMetadataOnProjectTree();
            loadModelsOnTree();
            updateTools();
        }
        //Save the project
        mPersistenceManager->updateProject(mProject);
        setWorkflowWidgetStatus();
        loadProjectMetadataOnProjectTree();
        updateImagesTree();
        updateTools();

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Batch process finished."));
        mProgressDialog->setFinished(true);
    }
}

void MainWindowGRAPHOS::on_LaunchMaltMultiMainImageForBatchProcess(){

    PW::MultiProcess *maltForBatch = new PW::MultiProcess(true);

    QStringList mainImgNames = mDensificationWizard->getMainImages();

    if(mainImgNames.count() > 0){

        //Create temp .ply folder
        QDir tmpPly(mProject->getBasePath()+"/tmpPLY");
        if (tmpPly.exists()) {
            removeDir(tmpPly.absolutePath());
        }
        QDir().mkdir(tmpPly.absolutePath());

        foreach (QString mainImage, mainImgNames) {
            QStringList nNearestImages = getMicMacSlavesForMainImage(mainImage);

            //Generate Input Regular Expression:
            QString inputRegExp = QString("(");

            for(int i=0; i< nNearestImages.count(); i++){
                inputRegExp = inputRegExp + nNearestImages.at(i) + QString("|");
            }
            inputRegExp.replace(inputRegExp.length()-1,1,")");

            inputRegExp=mProject->getBasePath()+"/"+inputRegExp;
            MaltProcess *densificationProcess= new MaltProcess();
            densificationProcess->setWorkingDir(mProject->getBasePath());
            QStringList densificationInputs;
            densificationInputs.append("GeomImage");
            densificationInputs.append(inputRegExp);
            densificationInputs.append(mProject->getCurrentOrientation());
            densificationInputs.append("Master="+mainImage);
            if (CUDA_ENABLED) {
               densificationInputs.append("UseGpu=true");
            }
            densificationInputs.append("ZoomF="+QString::number(mDensificationWizard->getMicMacDeZoomValue()));
            densificationInputs.append("Regul="+QString::number(mDensificationWizard->getMicMacZRegulValue()));
            densificationInputs.append("ZPas="+QString::number(mDensificationWizard->getMicMacZPasValue()));
            densificationProcess->addIntputs(densificationInputs);

            maltForBatch->appendProcess(densificationProcess);

            Nuage2PlyProcess *plyProcess= new Nuage2PlyProcess();

            QFileInfo mainImageFile(mProject->getBasePath()+"/"+mainImage);

            QFileInfo nuageFile;

            switch (mDensificationWizard->getMicMacDeZoomValue()) {
            case 1:
                nuageFile.setFile(mProject->getBasePath()+"/MM-Malt-Img-"+mainImageFile.baseName()+"/NuageImProf_STD-MALT_Etape_8.xml");
                break;
            case 2:
                nuageFile.setFile(mProject->getBasePath()+"/MM-Malt-Img-"+mainImageFile.baseName()+"/NuageImProf_STD-MALT_Etape_7.xml");
                break;
            case 4:
                nuageFile.setFile(mProject->getBasePath()+"/MM-Malt-Img-"+mainImageFile.baseName()+"/NuageImProf_STD-MALT_Etape_6.xml");
                break;
            default:
                nuageFile.setFile(mProject->getBasePath()+"/MM-Malt-Img-"+mainImageFile.baseName()+"/NuageImProf_STD-MALT_Etape_7.xml");
                break;
            }

            plyProcess->addIntputs(QStringList() << nuageFile.absoluteFilePath() << "Attr="+mainImageFile.absoluteFilePath() << "Scale="+QString::number(mDensificationWizard->getMicMacDeZoomValue()) << "Out="+mProject->getBasePath()+"/tmpPLY/"+mainImageFile.baseName()+".ply");

            maltForBatch->appendProcess(plyProcess);

        }


        QStringList mergePlyInputs;
        QFileInfo plyfiles(mProject->getBasePath()+"/tmpPly/.*.ply");
        mergePlyInputs<<"MergePly" <<plyfiles.absoluteFilePath()<<"Out=MicMac.ply";

        PlyMergeProcess *mergePlyProcess= new PlyMergeProcess();
        mergePlyProcess->addIntputs(mergePlyInputs);
        mergePlyProcess->setWorkingDir(mProject->getBasePath());
        maltForBatch->appendProcess(mergePlyProcess);

        mDenseModelPath = "MicMac.ply";
    }

    maltForBatch->start();

    connect(maltForBatch, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(maltForBatch, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(maltForBatch, SIGNAL(finished()), this, SLOT(on_BatchProcess_Finished()));
    connect(mProgressDialog,SIGNAL(cancel()),maltForBatch,SLOT(stop()));
}

void MainWindowGRAPHOS::on_actionGeorreference_triggered(){
    //create georref dock
//    mDockGeorref = new QDockWidget(tr("Georeferencing"),this);
    mDockGeorref->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    addDockWidget(Qt::LeftDockWidgetArea, mDockGeorref);
    mGCPWidget= new GCPWidget(this,mSettings,mDockGeorref,mProject,mPhotoViewer,mPersistenceManager);
    connect(mGCPWidget,SIGNAL(computeGeorref()),this,SLOT(on_computeGeorref_triggered()));
    mDockGeorref->setWidget(mGCPWidget);
    mDockGeorref->setVisible(true);
    this->tabifyDockWidget(mDockProject,mDockGeorref);

    mBasicUserGUI->setCurrentIndex(0);

}
void MainWindowGRAPHOS::on_computeGeorref_triggered(){

    if (!mProject->getDenseModelRelativePath().isEmpty()) {

        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this, "Caution!", "Current dense matching will be lost.<br>Continue?",
                                      QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::No) {
          return;

        }
        removePreviousDensifications();

        mProject->setDenseModelRelativePath("");


        mProject->removeProcessMetadata("Model");

        mPersistenceManager->updateProject(mProject);
        loadProjectMetadataOnProjectTree();
        updateImagesTree();
        loadModelsOnTree();
        updateTools();
        mBasicUserGUI->setCurrentIndex(2);
        setWorkflowWidgetStatus();
    }

    mGeorrefProcess = new PW::MultiProcess(true);

    QFileInfo outputGCPXMLFile(mProject->getBasePath()+"/GCP.xml");
    mGCPWriterProcess = new PW::GCPWriter(mProject->getModelCPoints(),outputGCPXMLFile.absoluteFilePath());
    mGeorrefProcess->appendProcess(mGCPWriterProcess);
    QFileInfo outputImgPtsXMLFile(mProject->getBasePath()+"/imgPts.xml");
    mImgPtWriterProcess = new PW::imgPointWriter(mProject->getImagePointsMap(),outputImgPtsXMLFile.absoluteFilePath());
    mGeorrefProcess->appendProcess(mImgPtWriterProcess);


    //GCPBascule Process:
    if(mGCPBasculeProcess)
        delete (mGCPBasculeProcess);
    mGCPBasculeProcess = new PW::GCPBasculeProcess();

    QString inputRegExp = QString("(");

    //Generate Input Regular Expression:
    for(int i=0; i< mProject->getImages().count(); i++){
        inputRegExp = inputRegExp + mProject->getImages().at(i)->getFileName() + QString("|");
    }
    inputRegExp.replace(inputRegExp.length()-1,1,")");
    inputRegExp=mImagesPath+"/"+inputRegExp;

    QStringList gcpBasculeInputs;
    gcpBasculeInputs.append(inputRegExp);
    gcpBasculeInputs.append(mProject->getCurrentOrientation());
    gcpBasculeInputs.append(mProject->getCurrentOrientation());
    gcpBasculeInputs.append("GCP.xml");
    gcpBasculeInputs.append("imgPts.xml");


    mGCPBasculeProcess->addIntputs(gcpBasculeInputs);
    mGeorrefProcess->appendProcess(mGCPBasculeProcess);

    //CAMpari aqui si está activado
    if (mGCPWidget->isBundleChecked()) {
        mCampariProcess = new PW::CampariProcess();
        QStringList campariInputs;
        campariInputs.append(inputRegExp);
        campariInputs.append(mProject->getCurrentOrientation());
        campariInputs.append(mProject->getCurrentOrientation());
        QString precInput("GCP=[GCP.xml,");
        precInput.append( QString::number(mGCPWidget->getGCPPrec()));
        precInput.append(",imgPts.xml,");
        precInput.append( QString::number(mGCPWidget->getImagePrec()));
        precInput.append("]");
        campariInputs.append(precInput);
        campariInputs.append("FocFree=1");
        campariInputs.append("ExpTxt=1");
        mCampariProcess->addIntputs(campariInputs);
        mGeorrefProcess->appendProcess(mCampariProcess);
    }

    //

    AperiCloudProcess *aperiCloudProcess = new AperiCloudProcess();

    QString homolPath= mProject->getBasePath() + "/" + "Homol";
    QDir homolDir(homolPath);
    removeDir(homolDir.absolutePath());
    //Copy "Homol" to project directory:
    if(!homolDir.exists())
    {
        if(!homolDir.mkdir(homolDir.absolutePath()))
        {
            QMessageBox::critical(this,tr("GRAPHOS - Error"),tr("Error making homol dir"));
            return;
        }
    }
    QString sourceFolder=mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mProject->getActiveTiePointsSet();

    QString targetFolder=mProject->getBasePath()+"/"+TAPIOCA_MATCHES_ORIGINAL_PATH;
    QDir souceDir(sourceFolder);
    QDir targetDir(targetFolder);
    while (!targetDir.exists()) {
        QDir().mkdir(targetDir.absolutePath());
    }

    if(!copyDir(souceDir.absolutePath(),targetDir.absolutePath(),false))
    {
        QString title="MainWindow::onTiePointsFinished";
        QString strError=tr("Error moving matching files to Homol");
        QMessageBox::critical(this,title,strError);
        return;
    }

    aperiCloudProcess->setWorkingDir(mProject->getBasePath());
    QStringList aperiCloudInputs;
    aperiCloudInputs <<inputRegExp<<mProject->getCurrentOrientation() <<
                       "Out="+mProject->getCurrentOrientation()+".ply";
    if(isTiePointsTxt(mProject->getBasePath()))
        aperiCloudInputs << "ExpTxt=1";
    aperiCloudProcess->addIntputs(aperiCloudInputs);
    mGeorrefProcess->appendProcess(aperiCloudProcess);

    connect(mGeorrefProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mGeorrefProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mGeorrefProcess, SIGNAL(finished()),this,SLOT(on_computeGeorref_Finished()));
    connect(mGeorrefProcess, SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mGeorrefProcess,SLOT(stop()));

    mGeorrefProcess->start();

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle(mGeorrefProcess->getStartupMessage());
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
}

void MainWindowGRAPHOS::on_computeGeorref_Finished(){
    if (!mGeorrefProcess->isStopped()){

        //Remove homol folder;
        QDir homolDir(mProject->getBasePath() + "/Homol");
        if(homolDir.exists())
            removeDir(homolDir.absolutePath());

        QStringList modelsList;
        modelsList.append(mProject->getSparseModelFullPath());
        mCCVW->addToDB(modelsList);

        mBasicUserGUI->setCurrentIndex(2);

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Georreferencing process finished."));
        mProgressDialog->setFinished(true);
    }
    disconnect(mProgressDialog,SIGNAL(cancel()),mGeorrefProcess,SLOT(stop()));
}

void MainWindowGRAPHOS::on_actionScaleCloud_triggered(){

    scaleDialog = new ScaleModelDialog(this);
    connect(scaleDialog,SIGNAL(readDistanceToScale()),this,SLOT(on_ReadDistanceToScale()));
    if (!scaleDialog->exec()) {
        disconnect(scaleDialog,SIGNAL(readDistanceToScale()),this,SLOT(on_ReadDistanceToScale()));
        return;
    }
    QFileInfo baseFile(mProject->getDenseModelFullPath());
    if (baseFile.suffix().compare("ply",Qt::CaseInsensitive)==0) {
        ccHObject* entitiesToDispatch = mCCVW2->getCcHObject();
        QFileInfo auxFileInfo(mProject->getDenseModelFullPath());

        if (entitiesToDispatch->getChildrenNumber() != 0){
            CC_FILE_ERROR result = CC_FERR_NO_ERROR;


            result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),(auxFileInfo.absoluteFilePath()).replace(".ply",".las").toAscii(),CC_FILE_TYPES::LAS);
        }
        QFile oldPlyFile(mProject->getDenseModelFullPath());
        oldPlyFile.remove();
        mProject->setDenseModelRelativePath(auxFileInfo.baseName()+".las");
    }
    double scale;
    switch (scaleDialog->getScaleMethod()) {
    case 1:
        scale = scaleDialog->getDistanceReality()/scaleDialog->getDistanceObject();
        mScaleProcess = new ScaleProcess(mProject->getDenseModelFullPath(),scale,scale,scale);
        break;
    case 2:
        mScaleProcess = new ScaleProcess(mProject->getDenseModelFullPath(),scaleDialog->getScalex(),scaleDialog->getScaley(),scaleDialog->getScalez());
        break;
    }
    connect(mScaleProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mScaleProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mScaleProcess, SIGNAL(finished()),this,SLOT(on_ScaleCloud_Finished()));
    connect(mScaleProcess, SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mScaleProcess,SLOT(stop()));

    mScaleProcess->start();

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle(mScaleProcess->getStartupMessage());
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
}

void MainWindowGRAPHOS::on_ScaleCloud_Finished(){
    if (!mScaleProcess->isStopped()){
        QFileInfo baseFileInfo(mProject->getDenseModelFullPath());
        QFile baseFile(baseFileInfo.absoluteFilePath());
        baseFile.remove();
        QFile scaledFile(baseFileInfo.absolutePath()+"/"+baseFileInfo.baseName()+"_scaled.las");
        scaledFile.rename(baseFileInfo.absoluteFilePath());

        QStringList modelsList;
        modelsList.append(mProject->getDenseModelFullPath());
        mCCVW2->addToDB(modelsList);

        mBasicUserGUI->setCurrentIndex(3);

        mProgressDialog->setRange(0,1);
        mProgressDialog->setValue(1);
        mProgressDialog->setStatusText(tr("Scale finished."));
        mProgressDialog->setFinished(true);
    }
    disconnect(mProgressDialog,SIGNAL(cancel()),mScaleProcess,SLOT(stop()));
}

void MainWindowGRAPHOS::on_ReadDistanceToScale(){
    connect(mCCVW2,SIGNAL(distanceAvailable()),this,SLOT(on_distanceToScaleAvailable()));
    mCCVW2->activateGetDistanceToScale();
}
void MainWindowGRAPHOS::on_distanceToScaleAvailable(){
    disconnect(mCCVW2,SIGNAL(distanceAvailable()),this,SLOT(on_distanceToScaleAvailable()));
    mCCVW2->getGLWindow()->setPickingMode(ccGLWindow::DEFAULT_PICKING);
    mCCVW2->clearLables();

    scaleDialog->setObjectDistance(mCCVW2->getDistToScale());

    if (!scaleDialog->exec()) {
        disconnect(scaleDialog,SIGNAL(readDistanceToScale()),this,SLOT(on_ReadDistanceToScale()));
        return;
    }
    QFileInfo baseFile(mProject->getDenseModelFullPath());
    if (baseFile.suffix().compare("ply",Qt::CaseInsensitive)==0) {
        ccHObject* entitiesToDispatch = mCCVW2->getCcHObject();
        QFileInfo auxFileInfo(mProject->getDenseModelFullPath());

        if (entitiesToDispatch->getChildrenNumber() != 0){
            CC_FILE_ERROR result = CC_FERR_NO_ERROR;


            result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),(auxFileInfo.absoluteFilePath()).replace(".ply",".las").toAscii(),CC_FILE_TYPES::LAS);
        }
        QFile oldPlyFile(mProject->getDenseModelFullPath());
        oldPlyFile.remove();
        mProject->setDenseModelRelativePath(auxFileInfo.baseName()+".las");
    }
    double scale;
    switch (scaleDialog->getScaleMethod()) {
    case 1:
        scale = scaleDialog->getDistanceReality()/scaleDialog->getDistanceObject();
        mScaleProcess = new ScaleProcess(mProject->getDenseModelFullPath(),scale,scale,scale);
        break;
    case 2:
        mScaleProcess = new ScaleProcess(mProject->getDenseModelFullPath(),scaleDialog->getScalex(),scaleDialog->getScaley(),scaleDialog->getScalez());
        break;
    }
    connect(mScaleProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
    connect(mScaleProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
    connect(mScaleProcess, SIGNAL(finished()),this,SLOT(on_ScaleCloud_Finished()));
    connect(mScaleProcess, SIGNAL(statusChanged(int,QString)),mProgressDialog,SLOT(onSatutsChanged(int,QString)));
    connect(mProgressDialog,SIGNAL(cancel()),mScaleProcess,SLOT(stop()));

    mScaleProcess->start();

    mConsole->clear();
    mProgressDialog->setModal(true);
    mProgressDialog->setRange(0,0);
    mProgressDialog->setWindowTitle(mScaleProcess->getStartupMessage());
    mProgressDialog->setFinished(false);
    mProgressDialog->show();
}

void MainWindowGRAPHOS::setTopView(){
    mCCVW2->getGLWindow()->setView(CC_TOP_VIEW);
    mCCVW->getGLWindow()->setView(CC_TOP_VIEW);
}
void MainWindowGRAPHOS::setBottomView(){
    mCCVW2->getGLWindow()->setView(CC_BOTTOM_VIEW);
    mCCVW->getGLWindow()->setView(CC_BOTTOM_VIEW);
}
void MainWindowGRAPHOS::setLeftView(){
    mCCVW2->getGLWindow()->setView(CC_LEFT_VIEW);
    mCCVW->getGLWindow()->setView(CC_LEFT_VIEW);
}
void MainWindowGRAPHOS::setRightView(){
    mCCVW2->getGLWindow()->setView(CC_RIGHT_VIEW);
    mCCVW->getGLWindow()->setView(CC_RIGHT_VIEW);
}
void MainWindowGRAPHOS::setFrontView(){
    mCCVW2->getGLWindow()->setView(CC_FRONT_VIEW);
    mCCVW->getGLWindow()->setView(CC_FRONT_VIEW);
}
void MainWindowGRAPHOS::setBackView(){
    mCCVW2->getGLWindow()->setView(CC_BACK_VIEW);
    mCCVW->getGLWindow()->setView(CC_BACK_VIEW);
}
void MainWindowGRAPHOS::setFronIsometricView(){
    mCCVW2->getGLWindow()->setView(CC_ISO_VIEW_1);
    mCCVW->getGLWindow()->setView(CC_ISO_VIEW_1);
}
void MainWindowGRAPHOS::setBackIsometricView(){
    mCCVW2->getGLWindow()->setView(CC_ISO_VIEW_2);
    mCCVW->getGLWindow()->setView(CC_ISO_VIEW_2);
}


void MainWindowGRAPHOS::on_actionCalibration_conversion_triggered()
{
     CalibrationConversion_Process *process = new CalibrationConversion_Process();
     process->start();
}

void MainWindowGRAPHOS::removePRJ_Files(){
    QFile *prj1= new QFile(mProject->getBasePath()+"/PRG_tapioca_Densidad.png");
    if (prj1->exists()) prj1->remove();
    prj1->setFileName(mProject->getBasePath()+"/PRG_tapioca_Keypoints.png");
    if (prj1->exists()) prj1->remove();
    prj1->setFileName(mProject->getBasePath()+"/prg1.bmp");
    if (prj1->exists()) prj1->remove();
    prj1->setFileName(mProject->getBasePath()+"/prg2.bmp");
    if (prj1->exists()) prj1->remove();
}
