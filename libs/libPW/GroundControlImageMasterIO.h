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
#ifndef GROUNDCONTROLIMAGEMASTERIO_H
#define GROUNDCONTROLIMAGEMASTERIO_H

#include "GroundControlIO.h"

namespace PW{
class LIBPWSHARED_EXPORT GroundControlImageMasterIO : public GroundControlIO
{
public:
    GroundControlImageMasterIO();

    virtual void read(QString url,
                      QList<PW::PW3dPoint> &groudPoints,
                      QMap<QString, QList<PW2dPoint *> *> &imagePoints);
    virtual QList<PW::PW3dPoint> readGroundPoinst(QString url);
    virtual QList<PW2dPoint *> readImagePoints(QString url);
    QMap<QString, QList<PW2dPoint *> *> readImagePointsByImage(QString url);

    virtual int writeGroudPoints(QString url, QList<PW::PW3dPoint *> *points);
    virtual int writeImagePoints(QString url, QList<PWImage *> images);
};
}
#endif // GROUNDCONTROLIMAGEMASTERIO_H
