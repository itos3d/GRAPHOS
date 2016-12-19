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
#include "TiePointsWizard.h"
#include <QVBoxLayout>
#include <QSignalMapper>
#include "ClickableImage.h"
#include <QPushButton>
#include <QComboBox>
#include <QGroupBox>
#include <QMap>
#include <QMessageBox>
#include <math.h>
#include "opencv/cv.h"
#include "ClickableImage.h"
#include "ExternalProcess/FME_Process.h"
#include "ExternalProcess/WallisStimator.h"
#include "libPW.h"
#include "AboutWallis_dialog.h"
#include "aboutFeatures_Dialog.h"
TiePointsWizard::TiePointsWizard(QWidget *parent,QSize imageSize,QString imagesPath) :
    QDialog(parent),
    mImageSize(imageSize),
    mImagesPath(imagesPath)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    int maxRexizeValue;
    if (mImageSize.height()>=mImageSize.width()) {
        maxRexizeValue=mImageSize.height();
    }else {
        maxRexizeValue=mImageSize.width();
    }

    methodSelected=false;

    setWindowTitle("Tie points detection and description");
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(new QLabel("Select capture configuration:"));
    QFrame *captureTypeSelector = new QFrame();
    QHBoxLayout *captureTypeSelectorLayout = new QHBoxLayout();
    captureTypeSelectorLayout->setContentsMargins(0,0,0,0);
    QSignalMapper* signalMapper = new QSignalMapper (this) ;

    QPixmap mImageParallel (":/PW/icons/img/Parallel.png");
    QPixmap mImageRing(":/PW/icons/img/Ring.png");
    QPixmap mImageCustom(":/PW/icons/img/custom.png");

    mParallelImage = new ClickableImage();
    mParallelImage->setPixmap(mImageParallel);
    connect(mParallelImage,SIGNAL(leftButtonPressed(ClickableImage*)), signalMapper, SLOT(map()));
    signalMapper -> setMapping (mParallelImage, "parallel") ;
    connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(clicked(QString))) ;
    captureTypeSelectorLayout->addWidget(mParallelImage);
    connect(mParallelImage,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(mParallelImage,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));


    mRingImage = new ClickableImage();
    mRingImage->setPixmap(mImageRing);
    connect(mRingImage,SIGNAL(leftButtonPressed(ClickableImage*)), signalMapper, SLOT(map()));
    signalMapper -> setMapping (mRingImage, "ring") ;
    connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(clicked(QString)));
    captureTypeSelectorLayout->addWidget(mRingImage);
    connect(mRingImage,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(mRingImage,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));

    mCustomImage = new ClickableImage();
    mCustomImage->setPixmap(mImageCustom);
    connect(mCustomImage,SIGNAL(leftButtonPressed(ClickableImage*)), signalMapper, SLOT(map()));
    signalMapper -> setMapping (mCustomImage, "custom") ;
    connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(clicked(QString)));
    captureTypeSelectorLayout->addWidget(mCustomImage);
    connect(mCustomImage,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(mCustomImage,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));

    captureTypeSelector->setLayout(captureTypeSelectorLayout);
    mainLayout->addWidget(captureTypeSelector);

    //Matchings evaluation menu
    QGroupBox *gbFeatureEvaluationTools= new QGroupBox("Feature evaluation tools");
    QHBoxLayout *featureEvaluationToolsLayout = new QHBoxLayout();
    mPbWallisAnalisys = new QPushButton("Wallis suitability evaluation");
    mPbFME = new QPushButton("Feature detection and matching suite");
    featureEvaluationToolsLayout->addWidget(mPbWallisAnalisys);
    featureEvaluationToolsLayout->addWidget(mPbFME);
    gbFeatureEvaluationTools->setLayout(featureEvaluationToolsLayout);
    mainLayout->addWidget(gbFeatureEvaluationTools);

    connect(mPbWallisAnalisys,SIGNAL(clicked()),this,SLOT(showWallisEvaluation()));
    connect(mPbFME,SIGNAL(clicked()),this,SLOT(showFME()));

    //Advanced menu
    extension = new QWidget;
    QVBoxLayout *extensionLayout = new QVBoxLayout;
    extensionLayout->setMargin(0);
    extensionLayout->addWidget(new QLabel("Advanced settings"));

    //Wallis options
    QGroupBox *wallisFrame = new QGroupBox("Wallis settings");
    QHBoxLayout *wallisFrameLayout = new QHBoxLayout();
    wallisFrameLayout->setAlignment(Qt::AlignLeft);
    mCbWallis = new QCheckBox("Apply Wallis filter");
    connect(mCbWallis,SIGNAL(stateChanged(int)),this,SLOT(setWallisValueVisibility()));
    wallisFrameLayout->addWidget(mCbWallis);

    ClickableImage *wallisInfo = new ClickableImage();
    wallisInfo->setToolTip("Wallis info");
    QPixmap wallisInfoPixmap(":/PW/icons/img/info.png");
    wallisInfo->setPixmap(wallisInfoPixmap.scaled(20,20,Qt::KeepAspectRatio));
    connect(wallisInfo,SIGNAL(leftButtonPressed(ClickableImage*)),this,SLOT(showAboutwallis()));
    connect(wallisInfo,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(wallisInfo,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));
    wallisFrameLayout->addWidget(wallisInfo);


    mWallisSettings = new QFrame();
    QHBoxLayout *wallisSettingsLayout = new QHBoxLayout();
    wallisSettingsLayout->setAlignment(Qt::AlignLeft);

    //Wallis contrast
    QLabel *lbWallisContrast = new QLabel(" Contrast: ");
    mWallisContrastValue= new QDoubleSpinBox();
    mWallisContrastValue->setRange(0.0,1.0);
    mWallisContrastValue->setValue(0.5);
    mWallisContrastValue->setSingleStep(0.1);
    wallisSettingsLayout->addWidget(lbWallisContrast);
    wallisSettingsLayout->addWidget(mWallisContrastValue);

    //Wallis Brightness
    QLabel *lbWallisBrightness = new QLabel("      Brightness: ");
    mWallisBrightnessValue= new QDoubleSpinBox();
    mWallisBrightnessValue->setRange(0.0,1.0);
    mWallisBrightnessValue->setValue(1.0);
    mWallisBrightnessValue->setSingleStep(0.1);

    wallisSettingsLayout->addWidget(lbWallisBrightness);
    wallisSettingsLayout->addWidget(mWallisBrightnessValue);

    //Wallis standard deviation
    QLabel *lbWallisStdDeviation = new QLabel("      Standard deviation: ");
    mWallisStdDeviationValue= new QSpinBox();
    mWallisStdDeviationValue->setRange(50,80);
    mWallisStdDeviationValue->setValue(50);
    mWallisStdDeviationValue->setSingleStep(1);
    wallisSettingsLayout->addWidget(lbWallisStdDeviation);
    wallisSettingsLayout->addWidget(mWallisStdDeviationValue);

    //Wallis kernel size
    QLabel *lbWallisKernelSize = new QLabel("      Kernel size: ");
    mWallisKernelSizeValue= new QSpinBox();
    mWallisKernelSizeValue->setRange(15,250); //Kernell maximo???
    float width =mImageSize.width();
    float height=mImageSize.height();
    float rad = (sqrt(pow(width,2)+pow(height,2)))/2; //pasamos al 2% del radio de forma automática
    int kernel = (int)(rad*0.02);
    mWallisKernelSizeValue->setValue(kernel); //Calculo del kernell
    mWallisKernelSizeValue->setSingleStep(1);
    wallisSettingsLayout->addWidget(lbWallisKernelSize);
    wallisSettingsLayout->addWidget(mWallisKernelSizeValue);

    mWallisSettings->setLayout(wallisSettingsLayout);
    mWallisSettings->setEnabled(false);
    wallisFrameLayout->addWidget(mWallisSettings);

    wallisFrame->setLayout(wallisFrameLayout);
    extensionLayout->addWidget(wallisFrame);
    //

    QFrame *tiePointsMethodFrame = new QFrame();
    QHBoxLayout *tiePointsMethodFrameLayout = new QHBoxLayout();
    tiePointsMethodFrameLayout->setContentsMargins(0,0,0,0);
    tiePointsMethodFrameLayout->setAlignment(Qt::AlignLeft);

    tiePointsMethodFrameLayout->addWidget(new QLabel("Tie points detection method: "));

    mCbTiePointsMethod = new QComboBox();
    mCbTiePointsMethod->addItem("Tapioca");
    mCbTiePointsMethod->addItem("MSD+SIFT");
    mCbTiePointsMethod->addItem("ASIFT");

    connect(mCbTiePointsMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(on_mCbTiePointsMethod_selectedItemChanged()));


    tiePointsMethodFrameLayout->addWidget(mCbTiePointsMethod);

    ClickableImage *tpMethodInfo = new ClickableImage();
    tpMethodInfo->setToolTip("Tie points method info");
    QPixmap tpMethodInfoPixmap(":/PW/icons/img/info.png");
    tpMethodInfo->setPixmap(tpMethodInfoPixmap.scaled(20,20,Qt::KeepAspectRatio));
    connect(tpMethodInfo,SIGNAL(leftButtonPressed(ClickableImage*)),this,SLOT(showAbouttpMethod()));
    connect(tpMethodInfo,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(tpMethodInfo,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));
    tiePointsMethodFrameLayout->addWidget(tpMethodInfo);

    tiePointsMethodFrame->setLayout(tiePointsMethodFrameLayout);

    extensionLayout->addWidget(tiePointsMethodFrame);

    //Add frame with advanced menu items here
    mGbTapiocaSettings = new QGroupBox("Tapioca settings");
    QHBoxLayout *tapiocaSettingsLayout = new QHBoxLayout();
    tapiocaSettingsLayout->setAlignment(Qt::AlignLeft);
    tapiocaSettingsLayout->setContentsMargins(0,0,0,0);
    QFrame *searchMethodFrame = new QFrame();
    QHBoxLayout *searchMethodFrameLayout = new QHBoxLayout();
    searchMethodFrameLayout->setAlignment(Qt::AlignLeft);
    searchMethodFrameLayout->addWidget(new QLabel("Search mode: "));
    mCbSearchMethod = new QComboBox();
    mCbSearchMethod->addItem("All");
    mCbSearchMethod->addItem("Line");
    mCbSearchMethod->addItem("MulScale");
    connect(mCbSearchMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(on_mCbSearchMethod_selectedItemChanged()));

    searchMethodFrameLayout->addWidget(mCbSearchMethod);
    lineRangeFrame = new QFrame();
    QHBoxLayout *lineRangeFrameLayout = new QHBoxLayout();
    lineRangeFrameLayout->addWidget(new QLabel("Range: "));
    mlineRangeValue= new QSpinBox();
    mlineRangeValue->setRange(1,10);
    mlineRangeValue->setSingleStep(1);
    mlineRangeValue->setValue(3);
    lineRangeFrameLayout->addWidget(mlineRangeValue);
    lineRangeFrame->setLayout(lineRangeFrameLayout);
    lineRangeFrame->hide();
    searchMethodFrameLayout->addWidget(lineRangeFrame);
    searchMethodFrame->setLayout(searchMethodFrameLayout);
    lineRangeFrame->setLayout(lineRangeFrameLayout);
    searchMethodFrameLayout->addWidget(lineRangeFrame);

    MulScaleParametersFrame = new QFrame();
    QHBoxLayout *MulScaleParametersFrameLayout = new QHBoxLayout();
    MulScaleParametersFrameLayout->addWidget(new QLabel("Min scale: "));
    mMulScaleMinValue= new QSpinBox();

    mMulScaleMinValue->setRange(300,maxRexizeValue-1);
    mMulScaleMinValue->setSingleStep(1);
    if (maxRexizeValue>=1500) {
        mMulScaleMinValue->setValue(800);
    }else {
        mMulScaleMinValue->setValue((int)(maxRexizeValue/2));
    }

