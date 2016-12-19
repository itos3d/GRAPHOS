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
#ifndef PSMARKERSIO_H
#define PSMARKERSIO_H

#include <QObject>

#include "Project.h"
#include "GroundControlIO.h"

namespace PW{

class LIBPWSHARED_EXPORT PSMarkersIO : public GroundControlIO
{
    Q_OBJECT
public:
    explicit PSMarkersIO();

    virtual void read(QString url,
                      QList<PW::PW3dPoint> &groudPoints,
                      QMap<QString, QList<PW2dPoint *> *> &imagePoints);
    virtual void read(QString url,
                      QMap<QString,QVector<double> > &groundPoints,
                      QMap<QString,QList<PW2dPoint *> *> &imagePoints);
    virtual QList<PW::PW3dPoint> readGroundPoinst(QString url);
    virtual bool readGroundPoinst(QString url,QMap<QString,QVector<double> >& points3D);
    virtual QList<PW2dPoint *> readImagePoints(QString url);
    virtual QMap<QString, QList<PW2dPoint *> *> readImagePointsByImage(QString url);

    virtual int writeGroudPoints(QString url, QList<PW::PW3dPoint *> *points);
    virtual int writeImagePoints(QString url, QList<PWImage *> images);
    
signals:
    
public slots:
    
};
}

#endif // PSMARKERSIO_H
