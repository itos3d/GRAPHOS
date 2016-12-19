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
#ifndef TIEPOINTSIO_H
#define TIEPOINTSIO_H

#define TIEPOINTSIO_ERROR       1
#define TIEPOINTSIO_NO_ERROR    0

#include "libPW_global.h"
#include <QStringList>
#include <QMap>
#include <QVector>

namespace PW{

//TODO: Documentar: formatos de ficheros que lee y escribe.
class LIBPWSHARED_EXPORT TiePointsIO
{
public:
    TiePointsIO();

    static int mergeTiePointsResults(QStringList inputPaths, QString outputPath, bool removeDuplicates=false);
    static int readTiePointsFile(QString& url,
                                 QVector<double>& firstImagePixelsColumn,
                                 QVector<double>& firstImagePixelsRow,
                                 QVector<double> &secondImagePixelsColumn,
                                 QVector<double> &secondImagePixelsRow,
                                 QString &strError);
    static int writeHomol(QString &homolPath,
                              QMap<QString,QVector<QString> >& imagesIdsTiePoints,
                              QMap<QString, QMap<QString, QVector<double> > > &imagesFirstColumnsTiePoints,
                              QMap<QString, QMap<QString, QVector<double> > > &imagesFirstRowsTiePoints,
                              QMap<QString, QMap<QString, QVector<double> > > &imagesSecondColumnsTiePoints,
                              QMap<QString, QMap<QString, QVector<double> > > &imagesSecondRowsTiePoints,
                              QString &strError,
                              bool binaryFormat);
    static int writeHomolOrtoSky(QString &homolPath,
                                 QMap<QString, QString>& imageFileNameWithoutPathsByName,
                                 QMap<QString,QVector<QString> >& imagesIdsTiePoints,
                                 QMap<QString, QMap<QString, QVector<double> > > &imagesFirstColumnsTiePoints,
                                 QMap<QString, QMap<QString, QVector<double> > > &imagesFirstRowsTiePoints,
                                 QMap<QString, QMap<QString, QVector<double> > > &imagesSecondColumnsTiePoints,
                                 QMap<QString, QMap<QString, QVector<double> > > &imagesSecondRowsTiePoints,
                                 QString &strError);
    static int writeHomolOrtoSky(QString &homolPath,
                                 QMap<QString, QString>& imageFileNameWithoutPathsByName,
                                 QMap<QString,QVector<QString> >& imagesIdsTiePoints,
                                 QMap<QString,QMap<QString,QVector<bool> > >& imagesEnabledsTiePoints,
                                 QMap<QString, QMap<QString, QVector<double> > > &imagesFirstColumnsTiePoints,
                                 QMap<QString, QMap<QString, QVector<double> > > &imagesFirstRowsTiePoints,
                                 QMap<QString, QMap<QString, QVector<double> > > &imagesSecondColumnsTiePoints,
                                 QMap<QString, QMap<QString, QVector<double> > > &imagesSecondRowsTiePoints,
                                 QString &strError);
    static int WriteDatTiePoints(QString& url,
                                 QVector<double>& firstImagePixelsColumn,
                                 QVector<double>& firstImagePixelsRow,
                                 QVector<double> &secondImagePixelsColumn,
                                 QVector<double> &secondImagePixelsRow,
                                 QString &strError);
private:
    static int removeDuplicateLines(QString filePath);
};
}
#endif // TIEPOINTSIO_H