//    mMulScaleMinValue->setValue(3);
    MulScaleParametersFrameLayout->addWidget(mMulScaleMinValue);

    MulScaleParametersFrameLayout->addWidget(new QLabel("Max scale: "));
    mMulScaleMaxValue= new QSpinBox();
    mMulScaleMaxValue->setRange(mMulScaleMinValue->value()+1,maxRexizeValue);
    mMulScaleMaxValue->setSingleStep(1);
    if (maxRexizeValue>=1500) {
        mMulScaleMaxValue->setValue(1500);
    }else {
        mMulScaleMaxValue->setValue(maxRexizeValue);
    }
//    mMulScaleMaxValue->setValue(maxRexizeValue);
    MulScaleParametersFrameLayout->addWidget(mMulScaleMaxValue);

    connect(mMulScaleMaxValue,SIGNAL(valueChanged(int)),this,SLOT(on_MulScaleValuesChanged()));
    connect(mMulScaleMinValue,SIGNAL(valueChanged(int)),this,SLOT(on_MulScaleValuesChanged()));

    MulScaleParametersFrame->setLayout(MulScaleParametersFrameLayout);
    MulScaleParametersFrame->hide();
    searchMethodFrameLayout->addWidget(MulScaleParametersFrame);
    searchMethodFrame->setLayout(searchMethodFrameLayout);
    MulScaleParametersFrame->setLayout(MulScaleParametersFrameLayout);
    searchMethodFrameLayout->addWidget(MulScaleParametersFrame);
    MulScaleParametersFrame->hide();


    searchMethodFrame->setLayout(searchMethodFrameLayout);

    tapiocaSettingsLayout->addWidget(searchMethodFrame);

    sizeTapiocaFrame = new QFrame();
    QHBoxLayout *sizeTapiocaFrameLayout = new QHBoxLayout();
    sizeTapiocaFrameLayout->setAlignment(Qt::AlignLeft);

    mDownsampleTapiocaImages = new QCheckBox("Downsample images  ");
    mDownsampleTapiocaImages->setChecked(true);
    connect(mDownsampleTapiocaImages,SIGNAL(stateChanged(int)),this,SLOT(on_mDownsampleTapiocaImages_statusChanged()));

    sizeTapiocaFrameLayout->addWidget(mDownsampleTapiocaImages);
    sizeTapiocaFrameLayout->addWidget(new QLabel("Size: "));
    mTapiocaResizeValue= new QSpinBox();
    mTapiocaResizeValue->setRange(0,maxRexizeValue); //Set maximum size value to ImageSize
    if (maxRexizeValue>=1500) {
        mTapiocaResizeValue->setValue(1500);
    }else {
        mTapiocaResizeValue->setValue(maxRexizeValue);
    }
    mTapiocaResizeValue->setSingleStep(1);
    sizeTapiocaFrameLayout->addWidget(mTapiocaResizeValue);
    sizeTapiocaFrame->setLayout(sizeTapiocaFrameLayout);
    tapiocaSettingsLayout->addWidget(sizeTapiocaFrame);

    //Minimum Tapioca Matches
    QFrame *minimumTapiocaMatchesFrame = new QFrame();
    QHBoxLayout *minimumTapiocaMatchesFrameLayout = new QHBoxLayout();
    minimumTapiocaMatchesFrameLayout->addWidget(new QLabel("Minimum matches: "));
    minimumTapiocaMatches= new QSpinBox();
    minimumTapiocaMatches->setRange(0,1000);
    minimumTapiocaMatches->setSingleStep(1);
    minimumTapiocaMatches->setValue(10);
    minimumTapiocaMatchesFrameLayout->addWidget(minimumTapiocaMatches);
    minimumTapiocaMatchesFrame->setLayout(minimumTapiocaMatchesFrameLayout);
    searchMethodFrameLayout->addWidget(minimumTapiocaMatchesFrame);

    mGbTapiocaSettings->setLayout(tapiocaSettingsLayout);
    mGbTapiocaSettings->hide();

    extensionLayout->addWidget(mGbTapiocaSettings);

    //MSD parameters
    mGbMSDSettings = new QGroupBox("MSD settings");
    QFrame *msdSettingsLine1 = new QFrame();
    QFrame *msdSettingsLine2 = new QFrame();
    QFrame *msdSettingsLine3 = new QFrame();
    QFrame *msdSettingsLine4 = new QFrame();

    QVBoxLayout *MSDSettingsLayout = new QVBoxLayout();
    QHBoxLayout *MSDSettingsLine1Layout = new QHBoxLayout();
    QHBoxLayout *MSDSettingsLine2Layout = new QHBoxLayout();
    QHBoxLayout *MSDSettingsLine3Layout = new QHBoxLayout();
    QHBoxLayout *MSDSettingsLine4Layout = new QHBoxLayout();
    MSDSettingsLine3Layout->setContentsMargins(0,0,0,0);
    MSDSettingsLine4Layout->setContentsMargins(0,0,0,0);
    MSDSettingsLine1Layout->setContentsMargins(0,0,0,0);
    MSDSettingsLine2Layout->setContentsMargins(0,0,0,0);

    MSDSettingsLine1Layout->setAlignment(Qt::AlignLeft);
    MSDSettingsLine4Layout->setAlignment(Qt::AlignLeft);
    MSDSettingsLine2Layout->setAlignment(Qt::AlignLeft);
    MSDSettingsLine3Layout->setAlignment(Qt::AlignLeft);

    //MsdPatchRadius
    QFrame *MSDPatchRadiusFrame = new QFrame();
    QHBoxLayout *MSDPatchRadiusFrameLayout = new QHBoxLayout();
    MSDPatchRadiusFrameLayout->setContentsMargins(0,0,0,0);
    MSDPatchRadiusFrameLayout->addWidget(new QLabel("Patch radius: "));
    MSD_PatchRadius= new QSpinBox();
    MSD_PatchRadius->setRange(1,10);
    MSD_PatchRadius->setSingleStep(1);
    MSD_PatchRadius->setValue(3);
    connect(MSD_PatchRadius,SIGNAL(valueChanged(int)),this,SLOT(computeNScales()));
    MSDPatchRadiusFrameLayout->addWidget(MSD_PatchRadius);
    MSDPatchRadiusFrame->setLayout(MSDPatchRadiusFrameLayout);
    MSDSettingsLine1Layout->addWidget(MSDPatchRadiusFrame);

    //MsdSearchAreaRadius
    QFrame *MSDSearchAreaRadiusFrame = new QFrame();
    QHBoxLayout *MSDSearchAreaRadiusFrameLayout = new QHBoxLayout();
    MSDSearchAreaRadiusFrameLayout->addWidget(new QLabel("Search area radius: "));
    MSD_SearchAreaRadius= new QSpinBox();
    MSD_SearchAreaRadius->setRange(1,10);
    MSD_SearchAreaRadius->setSingleStep(1);
    MSD_SearchAreaRadius->setValue(5);
    connect(MSD_SearchAreaRadius,SIGNAL(valueChanged(int)),this,SLOT(computeNScales()));
    MSDSearchAreaRadiusFrameLayout->addWidget(MSD_SearchAreaRadius);
    MSDSearchAreaRadiusFrame->setLayout(MSDSearchAreaRadiusFrameLayout);
    MSDSettingsLine1Layout->addWidget(MSDSearchAreaRadiusFrame);

    //MsdNMSRadius
    QFrame *MSDNMSRadiusFrame = new QFrame();
    QHBoxLayout *MSDNMSRadiusFrameLayout = new QHBoxLayout();
    MSDNMSRadiusFrameLayout->addWidget(new QLabel("NMS radius: "));
    MSD_NMSRadius= new QSpinBox();
    MSD_NMSRadius->setRange(1,10);
    MSD_NMSRadius->setSingleStep(1);
    MSD_NMSRadius->setValue(5);
    MSDNMSRadiusFrameLayout->addWidget(MSD_NMSRadius);
    MSDNMSRadiusFrame->setLayout(MSDNMSRadiusFrameLayout);
    MSDSettingsLine1Layout->addWidget(MSDNMSRadiusFrame);

    //MsdNMSScaleRadius
    QFrame *MSDNMSScaleRadiusFrame = new QFrame();
    QHBoxLayout *MSDNMSScaleRadiusFrameLayout = new QHBoxLayout();
    MSDNMSScaleRadiusFrameLayout->addWidget(new QLabel("NMS scale radius: "));
    MSD_NMSScaleRadius= new QSpinBox();
    MSD_NMSScaleRadius->setRange(0,10);
    MSD_NMSScaleRadius->setSingleStep(1);
    MSD_NMSScaleRadius->setValue(0);
    MSDNMSScaleRadiusFrameLayout->addWidget(MSD_NMSScaleRadius);
    MSDNMSScaleRadiusFrame->setLayout(MSDNMSScaleRadiusFrameLayout);
    MSDSettingsLine1Layout->addWidget(MSDNMSScaleRadiusFrame);

    //MsdMSD_ThSaliency
    QFrame *MSD_ThSaliencyFrame = new QFrame();
    QHBoxLayout *MSD_ThSaliencyFrameLayout = new QHBoxLayout();
    MSD_ThSaliencyFrameLayout->setContentsMargins(0,0,0,0);
    MSD_ThSaliencyFrameLayout->addWidget(new QLabel("ThSaliency: "));
    MSD_ThSaliency= new QSpinBox();
    MSD_ThSaliency->setRange(0,2000);
    MSD_ThSaliency->setSingleStep(1);
    MSD_ThSaliency->setValue(250);
    MSD_ThSaliencyFrameLayout->addWidget(MSD_ThSaliency);
    MSD_ThSaliencyFrame->setLayout(MSD_ThSaliencyFrameLayout);
    MSDSettingsLine2Layout->addWidget(MSD_ThSaliencyFrame);

    //MsdKNN
    QFrame *MSDKNNFrame = new QFrame();
    QHBoxLayout *MSDKNNFrameLayout = new QHBoxLayout();
    MSDKNNFrameLayout->setContentsMargins(0,0,0,0);

    MSDKNNFrameLayout->addWidget(new QLabel("KNN: "));
    MSD_KNN= new QSpinBox();
    MSD_KNN->setRange(1,10);
    MSD_KNN->setSingleStep(1);
    MSD_KNN->setValue(4);
    MSDKNNFrameLayout->addWidget(MSD_KNN);
    MSDKNNFrame->setLayout(MSDKNNFrameLayout);
    MSDSettingsLine2Layout->addWidget(MSDKNNFrame);

    //MsdScaleFactor
    QFrame *MSDScaleFactorFrame = new QFrame();
    QHBoxLayout *MSDScaleFactorFrameLayout = new QHBoxLayout();
    MSDScaleFactorFrameLayout->addWidget(new QLabel("Scale factor: "));
    MSD_ScaleFactor= new QDoubleSpinBox();
    MSD_ScaleFactor->setRange(1,10);
    MSD_ScaleFactor->setSingleStep(0.05);
    MSD_ScaleFactor->setValue(1.25);
    connect(MSD_ScaleFactor,SIGNAL(valueChanged(double)),this,SLOT(computeNScales()));
    MSDScaleFactorFrameLayout->addWidget(MSD_ScaleFactor);
    MSDScaleFactorFrame->setLayout(MSDScaleFactorFrameLayout);
    MSDSettingsLine2Layout->addWidget(MSDScaleFactorFrame);

    //MsdNScales
    QFrame *MSDNScalesFrame = new QFrame();
    QHBoxLayout *MSDNScalesFrameLayout = new QHBoxLayout();
    MSDNScalesFrameLayout->addWidget(new QLabel("N scales: "));
    MSD_NScales= new QSpinBox();
    MSD_NScales->setSingleStep(1);
    MSDNScalesFrameLayout->addWidget(MSD_NScales);
    MSDNScalesFrame->setLayout(MSDNScalesFrameLayout);
    MSDSettingsLine2Layout->addWidget(MSDNScalesFrame);

    MSD_ComputeOrientations = new QCheckBox("Compute orientation");
    MSDSettingsLine2Layout->addWidget(MSD_ComputeOrientations);

    msdSettingsLine1->setLayout(MSDSettingsLine1Layout);
    msdSettingsLine2->setLayout(MSDSettingsLine2Layout);

    MSDSettingsLayout->addWidget(msdSettingsLine1);
    MSDSettingsLayout->addWidget(msdSettingsLine2);
    MSD_ComputeOrientations->hide();

    mDownsampleMSDImages = new QCheckBox("Downsample images  ");
    mDownsampleMSDImages->setChecked(false);
    connect(mDownsampleMSDImages,SIGNAL(stateChanged(int)),this,SLOT(on_mDownsampleMSDImages_statusChanged()));
    connect(mDownsampleMSDImages,SIGNAL(stateChanged(int)),this,SLOT(computeNScales()));
    MSDSettingsLine3Layout->addWidget(mDownsampleMSDImages);
    MSDSettingsLine3Layout->addWidget(new QLabel("Size: "));
    mMSDResizeValue= new QSpinBox();
    mMSDResizeValue->setRange(0,maxRexizeValue);
    if (maxRexizeValue>=1500) {
        mMSDResizeValue->setValue(1500);
    }else {
        mMSDResizeValue->setValue(maxRexizeValue);

    }
    mMSDResizeValue->setSingleStep(1);
    MSDSettingsLine3Layout->addWidget(mMSDResizeValue);
    connect(mMSDResizeValue,SIGNAL(valueChanged(int)),this,SLOT(computeNScales()));

    //MSD Max tiepoints
    mMSDMaxTiepoints = new QCheckBox("Set tiepoints limit  ");
    mMSDMaxTiepoints->setChecked(true);
    connect(mMSDMaxTiepoints,SIGNAL(stateChanged(int)),this,SLOT(on_mMSDMaxTiepoints_statusChanged()));
    MSDSettingsLine3Layout->addSpacing(20);
    MSDSettingsLine3Layout->addWidget(mMSDMaxTiepoints);
    MSDSettingsLine3Layout->addWidget(new QLabel("Max: "));
    mMSDMaxTiepointsValue= new QSpinBox();
    mMSDMaxTiepointsValue->setRange(0,10000);
    mMSDMaxTiepointsValue->setValue(5000);
    mMSDMaxTiepointsValue->setSingleStep(1);
    MSDSettingsLine3Layout->addWidget(mMSDMaxTiepointsValue);

    msdSettingsLine3->setLayout(MSDSettingsLine3Layout);
    MSDSettingsLayout->addWidget(msdSettingsLine3);


    //MSD Tilts
    mMSDaffine = new QCheckBox("Affine MSD  ");
    mMSDaffine->setChecked(false);
    connect(mMSDaffine,SIGNAL(stateChanged(int)),this,SLOT(on_mMSDAffine_statusChanged()));
    //    MSDSettingsLine4Layout->addSpacing(20);
    MSDSettingsLine4Layout->addWidget(mMSDaffine);
    MSDSettingsLine4Layout->addWidget(new QLabel("Tilts: "));
    mMSDTiltsValue= new QSpinBox();
    mMSDTiltsValue->setRange(1,9);
    mMSDTiltsValue->setValue(4);
    mMSDTiltsValue->setSingleStep(1);
    MSDSettingsLine4Layout->addWidget(mMSDTiltsValue);
    mMSDTiltsValue->setEnabled(false);
    msdSettingsLine4->setLayout(MSDSettingsLine4Layout);
