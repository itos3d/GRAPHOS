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
#include <QMessageBox>
#include <QInputDialog>
#include <QTextEdit>
#include <typeinfo>
#include <QUuid>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "libPW.h"
#include "Project.h"
#include "PWImage.h"
#include "MicMac/TapiocaIO.h"
#include "MicMac/TapiocaProcess.h"
#include "MicMac/MicMacSparseProcess.h"
#include "MicMac/MicMacDenseProcess.h"
#include "MicMac/MicMacProcess.h"
#include "MicMac/TapasProcess.h"
#include "PWImage.h"
#include "ccHObject.h"
#include "ccPointCloud.h"
#include "PW3dPoint.h"
#include "MicMac/AperoModelReader.h"
#include "MicMac/MicMacEOReader.h"
#include "PhotogrammetricModel.h"
#include "RadialExtended.h"
#include "FraserModel.h"
#include "FishEyeModel.h"
#include "libPW.h"
#include "NewCameraDialog.h"
#include "MicMac/AppuisWriter.h"
#include "MicMac/AperoProcess.h"
#include "ccGLWindow.h"
#include "MicMac/MicMacOrtho2Process.h"
#include "MicMac/MicMacOrthoProcess.h"
#include "MicMac/AperiCloudProcess.h"
#include "CameraExifIO.h"
#include "CameraMetadataIO.h"
#include "QDebugStream.h"
#include "ASIFT/AsiftMatchingIO.h"
#include "MicMac/TapiocaIO.h"
#include "ASIFT/AsiftProcessConcurrent.h"
#include "PS/PSMarkersIO.h"
#include "MicMac/AppuisWriter.h"
#include "PMVS/PMVSProccess.h"
#include "MicMac/Apero2pmvs.h"
#include "MicMac/MesureBascWriter.h"
#include "MicMac/SBGlobBasculeProcess.h"
#include "MicMac/MicMacParametersDefinitions.h"
#include "ASIFT/ASIFTParametersDefinitions.h"
#include "OpenCV/OpenCVKpMParametersDefinitions.h"
#include "OpenCV/OpenCVKpM.h"
#include "OpenCV/OpenCV_kpm_process.h"
#include "Tools/ConvertProcess.h"
#include "ImagePairsFileIO.h"
#include "TiePointsIO.h"
#include "OpenMVG/OpenMVGParametersDefinitions.h"
#include "OpenMVG/OpenMVGKpmProcessConcurrent.h"
#include "PersistenceProcess/WriteMatchesProcess.h"
#include "PersistenceProcess/WriteProjectProcess.h"
#include "PWMatchesCategory.h"
#include "aboutgraphos.h"
#include <liblas/liblas.hpp>
#include <fstream>  // std::ofstream
#include <algorithm> // std::copy
#include "qCC_db_dll.h"
#include "cc/qCC/fileIO/FileIOFilter.h"


