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
#ifndef FRASERMODEL_H
#define FRASERMODEL_H

#include "DistortionModel.h"


namespace PW{

class LIBPWSHARED_EXPORT FraserModel : public DistortionModel
{
public:
    FraserModel();

    int getID();

    /*!
     \brief Gets the first radial distotion coefficient.

     \return double coefficient
    */
    double getK1();

    /*!
     \brief Gets the second radial distotion coefficient.

     \return double coefficient
    */
    double getK2();

    /*!
     \brief Gets the third radial distotion coefficient.

     \return double coefficient
    */
    double getK3();

    /*!
     \brief Gets the first decentering coefficient.

     \return double coefficient
    */
    double getP1();

    /*!
     \brief Gets the second decentering coefficient.

     \return double coefficient
    */
    double getP2();

    /*!
     \brief Gets the first radial distotion coefficient.

     \return double coefficient
    */
    double getB1();

    /*!
     \brief Gets the second affine coefficient.

     \return double coefficient
    */
    double getB2();

    /*!
     \brief Sets the first affine coefficient.

     \param k1 coefficient
    */
    void setK1(double k1);

    /*!
     \brief Sets the second radial distotion coefficient.

     \param k2 coefficient
    */
    void setK2(double k2);

    /*!
     \brief Sets the third radial distotion coefficient.

     \param k3 coefficient
    */
    void setK3(double k3);

    /*!
     \brief Sets the first decentering coefficient.

     \param p1 coefficient
    */
    void setP1(double p1);

    /*!
     \brief Sets the second decentering coefficient.

     \param p2 coefficient
    */
    void setP2(double p2);

    /*!
     \brief Sets the first affine coefficient.

     \param b1 coefficient
    */
    void setB1(double b1);

    /*!
     \brief Sets the scond affine coefficient.

     \param b2 coefficient
    */
    void setB2(double b2);

    /*!
     \brief Gets the x coordinate of distortion center in pixel

     \return double
    */
    double getXcd();
    /*!
     \brief Gets the y coordinate of distortion center in pixel

     \return double
    */
    double getYcd();

    /*!
     \brief Sets the x coordinate of distortion center in pixel

     \param xcd
    */
    void setXcd(double xcd);

    /*!
     \brief Sets the y coordinate of distortion center in pixel

     \param ycd
    */
    void setYcd(double ycd);

    /*!
     \brief

     \return bool true if PP is equal CD (Fraser Basic).
    */
    bool isBasic();

    /*!
     \brief

     \param Fraser basic
    */
    void setBasic(bool basic);


    /********************TODO: ¿sacar de aquí? ***********************/
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
    /********************TODO: ¿sacar de aquí? ***********************/

    virtual void undistort(double xpp, double ypp, double &x, double &y);

    virtual void distort(double xpp, double ypp,double& x,double& y);

private:

    double mK1;
    double mK2;
    double mK3;
    double mP1;
    double mP2;
    double mB1;
    double mB2;

    bool mBasic;
    double mXcd; /*!< mm */
    double mYcd; /*!< mm */
};
}

#endif // FRASERMODEL_H