//    MSDSettingsLayout->addWidget(msdSettingsLine4); Uncomment to use affine MSD

    mGbMSDSettings->setLayout(MSDSettingsLayout);
    extensionLayout->addWidget(mGbMSDSettings);
    mMSDMaxTiepointsValue->setEnabled(true);
    mMSDMaxTiepoints->setChecked(true);



    mDownsampleMSDImages->setChecked(true);
    mGbMSDSettings->hide();


    //ASIFTU parameters
    mGbASIFTUSettings = new QGroupBox("ASIFT settings");

    QFrame *ASIFTUSettingsLine1 = new QFrame();
    QFrame *ASIFTUSettingsLine2 = new QFrame();

    QVBoxLayout *ASIFTUSettingsLayout = new QVBoxLayout();
    ASIFTUSettingsLayout->setContentsMargins(0,0,0,0);
    QHBoxLayout *ASIFTUSettingsLine1Layout = new QHBoxLayout();
    QHBoxLayout *ASIFTUSettingsLine2Layout = new QHBoxLayout();


    ASIFTUSettingsLine1Layout->setAlignment(Qt::AlignLeft);
    ASIFTUSettingsLine2Layout->setAlignment(Qt::AlignLeft);

    //Advanced ASIFT configuration

    //ASIFTU Tilts
    QFrame *ASIFTU_TiltsFrame = new QFrame();
    QHBoxLayout *ASIFTU_TiltsFrameLayout = new QHBoxLayout();
    ASIFTU_TiltsFrameLayout->setContentsMargins(0,0,0,0);
    ASIFTU_TiltsFrameLayout->addWidget(new QLabel("Tilts: "));
    mASIFTU_Tilts= new QSpinBox();
    mASIFTU_Tilts->setRange(3,9);
    mASIFTU_Tilts->setSingleStep(1);
    mASIFTU_Tilts->setValue(4);
    ASIFTU_TiltsFrameLayout->addWidget(mASIFTU_Tilts);
    ASIFTU_TiltsFrame->setLayout(ASIFTU_TiltsFrameLayout);
    ASIFTUSettingsLine1Layout->addWidget(ASIFTU_TiltsFrame);

    //ASIFTU PeakTh
    QFrame *ASIFTU_PeakThFrame = new QFrame();
    QHBoxLayout *ASIFTU_PeakThFrameLayout = new QHBoxLayout();
    ASIFTU_PeakThFrameLayout->setContentsMargins(0,0,0,0);
    ASIFTU_PeakThFrameLayout->addWidget(new QLabel("Peak threshold: "));
    ASIFTU_PeakTh= new QSpinBox();
    ASIFTU_PeakTh->setRange(0,30);
    ASIFTU_PeakTh->setSingleStep(1);
    ASIFTU_PeakTh->setValue(10);
    ASIFTU_PeakThFrameLayout->addWidget(ASIFTU_PeakTh);
    ASIFTU_PeakThFrame->setLayout(ASIFTU_PeakThFrameLayout);
    ASIFTUSettingsLine1Layout->addWidget(ASIFTU_PeakThFrame);

    //ASIFTU EdgeTh
    QFrame *ASIFTU_EdgeThFrame = new QFrame();
    QHBoxLayout *ASIFTU_EdgeThFrameLayout = new QHBoxLayout();
    ASIFTU_EdgeThFrameLayout->setContentsMargins(0,0,0,0);
    ASIFTU_EdgeThFrameLayout->addWidget(new QLabel("Edge threshold: "));
    ASIFTU_EdgeTh= new QDoubleSpinBox();
    ASIFTU_EdgeTh->setRange(3.5,10);
    ASIFTU_EdgeTh->setSingleStep(0.5);
    ASIFTU_EdgeTh->setValue(6);
    ASIFTU_EdgeThFrameLayout->addWidget(ASIFTU_EdgeTh);
    ASIFTU_EdgeThFrame->setLayout(ASIFTU_EdgeThFrameLayout);
    ASIFTUSettingsLine1Layout->addWidget(ASIFTU_EdgeThFrame);

    //ASIFTU Octaves
    QFrame *ASIFTU_OctavesFrame = new QFrame();
    QHBoxLayout *ASIFTU_OctavesFrameLayout = new QHBoxLayout();
    ASIFTU_OctavesFrameLayout->setContentsMargins(0,0,0,0);
    ASIFTU_OctavesFrameLayout->addWidget(new QLabel("Octaves: "));
    ASIFTU_Octaves= new QSpinBox();
    ASIFTU_Octaves->setRange(1,7);
    ASIFTU_Octaves->setSingleStep(1);
    ASIFTU_Octaves->setValue(4);
    ASIFTU_OctavesFrameLayout->addWidget(ASIFTU_Octaves);
    ASIFTU_OctavesFrame->setLayout(ASIFTU_OctavesFrameLayout);
    ASIFTUSettingsLine1Layout->addWidget(ASIFTU_OctavesFrame);

    ASIFTUSettingsLine1->setLayout(ASIFTUSettingsLine1Layout);
    ASIFTUSettingsLayout->addWidget(ASIFTUSettingsLine1);

    mDownsampleASIFTUImages = new QCheckBox("Downsample images  ");
    mDownsampleASIFTUImages->setChecked(false);
    connect(mDownsampleASIFTUImages,SIGNAL(stateChanged(int)),this,SLOT(on_mDownsampleASIFTUImages_statusChanged()));
    ASIFTUSettingsLine2Layout->addWidget(mDownsampleASIFTUImages);
    ASIFTUSettingsLine2Layout->addWidget(new QLabel("Size: "));
    mASIFTUResizeValue= new QSpinBox();
    mASIFTUResizeValue->setRange(0,maxRexizeValue);
    if (maxRexizeValue>=1500) {
        mASIFTUResizeValue->setValue(1500);
    }else {
        mASIFTUResizeValue->setValue(maxRexizeValue);
    }
    mASIFTUResizeValue->setSingleStep(1);
    ASIFTUSettingsLine2Layout->addWidget(mASIFTUResizeValue);


    mDownsampleASIFTUImages->setChecked(true);

    //ASIFT Max tiepoints
    mASIFTUMaxTiepoints = new QCheckBox("Set tiepoints limit  ");
    mASIFTUMaxTiepoints->setChecked(true);
    connect(mASIFTUMaxTiepoints,SIGNAL(stateChanged(int)),this,SLOT(on_mASIFTUMaxTiepoints_statusChanged()));
    ASIFTUSettingsLine2Layout->addSpacing(20);
    ASIFTUSettingsLine2Layout->addWidget(mASIFTUMaxTiepoints);
    ASIFTUSettingsLine2Layout->addWidget(new QLabel("Max: "));
    mASIFTUMaxTiepointsValue= new QSpinBox();
    mASIFTUMaxTiepointsValue->setRange(0,10000);
    mASIFTUMaxTiepointsValue->setValue(5000);
    mASIFTUMaxTiepointsValue->setSingleStep(1);
    ASIFTUSettingsLine2Layout->addWidget(mASIFTUMaxTiepointsValue);

    ASIFTUSettingsLine2->setLayout(ASIFTUSettingsLine2Layout);
    ASIFTUSettingsLayout->addWidget(ASIFTUSettingsLine2);
    mGbASIFTUSettings->setLayout(ASIFTUSettingsLayout);
    extensionLayout->addWidget(mGbASIFTUSettings);
    mASIFTUMaxTiepointsValue->setEnabled(true);
    mASIFTUMaxTiepoints->setChecked(true);

    mGbASIFTUSettings->hide();

    //Matching method
    mMatchingMethodFrame = new QFrame();
    QVBoxLayout *matchingMethodFrameLayout = new QVBoxLayout();
    matchingMethodFrameLayout->setContentsMargins(0,0,0,0);
    QFrame *matchingMethodSelectorFrame = new QFrame();
    QHBoxLayout *matchingMethodSelectorFrameLayout = new QHBoxLayout();
    matchingMethodSelectorFrameLayout->setContentsMargins(0,0,0,0);
    matchingMethodSelectorFrameLayout->setAlignment(Qt::AlignLeft);
    matchingMethodSelectorFrameLayout->addWidget(new QLabel("Matching method: "));

    mCbmatchingMethod = new QComboBox();
    mCbmatchingMethod->addItem("Robust Matcher (Brute force)");
    mCbmatchingMethod->addItem("Flann Matcher");
    connect(mCbmatchingMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(on_mCbmatchingMethod_selectedItemChanged()));


    matchingMethodSelectorFrameLayout->addWidget(mCbmatchingMethod);
    //MinimumMatches
    QFrame *minimumMatchesFrame = new QFrame();
    QHBoxLayout *minimumMatchesFrameLayout = new QHBoxLayout();
    minimumMatchesFrameLayout->addWidget(new QLabel("Minimum matches: "));
    minimumMatches= new QSpinBox();
    minimumMatches->setRange(0,1000);
    minimumMatches->setSingleStep(1);
    minimumMatches->setValue(10);
    minimumMatchesFrameLayout->addWidget(minimumMatches);
    minimumMatchesFrame->setLayout(minimumMatchesFrameLayout);
    matchingMethodSelectorFrameLayout->addWidget(minimumMatchesFrame);

    matchingMethodSelectorFrame->setLayout(matchingMethodSelectorFrameLayout);
    matchingMethodFrameLayout->addWidget(matchingMethodSelectorFrame);

    //RobustMatcher parameters
    mGbRobustMatcherSettings = new QGroupBox("Robust matcher settings");
    QHBoxLayout *mGbRobustMatcherSettingsLayout = new QHBoxLayout();
    mGbRobustMatcherSettingsLayout->setContentsMargins(0,0,0,0);
    mGbRobustMatcherSettingsLayout->setAlignment(Qt::AlignLeft);
    //RB_ratio
    QFrame *RB_ratioFrame = new QFrame();
    QHBoxLayout *RB_ratioFrameLayout = new QHBoxLayout();
    RB_ratioFrameLayout->addWidget(new QLabel("Ratio: "));
    RB_ratio= new QDoubleSpinBox();
    RB_ratio->setRange(0.0,1.0);
    RB_ratio->setSingleStep(0.05);
    RB_ratio->setValue(0.85);
    RB_ratioFrameLayout->addWidget(RB_ratio);
    RB_ratioFrame->setLayout(RB_ratioFrameLayout);
    mGbRobustMatcherSettingsLayout->addWidget(RB_ratioFrame);

