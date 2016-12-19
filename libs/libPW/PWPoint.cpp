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
#include "PWPoint.h"

using namespace PW;

PWPoint::PWPoint(PointType type, QString name):
    mType(type),
    mName(name)
{
}

QList<PW::PWPoint *> PW::PWPoint::getAssociatedPoints()
{
    return mAssociatedPoints;
}

PW::PWPoint::PointType PW::PWPoint::getType()
{
    return mType;
}

QString PW::PWPoint::getName()
{
    return mName;
}

void PW::PWPoint::setName(QString name)
{
    mName = name;
}
