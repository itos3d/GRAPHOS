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
#include <QStringList>

#include "CameraMetadataIO.h"

using namespace PW;

CameraMetadataIO::CameraMetadataIO(QString imagePath):
    mImagePath(imagePath)
{
    mImageMetaData = new QImageMetaData();
}

CameraMetadataIO::~CameraMetadataIO()
{
    delete mImageMetaData;
}

void CameraMetadataIO::setImagePath(QString imagePath)
{
    mImagePath = imagePath;
}

void CameraMetadataIO::read(Camera *camera)
{
    mImageMetaData->read(mImagePath);
    QString model = mImageMetaData->model();
    if(model == "Not defined")
        model = "";
    camera->setName(model);
    QString lens = mImageMetaData->lens();
    if(lens == "Not defined")
        lens = "";
    camera->setLensName(lens);
    camera->setDeclaredFocal(mImageMetaData->focalLength().value());
//    camera->setScaleFactor35(0.0);
}

void CameraMetadataIO::write(Camera *camera)
{

}

void CameraMetadataIO::writeCameraName(QString name){

}

void CameraMetadataIO::writeLensName(QString lensName)
{

}

void CameraMetadataIO::writeFocalLegth(double focal)
{

}

void CameraMetadataIO::writeFocalLegth35(double focal35)
{

}
