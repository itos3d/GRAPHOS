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
#include "PhotogrammetricModel.h"

using namespace PW;

PhotogrammetricModel::PhotogrammetricModel()
{
}

PhotogrammetricModel::~PhotogrammetricModel(){
    delete mDistortionModel;
}

double PhotogrammetricModel::getFocal(){
    return mFocal;
}

double PhotogrammetricModel::getXp(){
    return mXp;
}

double PhotogrammetricModel::getYp(){
    return mYp;
}

DistortionModel * PhotogrammetricModel::getDistortionModel()
{
    return mDistortionModel;
}

void PhotogrammetricModel::setFocal(double f){
    mFocal = f;
}

void PhotogrammetricModel::setXp(double xp){
    mXp = xp;
}

void PhotogrammetricModel::setYp(double yp){
    mYp = yp;
}

void PhotogrammetricModel::setDistortionModel(DistortionModel *model)
{
    mDistortionModel = model;
}

QString PhotogrammetricModel::undistort(QString inputImage)
{
    return mDistortionModel->undistort(inputImage,mFocal,mXp,mYp);
}

bool PhotogrammetricModel::canUnistort()
{
    return mDistortionModel->canUnistort();
}

void PhotogrammetricModel::undistort(double &x, double &y)
{
    mDistortionModel->undistort(mXp,mYp,x,y);
}

void PhotogrammetricModel::distort(double &x, double &y)
{
    mDistortionModel->distort(mXp,mYp,x,y);
}
