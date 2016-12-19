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
#include "FishEyeModel.h"
#include <QVector>
#include <math.h>

using namespace PW;

FishEyeModel::FishEyeModel()
{
}

int FishEyeModel::getID()
{
    return APERO_MODEL_FISHEYE;
}

double FishEyeModel::getXcd()
{
    return mXcd;
}

double FishEyeModel::getYcd()
{
    return mYcd;
}

double FishEyeModel::getParam(int index)
{
    return mParams.at(index);
}

int FishEyeModel::getParamsCount()
{
    return mParams.count();
}

void FishEyeModel::setXcd(double xcd)
{
    mXcd = xcd;
}

void FishEyeModel::setYcd(double ycd)
{
    mYcd = ycd;
}

void FishEyeModel::setParam(int index, double value)
{
    mParams[index]=value;
}

void FishEyeModel::addParam(double value)
{
    mParams.append(value);
}

QString FishEyeModel::undistort(QString inputImage, double focal, double xpp, double ypp)
{
    QString outputPath;

    return outputPath;
}

bool FishEyeModel::canUnistort()
{
    return false;
}

void FishEyeModel::undistort(double xpp, double ypp, double &x, double &y)
{

}

void FishEyeModel::distort(double xpp, double ypp, double &x, double &y)
{

}