//    //RB_distance
//    QFrame *RB_distanceFrame = new QFrame();
//    QHBoxLayout *RB_distanceFrameLayout = new QHBoxLayout();
//    RB_distanceFrameLayout->addWidget(new QLabel("Distance: "));
//    RB_distance= new QDoubleSpinBox();
//    RB_distance->setRange(1.0,10.0);
//    RB_distance->setSingleStep(0.1);
//    RB_distance->setValue(3.0);
//    RB_distanceFrameLayout->addWidget(RB_distance);
//    RB_distanceFrame->setLayout(RB_distanceFrameLayout);
//    mGbRobustMatcherSettingsLayout->addWidget(RB_distanceFrame);

//    //RB_confidence
//    QFrame *RB_confidenceFrame = new QFrame();
//    QHBoxLayout *RB_confidenceFrameLayout = new QHBoxLayout();
//    RB_confidenceFrameLayout->addWidget(new QLabel("Confidence: "));
//    RB_confidence= new QDoubleSpinBox();
//    RB_confidence->setRange(0.0,1.0);
//    RB_confidence->setSingleStep(0.05);
//    RB_confidence->setValue(0.95);
//    RB_confidenceFrameLayout->addWidget(RB_confidence);
//    RB_confidenceFrame->setLayout(RB_confidenceFrameLayout);
//    mGbRobustMatcherSettingsLayout->addWidget(RB_confidenceFrame);

    //RB_threshold_K
    QFrame *RB_threshold_KFrame = new QFrame();
    QHBoxLayout *RB_threshold_KFrameLayout = new QHBoxLayout();
    RB_threshold_KFrameLayout->addWidget(new QLabel("Threshold K: "));
    RB_threshold_K= new QDoubleSpinBox();
    RB_threshold_K->setRange(0.0,1.0);
    RB_threshold_K->setSingleStep(0.05);
    RB_threshold_K->setValue(0.6);
    RB_threshold_KFrameLayout->addWidget(RB_threshold_K);
    RB_threshold_KFrame->setLayout(RB_threshold_KFrameLayout);
    mGbRobustMatcherSettingsLayout->addWidget(RB_threshold_KFrame);


    mGbRobustMatcherSettings->setLayout(mGbRobustMatcherSettingsLayout);

    matchingMethodFrameLayout->addWidget(mGbRobustMatcherSettings);
    mMatchingMethodFrame->setLayout(matchingMethodFrameLayout);

    extensionLayout->addWidget(mMatchingMethodFrame);

    mMatchingMethodFrame->hide();

    extension->setLayout(extensionLayout);
    mainLayout->addWidget(extension);

    //Botones de navegación
    QFrame *navigationButtonsFrame = new QFrame();
    QHBoxLayout *navigationButtonsFrameLayout = new QHBoxLayout();
    navigationButtonsFrameLayout->setContentsMargins(0,0,0,0);
    navigationButtonsFrameLayout->setAlignment(Qt::AlignRight);
    QPushButton *pbAdavancedOptions = new QPushButton("Advanced options");
    pbAdavancedOptions->setCheckable(true);
    pbAdavancedOptions->setAutoDefault(false);
    connect(pbAdavancedOptions, SIGNAL(toggled(bool)), extension, SLOT(setVisible(bool)));

    navigationButtonsFrameLayout->addWidget(pbAdavancedOptions);
    navigationButtonsFrameLayout->addStretch(1);


    mPbProccess = new QPushButton("Accept");
    mPbProccess->setFixedWidth(100);
    connect(mPbProccess,SIGNAL(clicked()),this,SLOT(on_pbProccess_clicked()));
    QPushButton *pbCancel = new QPushButton("Cancel");
    pbCancel->setFixedWidth(100);
    connect(pbCancel,SIGNAL(clicked()),this,SLOT(on_pbCancel_clicked()));
    navigationButtonsFrameLayout->addWidget(pbCancel);
    navigationButtonsFrameLayout->addWidget(mPbProccess);
    navigationButtonsFrame->setLayout(navigationButtonsFrameLayout);

    mainLayout->addWidget(navigationButtonsFrame);

    extension->hide();
    setLayout(mainLayout);
    mPbProccess->setFocus();
}

