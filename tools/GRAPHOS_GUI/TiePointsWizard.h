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
#ifndef TIEPOINTSWIZARD_H
#define TIEPOINTSWIZARD_H

#include <QDialog>
#include "ClickableImage.h"
#include <QComboBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QCheckBox>
#include <QMap>

class TiePointsWizard : public QDialog
{
    Q_OBJECT

public:
    explicit TiePointsWizard(QWidget *parent = 0,QSize imageSize=QSize(0,0),QString imagesPath="");
    ~TiePointsWizard();

    QMap<QString, QString> getTiePointsMethod();
    float getWallisBrithness();
    float getWallisContrast();
    int getWallisKernell();
    int getWallisStdDeviation();
    int getTapiocaMulScaleMinValue();
    int getTapiocaMulScaleMaxValue();
    int getMinimumTapiocaMatches();
    bool isWallisChecked();
    QString getCaptureConfiguration();
    bool isMSDAffineChecked();
    int getMSDAffineTilts();
private:

    QPushButton *mPbWallisAnalisys,*mPbFME;
    QString mImagesPath;
    QString mCaptureConfiguration;
    QFrame *mMatchingMethodFrame;
    bool methodSelected;
    ClickableImage *mParallelImage;
    ClickableImage *mRingImage;
    ClickableImage *mCustomImage;
    QPushButton *mPbProccess;
    QComboBox *mCbTiePointsMethod;
    QComboBox *mCbmatchingMethod;
    QGroupBox *mGbTapiocaSettings;
    QGroupBox *mGbMSDSettings;
    QGroupBox *mGbASIFTUSettings;
    QGroupBox *mGbRobustMatcherSettings;


    QComboBox *mCbSearchMethod;
    QFrame *lineRangeFrame;
    QFrame *MulScaleParametersFrame;
    QFrame *sizeTapiocaFrame;
    QSpinBox *mMulScaleMinValue;
    QSpinBox *mMulScaleMaxValue;
    QSpinBox *mlineRangeValue;
    QSpinBox *mTapiocaResizeValue;
    QSpinBox *mMSDResizeValue;
    QSpinBox *mMSDTiltsValue;
    QSpinBox *minimumMatches;
    QSpinBox *minimumTapiocaMatches;
    QSpinBox *mASIFTUResizeValue;
    QCheckBox *mDownsampleMSDImages;
    QCheckBox *mMSDaffine;
    QCheckBox *mMSDMaxTiepoints;
    QCheckBox *mDownsampleASIFTUImages;
    QCheckBox *mDownsampleTapiocaImages;
    QCheckBox *mASIFTUMaxTiepoints;
    QWidget *extension;


    //Wallis parameters
    QSize mImageSize;
    QCheckBox *mCbWallis;
    QDoubleSpinBox *mWallisContrastValue;
    QDoubleSpinBox *mWallisBrightnessValue;
    QSpinBox *mWallisStdDeviationValue;
    QSpinBox *mWallisKernelSizeValue;
    QFrame *mWallisSettings;

    //MsdParameters
    QSpinBox *MSD_PatchRadius;
    QSpinBox *MSD_SearchAreaRadius;
    QSpinBox *MSD_NMSRadius;
    QSpinBox *MSD_NMSScaleRadius;
    QSpinBox *MSD_ThSaliency;
    QSpinBox *MSD_KNN;
    QSpinBox *mMSDMaxTiepointsValue;
    QDoubleSpinBox *MSD_ScaleFactor;
    QSpinBox *MSD_NScales;
    QCheckBox *MSD_ComputeOrientations;

    //ASIFTU Parameters

    QSpinBox *ASIFTU_PeakTh;
    QDoubleSpinBox *ASIFTU_EdgeTh;
    QSpinBox *ASIFTU_Octaves;
    QSpinBox *mASIFTUMaxTiepointsValue;
    QSpinBox *mASIFTU_Tilts;

    //Robust Matcher Parameters
    QDoubleSpinBox *RB_ratio;
//    QDoubleSpinBox *RB_distance;
//    QDoubleSpinBox *RB_confidence;
    QDoubleSpinBox *RB_threshold_K;

private slots:
    void clicked(QString captureType);
    void on_pbCancel_clicked();
    void on_pbProccess_clicked();
    void on_mCbTiePointsMethod_selectedItemChanged();
    void on_mCbmatchingMethod_selectedItemChanged();
    void on_mCbSearchMethod_selectedItemChanged();
    void on_mDownsampleTapiocaImages_statusChanged();
    void on_mDownsampleMSDImages_statusChanged();
    void on_mDownsampleASIFTUImages_statusChanged();
    void on_mASIFTUMaxTiepoints_statusChanged();
    void on_mMSDMaxTiepoints_statusChanged();
    void setWallisValueVisibility();
    void computeNScales();
    void imageHovered();
    void imageLeft();
    void on_MulScaleValuesChanged();
    void on_mMSDAffine_statusChanged();
    void showAbouttpMethod();
    void showAboutwallis();
    void showFME();
    void showWallisEvaluation();

};

#endif // TIEPOINTSWIZARD_H
