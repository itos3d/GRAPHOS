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
#ifndef DISTORTIONMODEL_H
#define DISTORTIONMODEL_H

#define APERO_MODEL_RADIAL_EXTENDED               0
#define APERO_MODEL_RADIAL_BASIC                  1
#define APERO_MODEL_FRASER                        3
#define APERO_MODEL_FRASER_BASIC                  4
#define APERO_MODEL_FISHEYE                       5

#include "libPW_global.h"
#include <QString>

namespace PW{

/*!
 \brief Base class representing camera distortion model.

*/
class LIBPWSHARED_EXPORT DistortionModel
{
public:
/*!
 \brief Constructor.

*/
    DistortionModel();

//    virtual int getID() = 0;

    /*!
     \brief Undistort a image according to distortion model.

     \param inputImage image to undistort
     \return PWImage undistorted image
    */
    virtual QString undistort(QString inputImagePath,
                              double focal,
                              double xpp,
                              double ypp) = 0;
    /*!
     \brief

     \return bool true if distortion model allows to undistort images.
    */
    virtual bool canUnistort() = 0;

    virtual void undistort(double xpp, double ypp, double &x, double &y) = 0;
    virtual void distort(double xpp, double ypp, double &x, double &y) = 0;


};

}

#endif // DISTORTIONMODEL_H
