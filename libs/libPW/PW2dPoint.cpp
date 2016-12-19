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

#include "PW2dPoint.h"

using namespace PW;

PW2dPoint::PW2dPoint(PWPoint::PointType type):
    PWPoint(type)
{
}

PW2dPoint::PW2dPoint(double x, double y, QString name, PWPoint::PointType type):
    PWPoint(type, name),
    QPointF(x, y)
{

}

int PW::PW2dPoint::getCoordsCount()
{
    return 2;
}

double PW::PW2dPoint::getCoord(int index)
{
    if(index>=0 && index <2){
        switch(index){
        case 0:
            return x();
            break;
        case 1:
            return y();
            break;
        default:
            qCritical() << "Index out of bounds";
            return 0;

        }
    }
    qCritical() << "Index out of bounds";
    return 0;
}

QPointF PW2dPoint::getPoint()
{
    return QPointF(x(),y());
}

void PW::PW2dPoint::setCoord(int index, double value)
{
    if(index>=0 && index <2){
        switch(index){
        case 0:
            setX(value);
            break;
        case 1:
            setY(value);
            break;
        default:
            qCritical() << "Index out of bounds";
        }
    }
    else
        qCritical() << "Index out of bounds";
}


