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
#include "DensificationWizard.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QSignalMapper>
#include "ClickableImage.h"
#include <QPushButton>
#include <libPW.h>
#include <QMessageBox>
#include "AboutSureDialog.h"
#include <QGroupBox>
#include "PWImage.h"
#include "AboutDensification_Dialog.h"

DensificationWizard::DensificationWizard(QWidget *parent,PW::Project *Project,QMap<QString, QImage> *mapImages,QSettings *settings) :
    QDialog(parent),
    mProject(Project),
    mMapImages(mapImages),
    mSettings(settings)
{
    methodSelected=true;
    setWindowTitle("Dense matching");
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    mProject = Project;

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

    QPixmap mImageParallelSELECTED(":/PW/icons/img/ParallelSELECTED.png");
    QPixmap mImageRingSELECTED(":/PW/icons/img/RingSELECTED.png");
    QPixmap mImageCustomSELECTED(":/PW/icons/img/customSelected.png");

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

//    //MainPictureSelection
//    mImageSelectionFrame = new QFrame();
//    QVBoxLayout *imageSelectionFrameLayout= new QVBoxLayout();
//    imageSelectionFrameLayout->addWidget(new QLabel("Select main image"));
//    mListWidget = new QListWidget();
//    if (mProject->getImagesFileName().count()!=0) {
//        mListWidget->setViewMode(QListWidget::IconMode );
//        mListWidget->setIconSize(QSize(90,90));
//        mListWidget->setResizeMode(QListWidget::Adjust);
//        for (int var = 0; var < mProject->getImagesFileName().count(); ++var) {

//                    QFile\" file\"(mProject->getBasePath()+"/"+mProject->getImagesFileName()[var]);
//                    QString filename(fileInfo.fileName());
//                    QListWidgetItem *listItem = new QListWidgetItem(QIcon(QPixmap::fromImage(mMapImages->value(filename))),filename);
//                    mListWidget->addItem(listItem);
//        }
//        mListWidget->sortItems();
//    }
//    mListWidget->setDragEnabled(false);
//    mListWidget->viewport()->setAcceptDrops(false);
//    mListWidget->setDropIndicatorShown(false);

//    mListWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
//    imageSelectionFrameLayout->addWidget(mListWidget);
//    connect(mListWidget,SIGNAL(currentItemChanged(QListWidgetItem*,QListWidgetItem*)),this,SLOT(on_mainImageSelectionChanged()));
//    mImageSelectionFrame->setLayout(imageSelectionFrameLayout);
//    mainLayout->addWidget(mImageSelectionFrame);

    //Advanced menum
    extension = new QWidget;
    QVBoxLayout *extensionLayout = new QVBoxLayout;
    extensionLayout->setMargin(0);
    extensionLayout->addWidget(new QLabel("Advanced settings"));

    QGroupBox *SUREFrame = new QGroupBox("Sure settings");
    QHBoxLayout *SUREFrameLayout = new QHBoxLayout();
    mCbSURE = new QCheckBox("Process using SURE");
    connect(mCbSURE,SIGNAL(stateChanged(int)),this,SLOT(setSUREValuesVisibility()));

    if (PW::LibPW::getSUREBinPath().isEmpty() || PW::LibPW::getSUREBinPath().toAscii().contains("SURE_BIN")) {
        mCbSURE->setEnabled(false);
    }else {
        mCbSURE->setEnabled(true);
    }

    ClickableImage *sureInfo = new ClickableImage();
    sureInfo->setToolTip("SURE info");
    QPixmap sureInfoPixmap(":/PW/icons/img/info.png");
    sureInfo->setPixmap(sureInfoPixmap.scaled(20,20,Qt::KeepAspectRatio));
    connect(sureInfo,SIGNAL(leftButtonPressed(ClickableImage*)),this,SLOT(showAboutSURE()));
    connect(sureInfo,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(sureInfo,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));

    mSURE_PyrValue= new QSpinBox();
    mSURE_PyrValue->setRange(0,2);
    mSURE_PyrValue->setSingleStep(1);
    mSURE_PyrValue->hide();
    mLbSURE_PyrValue = new QLabel("    Pyr value: ");
    mLbSURE_PyrValue->hide();

    mSURE_FoldValue= new QSpinBox();
    mSURE_FoldValue->setRange(2,5);
    mSURE_FoldValue->setSingleStep(1);
    mSURE_FoldValue->hide();

    mLbSURE_FoldValue = new QLabel("    Fold value: ");
    mLbSURE_FoldValue->hide();


    mSURE_MaxModelsValue= new QSpinBox();
    mSURE_MaxModelsValue->setRange(1,1000);
    mSURE_MaxModelsValue->setValue(5);
    mSURE_MaxModelsValue->setSingleStep(1);
    mSURE_MaxModelsValue->hide();

    mLbSURE_MaxModelsValue = new QLabel("    Max models: ");
    mLbSURE_MaxModelsValue->hide();


//    mCbSURE_DishableAngleTest = new QCheckBox("Dishable angle test");
//    mCbSURE_DishablebaselineTest = new QCheckBox("Dishable baseline test");
//    mCbSURE_DishableAngleTest->hide();
//    mCbSURE_DishablebaselineTest->hide();
    SUREFrameLayout->addWidget(mCbSURE);
    SUREFrameLayout->addWidget(sureInfo);
    SUREFrameLayout->addWidget(mLbSURE_PyrValue);
    SUREFrameLayout->addWidget(mSURE_PyrValue);
    SUREFrameLayout->addWidget(mLbSURE_FoldValue);
    SUREFrameLayout->addWidget(mSURE_FoldValue);
    SUREFrameLayout->addWidget(mLbSURE_MaxModelsValue);
    SUREFrameLayout->addWidget(mSURE_MaxModelsValue);
//    SUREFrameLayout->addWidget(mCbSURE_DishableAngleTest);
//    SUREFrameLayout->addWidget(mCbSURE_DishablebaselineTest);
    SUREFrameLayout->addStretch();
    SUREFrame->setLayout(SUREFrameLayout);

    extensionLayout->addWidget(SUREFrame);


    densificationMethodFrame = new QFrame();
    QHBoxLayout *densificationMethodFrameLayout = new QHBoxLayout();
    densificationMethodFrameLayout->setContentsMargins(0,0,0,0);
    densificationMethodFrameLayout->addWidget(new QLabel("Dense matching method:  "));


    mCbDensificationMethod = new QComboBox();
    mCbDensificationMethod->addItem("MicMac master image");
    mCbDensificationMethod->addItem("MicMac object space");
    mCbDensificationMethod->addItem("PMVS");
    mCbDensificationMethod->addItem("MicMac C3DC QuickMac");
    mCbDensificationMethod->addItem("MicMac C3DC Statue");
    mCbDensificationMethod->addItem("MicMac C3DC BigMac");

    densificationMethodFrameLayout->addWidget(mCbDensificationMethod);
    ClickableImage *denseMatchingInfo = new ClickableImage();
    denseMatchingInfo->setToolTip("Dense matching info");
    QPixmap denseMatchingInfoPixmap(":/PW/icons/img/info.png");
    denseMatchingInfo->setPixmap(denseMatchingInfoPixmap.scaled(20,20,Qt::KeepAspectRatio));
    connect(denseMatchingInfo,SIGNAL(leftButtonPressed(ClickableImage*)),this,SLOT(showAboutDenseMatching()));
    connect(denseMatchingInfo,SIGNAL(mouseEntered(ClickableImage*)),this,SLOT(imageHovered()));
    connect(denseMatchingInfo,SIGNAL(mouseLeft(ClickableImage*)),this,SLOT(imageLeft()));

    densificationMethodFrameLayout->addWidget(denseMatchingInfo);
    densificationMethodFrameLayout->addStretch();

    densificationMethodFrame->setLayout( densificationMethodFrameLayout);
    connect(mCbDensificationMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(on_mCbDensificationMethod_selectedItemChanged()));

    extensionLayout->addWidget( densificationMethodFrame);

    /////////////PMVS
    //PMVS options
    mPMVSFrame = new QGroupBox("PMVS settings");
    QHBoxLayout *mPMVSFrameLayout = new QHBoxLayout();
    mPMVSFrameLayout->setAlignment(Qt::AlignLeft);


    //PMVS Level
    QLabel *lbPMVSLevel = new QLabel(" Level: ");
    mPMVSLevelValue= new QSpinBox();
    mPMVSLevelValue->setRange(0,2);
    mPMVSLevelValue->setValue(1);
    mPMVSLevelValue->setSingleStep(1);
    mPMVSFrameLayout->addWidget(lbPMVSLevel);
    mPMVSFrameLayout->addWidget(mPMVSLevelValue);

    //PMVS Min
    QLabel *lbPMVSMin = new QLabel("      Min: ");
    mPMVSMinValue= new QSpinBox();
    mPMVSMinValue->setRange(2,5);
    mPMVSMinValue->setValue(3);
    mPMVSMinValue->setSingleStep(1);

    mPMVSFrameLayout->addWidget(lbPMVSMin);
    mPMVSFrameLayout->addWidget(mPMVSMinValue);

    //PMVS CSize
    QLabel *lbPMVSCSize = new QLabel("      CSize: ");
    mPMVSCSizeValue= new QSpinBox();
    mPMVSCSizeValue->setRange(1,3);
    mPMVSCSizeValue->setValue(2);
    mPMVSCSizeValue->setSingleStep(1);
    mPMVSFrameLayout->addWidget(lbPMVSCSize);
    mPMVSFrameLayout->addWidget(mPMVSCSizeValue);

    //PMVS Threshold
    QLabel *lbPMVSThreshold = new QLabel("      Threshold: ");
    mPMVSThresholdValue= new QDoubleSpinBox();
    mPMVSThresholdValue->setRange(-1,1);
    mPMVSThresholdValue->setValue(0.7);
    mPMVSThresholdValue->setSingleStep(0.05);
    mPMVSFrameLayout->addWidget(lbPMVSThreshold);
    mPMVSFrameLayout->addWidget(mPMVSThresholdValue);

    mPMVSFrame->setLayout(mPMVSFrameLayout);
    extensionLayout->addWidget(mPMVSFrame);
    mPMVSFrame->hide();


    /////////////MicMac settings
    //MicMac options
    mMicMacFrame = new QGroupBox("MicMac settings");
    QVBoxLayout *mMicMacFrameLayout = new QVBoxLayout();
    mMicMacFrameLayout->setAlignment(Qt::AlignLeft);

    //MainPictureSelection

    mImageSelectionFrame = new QFrame();
    QVBoxLayout *imageSelectionFrameLayout= new QVBoxLayout();
    imageSelectionFrameLayout->setContentsMargins(0,0,0,0);
    imageSelectionFrameLayout->addWidget(new QLabel("Select main image"));
    mListWidget = new QListWidget();
    mListWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    if (mProject->getImagesFileName().count()!=0) {
        mListWidget->setViewMode(QListWidget::IconMode );
        mListWidget->setIconSize(QSize(90,90));
        mListWidget->setResizeMode(QListWidget::Adjust);
        for (int var = 0; var < mProject->getImagesFileName().count(); ++var) {

                    QFileInfo fileInfo(mProject->getBasePath()+"/"+mProject->getImagesFileName()[var]);
                    QString filename(fileInfo.fileName());
                    QListWidgetItem *listItem = new QListWidgetItem(QIcon(QPixmap::fromImage(mMapImages->value(filename))),filename);
                    mListWidget->addItem(listItem);
        }
        mListWidget->sortItems();
    }
    mListWidget->setDragEnabled(false);
    mListWidget->viewport()->setAcceptDrops(false);
    mListWidget->setDropIndicatorShown(false);

    mListWidget->setDragDropMode(QAbstractItemView::NoDragDrop);
    imageSelectionFrameLayout->addWidget(mListWidget);
    connect(mListWidget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(on_mainImageSelectionChanged()));
    mImageSelectionFrame->setLayout(imageSelectionFrameLayout);
//    mainLayout->addWidget(mImageSelectionFrame);

    mMicMacFrameLayout->addWidget(mImageSelectionFrame);
    //MicMac Mask
    mUseMaskMicMac = new QCheckBox("Use masks");
    mUseMaskMicMac->setEnabled(false);
    mUseMaskMicMac->setChecked(false);
    imageSelectionFrameLayout->addWidget(mUseMaskMicMac);
    mUseMaskMicMac->hide();
//    QFrame *slaveImagesFrame = new QFrame();
//    QHBoxLayout * slaveImagesFrameLayout = new QHBoxLayout();
//    slaveImagesFrameLayout->setAlignment(Qt::AlignLeft);
//    slaveImagesFrameLayout->setContentsMargins(0,0,0,0);
//    slaveImagesFrameLayout->addWidget(new QLabel("Slave Images:"));
//    mMicMacNearestImagesValue = new QSpinBox();
//    mMicMacNearestImagesValue->setRange(2,10);
//    mMicMacNearestImagesValue->setValue(4);
//    slaveImagesFrameLayout->addWidget(mMicMacNearestImagesValue);

//    slaveImagesFrame->setLayout(slaveImagesFrameLayout);
//    imageSelectionFrameLayout->addWidget(slaveImagesFrame);

    mMicMacFrame->setLayout(mMicMacFrameLayout);

    QFrame *micmacCommonSettingsFrame = new QFrame();
    QHBoxLayout *micmacCommonSettingsFrameLayout = new QHBoxLayout();
    micmacCommonSettingsFrameLayout->setAlignment(Qt::AlignLeft);
    micmacCommonSettingsFrameLayout->setContentsMargins(0,0,0,0);
    micmacCommonSettingsFrameLayout->addWidget(new QLabel("DeZoom value: "));

    mMicMac_DeZoomValue= new QComboBox();
    mMicMac_DeZoomValue->addItem("1");
    mMicMac_DeZoomValue->addItem("2");
    mMicMac_DeZoomValue->addItem("4");
    mMicMac_DeZoomValue->setCurrentIndex(1);
    micmacCommonSettingsFrameLayout->addWidget(mMicMac_DeZoomValue);


    micmacCommonSettingsFrameLayout->addWidget(new QLabel("    ZRegul value: "));

    mMicMac_ZRegulValue = new QDoubleSpinBox();
    mMicMac_ZRegulValue->setRange(0.01,0.2);
    mMicMac_ZRegulValue->setValue(0.05);
    mMicMac_ZRegulValue->setSingleStep(0.01);
    micmacCommonSettingsFrameLayout->addWidget(mMicMac_ZRegulValue);

    micmacCommonSettingsFrameLayout->addWidget(new QLabel("    ZPas value: "));

    mMicMac_ZPasValue = new QDoubleSpinBox();
    mMicMac_ZPasValue->setRange(0.1,0.6);
    mMicMac_ZPasValue->setValue(0.4);
    mMicMac_ZPasValue->setSingleStep(0.1);
    micmacCommonSettingsFrameLayout->addWidget(mMicMac_ZPasValue);

    micmacCommonSettingsFrame->setLayout(micmacCommonSettingsFrameLayout);

    mMicMacFrameLayout->addWidget(micmacCommonSettingsFrame);
    extensionLayout->addWidget(mMicMacFrame);



    extension->setLayout(extensionLayout);
    mainLayout->addWidget(extension);

    //Botones de navegación
    QFrame *navigationButtonsFrame = new QFrame();
    QHBoxLayout *navigationButtonsFrameLayout = new QHBoxLayout();
    navigationButtonsFrameLayout->setContentsMargins(0,0,0,0);
    navigationButtonsFrameLayout->setAlignment(Qt::AlignRight);
    mPbAdavancedOptions = new QPushButton("Advanced options");
    mPbAdavancedOptions->setAutoDefault(false);
    connect(mPbAdavancedOptions, SIGNAL(clicked()), this, SLOT(toggleAdvancedMenu()));


    navigationButtonsFrameLayout->addWidget(mPbAdavancedOptions);
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
//    mImageSelectionFrame->hide();
    setLayout(mainLayout);
    mPbProccess->setFocus();

    QStringList cameraOptions;
    cameraOptions << "Parallel" << "Ring" << "Custom";

    switch (cameraOptions.indexOf(mProject->getCaptureType())) {
    case 0:
               mCbDensificationMethod->setCurrentIndex(1);
               mParallelImage->setPixmap(mImageParallelSELECTED);
               mRingImage->setPixmap(mImageRing);
               mCustomImage->setPixmap(mImageCustom);
//               mImageSelectionFrame->setVisible(true);
            break;
    case 1:
           mCbDensificationMethod->setCurrentIndex(2);
           mParallelImage->setPixmap(mImageParallel);
           mRingImage->setPixmap(mImageRingSELECTED);
           mCustomImage->setPixmap(mImageCustom);
//           mImageSelectionFrame->setVisible(false);
        break;
    case 2:
           mCbDensificationMethod->setCurrentIndex(1);
           mParallelImage->setPixmap(mImageParallel);
           mRingImage->setPixmap(mImageRing);
           mCustomImage->setPixmap(mImageCustomSELECTED);
           extension->show();
        break;

    }
}

