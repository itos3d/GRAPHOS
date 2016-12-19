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
#include "TiePoint.h"

using namespace PW;

TiePoint::TiePoint(int id,
                   ImagePoint *firstImagePoint,
                   ImagePoint *secondImagePoint):
    mId(id)
{
    mImagePoints[firstImagePoint->imagePosition()]=firstImagePoint;
    mImagePoints[secondImagePoint->imagePosition()]=secondImagePoint;
    mIsValid=true;
}

bool TiePoint::addImagePoint(ImagePoint *imagePoint,
                             QString &strError)
{
    if(mImagePoints.contains(imagePoint->imagePosition()))
    {
        strError=QObject::tr("TiePoint::addImagePoint, duplicated image position %1")
                .arg(QString::number(imagePoint->imagePosition()));
        return(false);
    }
    mImagePoints[imagePoint->imagePosition()]=imagePoint;
    return(true);
}

bool TiePoint::containsImagePoint(int imagePosition,
                                  int column,
                                  int row)
{
    QMap<int,ImagePoint*> ::const_iterator iter=mImagePoints.begin();
    while(iter!=mImagePoints.end())
    {
        if(iter.key()==imagePosition)
        {
            if(column==iter.value()->column()
                    &&row==iter.value()->row())
            {
                return(true);
            }
        }
        iter++;
    }
    return(false);
}

bool TiePoint::containsImage(int imagePosition)
{
    QMap<int,ImagePoint*> ::const_iterator iter=mImagePoints.begin();
    while(iter!=mImagePoints.end())
    {
        if(iter.key()==imagePosition)
        {
            return(true);
        }
        iter++;
    }
    return(false);
}