using namespace PW;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mPicking(false),
    mNewCameraDialog(0),
    mSettingsDialog(0),
    mExifDataDialog(0),
    mCameraDefinitionDialog(0),
    mComputeOrientationProcess(0),
    mSparseProcess(0),
    mDenseProcess(0),
    mAperoProcess(0),
    mOrientationsGCProcess(0),
    mTapiocaProcess(0),
    mDenseGCProcess(0),
    mOrthoProcess(0),
    mPMVSProcess(0),
    mPMVSMultiProcess(0),
    mApero2PMVSProcess(0),
    mRequiredCameraDefinition(true)
{
    ui->setupUi(this);

    mDockProject = new QDockWidget(tr("Project"),this);
    mDockThumbs = new QDockWidget(tr("Thumbnails"),this);
    mDockThumbs->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    addDockWidget(Qt::LeftDockWidgetArea, mDockProject);
    addDockWidget(Qt::BottomDockWidgetArea, mDockThumbs);

    mPhotoViewerFrame = new QFrame();

    //Setup PhotoViewer:
    mPhotoViewer = new PhotoViewer(this);
    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralLayout->addWidget(mPhotoViewer->getViewWidget());
    mPhotoViewerFrame->setLayout(centralLayout);
    mDockThumbs->setWidget(mPhotoViewer->getThumbsWidget());

    //Setup CC Viewer:
    mCCVW = new ccViewerWrapper();
    mCCVW2 = new ccViewerWrapper();


    //Setup MatchingsViewer:
    mMatchingsViewerFrame = new QFrame();
    mMatchingsViewer = new MatchingViewer(this);
    QVBoxLayout *matchingsCentralLayout = new QVBoxLayout;
    matchingsCentralLayout->addWidget(mMatchingsViewer->getView());
    mMatchingsViewerFrame->setLayout(matchingsCentralLayout);

    //Setup Project tree:
    mProjectTreeWidget = new QTreeWidget();
    mProjectTreeWidget->setHeaderHidden(true);
    mProjectTreeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    mProjectTreeWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
    mDockProject->setWidget(mProjectTreeWidget);

    mConsole = new QTextEdit(this);
    QFont* font = new QFont("Courier");
    font->setPixelSize(10);
    mConsole->setFont(*font);
    mConsole->setReadOnly(true);


    connect(this, SIGNAL(projectChanged()),this, SLOT(loadProjectImages()));
    connect(mPhotoViewer,SIGNAL(saveMask(QPolygonF)),this,SLOT(onSaveMask(QPolygonF)));
    connect(mProjectTreeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this,SLOT(onTreeItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(mProjectTreeWidget, SIGNAL(customContextMenuRequested(QPoint)),
            this, SLOT(onTreeContextMenu(QPoint)));
    connect(mProjectTreeWidget, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
            this, SLOT(onTreeItemDoubleClicked(QTreeWidgetItem*,int)));
    connect(mPhotoViewer,SIGNAL(imgDrawn()),this,SLOT(onImgDrawn()));

    //Desconexiones para usar la barra de menu desde GRAPHOS
    disconnect(ui->actionOpen_Project,SIGNAL(triggered()),this,SLOT(on_actionOpen_Project_triggered()));
    disconnect(ui->actionExport_Project,SIGNAL(triggered()),this,SLOT(on_actionExport_Project_triggered()));
    disconnect(ui->actionImport_Project,SIGNAL(triggered()),this,SLOT(on_actionImport_Project_triggered()));
    disconnect(mProjectTreeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this,SLOT(onTreeItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionSettings_2_triggered()
{
    getSettingsDialog()->show();
}

void MainWindow::initSetups()
{
    mProject = new Project();

    mProgressDialog = new ProgressDialog(mSettings, this);
    mProgressDialog->setConsole(mConsole);

//    QString micmacBinaries = mSettings->value("micmac/binaries").toString();
//    if(micmacBinaries.isEmpty())
//        getSettingsDialog()->show();

//    QString toolsBinaries = mSettings->value("tools/binaries").toString();
//    if(toolsBinaries.isEmpty())
//        mSettings->setValue("tools/binaries", QDir::currentPath()+"/tools");

//    QString sureBinaries = mSettings->value("sure/binaries").toString();
//    if(sureBinaries.isEmpty())
//        mSettings->setValue("sure/binaries", QDir::currentPath()+"/SURE");

//    QString strKeepMatchesInMemory = mSettings->value("app/KeepMatchesInMemory").toString();
//    if(strKeepMatchesInMemory.isEmpty())
//        mSettings->setValue("app/KeepMatchesInMemory", DEFAULT_KEEP_MATCHES_IN_MEMORY);

//    QString strDefaultAccuracyToleranceForMatches=mSettings->value("app/DefaultAccuracyToleranceForMatches").toString();
//    if(strDefaultAccuracyToleranceForMatches.isEmpty())
//        mSettings->setValue("app/DefaultAccuracyToleranceForMatches", DEFAULT_DEFAULT_ACCURACY_TOLERANCE_FOR_MATCHES);


    PW::LibPW::setMicMacBinPath(mSettings->value("micmac/binaries").toString());
    PW::LibPW::setMicMacWorkigPath(mSettings->value("micmac/working").toString());
//    PW::LibPW::setAsiftBinPath(mSettings->value("asift/binaries").toString());
    PW::LibPW::setPMVSBinPath(mSettings->value("pmvs/binaries").toString());
//    PW::LibPW::setOpenCVBinPath(mSettings->value("openCV/binaries").toString());
//    PW::LibPW::setOpenMVGBinPath(mSettings->value("openMVG/binaries").toString());
    PW::LibPW::setToolsPath(mSettings->value("tools/binaries").toString());
    PW::LibPW::setSUREBinPath(mSettings->value("sure/binaries").toString());
    if(PW::LibPW::getToolsPath().isEmpty())
         PW::LibPW::setToolsPath(QDir::currentPath()+"/tools");
    if(PW::LibPW::getSUREBinPath().isEmpty())
         PW::LibPW::setSUREBinPath(QDir::currentPath()+"/sure");

//    PW::LibPW::setKeepMatchesInMemory(mSettings->value("app/KeepMatchesInMemory").toBool());
//    PW::LibPW::setDefaultAccuracyToleranceForMatches(mSettings->value("app/DefaultAccuracyToleranceForMatches").toFloat());

    mOpenProjectDialog = new OpenProjectDialog(mPersistenceManager, this);
    connect(mOpenProjectDialog,SIGNAL(projectSelected(QString)),this,SLOT(onProjectSelected(QString)));

    ui->actionMask->setEnabled(false);
    ui->actionExport_Dense_Model->setEnabled(false);
    ui->actionExport_Sparse_Model->setEnabled(false);
    ui->actionDistance_Tool->setEnabled(false);

    ui->actionDefaultTool->setChecked(true);

    loadProject();
    mPhotoViewer->setEditingMask(false);
}

void MainWindow::cleanEnviroment()
{
    mProjectTreeWidget->clear();

    //clear 3D viewers:
    mCCVW->getGLWindow()->setPickingMode(ccGLWindow::DEFAULT_PICKING);
    mCCVW->clearLables();
    mCCVW2->getGLWindow()->setPickingMode(ccGLWindow::DEFAULT_PICKING);
    mCCVW2->clearLables();
    mCCVW2->addToDB(QStringList());
    mCCVW->addToDB(QStringList());

    //Clear Thumbs and Photo View:
    mPhotoViewer->clearAll();
    mMatchingsViewer->clearAll();
}

int MainWindow::checkToSave()
{
    int ret=QMessageBox::Save;
    if (mProject->needToSave()){
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("Save project");
        msgBox.setText("The project has been modified.");
        msgBox.setInformativeText("Do you want to save your changes?");
        msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Save);
        ret = msgBox.exec();
        switch (ret) {
        case QMessageBox::Save:
            mOpenProjectDialog->setNameVisible(true);
            if (mProject->getName().isEmpty()){
                mOpenProjectDialog->setProjectName(mProject->getName());
                mOpenProjectDialog->setForSave(true);
                mOpenProjectDialog->refreshData();
                mToSave = true;
                mOpenProjectDialog->open();
            }
            else
                mPersistenceManager->updateProject(mProject);
            break;
        case QMessageBox::Discard:
            break;
        case QMessageBox::Cancel:
            break;
        default:
            break;
        }
    }
    return ret;
}

QDockWidget * MainWindow::getDockThumbs()
{
    return mDockThumbs;
}

QFrame * MainWindow::getViewFrame()
{
    return mPhotoViewerFrame;
}

void MainWindow::loadProject()
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
    loadModelsOnTree();

    updateTools();
}

QStringList MainWindow::updateImagesTree()
{
    int imagesCount = mProject->getImages().count();
    //Clear data:
    QList<QTreeWidgetItem*> items = mProjectTreeWidget->findItems(tr("Images"),Qt::MatchContains, 0);
    QTreeWidgetItem* item;
    if(items.count()){
        delete items.at(0);

    }
    item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Images("+QString::number(imagesCount).toAscii()+")")));

    //Load Images:
    mProjectTreeWidget->insertTopLevelItem(1,item);
    QStringList fileNames;

    if(imagesCount>0)
    {
        if(PERSISTENCEMANAGER_NO_ERROR!=mPersistenceManager->setMatchesCategories(mProject))
        {
            QMessageBox::critical(this,tr("Photogrammetry Workbench - Error"),tr("Error setting matches categories"));
            return(fileNames);
        }
        QStringList tiePointsSets;
        tiePointsSets << mProject->getActiveTiePointsSet();
        if(!tiePointsSets.isEmpty())
        {
            if(tiePointsSets.size()==1
                    &&!tiePointsSets[0].isEmpty()){
                TapiocaIO tapiocaIO;
                tapiocaIO.readImagePairs(QDir(mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mProject->getActiveTiePointsSet()).absolutePath(), mImagesIdsPairs);
            }
        }

        for(int i=0; i< imagesCount; i++)
        {
            QString imageName = mProject->getImages().at(i)->getFullPath();
            fileNames.append(imageName);
            item->addChild(getImageTreeItem(mProject->getImages().at(i)));

        }
        QString aImagePath = mProject->getImages().at(0)->getFullPath();
        mImagesPath = aImagePath.left(aImagePath.lastIndexOf(QRegExp("/")));
    }
    item->setExpanded(true);
    return fileNames;
}

void MainWindow::loadProjectImages()
{    
    mPhotoViewer->openFile(updateImagesTree());
}

void MainWindow::loadModelsOnTree()
{
    QList<QTreeWidgetItem*> items = mProjectTreeWidget->findItems(tr("Models"),Qt::MatchExactly, 0);
    QTreeWidgetItem* item;
    if(items.count()){
        int childCount = items.at(0)->childCount();
        for (int i = 0; i < childCount ;i++)
            delete items.at(0)->child(0);
        item = items.at(0);
    }
    else
        item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Models")));
    mProjectTreeWidget->addTopLevelItem(item);
    if(!mProject->getDenseModelRelativePath().isEmpty()){
        QTreeWidgetItem *auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Dense Model"));
        auxItem->setData(0,Qt::ToolTipRole,mProject->getDenseModelFullPath());
        item->addChild(auxItem);
    }

    if(!mProject->getSparseModelRelativePath().isEmpty()){
        QTreeWidgetItem *auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Sparse Model"));
        auxItem->setData(0,Qt::ToolTipRole,mProject->getSparseModelFullPath());
        item->addChild(auxItem);
    }
}

QTreeWidgetItem * MainWindow::getImageTreeItem(PWImage *image){

    //Root Image item:
    QString imageName = image->getFullPath();
    imageName = imageName.right(imageName.length()-imageName.lastIndexOf(QRegExp("/"))-1);
    QString childName = imageName;

    QTreeWidgetItem *item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(childName));
    item->setData(0,Qt::ToolTipRole,image->getFullPath());

    //Mask:
    if (image->getMask().count() > 1){
        QTreeWidgetItem *maskItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Mask")));
        item->addChild(maskItem);
    }
    //Camera:
    if(image->getCamera()){
        QTreeWidgetItem *cameraItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(image->getCamera()->getName()));
        item->addChild(cameraItem);
    }

    QTreeWidgetItem *auxItem;

    //Images Matching:
    QVector<QString> pairs = mImagesIdsPairs.value(image->getFileName());
    if(!pairs.isEmpty()){
        QTreeWidgetItem *matchingsItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Image Matchings")));
        for(int i =0; i<pairs.count(); i++){
            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(pairs.at(i)));
            matchingsItem->addChild(auxItem);
        }
        item->addChild(matchingsItem);
    }


    if (!mProject->getCurrentOrientation().isEmpty()) {
        //Interior Orientation:
        PhotogrammetricModel *cameraModel = (PhotogrammetricModel*)image->getCamera()->getCameraModel();
        if (cameraModel){
            QTreeWidgetItem *InOriItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Internal Orientation")));
            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("focal: ") +
                                                                       QString::number(cameraModel->getFocal())));
            InOriItem->addChild(auxItem);
            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Xp: ") +
                                                                       QString::number(cameraModel->getXp())));
            InOriItem->addChild(auxItem);
            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Yp: ") +
                                                                       QString::number(cameraModel->getYp())));
            InOriItem->addChild(auxItem);

            DistortionModel *distortion = cameraModel->getDistortionModel();

            RadialExtended *extended = dynamic_cast<RadialExtended*>(distortion);

            if(extended != NULL){
                InOriItem->setText(0, tr("Int. Orientation: Radial ext."));
                auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Xcd: ") +
                                                                           QString::number(extended->getXcd())));
                InOriItem->addChild(auxItem);
                auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Ycd: ") +
                                                                           QString::number(extended->getYcd())));
                InOriItem->addChild(auxItem);
                auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("k1: ") +
                                                                           QString::number(extended->getK1())));
                InOriItem->addChild(auxItem);
                auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("k2: ") +
                                                                           QString::number(extended->getK2())));
                InOriItem->addChild(auxItem);
                auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("k3: ") +
                                                                           QString::number(extended->getK3())));
                InOriItem->addChild(auxItem);
                auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("k4: ") +
                                                                           QString::number(extended->getK4())));
                InOriItem->addChild(auxItem);
                auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("k5: ") +
                                                                           QString::number(extended->getK5())));
                InOriItem->addChild(auxItem);
            }else{
                RadialBasic *radialBasic = dynamic_cast<RadialBasic*>(distortion);
                if(radialBasic!=NULL){
                    InOriItem->setText(0, tr("Int. Orientation: Radial basic"));
                    auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("k1: ") +
                                                                               QString::number(radialBasic->getK1())));
                    InOriItem->addChild(auxItem);
                    auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("k2: ") +
                                                                               QString::number(radialBasic->getK2())));
                    InOriItem->addChild(auxItem);
                }else{
                    FraserModel *fraser = dynamic_cast<FraserModel*>(distortion);
                    if(fraser!=NULL){
                        InOriItem->setText(0, tr("Int. Orientation: Fraser basic"));
                        if (!fraser->isBasic()){
                            InOriItem->setText(0, tr("Int. Orientation: Fraser"));
                            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Xcd: ") +
                                                                                       QString::number(fraser->getXcd())));
                            InOriItem->addChild(auxItem);
                            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Ycd: ") +
                                                                                       QString::number(fraser->getYcd())));
                            InOriItem->addChild(auxItem);
                        }
                        auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("k1: ") +
                                                                                   QString::number(fraser->getK1())));
                        InOriItem->addChild(auxItem);
                        auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("k2: ") +
                                                                                   QString::number(fraser->getK2())));
                        InOriItem->addChild(auxItem);
                        auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("k3: ") +
                                                                                   QString::number(fraser->getK3())));
                        InOriItem->addChild(auxItem);
                        auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("P1: ") +
                                                                                   QString::number(fraser->getP1())));
                        InOriItem->addChild(auxItem);
                        auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("P2: ") +
                                                                                   QString::number(fraser->getP2())));
                        InOriItem->addChild(auxItem);
                        auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("b1: ") +
                                                                                   QString::number(fraser->getB1())));
                        InOriItem->addChild(auxItem);
                        auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("b2: ") +
                                                                                   QString::number(fraser->getB2())));
                        InOriItem->addChild(auxItem);
                    }else{
                        FishEyeModel *fishEye = dynamic_cast<FishEyeModel*>(distortion);
                        if(fishEye!=NULL){
                            InOriItem->setText(0, tr("Int. Orientation: FishEye."));
                            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Xcd: ") +
                                                                                       QString::number(fishEye->getXcd())));
                            InOriItem->addChild(auxItem);
                            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Ycd: ") +
                                                                                       QString::number(fishEye->getYcd())));
                            InOriItem->addChild(auxItem);
                        }
                    }
                }
            }
            item->addChild(InOriItem);
        }

        //Exterior Orientation:
        ExteriorOrientation *ext = image->getExteriorOrientation();
        if(ext != NULL){
            QTreeWidgetItem *ExtOriItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("External Orientation")));

            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("CP: ") +
                                                                       QString::number(ext->getCP()->at(0)) + ", " +
                                                                       QString::number(ext->getCP()->at(1)) + ", " +
                                                                       QString::number(ext->getCP()->at(2))));
            ExtOriItem->addChild(auxItem);

            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("R")));
            auxItem->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString::number(ext->getR()->at(0).at(0)) + ", " +
                                                                               QString::number(ext->getR()->at(0).at(1)) + ", " +
                                                                               QString::number(ext->getR()->at(0).at(2)))));
            auxItem->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString::number(ext->getR()->at(1).at(0)) + ", " +
                                                                               QString::number(ext->getR()->at(1).at(1)) + ", " +
                                                                               QString::number(ext->getR()->at(1).at(2)))));
            auxItem->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString::number(ext->getR()->at(2).at(0)) + ", " +
                                                                               QString::number(ext->getR()->at(2).at(1)) + ", " +
                                                                               QString::number(ext->getR()->at(2).at(2)))));

            ExtOriItem->addChild(auxItem);
            item->addChild(ExtOriItem);
        }
    }

    //Control Points:
    if(image->getControlPoints()->count() > 0){
        QTreeWidgetItem *pointsItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Control Points")));
        for(int i = 0; i<image->getControlPoints()->count(); i++){
            PW2dPoint *point = image->getControlPoints()->at(i);
            auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(point->getName() + ": "  +
                                                                       QString::number(point->getCoord(0)) + ", " +
                                                                       QString::number(point->getCoord(1))));
            pointsItem->addChild(auxItem);
        }
        item->addChild(pointsItem);
    }
    return item;
}