TiePointsWizard::~TiePointsWizard()
{
}

void TiePointsWizard::clicked(QString captureType){
    methodSelected = true;
    QStringList cameraOptions;
    cameraOptions << "parallel" << "ring" << "custom";

    QPixmap ImageParallel (":/PW/icons/img/Parallel.png");
    QPixmap ImageRing(":/PW/icons/img/Ring.png");
    QPixmap ImageCustom(":/PW/icons/img/custom.png");

    QPixmap ImageParallelSELECTED(":/PW/icons/img/ParallelSELECTED.png");
    QPixmap ImageRingSELECTED(":/PW/icons/img/RingSELECTED.png");
    QPixmap ImageCustomSELECTED(":/PW/icons/img/customSelected.png");


    switch (cameraOptions.indexOf(captureType)) {
    case 0:
               mCbTiePointsMethod->setCurrentIndex(0);
               mParallelImage->setPixmap(ImageParallelSELECTED);
               mRingImage->setPixmap(ImageRing);
               mCustomImage->setPixmap(ImageCustom);
               mCaptureConfiguration="Parallel";
               mGbTapiocaSettings->show();
            break;
    case 1:
           mCbTiePointsMethod->setCurrentIndex(2);
           mParallelImage->setPixmap(ImageParallel);
           mRingImage->setPixmap(ImageRingSELECTED);
           mCustomImage->setPixmap(ImageCustom);
           mCaptureConfiguration="Ring";
        break;
    case 2:
           mParallelImage->setPixmap(ImageParallel);
           mRingImage->setPixmap(ImageRing);
           mCustomImage->setPixmap(ImageCustomSELECTED);
           mCaptureConfiguration="Custom";
           if (mCbTiePointsMethod->currentIndex()==0) {
               mGbTapiocaSettings->show();
               mGbASIFTUSettings->hide();
               mGbMSDSettings->hide();
           }else if (mCbTiePointsMethod->currentIndex()==1) {
               mGbTapiocaSettings->hide();
               mGbASIFTUSettings->hide();
               mGbMSDSettings->show();
           }else {
               mGbTapiocaSettings->hide();
               mGbASIFTUSettings->show();
               mGbMSDSettings->hide();
           }
           extension->show();

        break;
    }
}

