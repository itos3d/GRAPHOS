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
#ifndef IMAGEPAIRSFILEIO_H
#define IMAGEPAIRSFILEIO_H

#include "libPW_global.h"
#include <QMap>
#include <QString>
#include <QVector>

#define IMAGEPAIRSFILEIO_NO_ERROR               0
#define IMAGEPAIRSFILEIO_ERROR                  1
#define IMAGEPAIRSFILEIO_DUPLICATE_REVERSE      1

namespace PW{

class LIBPWSHARED_EXPORT ImagePairsFileIO
{
public:
    ImagePairsFileIO();
    ImagePairsFileIO(QMap<QString,QVector<QString> >& imagePairs);
    int getImagePairs(QMap<QString,QVector<QString> >& imagePairs);
    int readStandarAsciiFile(QString url);
//    int readXmlFile(QString url);
    int writeTapiocaPairsFile(QString url, int duplicateReverse);
    int writeStandarAsciiPairsFile(QString url, int duplicateReverse);

private:
    QMap<QString,QVector<QString> > mImagePairs;
};

}
#endif // IMAGEPAIRSFILEIO_H
