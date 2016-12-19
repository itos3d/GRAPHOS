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
#ifndef PWIMAGE_H
#define PWIMAGE_H

#include <QString>
#include <QPolygonF>

#include "PW2dPoint.h"
#include "ExternalOrientation.h"
#include "CameraModel.h"
#include "Camera.h"

/*!
 \brief Symple and provisional representation of an image.

*/
namespace PW{


class LIBPWSHARED_EXPORT PWImage
{
public:
    PWImage();
    ~PWImage();
    PWImage(QString url);

    int getID();
    QString getFullPath();
    QPolygonF getMask();
    ExteriorOrientation * getExteriorOrientation(int index);
    ExteriorOrientation * getExteriorOrientation();
    QString getFileName();
    QList<PW2dPoint *> *getControlPoints();
    Camera * getCamera();
    QSize getSize();

    void setID(int id);
    void setBasePath(QString url);
    void setMask(QPolygonF mask);
    void setExteriorOrientation(ExteriorOrientation * orientation);
    void setCamera(Camera * camera);
    void setFullPath(QString basePath){mBasePath=basePath;};


private:
    int mID; //Persistence id.
    QString mBasePath; //Directory containing image
    QString mFileName; //File name (relative to mUrl).
    QPolygonF mMask;
    QList<PW2dPoint *> mControlPoints;

    QList<ExteriorOrientation *> mExtOrientations;

    Camera * mCamera;
    ExteriorOrientation * mActiveExtOrientation;

    QSize mSize;
};

}

#endif // PWIMAGE_H