DensificationWizard::~DensificationWizard()
{
}
void DensificationWizard::clicked(QString cameraType){
    methodSelected = true;

    QStringList cameraOptions;
    cameraOptions << "parallel" << "ring" << "custom";

    QPixmap mImageParallel (":/PW/icons/img/Parallel.png");
    QPixmap mImageRing(":/PW/icons/img/Ring.png");
    QPixmap ImageCustom(":/PW/icons/img/custom.png");

    QPixmap mImageParallelSELECTED(":/PW/icons/img/ParallelSELECTED.png");
    QPixmap mImageRingSELECTED(":/PW/icons/img/RingSELECTED.png");
    QPixmap ImageCustomSELECTED(":/PW/icons/img/customSelected.png");

    switch (cameraOptions.indexOf(cameraType)) {
    case 0:
               mCbDensificationMethod->setCurrentIndex(1);
               mParallelImage->setPixmap(mImageParallelSELECTED);
               mRingImage->setPixmap(mImageRing);
               mCustomImage->setPixmap(ImageCustom);
//               mImageSelectionFrame->setVisible(true);
               extension->hide();
            break;
    case 1:
           mCbDensificationMethod->setCurrentIndex(2);
           mParallelImage->setPixmap(mImageParallel);
           mRingImage->setPixmap(mImageRingSELECTED);
           mCustomImage->setPixmap(ImageCustom);
//           mImageSelectionFrame->setVisible(false);
           extension->hide();
        break;
    case 2:
           mCbDensificationMethod->setCurrentIndex(1);
           mParallelImage->setPixmap(mImageParallel);
           mRingImage->setPixmap(mImageRing);
           mCustomImage->setPixmap(ImageCustomSELECTED);
           extension->show();
        break;

    }

}
void DensificationWizard::on_pbCancel_clicked(){
    this->close();
}
void DensificationWizard::on_pbProccess_clicked(){

    if (methodSelected || mCbSURE->isChecked()) {
        if (getDensificationMode().contains("MicMac master image")) {
            if (mListWidget->selectedItems().count()==0 && !mCbSURE->isChecked()) {
                QMessageBox::information(this,"MicMac dense matching","You must select the main image for the MicMac dense matching.",QMessageBox::Ok);
                return;
            }
            QStringList selectedImages =getMainImages();
            bool imagesWithoutMask=false;
            QString msgText;
            msgText.append("Some images (");
            foreach (QString MainImageName, selectedImages) {
                PW::PWImage *mainImage = mProject->getImageByName(MainImageName);
                if(mainImage->getMask().isEmpty()){
                    imagesWithoutMask=true;
                    msgText.append(MainImageName);
                    msgText.append(", ");
                }
            }
            msgText.replace(msgText.length()-2,2,")");
            msgText.append("have no asociated mask.\nDensification could be noisy.");
            if (imagesWithoutMask) {
                int res = QMessageBox::information(this,tr("Warning"),tr(msgText.toUtf8().constData()),QMessageBox::Ok|QMessageBox::Cancel);
                if (res==QMessageBox::Cancel) {
                    return;
                }
            }
        }

        this->accept();
    }else {
        QMessageBox msg;
        msg.setText("Dense matching method not selected.");
        msg.exec();
    }

}
//QString DensificationWizard::getMainImage(){

