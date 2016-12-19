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
#ifndef CAMERADEFINITIONDIALOG_H
#define CAMERADEFINITIONDIALOG_H

#include <QDialog>

#include "PersistenceManager.h"
#include "Camera.h"

namespace Ui {
class CameraDefinitionDialog;
}

class CameraDefinitionDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit CameraDefinitionDialog(PW::PersistenceManager * persistenceManager, QWidget *parent = 0,QSize imageSize=QSize(0,0));
    ~CameraDefinitionDialog();

    void setCamera(PW::Camera *camera);
    void setAspectRatio(float ratio);
    bool isAcepted();
    
private slots:
    void clearCamera();
    void clearLens();
    void validateFields();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_comboBoxCamera_currentIndexChanged(const QString &arg1);

    void on_comboBoxLens_currentIndexChanged(const QString &arg1);

    void on_lineEditCameraName_textChanged(const QString &arg1);

    void on_lineEditWidth_textChanged(const QString &arg1);

    void on_lineEditHeight_textChanged(const QString &arg1);

    void on_lineEditScale_textChanged(const QString &arg1);

    void on_lineEditLensName_textChanged(const QString &arg1);

    void on_lineEditFocal_textChanged(const QString &arg1);

private:
    QSize mImageSize;
    Ui::CameraDefinitionDialog *ui;
    PW::PersistenceManager *mPersistenceManager;
    PW::Camera *mCamera;
    float mAspectRatio;
    bool mAcepted;
    QPalette *mRedPalette;
    QPalette *mBlackPalette;
    QPalette *mYellowPalette;
    bool stimatedFocal,stimatedSize;

    QMap<QString, PW::Camera *> mCamerasMap;
    QMap<QString, PW::Camera *> mLensMap;

    float mStimatedSensor_width_mm;
    float mStimatedSensor_height_mm;
    float mStimatedSensor_focal_mm;
};

#endif // CAMERADEFINITIONDIALOG_H
