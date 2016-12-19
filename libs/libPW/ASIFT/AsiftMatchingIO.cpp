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
#include <QString>
#include <QFile>
#include <QStringList>

#include "AsiftMatchingIO.h"

using namespace PW;

AsiftMatchingIO::AsiftMatchingIO()
{
}

void AsiftMatchingIO::read(QString url, QMap<QString, QPointF> *matching, QMap<QString, QPointF> *inverseMatching)
{
    QFile file(url);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        file.readLine(); //first line: nº of matchings
        while (!file.atEnd()) {
            QString line = file.readLine();
            QStringList splitedLine = line.simplified().split(" ");
            if(splitedLine.count() == 4){
                if(!matching->contains(splitedLine.at(0)+" "+splitedLine.at(1)) &&
                        !inverseMatching->contains(splitedLine.at(2)+" "+splitedLine.at(3))){
                    QPointF point(splitedLine.at(2).toFloat(),splitedLine.at(3).toFloat());
                    matching->insert(splitedLine.at(0)+" "+splitedLine.at(1),point);

                    QPointF inversePoint(splitedLine.at(0).toFloat(),splitedLine.at(1).toFloat());
                    inverseMatching->insert(splitedLine.at(2)+" "+splitedLine.at(3),inversePoint);
                }
            }
        }
    }
}

void AsiftMatchingIO::read(QString url, QMap<QString, QPointF> *matching)
{
    QFile file(url);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        file.readLine(); //first line: nº of matchings
        while (!file.atEnd()) {
            QString line = file.readLine();
            QStringList splitedLine = line.simplified().split(" ");
            if(splitedLine.count() == 4){
                if(!matching->contains(splitedLine.at(0)+" "+splitedLine.at(1))){
                    QPointF point(splitedLine.at(2).toFloat(),splitedLine.at(3).toFloat());
                    matching->insert(splitedLine.at(0)+" "+splitedLine.at(1),point);
                }
            }
        }
    }
}