void TiePointsWizard::on_pbCancel_clicked(){
    this->close();
}
void TiePointsWizard::on_pbProccess_clicked(){

    if (methodSelected) {
        this->accept();
    }else {
        QMessageBox msg(this);
        msg.setWindowTitle("Tie points");
        msg.setText("Tie points method not selected.");
        msg.exec();
    }
}

void TiePointsWizard::on_mCbTiePointsMethod_selectedItemChanged(){
    switch (mCbTiePointsMethod->currentIndex()) {
    case 0:
        methodSelected=true;
        mGbMSDSettings->hide();
        mGbASIFTUSettings->hide();
        mGbRobustMatcherSettings->hide();
        mGbTapiocaSettings->show();
        mMatchingMethodFrame->hide();
        break;
    case 1:
        methodSelected=true;
        mGbMSDSettings->show();
        mGbASIFTUSettings->hide();
        mGbRobustMatcherSettings->show();
        mGbTapiocaSettings->hide();
        mMatchingMethodFrame->show();
        break;
    case 2:
        methodSelected=true;
        mGbMSDSettings->hide();
        mGbASIFTUSettings->show();
        mGbRobustMatcherSettings->show();
        mGbTapiocaSettings->hide();
        mMatchingMethodFrame->show();
        break;
    }

}
void TiePointsWizard::on_mCbSearchMethod_selectedItemChanged(){
    if (mCbSearchMethod->currentIndex()==1) {
        lineRangeFrame->show();
    }else {
        lineRangeFrame->hide();
    }
    if (mCbSearchMethod->currentIndex()==2) {
        MulScaleParametersFrame->show();
        sizeTapiocaFrame->hide();
    }else {
        MulScaleParametersFrame->hide();
        sizeTapiocaFrame->show();
    }
}

