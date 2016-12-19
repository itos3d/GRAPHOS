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
#include "OrientationWizard.h"
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QRadioButton>
#include "ClickableImage.h"
#include <QMessageBox>
#include "ClickableImage.h"
#include <QSignalMapper>
#include <QPushButton>
#include "ExternalProcess/CCDDistribution_Process.h"
#include "ExternalProcess/SingleMatchingAnalysis_Process.h"
#include "AboutCalibrations_Dialog.h"
OrientationWizard::OrientationWizard(QWidget *parent, QString projectPath) :
    QDialog(parent),
    mProjectPath(projectPath)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    setWindowTitle("Compute orientations");
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(new QLabel("Select camera type:"));
    QFrame *cameraTypeSelector = new QFrame();
    QHBoxLayout *cameraTypeSelectorLayout = new QHBoxLayout();
    cameraTypeSelectorLayout->setContentsMargins(0,0,0,0);
    QSignalMapper* signalMapper = new QSignalMapper (this) ;
    QPixmap mImageSmartphone (":/PW/icons/img/smartphoneTablet.png");
    QPixmap mImageCompact(":/PW/icons/img/compact.png");
    QPixmap mImageReflex(":/PW/icons/img/reflex.png");

    mSmartphoneImage = new ClickableImage();
    mSmartphoneImage->setPixmap(mImageSmartphone);
    connect(mSmartphoneImage,SIGNAL(leftButtonPressed(ClickableImage*)), signalMapper, SLOT(map()));
    signalMapper -> setMapping (mSmartphoneImage, "smartphone") ;
    connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(clicked(QString))) ;
    cameraTypeSelectorLayout->addWidget(mSmartphoneImage);
    connect(mSmartphoneImage,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(mSmartphoneImage,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));

    mCompactImage = new ClickableImage();
    mCompactImage->setPixmap(mImageCompact);
    connect(mCompactImage,SIGNAL(leftButtonPressed(ClickableImage*)), signalMapper, SLOT(map()));
    signalMapper -> setMapping (mCompactImage, "compact") ;
    connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(clicked(QString)));
    cameraTypeSelectorLayout->addWidget(mCompactImage);
    connect(mCompactImage,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(mCompactImage,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));

    mReflexImage = new ClickableImage();
    mReflexImage->setPixmap(mImageReflex);
    connect(mReflexImage,SIGNAL(leftButtonPressed(ClickableImage*)), signalMapper, SLOT(map()));
    signalMapper -> setMapping (mReflexImage, "reflex") ;
    connect (signalMapper, SIGNAL(mapped(QString)), this, SLOT(clicked(QString)));
    cameraTypeSelectorLayout->addWidget(mReflexImage);
    connect(mReflexImage,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(mReflexImage,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));

    cameraTypeSelector->setLayout(cameraTypeSelectorLayout);
    mainLayout->addWidget(cameraTypeSelector);

    //Matchings evaluation menu
    QGroupBox *gbMatchingsEvaluation= new QGroupBox("Matching evaluation tools");
    QHBoxLayout *matchingEvaluationToolsLayout = new QHBoxLayout();
    mPbMatchingAnalisys = new QPushButton("Single matching analysis");
    mPbCCD_Distribution = new QPushButton("CCD matchings distribution analysis");
    matchingEvaluationToolsLayout->addWidget(mPbMatchingAnalisys);
    matchingEvaluationToolsLayout->addWidget(mPbCCD_Distribution);
    gbMatchingsEvaluation->setLayout(matchingEvaluationToolsLayout);
    mainLayout->addWidget(gbMatchingsEvaluation);

    connect(mPbMatchingAnalisys,SIGNAL(clicked()),this,SLOT(showMatchingAnalisys()));
    connect(mPbCCD_Distribution,SIGNAL(clicked()),this,SLOT(showCCDEvaluator()));



    //Advanced menu
    extension = new QWidget;
    QVBoxLayout *extensionLayout = new QVBoxLayout;
    extensionLayout->setMargin(0);
    extensionLayout->addWidget(new QLabel("Advanced settings"));

    QFrame *calibrationModelFrame = new QFrame();
    QHBoxLayout *calibrationModelFrameLayout = new QHBoxLayout();
    calibrationModelFrameLayout->setContentsMargins(0,0,0,0);
   calibrationModelFrameLayout->addWidget(new QLabel("Camera calibration model:  "));
    mCbCalibrationModel = new QComboBox();