//    return mListWidget->currentItem()->text();
//}
QStringList DensificationWizard::getMainImages(){
    QStringList selectedMainImages;
    QList<QListWidgetItem*> selectedItems= mListWidget->selectedItems();
    foreach (QListWidgetItem *item, selectedItems) {
        selectedMainImages.append(item->text());
    }
    return selectedMainImages;
}

QString DensificationWizard::getDensificationMode(){
    return mCbDensificationMethod->currentText();
}

void DensificationWizard::on_mCbDensificationMethod_selectedItemChanged(){
    QPixmap mImageParallel (":/PW/icons/img/Parallel.png");
    QPixmap mImageRing(":/PW/icons/img/Ring.png");

    QPixmap mImageParallelSELECTED(":/PW/icons/img/ParallelSELECTED.png");
    QPixmap mImageRingSELECTED(":/PW/icons/img/RingSELECTED.png");

    switch (mCbDensificationMethod->currentIndex()) {
    case 0:
        methodSelected = true;
//        mImageSelectionFrame->setVisible(true);
        mPMVSFrame->hide();
        mMicMacFrame->show();
        mImageSelectionFrame->show();
        break;
    case 1:
        methodSelected = true;
//        mImageSelectionFrame->setVisible(false);
        mPMVSFrame->hide();
        mMicMacFrame->show();
        mImageSelectionFrame->hide();
        break;
    case 2:
        methodSelected = true;
//        mImageSelectionFrame->setVisible(false);
        mPMVSFrame->show();
        mMicMacFrame->hide();
        break;
    case 3:
        methodSelected = true;
//        mImageSelectionFrame->setVisible(false);
        mPMVSFrame->hide();
        mMicMacFrame->hide();
        break;
    case 4:
        methodSelected = true;
//        mImageSelectionFrame->setVisible(false);
        mPMVSFrame->hide();
        mMicMacFrame->hide();
        break;
    case 5:
        methodSelected = true;
//        mImageSelectionFrame->setVisible(false);
        mPMVSFrame->hide();
        mMicMacFrame->hide();
        break;
    default:
        methodSelected = false;
//        mImageSelectionFrame->setVisible(false);
        break;
    }
}

