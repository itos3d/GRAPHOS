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
#ifndef MAINWINDOWGRAPHOS_H
#define MAINWINDOWGRAPHOS_H

#define MAINWINDOWGRAPHOS_PROGRAM_NAME         "GRAPHOS"
#define MAINWINDOWGRAPHOS_PROGRAM_TAG          "GRAPHOS"
#define MAINWINDOWGRAPHOS_VERSION              "1.0"
#define MAINWINDOWGRAPHOS_BUILD_NUMBER         "35"
#define MAINWINDOWGRAPHOS_RELEASE_TYPE         "(beta)"


#include <mainwindow.h>
#include "NewProjectDialog.h"
#include <QStackedWidget>
#include "ImagesWizard.h"
#include "OrientationWizard.h"
#include "DensificationWizard.h"
#include "BatchProcessWizard.h"
#include <QListWidget>
#include "Preprocessing/WallisBatchProcess.h"
#include <SURE/Apero2SureProcess.h>
#include <SURE/SUREProcess.h>
#include <SURE/MergeLasResultsProcess.h>
#include <SURE/CustomSureProcess.h>
#include <QStringList>
#include "MicMac/DrunkProcess.h"
#include "MicMac/TapiocaProcess.h"
#include "MicMac/MicMacComputeSlavesProcess.h"
#include "MicMac/C3DCProcess.h"
#include "ExternalProcess.h"
#include "TiePointsWizard.h"
#include "quazip/quazip.h"
#include "quazip/quazipfile.h"
#include "GCPWidget.h"
#include "GeorefMicMac/GCPBasculeProcess.h"
#include "GeorefMicMac/GCPWriter.h"
#include "GeorefMicMac/imgPointWriter.h"
#include "GeorefMicMac/CampariProcess.h"
#include "Tools/ScaleProcess.h"
#include "ScaleModelDialog.h"
class MainWindowGRAPHOS : public MainWindow
{
    Q_OBJECT

public:
    MainWindowGRAPHOS(bool spatialDatabase);
    QLabel *lbVersionGRAPHOS;

signals:
    void recomputeOrientationsTriggered();
    void launchPMVS();
    void statusChanged(int step, QString message);

protected:
    virtual void updateTools();

private:
    bool CUDA_ENABLED;
    ScaleModelDialog *scaleDialog;
    QString mExportPath;
    TiePointsWizard *mTiePointsWizard;
    BatchProcessWizard *mBatchProcessWizard;
    QStringList *mFileNamesToLoad;
    QMap<QString, QString> mTiePointsMethod;
    bool mHaveNewImages;
    QFuture<int> mImageLoader;
    QFutureWatcher<int> *mImagesLoaderfutureWatcher;
    QFutureWatcher<QImage> *mImagesLoaderfutureWatcher2;

    QMap<QString, QImage> *mMapImages;
    PW::Process *mWallisProcess;
    PW::ExternalProcess *mApero2PMVSProcess;
    PW::ExternalProcess *mGCPBasculeProcess;
    PW::ExternalProcess *mCampariProcess;
    PW::MultiProcess *mGeorrefProcess;
    PW::ProcessConcurrent *mGCPWriterProcess;
    PW::ProcessConcurrent *mImgPtWriterProcess;

    PW::Process *mPMVSProcess;
    PW::MultiProcess *mMsdProcess;
    PW::MultiProcess *mASIFTUProcess;
    PW::MultiProcess *mMultiMainImageMicMacProcess;
    PW::C3DCProcess *mC3DCProcess;
    PW::MultiProcess *mMaltDensificationProcess;
    PW::MultiProcess *mBatchProcess;


    PW::MultiProcess *mCvDecolorMultiProcess;
    ScaleProcess *mScaleProcess;
    NewProjectDialog *mNewProjectDialog;
    QStackedWidget *mQStackedWidget;
    QStackedWidget *mBasicUserGUI;
    QDockWidget *mDockWorkflow;
    QDockWidget *mDockGeorref;
    GCPWidget *mGCPWidget;
    ImagesWizard *mImagesWizard;
    OrientationWizard *mOrientationWizard;
    DensificationWizard *mDensificationWizard;
    QFrame *mImagesWidget;
    QStringList *mProjectsNames;
    QVBoxLayout *mFrameRecentProjectsLayout;
    QList<PW::Project> mProjectDescriptors;

    QPushButton *mPbAddImages;
    QPushButton *mPbRecomputeOrientations;
    QPushButton *mPbRecomputeDensification;
    QPushButton *mPbRecomputeTiePoints;
    QPushButton *mPbBackToTieImagesConnection;
    QPushButton *mWorkflowButtonImages;
    QPushButton *mWorkflowButtonTiePoints;
    QPushButton *mWorkflowButtonOrientations;
    QPushButton *mWorkflowButtonDensification;
    QWidget *mWorkflowWidget;
    QWidget *mTiePointsInfoView;
    QWidget *mMatchingsView;


    void initSetups();
    void loadProject();
    void drawStartScreen();
    void drawBasicUserGUI();
    void setWorkflowWidgetStatus();
    void drawTiePointsInfoView(QMap<QString, QVector<QString> >& imagesPairs);

    void computeTiePoints();
    void computeTapiocaHomol(QString pairsFileName);
    void computeOrientations();
    void computeDensification();
    void setLatestProjectsLayout();
    void computeWallis();
    void computeCvDecolor();
    void computeOnlyOrientations(QString orientationMode);
    void buildModelPMVS();
    void closeEvent(QCloseEvent *event);
    void removePreviousDensifications();
    void removePreviousOrientatios();
    void cleanProject();