//    mCbCalibrationModel->addItem("");
    mCbCalibrationModel->addItem("Basic calibration");
    mCbCalibrationModel->addItem("Complete calibration");
    mCbCalibrationModel->addItem("Generic calibration");

//    mCbCalibrationModel->addItem("FraserBasic");

    calibrationModelFrameLayout->addWidget( mCbCalibrationModel);

    ClickableImage *distortionModelsInfo = new ClickableImage();
    distortionModelsInfo->setToolTip("Dense matching info");
    QPixmap distortionModelsInfoPixmap(":/PW/icons/img/info.png");
    distortionModelsInfo->setPixmap(distortionModelsInfoPixmap.scaled(20,20,Qt::KeepAspectRatio));
    connect(distortionModelsInfo,SIGNAL(leftButtonPressed(ClickableImage*)),this,SLOT(showAboutdistortionModels()));
    connect(distortionModelsInfo,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(distortionModelsInfo,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));

    calibrationModelFrameLayout->addWidget(distortionModelsInfo);
    calibrationModelFrameLayout->addStretch();

    connect(mCbCalibrationModel,SIGNAL(currentIndexChanged(int)),this,SLOT(on_mCbCalibrationModel_selectedItemChanged()));
    calibrationModelFrame->setLayout( calibrationModelFrameLayout);
    extensionLayout->addWidget( calibrationModelFrame);

    /////////////GenericCalibration settings
    //GenericCalibration options
    mGenericCalibrationFrame = new QGroupBox("GenericCalibration settings");
    QVBoxLayout *mGenericCalibrationFrameLayout = new QVBoxLayout();
    mGenericCalibrationFrameLayout->setAlignment(Qt::AlignLeft);


    mAfineParameters = new QCheckBox("Affine parameters (b1,b2)");
    mDecenteringParameters = new QCheckBox("Decentric parameters (p1, p2)");
    mPrincipalPointParameters = new QCheckBox("Principal point deviation (x0, y0)");
    mDistortionCenterParameters = new QCheckBox("Distortion center (x1, y1)");
    mFocalParameters = new QCheckBox("Focal (f)");

    mGenericCalibrationFrameLayout->addWidget(mFocalParameters);
    mGenericCalibrationFrameLayout->addWidget(mPrincipalPointParameters);
    mGenericCalibrationFrameLayout->addWidget(mDistortionCenterParameters);
    mGenericCalibrationFrameLayout->addWidget(mDecenteringParameters);
    mGenericCalibrationFrameLayout->addWidget(mAfineParameters);

    mGenericCalibrationFrame->setLayout(mGenericCalibrationFrameLayout);

    extensionLayout->addWidget(mGenericCalibrationFrame);
    mGenericCalibrationFrame->hide();


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


    setMaximumWidth(width());
    extension->hide();
    setLayout(mainLayout);
    mPbProccess->setFocus();

    mOrientationMode ="";

}

OrientationWizard::~OrientationWizard()
{
}