bool DensificationWizard::isSureSelected(){
    return mCbSURE->isChecked();
}

void DensificationWizard::setSUREValuesVisibility(){
    if (mCbSURE->isChecked()) {
        mSURE_FoldValue->setVisible(true);
        mSURE_PyrValue->setVisible(true);
        mSURE_MaxModelsValue->setVisible(true);

        mLbSURE_FoldValue->setVisible(true);
        mLbSURE_PyrValue->setVisible(true);
        mLbSURE_MaxModelsValue->setVisible(true);


        mCbDensificationMethod->setEnabled(false);
        densificationMethodFrame->setVisible(false);
        mMicMacFrame->hide();
//        mImageSelectionFrame->hide();
        mPMVSFrame->hide();
    }else {
        mSURE_FoldValue->hide();
        mSURE_PyrValue->hide();
        mSURE_MaxModelsValue->hide();

        mLbSURE_FoldValue->hide();
        mLbSURE_PyrValue->hide();
        mLbSURE_MaxModelsValue->hide();
//        mCbSURE_DishableAngleTest->hide();
//        mCbSURE_DishablebaselineTest->hide();
        mCbDensificationMethod->setEnabled(true);
        densificationMethodFrame->setVisible(true);

        if (mCbDensificationMethod->currentIndex()==2) {
            mPMVSFrame->setVisible(true);
        }else if (mCbDensificationMethod->currentIndex()==1) {
            mMicMacFrame->show();
        }else if (mCbDensificationMethod->currentIndex()==0) {
            mMicMacFrame->show();
            mImageSelectionFrame->show();
        }
    }
}

