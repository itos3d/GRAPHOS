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
#ifndef FISHEYEMODEL_H
#define FISHEYEMODEL_H

#include <DistortionModel.h>
#include <QVector>

namespace PW{


class LIBPWSHARED_EXPORT FishEyeModel : public DistortionModel
{
public:
    FishEyeModel();

    int getID();

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

    double getParam(int index);

    int getParamsCount();

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

    void setParam(int index, double value);
    void addParam(double value);


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
    virtual void distort(double xpp, double ypp, double &x, double &y);

private:
    double mXcd;
    double mYcd;
    QVector<double> mParams;

};

}

#endif // FISHEYEMODEL_H