void OrientationWizard::clicked(QString cameraType){
    QStringList cameraOptions;
    cameraOptions << "smartphone" << "compact" << "reflex";

    QPixmap mImageSmartphone (":/PW/icons/img/smartphoneTablet.png");
    QPixmap mImageCompact(":/PW/icons/img/compact.png");
    QPixmap mImageReflex(":/PW/icons/img/reflex.png");

    QPixmap mImageSmartphoneSELECTED(":/PW/icons/img/smartphoneTabletSELECTED.png");
    QPixmap mImageCompactSELECTED(":/PW/icons/img/compactSELECTED.png");
    QPixmap mImageReflexSELECTED(":/PW/icons/img/reflexSELECTED.png");

    switch (cameraOptions.indexOf(cameraType)) {
    case 0:
            mCompactImage->setPixmap(mImageCompact);
            mReflexImage->setPixmap(mImageReflex);
            mSmartphoneImage->setPixmap(mImageSmartphoneSELECTED);
            mOrientationMode="RadialBasic";
            mCbCalibrationModel->setCurrentIndex(0);
            break;
        case 1:
            mCompactImage->setPixmap(mImageCompactSELECTED);
            mReflexImage->setPixmap(mImageReflex);
            mSmartphoneImage->setPixmap(mImageSmartphone);
            mOrientationMode="Fraser";
            mCbCalibrationModel->setCurrentIndex(1);
            break;
        case 2:
            mCompactImage->setPixmap(mImageCompact);
            mReflexImage->setPixmap(mImageReflexSELECTED);
            mSmartphoneImage->setPixmap(mImageSmartphone);
            mOrientationMode="Fraser";
            mCbCalibrationModel->setCurrentIndex(1);
            break;
    }
}

void OrientationWizard::on_pbCancel_clicked(){
    this->close();
}

void OrientationWizard::on_pbProccess_clicked(){
    if (!getOrientationMode().isEmpty()) {
        this->accept();
    }else{
        QMessageBox msg(this);
        msg.setWindowTitle("GRAPHOS");
        msg.setText("Select type of camera.");
        msg.exec();
    }
}

QString OrientationWizard::getOrientationMode(){
    return mOrientationMode;
}

void OrientationWizard::on_mCbCalibrationModel_selectedItemChanged(){

    switch (mCbCalibrationModel->currentIndex()) {
    case 0:
        mGenericCalibrationFrame->hide();
        mOrientationMode = "RadialBasic";
        break;
    case 1:
        mGenericCalibrationFrame->hide();
        mOrientationMode = "Fraser";
        break;
    case 2:
        mGenericCalibrationFrame->show();
        mOrientationMode = "Generic";
        break;
    }
}

void OrientationWizard::imageHovered(){
    this->setCursor(Qt::PointingHandCursor);
}
void OrientationWizard::imageLeft(){
    this->setCursor(Qt::ArrowCursor);
}

void OrientationWizard::AdvancedOptionsClicked(){
    if (mCbCalibrationModel->currentIndex()==0) {
        mOrientationMode="RadialBasic";
    }else {
        mOrientationMode="Fraser";
    }
    if (extension->isVisible()) {
        extension->hide();
    }else {
        extension->show();
    }

}

bool OrientationWizard::isAffineParametersChecked(){
    return mAfineParameters->isChecked();
}

bool OrientationWizard::isDecenteringParametersChecked(){
    return mDecenteringParameters->isChecked();
}

bool OrientationWizard::isDistortionCenterParameterschecked(){
    return mDistortionCenterParameters->isChecked();
}

bool OrientationWizard::isFocalParametersChecked(){
    return mFocalParameters->isChecked();
}
bool OrientationWizard::isPrincipalPointParametersChecked(){
    return mPrincipalPointParameters->isChecked();
}

void OrientationWizard::showCCDEvaluator(){
    CCDDistribution_Process *process = new CCDDistribution_Process(mProjectPath);
    process->start();
}

void OrientationWizard::showMatchingAnalisys(){
    SingleMatchingAnalysis_Process *process = new SingleMatchingAnalysis_Process(mProjectPath);

    process->start();
}


void OrientationWizard::showAboutdistortionModels(){
    AboutCalibrations_Dialog *calibDialog = new AboutCalibrations_Dialog(this);
    calibDialog->exec();
}
