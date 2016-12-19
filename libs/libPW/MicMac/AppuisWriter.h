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
#ifndef APPUISWRITER_H
#define APPUISWRITER_H

#include "Project.h"

namespace PW{

class LIBPWSHARED_EXPORT AppuisWriter
{
public:
    AppuisWriter();

    int writeDicoAppuis(Project *project, QString url);
    int writeMesureAppuis(Project *project, QString url);

    int write(QList<PW::PW3dPoint> groudPoints,
              QMap<QString, QList<PW2dPoint *> *> imagePoints,
              QString dicoAppuisUrl,
              QString MesureAppuisUrl, QVector<PW3dPoint *> *ptrControlPointsAccuracies=NULL);
    int write(QMap<QString,QVector<double> >& groundPoints,
              QMap<QString, QList<PW2dPoint *> *> imagePoints,
              QString dicoAppuisUrl,
              QString MesureAppuisUrl,QVector<PW3dPoint *> *ptrControlPointsAccuracies);
    int writeDicoAppuis(QString url,
                        QVector<PW3dPoint *> controlPoints,
                        QVector<PW3dPoint *> *ptrControlPointsAccuracies);

};
}
#endif // APPUISWRITER_H
