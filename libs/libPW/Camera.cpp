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
#include <QDebug>

#include "Camera.h"

using namespace PW;

Camera::Camera():
    mName(""),
    mLensName(""),
    mSensorHeight(0),
    mSensorWidth(0),
    mDeclaredFocal(0),
    mScaleFactor35(0),
    mActiveCamModel(NULL)
{
}

Camera::Camera(QString name, QString lensName, double width, double height, double focal, double scaleFactor):
    mName(name),
    mLensName(lensName),
    mSensorHeight(height),
    mSensorWidth(width),
    mDeclaredFocal(focal),
    mScaleFactor35(scaleFactor),
    mActiveCamModel(NULL)
{
}

Camera::~Camera(){
//    for(int i=0; i<mCameraModels.count(); i++)
//        delete mCameraModels.at(i);
}

double PW::Camera::getSensorHeight()
{
    return mSensorHeight;
}

double PW::Camera::getSensorWidth()
{
    return mSensorWidth;
}

double Camera::getDeclaredFocal()
{
    return mDeclaredFocal;
}

double Camera::getScaleFactor35()
{
    return mScaleFactor35;
}

QString PW::Camera::getName()
{
    return mName;
}

QString Camera::getLensName()
{
    return mLensName;
}

void PW::Camera::setName(QString name)
{
    mName = name;
}

void Camera::setLensName(QString lensName)
{
    mLensName = lensName;
}

void PW::Camera::setSensorHeight(double height)
{
    mSensorHeight = height;
}

void PW::Camera::setSensorWidth(double width)
{
    mSensorWidth = width;
}

void Camera::setDeclaredFocal(double focal)
{
    mDeclaredFocal = focal;
}

void Camera::setScaleFactor35(double scaleFactor)
{
    mScaleFactor35 = scaleFactor;
}

void PW::Camera::setCameraModel(PW::CameraModel *cameraModel)
{
    if(mCameraModels.count() == 0 && cameraModel != NULL) /*TODO*/
        mCameraModels.append(cameraModel); /*TODO*/
    mActiveCamModel = cameraModel;
}

PW::CameraModel * PW::Camera::getCameraModel(int index)
{
    return mCameraModels.at(index);
}

QList<CameraModel *> Camera::getCameraModels()
{
    return mCameraModels;
}

PW::CameraModel * PW::Camera::getCameraModel()
{
    return mActiveCamModel;
}