QTreeWidgetItem * MainWindow::getModelsTreeItem(PW::Project *project){
    QTreeWidgetItem* modelsItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Models"));

    if(!project->getDenseModelRelativePath().isEmpty()){
        QTreeWidgetItem *auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Dense Model"));
        auxItem->setData(0,Qt::ToolTipRole,project->getDenseModelFullPath());
        modelsItem->addChild(auxItem);
    }

    if(!project->getSparseModelRelativePath().isEmpty()){
        QTreeWidgetItem *auxItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Sparse Model"));
        auxItem->setData(0,Qt::ToolTipRole,project->getSparseModelFullPath());
        modelsItem->addChild(auxItem);
    }
    return modelsItem;
}

void MainWindow::onError(int code, QString cause)
{
    if(!mSparseStopped){
        mSparseStopped = true;
        mSparseProcess->stop();
        mProgressDialog->close();
        qCritical() << tr("Error generating MicMac sparse model: ") << cause;
    }
}

int MainWindow::replace(QFile *inputFile, QFile *outputFile, QString from, QString to){
    if (inputFile->open(QIODevice::ReadOnly)){
        QString baseString(inputFile->readAll());
        baseString.replace(QRegExp(from),to);
        inputFile->close();

        if(outputFile->open(QIODevice::WriteOnly)){
            QTextStream outputStream(outputFile);
            outputStream << baseString << "\n";

            outputFile->close();
        }
    }
    return true;
}