int DensificationWizard::getSureFoldValue(){
    return mSURE_FoldValue->value();
}
int DensificationWizard::getSurePyrValue(){
    return mSURE_PyrValue->value();
}
int DensificationWizard::getSureMaxModelsValue(){
    return mSURE_MaxModelsValue->value();
}

void DensificationWizard::showAboutSURE(){
    AboutSureDialog *aboutSureD = new AboutSureDialog(mSettings,this);  
    aboutSureD->exec();
    if (PW::LibPW::getSUREBinPath().isEmpty()) {
        mCbSURE->setEnabled(false);
    }else {
        mCbSURE->setEnabled(true);
    }
}

int DensificationWizard::getPMVSLevel(){
    return mPMVSLevelValue->value();
}
int DensificationWizard::getPMVSMin(){
    return   mPMVSMinValue->value();
}
int DensificationWizard::getPMVSCSize(){
    return mPMVSCSizeValue->value();
}

float DensificationWizard::getPMVSThreshold(){
    return mPMVSThresholdValue->value();
}

void DensificationWizard::imageHovered(){
    this->setCursor(Qt::PointingHandCursor);
}

void DensificationWizard::imageLeft(){
    this->setCursor(Qt::ArrowCursor);
}

bool DensificationWizard::useMask(){
    return mUseMaskMicMac->isChecked();
}

