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
#ifndef DENSIFICATIONWIZARD_H
#define DENSIFICATIONWIZARD_H

#include <QDialog>
#include "ClickableImage.h"
#include <QListWidget>
#include "libPW.h"
#include <QCheckBox>
#include <QSpinBox>
#include <QGroupBox>
class DensificationWizard : public QDialog
{
    Q_OBJECT

public:
    explicit DensificationWizard(QWidget *parent = 0,PW::Project *mProject=0,QMap<QString, QImage> *mapImages=0,QSettings *settings=0);
    ~DensificationWizard();
//    QString getMainImage();
    QStringList getMainImages();
    QString getDensificationMode();
    bool isSureSelected();
    int getSureFoldValue();
    int getSurePyrValue();
    int getSureMaxModelsValue();
    int getPMVSCSize();
    int getPMVSLevel();
    int getPMVSMin();
    float getPMVSThreshold();
    bool useMask();
    int getMicMacDeZoomValue();
    double getMicMacZRegulValue();
    double getMicMacZPasValue();
//    int getMicMacNumNearestImages();
//    bool isDishableAngleTestChecked();
//    bool isDishableBaselineTestChecked();
private:
    QSpinBox *mMicMacNearestImagesValue;

    bool methodSelected;
    QMap<QString, QImage> *mMapImages;
    ClickableImage *mParallelImage;
    ClickableImage *mRingImage;
    ClickableImage *mCustomImage;
    QListWidget *mListWidget;
    PW::Project *mProject;
    QFrame *mImageSelectionFrame;
    QString mDensificationMode;
    QComboBox *  mCbDensificationMethod;
    QCheckBox *mCbSURE;
//    QCheckBox *mCbSURE_DishableAngleTest;
//    QCheckBox *mCbSURE_DishablebaselineTest;
    QPushButton *mPbProccess;
    QPushButton *mPbAdavancedOptions;
    QSpinBox *mSURE_PyrValue;
    QSpinBox *mSURE_FoldValue;
    QSpinBox *mSURE_MaxModelsValue;
    QLabel *mLbSURE_FoldValue;
    QLabel *mLbSURE_PyrValue;
    QLabel *mLbSURE_MaxModelsValue;

    QSettings *mSettings;
    QWidget *extension;
    //PMVS parameters
    QGroupBox *mPMVSFrame;
    QGroupBox *mMicMacFrame;
    QSize mImageSize;
    QSpinBox *mPMVSLevelValue;
    QSpinBox *mPMVSMinValue;
    QSpinBox *mPMVSCSizeValue;
    QDoubleSpinBox *mPMVSThresholdValue;
    QFrame *densificationMethodFrame;
    QCheckBox *mUseMaskMicMac;

    //MicMacParameters
    QComboBox *mMicMac_DeZoomValue;
    QDoubleSpinBox *mMicMac_ZRegulValue;
    QDoubleSpinBox *mMicMac_ZPasValue;
private slots:
    void clicked(QString cameraType);
    void on_pbCancel_clicked();
    void on_pbProccess_clicked();
    void on_mCbDensificationMethod_selectedItemChanged();
    void setSUREValuesVisibility();
    void showAboutSURE();
    void imageHovered();
    void imageLeft();
    void on_mainImageSelectionChanged();
    void toggleAdvancedMenu();
    void showAboutDenseMatching();
};

#endif // DENSIFICATIONWIZARD_H