void MainWindow::onSaveMask(QPolygonF polygon)
{
    PWImage *image = mProject->getImageByURL(mPhotoViewer->currentfile);
    if (image != NULL){
        if(polygon.count()>0){
            image->setMask(polygon);
            mPersistenceManager->updateProject(mProject);
            createMaskImg(mPhotoViewer->imgWidth, mPhotoViewer->imgHeight, polygon);
        }
        else{
            image->setMask(polygon);
            delteMaskImg();
        }
    }
    loadProjectImages();
}

void MainWindow::onTreeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(current != NULL && current->parent() != NULL && current->parent()->text(0).contains(tr("Images"))){
        QString imagePath = current->data(0,Qt::ToolTipRole).toString();
        mPhotoViewer->loadNewImg(imagePath,0);

        //Update Graphics (mask and points).
        updatePhotoViewerGraphics();
    }
}

void MainWindow::delteMaskImg(){
    QString imgPath = mPhotoViewer->currentfile;
    QString maskPath = imgPath.left(imgPath.lastIndexOf(".")) +"_Masq.tif";
    QFile file(maskPath);
    file.remove();

    file.setFileName(maskPath.left(maskPath.lastIndexOf(".")) +".xml");
    file.remove();
}

void MainWindow::createMaskImg(int width, int height, QPolygonF polygon)
{
    QString imgPath = mPhotoViewer->currentfile;

    //WRITE:
    QImage imgMask(width, height, QImage::Format_Mono);
    imgMask.setNumColors(2);
    imgMask.fill(0);
    for (int x=0; x<width;x++)
        for (int y = 0; y<height;y++){
            if (polygon.containsPoint(QPointF(x,y), Qt::OddEvenFill))
                imgMask.setPixel(QPoint(x,y),1);
        }
    QString maskPath = imgPath.left(imgPath.lastIndexOf(".")) +"_Masq.tif";
    QImageWriter writer(maskPath);
    writer.setText("parameters", "none bps=6");
    if(writer.write(imgMask) ){
        //Create XML file:
        QFile maskBaseFile(":/PW/MICMAC/mask");
        QFile maskFile(maskPath.left(maskPath.lastIndexOf(".")) +".xml");
        maskFile.remove();
        replace(&maskBaseFile, &maskFile,"PW_IMG",maskPath);
        replace(&maskFile, &maskFile,"PW_WIDTH",QString::number(width));
        replace(&maskFile, &maskFile,"PW_HEIGHT",QString::number(height));
    }
}

void MainWindow::on_actionMask_triggered()
{
    mPhotoViewer->setEditingMask(!mPhotoViewer->editingMask);
    mPhotoViewer->drawMask();
}