void DensificationWizard::on_mainImageSelectionChanged(){
    QStringList selectedImages =getMainImages();
    if (selectedImages.count()==0) {
        mUseMaskMicMac->setEnabled(false);
        mUseMaskMicMac->setChecked(false);
        return;
    }
    foreach (QString MainImageName, selectedImages) {

        PW::PWImage *mainImage = mProject->getImageByName(MainImageName);
        if(mainImage != NULL && !mainImage->getMask().isEmpty()){
            mUseMaskMicMac->setEnabled(true);
            return;
        }else{
            mUseMaskMicMac->setEnabled(false);
            mUseMaskMicMac->setChecked(false);
        }
    }

}

void DensificationWizard::toggleAdvancedMenu(){
    if (extension->isVisible()) {
        extension->hide();
    }else {
        extension->show();
    }
}

int DensificationWizard::getMicMacDeZoomValue(){
    return mMicMac_DeZoomValue->currentText().toInt();
}
double DensificationWizard::getMicMacZPasValue(){
    return mMicMac_ZPasValue->value();
}
double DensificationWizard::getMicMacZRegulValue(){
    return mMicMac_ZRegulValue->value();
}
//bool DensificationWizard::isDishableAngleTestChecked(){
//    return mCbSURE_DishableAngleTest->isChecked();
//}
//bool DensificationWizard::isDishableBaselineTestChecked(){
//    return mCbSURE_DishablebaselineTest->isChecked();
//}

//int DensificationWizard::getMicMacNumNearestImages(){
//    return mMicMacNearestImagesValue->value();
//}
void DensificationWizard::showAboutDenseMatching(){
    AboutDensification_Dialog *densDialog =new AboutDensification_Dialog(this);
    densDialog->exec();
}
