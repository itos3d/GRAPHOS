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
#ifndef APEROMODELREADER_H
#define APEROMODELREADER_H

#include <QDomDocument>

#include "PhotogrammetricModel.h"
#include "CameraModelReader.h"
#include "Camera.h"

namespace PW{
/*!
 \brief Reader for Apero camera calibration files whit Radial Distortion model.

*/
class LIBPWSHARED_EXPORT  AperoModelReader : public CameraModelReader
{
public:
    /*!
 \brief  Constructor

*/
    AperoModelReader(Camera * camera);

    /*!
     \brief Reads a calibration file.

     \param device The input device (ie QFile *).
     \return bool True if device is a valid Apero calibration file (Radial Distortion Model).
    */
    virtual PhotogrammetricModel *read(QString filePath);

    virtual PhotogrammetricModel *read(QDomElement& root);


private:
    QDomDocument mDomDocument;
    Camera * mCamera;

};
}
#endif // APEROMODELREADER_H
