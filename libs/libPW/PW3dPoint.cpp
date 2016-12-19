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
#include <QDebug>

#include "PW3dPoint.h"

using namespace PW;

PW3dPoint::PW3dPoint():
    PWPoint(PWPoint::Control, ""),
    QVector3D(0.0,0.0,0.0)
{
}

PW3dPoint::PW3dPoint(double x, double y, double z, QString name, PWPoint::PointType type):
    PWPoint(type, name),
    QVector3D((double)x,(double)y,(double)z)
{
}

int PW::PW3dPoint::getCoordsCount()
{
    return 3;
}

double PW::PW3dPoint::getCoord(int index)
{
    if(index>=0 && index <3){
        switch(index){
        case 0:
            return x();
            break;
        case 1:
            return y();
            break;
        case 2:
            return z();
            break;
        default:
            qCritical() << "Index out of bounds";
            return 0;

        }
    }
    return 0;
}

void PW::PW3dPoint::setCoord(int index, double value)
{
    if(index>=0 && index <3){
        switch(index){
        case 0:
            setX(value);
            break;
        case 1:
            setY(value);
            break;
        case 2:
            setZ(value);
            break;
        default:
            qCritical() << "Index out of bounds";
        }
    }else
        qCritical() << "Index out of bounds";
}