void TiePointsWizard::on_mDownsampleTapiocaImages_statusChanged(){
    if (mDownsampleTapiocaImages->isChecked()) {
        mTapiocaResizeValue->setEnabled(true);
    }else {
        mTapiocaResizeValue->setEnabled(false);
    }

}

void TiePointsWizard::on_mDownsampleMSDImages_statusChanged(){
    if (mDownsampleMSDImages->isChecked()) {
        mMSDResizeValue->setEnabled(true);
    }else {
        mMSDResizeValue->setEnabled(false);
    }

}

QMap<QString, QString> TiePointsWizard::getTiePointsMethod(){
    QMap<QString, QString> tiePointsMethod;

    QString method = mCbTiePointsMethod->currentText();
    tiePointsMethod.insert("method",method);

    if (method.contains("Tapioca")) {
        QString searchMethod =mCbSearchMethod->currentText();
        tiePointsMethod.insert("SearchMethod",searchMethod);
        if (searchMethod.contains("Line")) {
            tiePointsMethod.insert("Range",QString::number(mlineRangeValue->value()));
        }
        if (searchMethod.contains("MulScale")) {
            tiePointsMethod.insert("MulScaleMin",QString::number(mMulScaleMinValue->value()));
            tiePointsMethod.insert("MulScaleMax",QString::number(mMulScaleMaxValue->value()));
        }

        if (mDownsampleTapiocaImages->isChecked()) {
            tiePointsMethod.insert("ResizeValue",QString::number(mTapiocaResizeValue->value()));
        }else {
            tiePointsMethod.insert("ResizeValue",QString::number(-1));
        }


    }else if (method.contains("MSD+SIFT")) {

        tiePointsMethod.insert("PatchRadius",QString::number(MSD_PatchRadius->value()));
        tiePointsMethod.insert("SearchAreaRadius",QString::number(MSD_SearchAreaRadius->value()));
        tiePointsMethod.insert("NMSRadius",QString::number(MSD_NMSRadius->value()));
        tiePointsMethod.insert("NMSScaleRadius",QString::number(MSD_NMSScaleRadius->value()));
        tiePointsMethod.insert("ThSaliency",QString::number(MSD_ThSaliency->value()));
        tiePointsMethod.insert("KNN",QString::number(MSD_KNN->value()));
        tiePointsMethod.insert("ScaleFactor",QString::number(MSD_ScaleFactor->value()));
        tiePointsMethod.insert("NScales",QString::number(MSD_NScales->value()));

        tiePointsMethod.insert("RB_ratio",QString::number(RB_ratio->value()));
//        tiePointsMethod.insert("RB_distance",QString::number(RB_distance->value()));
//        tiePointsMethod.insert("RB_confidence",QString::number(RB_confidence->value()));
        tiePointsMethod.insert("RB_threshold_K",QString::number(RB_threshold_K->value()));
        tiePointsMethod.insert("minimumMatches",QString::number(minimumMatches->value()));
        if (mDownsampleMSDImages->isChecked()) {
            tiePointsMethod.insert("ResizeValue",QString::number(mMSDResizeValue->value()));
        }else {
            tiePointsMethod.insert("ResizeValue",QString::number(-1));
        }

        if (mMSDMaxTiepoints->isChecked()) {
            tiePointsMethod.insert("MaxTiepoints",QString::number(mMSDMaxTiepointsValue->value()));
        }else {
            tiePointsMethod.insert("MaxTiepoints",QString::number(-1));
        }

        if (MSD_ComputeOrientations->isChecked()) {
            tiePointsMethod.insert("ComputeOrientations","true");
        }else {
            tiePointsMethod.insert("ComputeOrientations","false");
        }
        if (mCbmatchingMethod->currentIndex()==0) {
            tiePointsMethod.insert("matchingMethod","BF");
        }else{
            tiePointsMethod.insert("matchingMethod","FLANN");
        }
    }else if (method.contains("ASIFT")) {
        tiePointsMethod.insert("Tilts",QString::number(mASIFTU_Tilts->value()));
        tiePointsMethod.insert("PeakTh",QString::number(ASIFTU_PeakTh->value()));
        tiePointsMethod.insert("EdgeTh",QString::number(ASIFTU_EdgeTh->value()));
        tiePointsMethod.insert("Octaves",QString::number(ASIFTU_Octaves->value()));

        tiePointsMethod.insert("RB_ratio",QString::number(RB_ratio->value()));
//        tiePointsMethod.insert("RB_0.98",QString::number(RB_distance->value()));
//        tiePointsMethod.insert("RB_confidence",QString::number(RB_confidence->value()));
        tiePointsMethod.insert("RB_threshold_K",QString::number(RB_threshold_K->value()));
        tiePointsMethod.insert("minimumMatches",QString::number(minimumMatches->value()));
        if (mDownsampleASIFTUImages->isChecked()) {
            tiePointsMethod.insert("ResizeValue",QString::number(mASIFTUResizeValue->value()));
        }else {
            tiePointsMethod.insert("ResizeValue",QString::number(-1));
        }

        if (mASIFTUMaxTiepoints->isChecked()) {
            tiePointsMethod.insert("MaxTiepoints",QString::number(mASIFTUMaxTiepointsValue->value()));
        }else {
            tiePointsMethod.insert("MaxTiepoints",QString::number(-1));
        }

        if (mCbmatchingMethod->currentIndex()==0) {
            tiePointsMethod.insert("matchingMethod","BF");
        }else{
            tiePointsMethod.insert("matchingMethod","FLANN");
        }
    }
    return tiePointsMethod;
}