void MainWindow::on_actionPicking_triggered()
{
    mPicking = !mPicking;

    ccPointCloud* cloud = 0;

    ccHObject* obj = mCCVW2->getGLWindow()->getSceneDB()->getFirstChild();

    if (obj && obj->isKindOf(CC_POINT_CLOUD)){
        cloud = static_cast<ccPointCloud*>(obj);
        if(mPicking){
            mCCVW2->activatePointListDisplay();
            connect(mCCVW2->getGLWindow(),SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onModel2ContextMenu(QPoint)));
            connect(mCCVW2->getGLWindow(),SIGNAL(rightButtonClicked(int,int)),this,SLOT(onModel2RightClick(int, int)));

        }
        else{
            mCCVW2->getGLWindow()->setPickingMode(ccGLWindow::NO_PICKING);
            disconnect(mCCVW2->getGLWindow(),SIGNAL(pointPicked(int cloudID, uint pointIndex, int x, int y)),this,SLOT(onModel2PointPicked(int cloudID, uint pointIndex, int x, int y)));
            disconnect(mCCVW2->getGLWindow(),SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(onModel2ContextMenu(QPoint)));
            disconnect(mCCVW2->getGLWindow(),SIGNAL(rightButtonClicked(int,int)),this,SLOT(onModel2RightClick(int, int)));

            //Save picked points:   **********************************************
            mProject->getModelCPoints()->clear();
            if(mCCVW2->getPickedPointsList().count() > 0){
                QList<unsigned> indexes = mCCVW2->getPickedPointsList();
                for(int i=0; i<indexes.size();i++){
                    const CCVector3* ccPoint = cloud->getPoint(indexes.at(i));
                    PW3dPoint *point = new PW3dPoint (ccPoint->x,ccPoint->y,ccPoint->z);
                    point->setName("P"+QString::number(i+1)); // Point Name...
                    mProject->getModelCPoints()->append(point);
                }

                //Calculate image points from model points:
                mProject->calculateImagePoints();

                loadProjectImages();
            }
        }
    }
}

void MainWindow::updatePhotoViewerGraphics()
{
    PW::PWImage *image = mProject->getImageByURL(mPhotoViewer->currentfile);
    if (image != NULL){
        mPhotoViewer->clearControlPoints();
        for(int i = 0; i< image->getControlPoints()->count(); i++){
            mPhotoViewer->currentControlPointsPW.append(image->getControlPoints()->at(i));
        }
        mPhotoViewer->currentMask = image->getMask();
    }
    mPhotoViewer->drawControlPoints();
    mPhotoViewer->drawMask();
    mPhotoViewer->drawAuxiliarSceneItems();
}

bool MainWindow::isRequiredCameraDefinition()
{
    return mRequiredCameraDefinition;
}

void MainWindow::setRequiredCameraDefinition(bool required)
{
    mRequiredCameraDefinition = required;
}

void MainWindow::on_actionSave_triggered()
{
    mOpenProjectDialog->setNameVisible(true);
    if (mProject->getName().isEmpty()){
        mOpenProjectDialog->setProjectName(mProject->getName());
        mOpenProjectDialog->setForSave(true);
        mOpenProjectDialog->refreshData();
        mToSave = true;
        mOpenProjectDialog->open();
    }
    else
        mPersistenceManager->updateProject(mProject);
}

void MainWindow::onProjectSelected(QString projectName)
{
    if(mToSave){
        mProject->setDescription("PW-GUI...");
        if (mProject->getID() && projectName == mProject->getName())
            mPersistenceManager->updateProject(mProject);
        else{
            mProject->setName(projectName);
            WriteProjectProcess *writeProjectProcess = new WriteProjectProcess(mPersistenceManager,mProject, false, mProject->getID());
            mProgressDialog->setFinished(false);
            mProgressDialog->setModal(true);
            connect(writeProjectProcess, SIGNAL(finished()),this,SLOT(onWriteProjectFinished()));
            connect(mProgressDialog,SIGNAL(cancel()),writeProjectProcess,SLOT(quit()));
            connect(writeProjectProcess, SIGNAL(finished()),writeProjectProcess,SLOT(deleteLater()));
            mProgressDialog->setStatusText("Writing project...");
            mProgressDialog->setRange(0,0);
            writeProjectProcess->start();
            mProgressDialog->exec();
        }
    }
    else{
        delete mProject;
        mProject = mPersistenceManager->readProject(projectName);
        loadProject();
        connect(mPhotoViewer->thumbs->thread,SIGNAL(finished()),this,SLOT(onThumbsLoadFinished()));
    }
    this->setWindowTitle(mAppTitle+" - " + projectName);
}

NewCameraDialog * MainWindow::getNewcameraDialog()
{
    if (mNewCameraDialog == NULL)
        mNewCameraDialog = new NewCameraDialog(mPersistenceManager);
    return mNewCameraDialog;
}

ExifDataDialog *MainWindow::getExifDataDialog()
{
    if (mExifDataDialog == NULL){
        mExifDataDialog = new ExifDataDialog(this);

    }
    return mExifDataDialog;
}

SettingsDialog *MainWindow::getSettingsDialog()
{
    if(mSettingsDialog == NULL){
        mSettingsDialog = new SettingsDialog(mSettings,this);
        mSettingsDialog->setWindowTitle("Settings");
    }

    return mSettingsDialog;
}


CameraDefinitionDialog *MainWindow::getCameraDefinitionDialog()
{
    if(mCameraDefinitionDialog == NULL){
        mCameraDefinitionDialog = new CameraDefinitionDialog(mPersistenceManager);
    }

    return mCameraDefinitionDialog;
}

void MainWindow::onTreeItemDoubleClicked(QTreeWidgetItem *item, int column)
{

}

bool MainWindow::removeDir(QString dirName)
{
    bool result = true;
    QDir dir(dirName);
    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }
            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

bool MainWindow::removeDir(QString dirName, QStringList exceptions)
{
    bool result = true;
    QDir dir(dirName);
    bool skip = false;
    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            foreach (const QString &str, exceptions) {
                if (info.absoluteFilePath().contains(QRegExp(str))){
                    skip = true;
                    break;
                }
            }
            if (skip){
                skip = false;
                continue;
            }
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }
            if (!result) {
                return result;
            }
        }

        if (dir.entryList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst).isEmpty())
            result = dir.rmdir(dirName);
    }
    return result;
}


