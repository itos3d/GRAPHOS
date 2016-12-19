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
#ifndef RADIALBASIC_H
#define RADIALBASIC_H

#include "DistortionModel.h"

namespace PW{


/*!
 \brief Class Representing basic radial distortion model, with 5 degrees of freedom:
1 for focal length , 2 for principal point and distorsion center, 2 for coefficients of
radial distorsion (r3 and r5 );
*/

class LIBPWSHARED_EXPORT RadialBasic : public DistortionModel
{
public:
/*!
 \brief Constructor

*/
    RadialBasic();

    int getID();

    /*!
     \brief Gets the first coefficient.

     \return double coefficient
    */
    double getK1();
    /*!
     \brief Gets the second coefficient.

     \return double coefficient
    */
    double getK2();
    /*!
     \brief Sets the first coefficient.

     \param k1 coefficient
    */
    void setK1(double k1);
    /*!
     \brief Sets the second coefficient.

     \param k2 coefficient
    */
    void setK2(double k2);

    /*!
     \brief Undistort a image according to distortion model.

     \param inputImage image to undistort
     \return PWImage undistorted image
    */
    virtual QString undistort(QString inputImage, double focal, double xpp, double ypp);

    /*!
     \brief

     \return bool true if distortion model allows to undistort images.
    */
    virtual bool canUnistort();

    virtual void undistort(double xpp, double ypp, double &x, double &y);

    virtual void distort(double xpp, double ypp,double& x,double& y);

protected:

    double mK1;
    double mK2;
};

}

#endif // RADIALBASIC_H