void TiePointsWizard::setWallisValueVisibility(){
    if (mCbWallis->isChecked()) {
        mWallisSettings->setEnabled(true);
    }else {
        mWallisSettings->setEnabled(false);
    }
}

float TiePointsWizard::getWallisBrithness(){
    return mWallisBrightnessValue->value();
}
float TiePointsWizard::getWallisContrast(){
    return mWallisContrastValue->value();
}
int TiePointsWizard::getWallisKernell(){
    return mWallisKernelSizeValue->value();
}
int TiePointsWizard::getWallisStdDeviation(){
    return mWallisStdDeviationValue->value();
}
bool TiePointsWizard::isWallisChecked(){
    return mCbWallis->isChecked();
}

QString TiePointsWizard::getCaptureConfiguration(){
    return mCaptureConfiguration;
}
void TiePointsWizard::computeNScales(){
    int nscales;
    if (mDownsampleMSDImages->isChecked()) {
        if (mImageSize.width()>mImageSize.height()) {
            nscales =cvFloor(std::log(cv::min(mMSDResizeValue->value(), (mImageSize.height()*1500)/mImageSize.width()) / ((MSD_PatchRadius->value() + MSD_SearchAreaRadius->value())*2.0 + 1)) / std::log(MSD_ScaleFactor->value()));
        }else {
            nscales =cvFloor(std::log(cv::min((mImageSize.width()*1500)/mImageSize.height(), mMSDResizeValue->value()) / ((MSD_PatchRadius->value() + MSD_SearchAreaRadius->value())*2.0 + 1)) / std::log(MSD_ScaleFactor->value()));
        }
    }else {
        nscales =cvFloor(std::log(cv::min(mImageSize.width(), mImageSize.height()) / ((MSD_PatchRadius->value() + MSD_SearchAreaRadius->value())*2.0 + 1)) / std::log(MSD_ScaleFactor->value()));
    }
    MSD_NScales->setRange(1,nscales);
    MSD_NScales->setValue(nscales);
}
void TiePointsWizard::on_mCbmatchingMethod_selectedItemChanged(){
    if (mCbmatchingMethod->currentIndex()==0) {
        mGbRobustMatcherSettings->setVisible(true);
    }else{
        mGbRobustMatcherSettings->setVisible(false);
    }
}

void TiePointsWizard::imageHovered(){
    this->setCursor(Qt::PointingHandCursor);
}
void TiePointsWizard::imageLeft(){
    this->setCursor(Qt::ArrowCursor);
}

void TiePointsWizard::on_mDownsampleASIFTUImages_statusChanged(){
    if (mDownsampleASIFTUImages->isChecked()) {
        mASIFTUResizeValue->setEnabled(true);
    }else {
        mASIFTUResizeValue->setEnabled(false);
    }
}

void TiePointsWizard::on_mASIFTUMaxTiepoints_statusChanged(){
    if (mASIFTUMaxTiepoints->isChecked()) {
        mASIFTUMaxTiepointsValue->setEnabled(true);
    }else {
        mASIFTUMaxTiepointsValue->setEnabled(false);
    }
}
void TiePointsWizard::on_mMSDMaxTiepoints_statusChanged(){
    if (mMSDMaxTiepoints->isChecked()) {
        mMSDMaxTiepointsValue->setEnabled(true);
    }else {
        mMSDMaxTiepointsValue->setEnabled(false);
    }
}

void TiePointsWizard::on_MulScaleValuesChanged(){
    mMulScaleMaxValue->setMinimum(mMulScaleMinValue->value()+1);
    mMulScaleMinValue->setMaximum(mMulScaleMaxValue->value()-1);
}
int TiePointsWizard::getTapiocaMulScaleMaxValue(){
    return mMulScaleMaxValue->value();
}
int TiePointsWizard::getTapiocaMulScaleMinValue(){
    return mMulScaleMinValue->value();
}
int TiePointsWizard::getMinimumTapiocaMatches(){
    return minimumTapiocaMatches->value();
}
bool TiePointsWizard::isMSDAffineChecked(){
    return mMSDaffine->isChecked();
}

int TiePointsWizard::getMSDAffineTilts(){
    return mMSDTiltsValue->value();
}

void TiePointsWizard::on_mMSDAffine_statusChanged(){
    if (mMSDaffine->isChecked()) {
        mMSDTiltsValue->setEnabled(true);
    }else {
        mMSDTiltsValue->setEnabled(false);
    }
}

void TiePointsWizard::showAbouttpMethod(){
    aboutFeatures_Dialog *aboutFeatures = new aboutFeatures_Dialog(this);
    aboutFeatures->exec();
}
void TiePointsWizard::showAboutwallis(){
    AboutWallis_dialog *aboutWallis = new AboutWallis_dialog(this);
    aboutWallis->exec();
}
void TiePointsWizard::showFME(){
    FME_Process *process= new FME_Process();
    process->start();
}
void TiePointsWizard::showWallisEvaluation(){
    WallisStimator *process= new WallisStimator(mImagesPath);
    process->start();
}