void MainWindow::onImgDrawn()
{
    updatePhotoViewerGraphics();
    mPhotoViewer->drawControlPoints();
    mPhotoViewer->drawMask();

    if(mProject->getOriginImage() == mProject->getImageByURL(mPhotoViewer->currentfile))
        mPhotoViewer->drawOriginPoint=true;
    else
        mPhotoViewer->drawOriginPoint=false;

    if(mProject->getOXImage()== mProject->getImageByURL(mPhotoViewer->currentfile))
        mPhotoViewer->drawOriginEdge=true;
    else
        mPhotoViewer->drawOriginEdge=false;

    if(mProject->getScaleImageA()== mProject->getImageByURL(mPhotoViewer->currentfile))
        mPhotoViewer->drawScaleLine1=true;
    else
        mPhotoViewer->drawScaleLine1=false;

    if(mProject->getScaleImageB()== mProject->getImageByURL(mPhotoViewer->currentfile))
        mPhotoViewer->drawScaleLine2=true;
    else
        mPhotoViewer->drawScaleLine2=false;

    mPhotoViewer->drawAuxiliarSceneItems();
}

void MainWindow::onTabWidgetCahnge(int index)
{
    if(index >= 0){
        updateTools();
    }
}


void MainWindow::onThumbsLoadFinished()
{
    mProgressDialog->setFinished(true);
    mProgressDialog->close();
}


void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_actionExport_Sparse_Model_triggered()
{
    QString initPath = mSettings->value("app/lastoutputpath").toString();
    if (initPath.isEmpty())
        initPath = QDir::homePath();

    QFileInfo densePath (mProject->getSparseModelFullPath());
    QString savePath("");

    QString filters("las file (*.las);;laz compressed file (*.laz);;Splits file (*.ply);;Cloud Compare file (*.bin);;Plane text file (*.asc)");
    QString defaultFilter;

    if (densePath.suffix().contains("las")) {
        defaultFilter="las file (*.las)";
    }else{
        defaultFilter="Splits (*.ply)";
    }

    savePath = QFileDialog::getSaveFileName(0, tr("Dense Model"),
                                                initPath,
                                                filters, &defaultFilter);
    QFileInfo saveFileInfo(savePath);
    if(!savePath.isEmpty()){
        ccHObject* entitiesToDispatch = mCCVW->getCcHObject();

        if (entitiesToDispatch->getChildrenNumber() != 0){
            CC_FILE_ERROR result = CC_FERR_NO_ERROR;

            QString filePath;
            filePath.append(saveFileInfo.absolutePath()).append("/").append(saveFileInfo.baseName());
            QFileInfo auxFileInfo(filePath);

            QStringList fileExtensions;
            fileExtensions << "ply" << "las" << "asc"<< "bin"<<"laz";
            switch (fileExtensions.indexOf(saveFileInfo.suffix())) {
            case 0:
                result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),auxFileInfo.absoluteFilePath().toAscii(),CC_FILE_TYPES::PLY);
                    break;
            case 1:
                result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),auxFileInfo.absoluteFilePath().toAscii(),CC_FILE_TYPES::LAS);
                break;
            case 2:
                result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),auxFileInfo.absoluteFilePath().toAscii(),CC_FILE_TYPES::ASCII);
                break;
            case 3:
                result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),auxFileInfo.absoluteFilePath().toAscii(),CC_FILE_TYPES::BIN);
                break;
            case 4:
                QFileInfo *tmpLasFile;
                if (!densePath.suffix().contains("las")) {
                    QString tmpLasPath =mProject->getBasePath()+"/tempLas.las";
                    tmpLasFile = new QFileInfo(tmpLasPath);
                    result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),tmpLasFile->absoluteFilePath().toAscii(),CC_FILE_TYPES::LAS);
                }else {
                    tmpLasFile = new QFileInfo(densePath.absoluteFilePath());

                }
                std::ifstream ifs(tmpLasFile->absoluteFilePath().toAscii(), std::ios::in | std::ios::binary);
                std::ofstream ofs((auxFileInfo.absoluteFilePath()+".laz").toAscii(), std::ios::out | std::ios::binary);

                liblas::ReaderFactory f;
                liblas::Reader reader = f.CreateWithStream(ifs);

                liblas::Header header = reader.GetHeader();
                header.SetCompressed(true);

                liblas::Writer writer(ofs, header);

                std::copy(liblas::lasreader_iterator(reader),  liblas::lasreader_iterator(),
                          liblas::laswriter_iterator(writer));
                ifs.close();
                QString tmpLasPath =mProject->getBasePath()+"/tempLas.las";
                QFileInfo tmpLasFileToRemove(tmpLasPath);
                if (tmpLasFileToRemove.exists()) {
                    QFile::remove(tmpLasFileToRemove.absoluteFilePath());
                }
                break;
            }

        }
    }
}