    void removePRJ_Files();
    PW::Apero2SureProcess *mApero2sure;
    PW::MergeLasResultsProcess *mMergeLasResultsProcess;
    PW::DrunkProcess *mDrunkProcess;
    PW::SUREProcess *mSureProcess;

    PW::CustomSureProcess *mCustomSureProcess;
    PW::ExternalProcess *mTapiocaProcess;
    PW::ExternalProcess *mMicMacSlavesProcess;
    int addImageThumnailToMap(QVector<QString> imagesList);

    //Calib models

    struct GraphosCalib {
      QString KnownConv;
      double PPx;
      double PPy;
      double F;
      int SzImx;
      int SzImy;
      double CDistx;
      double CDisty;
      double K1;
      double K2;
      double K3;
      double K4;
      double K5;
      double P1;
      double P2;
      double b1;
      double b2;
      QString Name;
      double SzCaptMmx;
      double SzCaptMmy;
      double focalMm;
    };

    struct AgisoftCalib {
      QString projection;
      int width;
      int height;
      double fx;
      double fy;
      double cx;
      double cy;
      double skew;
      double K1;
      double K2;
      double K3;
      double K4;
      double P1;
      double P2;
      QString date;
    };


    struct PhotomodelerCalib {
      double F;
      double Xp;
      double Yp;
      double Fw;
      double Fh;
      double K1;
      double K2;
      double K3;
      double P1;
      double P2;
      QString date;
    };

    struct BalancedCalib {
      double fb;
      double a0;
      double a1;
      double a2;
    };
    void BalancedTxtWriter(QString destfile, MainWindowGRAPHOS::BalancedCalib IoBalanced);
    void PhotomodellerTxtWriter(QString destfile, MainWindowGRAPHOS::PhotomodelerCalib IoPhotomodeller);
    void AgisoftXMLWriter(QString fileXMLAgisoft, MainWindowGRAPHOS::AgisoftCalib IoAgisoft);
    int Apero2X(MainWindowGRAPHOS::GraphosCalib IoGraphos, MainWindowGRAPHOS::AgisoftCalib &IoAgisoft,MainWindowGRAPHOS::PhotomodelerCalib &IoPhotomodeler,MainWindowGRAPHOS::BalancedCalib &IoBalanced);
    void computeMicMacSlaves();
    QStringList getMicMacSlavesForMainImage(QString mainImage);

private slots:

        void on_actionOrientationButton_triggered();
        void on_actionDensificationButton_triggered();
        void on_actionNew_Project_triggered();

        void on_actionAdd_Images_triggered();
        void onComputeOrientationFinished();
        void onDenseModelFinished();
        void on_actionCompute_Tie_Points_triggered();
        void on_actionCompute_Orientations_triggered();
        void on_actionDense_Model_triggered();
        void on_actionOpen_Project_triggered();
        void addImages();
        void openLatestProject(QString projectName);
        void on_recomputeTiePointsTriggered();
        void on_recomputeOrientationsTriggered();
        void on_recomputeDensificationTriggered();
        void on_actionAbout_GRAPHOS_triggered();
        void onPMVSFinished();
        void onWallisFinished();
        void onTapiocaTiePointsFinished();
        void buildModelSURECustom();
        void onSureFinished();
        void onLasmergeFinished();

        void on_imageLoadingOfExistingProjectFinished();
        void on_addImagesFinished();
        void on_imagesLoading_cancel();

        void on_addImageToMap(int num);
        void on_OpenProject_AddImagesToMapFinished();
        void on_QStackedWidget_currentChanged(int currentIndex);
        void onMSDTiePointsFinished();

        void onMultiDecolorFinished();
        bool onImagesConnectionDoubleClicked(QListWidgetItem* listWidget);
        void on_BackToImagesConnectionTriggered();
        void on_actionExport_Project_triggered();
        void on_actionImport_Project_triggered();
        void onTreeItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);
        void onASIFTUTiePointsFinished();
        void on_actionExport_UndistortedImages_triggered();
        void onExportUndistortedImagesFinished();
        void on_actionExport_AgisoftDistortion();
        void on_actionExport_BalancedDistortion();
        void on_actionExport_GRAPHOSDistortion();
        void on_actionExport_PhotomodellerDistortion();
        void on_actionPickRotationCenter_triggered();
        void onMaltProcessFinished();
        void buildMaltModel();
        void buildMaltMultiMainImageModel();
        void buildC3DCModel(QString type);
        void onC3DCProcessFinished();
        void writeMatchesInDatFormat();
        void on_actionBatch_ProcessTriggered();
        void on_BatchProcess_Finished();
        void on_LaunchMaltMultiMainImageForBatchProcess();
        void on_actionGeorreference_triggered();
        void on_computeGeorref_triggered();
        void on_computeGeorref_Finished();
        void on_actionScaleCloud_triggered();
        void on_ScaleCloud_Finished();
        void on_ReadDistanceToScale();
        void on_distanceToScaleAvailable();
        void setTopView();
        void setBottomView();
        void setLeftView();
        void setRightView();
        void setFrontView();
        void setBackView();
        void setFronIsometricView();
        void setBackIsometricView();

        void on_actionCalibration_conversion_triggered();

};

#endif // MAINWINDOWGRAPHOS_H
