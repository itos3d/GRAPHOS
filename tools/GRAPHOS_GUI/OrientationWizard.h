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
#ifndef ORIENTATIONWIZARD_H
#define ORIENTATIONWIZARD_H

#include <QDialog>
#include "ClickableImage.h"
#include <QComboBox>
#include <QGroupBox>
#include <QCheckBox>
class OrientationWizard : public QDialog
{
    Q_OBJECT

public:
    explicit OrientationWizard(QWidget *parent = 0, QString projectPath="");
    ~OrientationWizard();
    QString getOrientationMode();
    bool isAffineParametersChecked();
    bool isDecenteringParametersChecked();
    bool isPrincipalPointParametersChecked();
    bool isDistortionCenterParameterschecked();
    bool isFocalParametersChecked();

private:
    QString mProjectPath;
    QString mOrientationMode;
    ClickableImage *mSmartphoneImage;
    ClickableImage *mCompactImage;
    ClickableImage *mReflexImage;
    QComboBox *mCbCalibrationModel;
    QPushButton *mPbProccess, *mPbCCD_Distribution,*mPbMatchingAnalisys;
    QWidget *extension;
    QGroupBox *mGenericCalibrationFrame;

    //CalibrationParameters
    QCheckBox *mAfineParameters;
    QCheckBox *mDecenteringParameters;
    QCheckBox *mPrincipalPointParameters;
    QCheckBox *mDistortionCenterParameters;
    QCheckBox *mFocalParameters;
private slots:
    void clicked(QString cameraType);
    void on_pbCancel_clicked();
    void on_pbProccess_clicked();
    void on_mCbCalibrationModel_selectedItemChanged();
    void imageHovered();
    void imageLeft();
    void AdvancedOptionsClicked();
    void showCCDEvaluator();
    void showMatchingAnalisys();
    void showAboutdistortionModels();

};

#endif // ORIENTATIONWIZARD_H
