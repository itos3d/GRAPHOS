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
#include <QDialogButtonBox>
#include <QPushButton>

#include "CameraDefinitionDialog.h"
#include "ui_CameraDefinitionDialog.h"
#include "PersistenceManager.h"
#include "CameraExifIO.h"
#include <QMessageBox>
using namespace PW;

CameraDefinitionDialog::CameraDefinitionDialog(PersistenceManager * persistenceManager, QWidget *parent,QSize imageSize) :
    QDialog(parent),
    ui(new Ui::CameraDefinitionDialog),
    mPersistenceManager(persistenceManager),
    mAspectRatio(0),
    mImageSize(imageSize)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    QDoubleValidator * numericValidator = new QDoubleValidator(this);
    ui->lineEditWidth->setValidator(numericValidator);
    ui->lineEditHeight->setValidator(numericValidator);
    ui->lineEditScale->setValidator(numericValidator);
    ui->lineEditFocal->setValidator(numericValidator);

    ui->lineEditScale->setVisible(false);
    ui->labelScale->setVisible(false);

    mRedPalette = new QPalette();
    mBlackPalette = new QPalette();
    mYellowPalette = new QPalette();
    mRedPalette->setColor(QPalette::Text,Qt::red);
    mBlackPalette->setColor(QPalette::Text,Qt::black);
    mYellowPalette->setColor(QPalette::Text,Qt::darkYellow);
    validateFields();

    QPixmap pxWarning(":/PW/icons/img/warning.png");
    ui->lbFocalStimated->setPixmap(pxWarning.scaled(18,18,Qt::KeepAspectRatio));
    ui->lbHeightStimated->setPixmap(pxWarning.scaled(18,18,Qt::KeepAspectRatio));
    ui->lbWidthStimated->setPixmap(pxWarning.scaled(18,18,Qt::KeepAspectRatio));
    ui->lbFocalStimated->setVisible(false);
    ui->lbHeightStimated->setVisible(false);
    ui->lbWidthStimated->setVisible(false);
    ui->lbWarningImg->setPixmap(pxWarning.scaled(18,18,Qt::KeepAspectRatio));
    ui->warningFrame->setVisible(false);
    ui->aspectRatioErrorFrame->setVisible(false);
    stimatedFocal=false;
    stimatedSize=false;
}

CameraDefinitionDialog::~CameraDefinitionDialog()
{
    delete ui;
}

