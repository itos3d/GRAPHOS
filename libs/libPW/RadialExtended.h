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
#ifndef RADIALEXTENDED_H
#define RADIALEXTENDED_H

#include "RadialBasic.h"

namespace PW{


/*!
 \brief Class Representing extended radial distortion model, with 10degrees of freedom:
1 for focal length , 2 for principal point, 2 for distorsion center , 5 for coefficients
of radial distorsion (r3 , r5 . . . r11 );
*/
class LIBPWSHARED_EXPORT RadialExtended: public RadialBasic
{
public:
/*!
 \brief

*/
    RadialExtended();

    int getID();

    /*!
     \brief Gets the x coordinate of distortion center in milimeters

     \return double
    */
    double getXcd();
    /*!
     \brief Gets the y coordinate of distortion center in milimeters

     \return double
    */
    double getYcd();
    /*!
     \brief Gets the third coefficient.

     \return double
    */
    double getK3();
    /*!
     \brief Gets the fourth coefficient.

     \return double
    */
    double getK4();
    /*!
     \brief Gets the fifth coefficient.

     \return double
    */
    double getK5();
    /*!
     \brief Sets the x coordinate of distortion center in milimeters

     \param xcd
    */
    void setXcd(double xcd);
    /*!
     \brief Sets the y coordinate of distortion center in milimeters

     \param ycd
    */
    void setYcd(double ycd);
    /*!
     \brief Sets the third coefficient.

     \param k3
    */
    void setK3(double k3);
    /*!
     \brief Sets the fourth coefficient.

     \param k4
    */
    void setK4(double k4);
    /*!
     \brief Sets the fifth coefficient.

     \param k5
    */
    void setK5(double k5);

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

private:
    double mXcd; /*!< mm */
    double mYcd; /*!< mm */

    double mK3;
    double mK4;
    double mK5;
};

}

#endif // RADIALEXTENDED_H