void MainWindow::on_actionExport_Dense_Model_triggered()
{
    QString initPath = mSettings->value("app/lastoutputpath").toString();
    if (initPath.isEmpty())
        initPath = QDir::homePath();

    QFileInfo densePath (mProject->getDenseModelFullPath());
    QString savePath("");

    QString filters("las file (*.las);;laz compressed file (*.laz);;Splits file (*.ply);;Cloud Compare file (*.bin);;Plane text file (*.asc)");
    QString defaultFilter;

    if (densePath.suffix().contains("las")) {
        defaultFilter="las file (*.las)";
    }else{
        defaultFilter="Splits (*.ply)";
    }

    savePath = QFileDialog::getSaveFileName(0, tr("Dense Model"),
                                                initPath,
                                                filters, &defaultFilter);
    QFileInfo saveFileInfo(savePath);
    if(!savePath.isEmpty()){
        ccHObject* entitiesToDispatch = mCCVW2->getCcHObject();

        if (entitiesToDispatch->getChildrenNumber() != 0){
            CC_FILE_ERROR result = CC_FERR_NO_ERROR;

            QString filePath;
            filePath.append(saveFileInfo.absolutePath()).append("/").append(saveFileInfo.baseName());
            QFileInfo auxFileInfo(filePath);

            QStringList fileExtensions;
            fileExtensions << "ply" << "las" << "asc"<< "bin"<<"laz";
            switch (fileExtensions.indexOf(saveFileInfo.suffix())) {
            case 0:
                result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),auxFileInfo.absoluteFilePath().toAscii(),CC_FILE_TYPES::PLY);
                    break;
            case 1:
                result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),auxFileInfo.absoluteFilePath().toAscii(),CC_FILE_TYPES::LAS);
                break;
            case 2:
                result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),auxFileInfo.absoluteFilePath().toAscii(),CC_FILE_TYPES::ASCII);
                break;
            case 3:
                result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),auxFileInfo.absoluteFilePath().toAscii(),CC_FILE_TYPES::BIN);
                break;
            case 4:
                QFileInfo *tmpLasFile;
                if (!densePath.suffix().contains("las")) {
                    QString tmpLasPath =mProject->getBasePath()+"/tempLas.las";
                    tmpLasFile = new QFileInfo(tmpLasPath);
                    result = FileIOFilter::SaveToFile(entitiesToDispatch->getChildrenNumber() > 1 ? entitiesToDispatch : entitiesToDispatch->getChild(0),tmpLasFile->absoluteFilePath().toAscii(),CC_FILE_TYPES::LAS);
                }else {
                    tmpLasFile = new QFileInfo(densePath.absoluteFilePath());

                }
                std::ifstream ifs(tmpLasFile->absoluteFilePath().toAscii(), std::ios::in | std::ios::binary);
                std::ofstream ofs((auxFileInfo.absoluteFilePath()+".laz").toAscii(), std::ios::out | std::ios::binary);

                liblas::ReaderFactory f;
                liblas::Reader reader = f.CreateWithStream(ifs);

                liblas::Header header = reader.GetHeader();
                header.SetCompressed(true);

                liblas::Writer writer(ofs, header);

                std::copy(liblas::lasreader_iterator(reader),  liblas::lasreader_iterator(),
                          liblas::laswriter_iterator(writer));
                break;
            }
        }
    }
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    //Need to save??
    if (mProject->needToSave()){
        QMessageBox msgBox;
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

void MainWindow::on_actionAbout_PW_triggered() //Cambiar PW por GRAPHOS
{
    AboutGraphos *aboutdialog = new AboutGraphos();
    aboutdialog->exec();
}

void MainWindow::on_actionUndistort_images_triggered()
{

}

void MainWindow::manageProccesStdOutput(QString data)
{
    mConsole->append("<font color='black'>" + data + "\n</font>");
}

void MainWindow::manageProccesErrorOutput(QString data)
{
    mConsole->append("<font color='#999900'>" + data + "</font>");
}

int MainWindow::validateImages(QStringList fileNames){
    if(fileNames.isEmpty())
        return 1;

    if(fileNames.at(0).contains(" "))
        return 2;

    Camera firstCamera;
    PWImage *firstImage;
    CameraMetadataIO exifIO;
    int i=0;
    if(mProject->getImages().count() > 0){
        firstImage = mProject->getImages().at(0);
        firstCamera = *(firstImage->getCamera());
    }
    else {
        exifIO.setImagePath(fileNames.at(0));
        exifIO.read(&firstCamera);
        firstImage = new PWImage(fileNames.at(0));
        i=1;
    }
    for (i;i<fileNames.count(); i++){
        if(fileNames.at(i).contains(" "))
            return 2;
        Camera camera;
        PWImage image(fileNames.at(i));
        exifIO.setImagePath(fileNames.at(i));
        exifIO.read(&camera);
        if(firstCamera.getName() != camera.getName() ||
                firstImage->getSize().width() != image.getSize().width() ||
                firstImage->getSize().height() != image.getSize().height()
                ){
            if(mProject->getImages().count() == 0){
                delete firstImage;
            }
            return 3;
        }
    }
    if(mProject->getImages().count() == 0){
        delete firstImage;
    }
    return 0;
}


bool MainWindow::isTiePointsTxt(QString basePath)
{
    QDir baseDir(basePath);
    if (baseDir.exists()){
        QStringList homolList = baseDir.entryList(QStringList("Homol"), QDir::Dirs | QDir::NoSymLinks);

        if (homolList.count() == 0)
            return false;
        QDir homolDir(basePath + "/" + homolList.at(0));
        QStringList homolContent = homolDir.entryList(QStringList("*"), QDir::Dirs | QDir::NoSymLinks);
        if (homolContent.count() == 0)
            return false;
        QList <PWImage*> images = mProject->getImages();
        for(int i = 0; i < images.count(); i++){
            if (homolContent.contains("Pastis"+images.at(i)->getFileName())){
                QDir pastisDir(basePath+"/Homol/Pastis"+images.at(i)->getFileName());
                QStringList txtList = pastisDir.entryList(QStringList("*.txt"), QDir::Files | QDir::NoSymLinks);
                if (!txtList.isEmpty())
                    return true;
            }
        }
        return false;
    }
    else
        return false;
}

void MainWindow::on_actionDistance_Tool_triggered()
{
    mCCVW->activateDistanceDisplay();
    mCCVW2->activateDistanceDisplay();
    ui->actionDefaultTool->setChecked(false);
    ui->actionDistance_Tool->setChecked(true);
    ui->actionAngleTool->setChecked(false);
    ui->actionPointTool->setChecked(false);
    ui->action_ActionPickRotationCenter->setChecked(false);

}

void MainWindow::on_actionAngleTool_triggered()
{
    mCCVW->activateTriangleDisplay();
    mCCVW2->activateTriangleDisplay();
    ui->actionDefaultTool->setChecked(false);
    ui->actionDistance_Tool->setChecked(false);
    ui->actionAngleTool->setChecked(true);
    ui->actionPointTool->setChecked(false);
    ui->action_ActionPickRotationCenter->setChecked(false);

}

void MainWindow::on_actionPointTool_triggered()
{
    mCCVW->activatePointDisplay();
    mCCVW2->activatePointDisplay();
    ui->actionDefaultTool->setChecked(false);
    ui->actionDistance_Tool->setChecked(false);
    ui->actionAngleTool->setChecked(false);
    ui->actionPointTool->setChecked(true);
    ui->action_ActionPickRotationCenter->setChecked(false);

}

void MainWindow::on_actionDefaultTool_triggered()
{
    mCCVW->getGLWindow()->setPickingMode(ccGLWindow::DEFAULT_PICKING);
    mCCVW->clearLables();
    mCCVW2->getGLWindow()->setPickingMode(ccGLWindow::DEFAULT_PICKING);
    mCCVW2->clearLables();
    ui->actionDefaultTool->setChecked(true);
    ui->actionDistance_Tool->setChecked(false);
    ui->actionAngleTool->setChecked(false);
    ui->actionPointTool->setChecked(false);
    ui->action_ActionPickRotationCenter->setChecked(false);

}

bool MainWindow::copyDir(QString sourceFolder, QString destFolder, bool move)
{
    QDir sourceDir(sourceFolder);
    if(!sourceDir.exists())
        return(false);
    QDir destDir(destFolder);
    if(!destDir.exists())
    {
        QDir().mkdir(destFolder);
    }
    QStringList files = sourceDir.entryList(QDir::Files);
    for(int i = 0; i< files.count(); i++)
    {
        QString srcName = sourceFolder + "/" + files[i];
        QString destName = destFolder + "/" + files[i];
        QFile::copy(srcName, destName);
        if (move)
            QFile::remove(srcName);
    }
    files.clear();
    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for(int i = 0; i< files.count(); i++)
    {
        QString srcName = sourceFolder + "/" + files[i];
        QString destName = destFolder + "/" + files[i];
        copyDir(srcName, destName, move);
    }
    if(move){
        if (sourceDir.exists()) {
            removeDir(sourceDir.absolutePath());
            }
    }
    return true;
}

void MainWindow::loadProjectMetadataOnProjectTree()
{
    QList<QTreeWidgetItem*> items = mProjectTreeWidget->findItems(tr("Project info"),Qt::MatchExactly, 0);
    QTreeWidgetItem* item;
    if(items.count()){
        int childCount = items.at(0)->childCount();
        for (int i = 0; i < childCount ;i++)
            delete items.at(0)->child(0);
        item = items.at(0);
    }
    else
        item = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr("Project info")));