void CameraDefinitionDialog::setCamera(Camera *camera)
{
    mCamera = camera;

    //Compute default parameters

    if (camera->getSensorHeight() == 0 && camera->getSensorWidth() == 0) {
        stimatedSize=true;
        mStimatedSensor_width_mm=0;
        mStimatedSensor_height_mm=0;
        mStimatedSensor_focal_mm=0;
        //Cálculo inicial diagonal de la imagen en píxeles
        float diag=sqrt(pow((float)mImageSize.width(),2)+pow((float)mImageSize.height(),2));

        float f_pixel=(50*diag)/(43.26661531); //Primera hipótesis
        float pix_size;
        //si se conoce la focal exif (en mm)
        if (camera->getDeclaredFocal() != 0){
                mStimatedSensor_focal_mm=camera->getDeclaredFocal();
                pix_size=mStimatedSensor_focal_mm/f_pixel;

                if (pix_size<0.0012){
                    pix_size=0.0012;
                }
        }else{
            stimatedFocal=true;
            pix_size=0.0012;
            mStimatedSensor_focal_mm=f_pixel*pix_size;
        }

        //Datos del sensor
        mStimatedSensor_width_mm=mImageSize.width()*pix_size;
        mStimatedSensor_height_mm=mImageSize.height()*pix_size;
    }

    ui->comboBoxCamera->clear();
    ui->comboBoxCamera->addItem("...");
    ui->comboBoxLens->clear();
    ui->comboBoxLens->addItem("...");

    for (int  i=0; i<mCamerasMap.values().count();i++)
        delete mCamerasMap.values().at(i);
    mCamerasMap.clear();
    mLensMap.clear();

    // Get cámeras from db.
    QList<Camera *> cameras = mPersistenceManager->readCameras("","");

    if (camera->getName().isEmpty()){
        ui->comboBoxCamera->setEnabled(true);
        ui->labelCameraName->setEnabled(true);
        for (int i=0; i<cameras.count() ; i++){
            if (!mCamerasMap.contains(cameras.at(i)->getName())){
                ui->comboBoxCamera->addItem(cameras.at(i)->getName());
                mCamerasMap.insert(cameras.at(i)->getName(), cameras.at(i));
            }
        }
    }
    else{
        ui->lineEditCameraName->setText(camera->getName());
        ui->comboBoxCamera->setEnabled(false);
        ui->labelCameraName->setEnabled(false);
    }

    if (camera->getSensorWidth() != 0){
        ui->lineEditWidth->setText(QString::number(camera->getSensorWidth()));
        ui->lineEditWidth->setEnabled(false);
    }
    else{
//        ui->lineEditWidth->setText("");
        //Set stimated sensor width
        ui->lineEditWidth->setText(QString::number(mStimatedSensor_width_mm));
        ui->lbWidthStimated->setVisible(true);
        ui->lineEditWidth->setEnabled(true);
    }

    if (camera->getSensorHeight() != 0){
        ui->lineEditHeight->setText(QString::number(camera->getSensorHeight()));
        ui->lineEditHeight->setEnabled(false);
    }
    else{
//        ui->lineEditHeight->setText("");
        //Set stimated sensor height
        ui->lineEditHeight->setText(QString::number(mStimatedSensor_height_mm));
        ui->lineEditHeight->setPalette(*mYellowPalette);
        ui->lbHeightStimated->setVisible(true);
        ui->lineEditHeight->setEnabled(true);
    }

    if (camera->getScaleFactor35() != 0){
        ui->lineEditScale->setText(QString::number(camera->getScaleFactor35()));
        ui->lineEditScale->setEnabled(false);
    }
    else{
        ui->lineEditScale->setText("");
        ui->lineEditScale->setEnabled(true);
    }

    // *********** Lens:

    if (camera->getLensName().isEmpty()){
        ui->comboBoxLens->setEnabled(true);
        ui->lineEditLensName->setEnabled(true);
        for (int i=0; i<cameras.count() ; i++){
            if (!mLensMap.contains(cameras.at(i)->getLensName())){
                ui->comboBoxLens->addItem(cameras.at(i)->getLensName());
                mLensMap.insert(cameras.at(i)->getLensName(), cameras.at(i));
            }
        }
    }
    else{
        ui->lineEditLensName->setText(camera->getLensName());
        ui->comboBoxLens->setEnabled(false);
        ui->lineEditLensName->setEnabled(false);
    }

    if (camera->getDeclaredFocal() != 0){
        ui->lineEditFocal->setText(QString::number(camera->getDeclaredFocal()));
        ui->lineEditFocal->setEnabled(false);
    }
    else{
//        ui->lineEditFocal->setText("");
        // set stimated focal
        ui->lineEditFocal->setText(QString::number(mStimatedSensor_focal_mm));
        ui->lineEditFocal->setPalette(*mYellowPalette);
        ui->lbFocalStimated->setVisible(true);
        ui->lineEditFocal->setEnabled(true);
    }


    validateFields();
    if (stimatedFocal || stimatedSize) {
        ui->warningFrame->setVisible(true);
    }
}

void CameraDefinitionDialog::setAspectRatio(float ratio)
{
    mAspectRatio = ratio;
}

void CameraDefinitionDialog::clearCamera()
{
    ui->lineEditCameraName->setText("");
    ui->lineEditHeight->setText("");
    ui->lineEditWidth->setText("");
    ui->lineEditScale->setText("");
}

void CameraDefinitionDialog::clearLens()
{
    ui->lineEditLensName->setText("");
    ui->lineEditFocal->setText("");
}

