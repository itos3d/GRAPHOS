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
#include <QRegExp>
#include <QImageReader>
#include <QFileInfo>

#include "PWImage.h"

using namespace PW;

PWImage::PWImage():
    mCamera(NULL),
    mActiveExtOrientation(NULL),
    mMask(NULL),
    mID(0)
{
}

PWImage::PWImage(QString url):
    mCamera(NULL),
    mActiveExtOrientation(NULL),
    mMask(NULL),
    mID(0)
{
    QFileInfo fileInfo(url);
    mFileName=fileInfo.fileName();
    mBasePath=fileInfo.absolutePath();
//    mFileName = url.right(url.length()-url.lastIndexOf(QRegExp("/"))-1);
//    mBasePath = url.left(url.lastIndexOf(QRegExp("/")));
    QImageReader imageReader(url);
    mSize = imageReader.size();
}

PWImage::~PWImage(){
    for(int i=0; i<mControlPoints.count(); i++)
        delete mControlPoints.at(i);

    for(int i=0; i<mExtOrientations.count(); i++)
        delete mExtOrientations.at(i);
}

int PWImage::getID()
{
    return mID;
}

QString PWImage::getFullPath()
{
    return mBasePath + "/" + mFileName;
}

void PWImage::setBasePath(QString url)
{
    mBasePath = url;
}

void PW::PWImage::setMask(QPolygonF mask)
{
    mMask = mask;
}

QPolygonF PW::PWImage::getMask()
{
    return mMask;
}

void PW::PWImage::setExteriorOrientation(PW::ExteriorOrientation *orientation)
{
    mExtOrientations.append(orientation);
    mActiveExtOrientation = orientation;    /*TODO*/
}

PW::ExteriorOrientation * PW::PWImage::getExteriorOrientation()
{
    return mActiveExtOrientation;
}

PW::ExteriorOrientation * PW::PWImage::getExteriorOrientation(int index)
{
    return mExtOrientations.at(index);
}

QString PW::PWImage::getFileName()
{
    return mFileName;
}

QList<PW::PW2dPoint *> * PW::PWImage::getControlPoints()
{
    return &mControlPoints;
}

void PW::PWImage::setCamera(PW::Camera *camera)
{
    mCamera = camera;
}

PW::Camera * PW::PWImage::getCamera()
{
    return mCamera;
}

QSize PWImage::getSize()
{
    return mSize;
}

void PWImage::setID(int id)
{
    mID = id;
}
