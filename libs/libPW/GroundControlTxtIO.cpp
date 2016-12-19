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

#include "GroundControlTxtIO.h"


using namespace PW;

GroundControlTxtIO::GroundControlTxtIO()
{
}

void GroundControlTxtIO::read(QString url, QList<PW3dPoint> &groudPoints, QMap<QString, QList<PW2dPoint *> *> &imagePoints)
{

}

QList<PW3dPoint> GroundControlTxtIO::readGroundPoinst(QString url)
{
    QFile file(url);
    QList<PW3dPoint> points;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        bool ok;
        while (!file.atEnd()) {
            QString line = file.readLine();
            QStringList splitedLine = line.simplified().split(" ");
            if(splitedLine.count() == 4)
                points.append(PW3dPoint(splitedLine.at(1).toDouble(&ok),
                                        splitedLine.at(2).toDouble(&ok),
                                        splitedLine.at(3).toDouble(&ok),
                                        splitedLine.at(0)));
            else ok = false;
            if(!ok){
                points.clear();
                return points;
            }
        }
    }
    return points;
}

int GroundControlTxtIO::writeGroudPoints(QString url, QList<PW3dPoint *> *points)
{
    QFile file(url);
    if(file.open(QIODevice::WriteOnly)){
        QTextStream out(&file);
        for (int i = 0; i < points->count(); i++){
            out << points->at(i)->getName() << " " <<
                   QString::number(points->at(i)->getCoord(0)) << " " <<
                   QString::number(points->at(i)->getCoord(1)) << " " <<
                   QString::number(points->at(i)->getCoord(2)) << "\n";
        }
        file.close();
        return 0;
    }
    return 1;
}

int GroundControlTxtIO::writeImagePoints(QString url, QList<PWImage *> images)
{
    QDir dir(url);
    if(dir.exists()){
        for (int i = 0; i < images.count(); i++){
            if(images.at(i)->getControlPoints()->count()>0){
                QString imageName = images.at(i)->getFileName();
                QString fileName = url+"/"+imageName+".txt";
                QFile file(fileName);
                if(file.open(QIODevice::WriteOnly)){
                    QTextStream out(&file);
                    for (int j = 0; j < images.at(i)->getControlPoints()->count(); j++){
                        out << images.at(i)->getControlPoints()->at(j)->getName() << " " <<
                               QString::number(images.at(i)->getControlPoints()->at(j)->getCoord(0)) << " " <<
                               QString::number(images.at(i)->getControlPoints()->at(j)->getCoord(1)) << "\n";
                    }
                    file.close();
                }
                else return 1;
            }
        }
        return 0;
    }
    return 1;
}

QList<PW2dPoint *> PW::GroundControlTxtIO::readImagePoints(QString url)
{
    QFile file(url);
    QList<PW2dPoint *> points;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        bool ok;
        while (!file.atEnd()) {
            QString line = file.readLine();
            QStringList splitedLine = line.simplified().split(" ");
            if(splitedLine.count() == 3){
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

QMap<QString, QList<PW2dPoint *> *> GroundControlTxtIO::readImagePointsByImage(QString url)
{
    //Por implementar
    QMap<QString, QList<PW2dPoint *> *> points;
    return points;
}