void CameraDefinitionDialog::validateFields()
{
    ui->aspectRatioErrorFrame->setVisible(false);

    bool valid = true;

    if (stimatedFocal) {
        ui->lineEditFocal->setPalette(*mYellowPalette);
    }

    if (stimatedSize) {
        ui->lineEditHeight->setPalette(*mYellowPalette);
        ui->lineEditWidth->setPalette(*mYellowPalette);

    }else {
        ui->lineEditHeight->setPalette(*mBlackPalette);
        ui->lineEditWidth->setPalette(*mBlackPalette);

    }


    if(ui->lineEditCameraName->text().isEmpty() ||
            ui->lineEditHeight->text().isEmpty() ||
            ui->lineEditWidth->text().isEmpty() ||
            ui->lineEditFocal->text().isEmpty()
            )
        valid = false;
    else{
        float sensorAspectRatio = ui->lineEditWidth->text().toDouble()/ui->lineEditHeight->text().toDouble();
        if (mAspectRatio != 0 && ((sensorAspectRatio > mAspectRatio + 0.1) || (sensorAspectRatio < mAspectRatio - 0.1))){
            valid = false;
            ui->lineEditHeight->setPalette(*mRedPalette);
            ui->lineEditWidth->setPalette(*mRedPalette);
            ui->aspectRatioErrorFrame->setVisible(true);
        }else {
            ui->aspectRatioErrorFrame->setVisible(false);
        }
    }

//    if(ui->lineEditScale->text().isEmpty() && ui->lineEditHeight->text().toDouble() <= 24 && ui->lineEditWidth->text().toDouble() <= 36)
//        valid = false;
//    if(ui->lineEditLensName->text().isEmpty())
//        valid = false;
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(valid);
}

void CameraDefinitionDialog::on_comboBoxCamera_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "..."){
        clearCamera();
    }else{
        Camera * camera = mCamerasMap.value(arg1);
        if (camera != NULL){
            ui->lineEditCameraName->setText(camera->getName());
            ui->lineEditWidth->setText(QString::number(camera->getSensorWidth()));
            ui->lineEditHeight->setText(QString::number(camera->getSensorHeight()));
            ui->lineEditScale->setText(QString::number(camera->getScaleFactor35()));
        }
    }
}

void CameraDefinitionDialog::on_comboBoxLens_currentIndexChanged(const QString &arg1)
{
    if(arg1 == "..."){
        clearLens();
    }else{
        Camera * camera = mLensMap.value(arg1);
        if (camera != NULL){
            ui->lineEditLensName->setText(camera->getLensName());
            ui->lineEditFocal->setText(QString::number(camera->getDeclaredFocal()));
        }
    }
}

void CameraDefinitionDialog::on_buttonBox_accepted()
{
    mCamera->setName(ui->lineEditCameraName->text());
    mCamera->setLensName(ui->lineEditLensName->text());
    mCamera->setSensorWidth(ui->lineEditWidth->text().toDouble());
    mCamera->setSensorHeight(ui->lineEditHeight->text().toDouble());
    mCamera->setDeclaredFocal(ui->lineEditFocal->text().toDouble());
//    mCamera->setScaleFactor35(ui->lineEditScale->text().toDouble());

//    mAcepted = true;
    this->accept();
}

void CameraDefinitionDialog::on_buttonBox_rejected()
{
//    mAcepted = false;
    this->close();
}

bool CameraDefinitionDialog::isAcepted()
{
    return mAcepted;
}

void CameraDefinitionDialog::on_lineEditCameraName_textChanged(const QString &arg1)
{
    validateFields();
}

void CameraDefinitionDialog::on_lineEditWidth_textChanged(const QString &arg1)
{
    ui->lbWidthStimated->setVisible(false);
    if (!ui->lbWidthStimated->isVisible() && !ui->lbHeightStimated->isVisible() && !ui->lbFocalStimated->isVisible()) {
        ui->warningFrame->setVisible(false);
    }
    validateFields();
}

void CameraDefinitionDialog::on_lineEditHeight_textChanged(const QString &arg1)
{
    ui->lbHeightStimated->setVisible(false);
    if (!ui->lbWidthStimated->isVisible() && !ui->lbHeightStimated->isVisible() && !ui->lbFocalStimated->isVisible()) {
        ui->warningFrame->setVisible(false);
    }
    validateFields();
}

void CameraDefinitionDialog::on_lineEditScale_textChanged(const QString &arg1)
{
    validateFields();
}

void CameraDefinitionDialog::on_lineEditLensName_textChanged(const QString &arg1)
{
    validateFields();
}

void CameraDefinitionDialog::on_lineEditFocal_textChanged(const QString &arg1)
{
    ui->lbFocalStimated->setVisible(false);
    if (!ui->lbWidthStimated->isVisible() && !ui->lbHeightStimated->isVisible() && !ui->lbFocalStimated->isVisible()) {
        ui->warningFrame->setVisible(false);
    }
    validateFields();
}
