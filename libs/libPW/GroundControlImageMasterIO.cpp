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
#include <QFile>
#include <QDir>
#include <QStringList>
#include <QTextStream>

#include "GroundControlImageMasterIO.h"

using namespace PW;

GroundControlImageMasterIO::GroundControlImageMasterIO()
{
}

void GroundControlImageMasterIO::read(QString url, QList<PW3dPoint> &groudPoints, QMap<QString, QList<PW2dPoint *> *> &imagePoints)
{

}

QList<PW::PW3dPoint> GroundControlImageMasterIO::readGroundPoinst(QString url)
{
    QList<PW::PW3dPoint> result;
    return result;
}

QList<PW2dPoint *> GroundControlImageMasterIO::readImagePoints(QString url)
{
    QFile file(url);
    QList<PW2dPoint *> points;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        bool ok;
        file.readLine();
        file.readLine();
        QString line = file.readLine();
        int lines = line.simplified().toInt();
        for(int i=0; i<lines; i++) {
            QString line = file.readLine();
            QStringList splitedLine = line.simplified().split(" ");
            if(splitedLine.count() >= 3){
                points.append(new PW2dPoint(splitedLine.at(1).toDouble(&ok),
                                            splitedLine.at(2).toDouble(&ok),
                                            splitedLine.at(0)));
            }
            else ok = false;
            if(!ok){
                points.clear();
                return points;
            }
        }
    }
    return points;
}

QMap<QString, QList<PW2dPoint *> *> GroundControlImageMasterIO::readImagePointsByImage(QString url)
{
    //TODO: Por implementar
    QMap<QString, QList<PW2dPoint *> *> points;
    return points;
}

int GroundControlImageMasterIO::writeGroudPoints(QString url, QList<PW::PW3dPoint *> *points)
{
    return 1;
}

int GroundControlImageMasterIO::writeImagePoints(QString url, QList<PWImage *> images)
{
    return 1;
}
