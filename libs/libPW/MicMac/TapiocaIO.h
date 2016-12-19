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
#ifndef APEROMATCHINGIO_H
#define APEROMATCHINGIO_H

#include <QMap>
#include "ImageMatching.h"
#include "PW2dPoint.h"

namespace PW{

class LIBPWSHARED_EXPORT  TapiocaIO
{
public:
    TapiocaIO();

    int write(QMap<QString, QPointF> *matching, QString url);
    int writeFromControlPoints(QList<PW2dPoint *> *pointListA, QList<PW2dPoint *> *pointListB, QString url);

    int readImagePairs(QString homolPath, QMap<QString, QVector<QString> > &imagePairs);

};

}

#endif // APEROMATCHINGIO_H
