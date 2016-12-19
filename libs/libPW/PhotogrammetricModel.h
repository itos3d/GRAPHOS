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
#ifndef PHOTOGRAMMETRICMODEL_H
#define PHOTOGRAMMETRICMODEL_H

#include "CameraModel.h"
#include "DistortionModel.h"

namespace PW{

/*!
 \brief Class representing photogrammetric camera model.

*/
class LIBPWSHARED_EXPORT PhotogrammetricModel : public CameraModel
{
public:
/*!
 \brief Constructor

*/
    PhotogrammetricModel();
    ~PhotogrammetricModel();

    /*!
     \brief Gets the focal lenght in milimeters.

     \return float focal lenght in milimeters.
    */
    double getFocal();
    /*!
     \brief Gets the x coordinate of the principal point (milimeters).

     \return float x coordinate of the principal point (milimeters).
    */
    double getXp();
    /*!
     \brief Gets the y coordinate of the principal point (milimeters).

     \return float y coordinate of the principal point (milimeters).
    */
    double getYp();
    /*!
     \brief Gets the distortion model containing the distortion parameters.

     \return DistortionModel * distortion model.
    */
    DistortionModel * getDistortionModel();

    /*!
     \brief Sets the focal lenght.

     \param f focal lenght in milimeters.
    */
    void setFocal(double f);
    /*!
     \brief Sets the x coordinate of the principal point.

     \param xp x coordinate of the principal point (milimeters).
    */
    void setXp(double xp);
    /*!
     \brief Sets y coordinate of the principal point.

     \param yp y coordinate of the principal point (milimeters).
    */
    void setYp(double yp);
    /*!
     \brief Sets the distortion model containing the distortion parameters.

     \param model distortion model.
    */
    void setDistortionModel(DistortionModel *model);

    /*!
     \brief Undistort a image according to distortion model.

     \param inputImage image to undistort
     \return PWImage undistorted image
    */
    virtual QString undistort(QString inputImage);

    /*!
     \brief

     \return bool true if distortion model allows to undistort images.
    */
    virtual bool canUnistort();

    virtual void undistort(double& x,
                           double& y);

    virtual void distort(double& x,
                         double& y);

private:

    //********** TODO:  PROVISIONALMENTE USAMOS VALORES EN PIXELES ******************
    double   mFocal; /*!< Focal lenght (mm) */
    double   mXp; /*!< x coordinate of principal point (mm) */
    double   mYp; /*!< y coordinate of principal point (mm) */
    //********** TODO:  PROVISIONALMENTE USAMOS VALORES EN PIXELES ******************

    DistortionModel *mDistortionModel;
};

}

#endif // PHOTOGRAMMETRICMODEL_H