#ifdef QT_DEBUG

#else
    QDomDocument metadataDoc;
    metadataDoc.setContent(mProject->getProcessMetadata());
    QDomElement root = metadataDoc.documentElement();
    if(root.tagName() == "ProcessMetadata"){
        for(int i=0; i<root.childNodes().count();i++){
            QDomNode node = root.childNodes().at(i);
            QTreeWidgetItem *auxitem,*auxitem2;
            int nodeToEvaluate=0;
            if (mProject->getActiveTiePointsSet().count()>0 && node.toElement().tagName()=="TiePoints") {
                auxitem = new QTreeWidgetItem((QTreeWidget*)0,QStringList("Tiepoints"));
                QString preprocessingMode = node.childNodes().at(nodeToEvaluate).toElement().text();
                nodeToEvaluate++;
                if (preprocessingMode.compare("Wallisfilter",Qt::CaseInsensitive)==0) {
                    auxitem2 = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Preprocessing: Wallis filter"));
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Contrast: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Brightness: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Std. deviation: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Kernell size: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                }else {
                    auxitem->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Preprocessing: Contrast preserving decolorization")));
                }
                auxitem->addChild(auxitem2);
                auxitem->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Tool: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                nodeToEvaluate++;
                QString searchMode = node.childNodes().at(nodeToEvaluate).toElement().text();
                nodeToEvaluate++;
                auxitem2 = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Search mode: "+searchMode));
                if (searchMode.compare("Line",Qt::CaseInsensitive)==0) {
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Range: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Size: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem->addChild(auxitem2);
                }else if(searchMode.compare("MulScale",Qt::CaseInsensitive)==0){
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Max scale: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Min scale: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem->addChild(auxitem2);
                }else{
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Size: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                }
                auxitem->addChild(auxitem2);
            }

            if (!mProject->getSparseModelFullPath().isEmpty() && node.toElement().tagName()=="Orientation") {
                auxitem = new QTreeWidgetItem((QTreeWidget*)0,QStringList("Orientation"));
                QString orientationMode = node.childNodes().at(nodeToEvaluate).toElement().text();
                nodeToEvaluate++;
                if (orientationMode.compare("Generic",Qt::CaseInsensitive)==0) {
                    auxitem2 = new QTreeWidgetItem((QTreeWidget*)0, QStringList("Orientation: "+orientationMode));
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Parameters: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem->addChild(auxitem2);
                }else {
                    if (orientationMode.compare("Fraser",Qt::CaseInsensitive)==0) {
                        auxitem->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Calibration model: Complete (Fraser)")));
                    }else{
                        auxitem->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Calibration model: basic (Radial basic)")));
                    }
                }
            }

            if (!mProject->getDenseModelFullPath().isEmpty() && node.toElement().tagName()=="Model") {
                auxitem = new QTreeWidgetItem((QTreeWidget*)0,QStringList("Dense matching"));
                auxitem->addChild(new QTreeWidgetItem((QTreeWidget*)0,QStringList("Cloud size: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                nodeToEvaluate++;
                QString denseMatchingMode = node.childNodes().at(nodeToEvaluate).toElement().text();
                nodeToEvaluate++;
                if (denseMatchingMode.contains("MicMac")) {
                    auxitem2 =new QTreeWidgetItem((QTreeWidget*)0, QStringList("Tool: "+denseMatchingMode));
                    if (denseMatchingMode.contains("master")) {
                        auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Master images: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                        nodeToEvaluate++;
                    }
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("DeZoom: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("ZRegul: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("ZPas: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem->addChild(auxitem2);
                }else if(denseMatchingMode.compare("PMVS",Qt::CaseInsensitive)==0){
                    auxitem2 =new QTreeWidgetItem((QTreeWidget*)0, QStringList("Tool: "+denseMatchingMode));
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Level: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Min: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Csize: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Threshold: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem->addChild(auxitem2);
                }else if(denseMatchingMode.compare("SURE",Qt::CaseInsensitive)==0){
                    auxitem2 =new QTreeWidgetItem((QTreeWidget*)0, QStringList("Tool: "+denseMatchingMode));
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Pyr: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("Fold: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem2->addChild(new QTreeWidgetItem((QTreeWidget*)0, QStringList("MaxModels: "+node.childNodes().at(nodeToEvaluate).toElement().text())));
                    nodeToEvaluate++;
                    auxitem->addChild(auxitem2);
                }else if(denseMatchingMode.compare("C3DC",Qt::CaseInsensitive)==0){
                    auxitem2 =new QTreeWidgetItem((QTreeWidget*)0, QStringList("Tool: "+denseMatchingMode));
                    auxitem->addChild(auxitem2);
                }
            }
            item->addChild(auxitem);
        }
    }
    mProjectTreeWidget->insertTopLevelItem(0,item);
#endif
}
void MainWindow::addItem(QTreeWidgetItem *item, QDomNode node){
    for(int i=0; i<node.childNodes().count();i++){
        QDomNode childNode = node.childNodes().at(i);
        QTreeWidgetItem *childItem;
        if (childNode.childNodes().count()>1){
            childItem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(tr(childNode.toElement().tagName().toAscii())));
            addItem(childItem, childNode);
        }
        else{
            QStringList fields;
            fields << tr(childNode.toElement().tagName().toAscii()) << tr(childNode.toElement().text().toAscii());
            childItem = new QTreeWidgetItem((QTreeWidget*)0, fields);
        }
        item->addChild(childItem);
    }
}

