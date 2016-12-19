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
#include <QTextStream>
#include <QDir>

#include "TapiocaIO.h"
#include "PW2dPoint.h"
#include "libPW.h"

using namespace PW;

TapiocaIO::TapiocaIO()
{
}

int TapiocaIO::write(QMap<QString, QPointF> *matching, QString url)
{
    QFile file(url);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    QMap<QString, QPointF>::iterator i;
    for (i = matching->begin(); i != matching->end(); ++i){
        QPointF point = i.value();
        out << i.key() + " " + QString::number(point.x()) + " " + QString::number(point.y()) << "\n";
    }

    return 0;
}

int TapiocaIO::writeFromControlPoints(QList<PW2dPoint *> *pointListA,
                                            QList<PW2dPoint *> *pointListB,
                                            QString url)
{
    QFile file(url);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);

    QMap<QString, QPointF> bMap;
    // Mapping B List:
    for(int i = 0; i<pointListB->count(); i++){
        bMap.insert(pointListB->at(i)->getName(), pointListB->at(i)->getPoint());
    }

    int matchesCount = 0;
    for(int i = 0; i<pointListA->count(); i++){
        QString pointName = pointListA->at(i)->getName();
        if (bMap.keys().contains(pointName)){

            out << QString::number(pointListA->at(i)->getCoord(0)) +
                   " " +
                   QString::number(pointListA->at(i)->getCoord(1)) +
                   " " +
                   QString::number(bMap.value(pointName).x()) +
                   " " +
                   QString::number(bMap.value(pointName).y()) << "\n";
            matchesCount++;
        }
    }
    if (matchesCount)
        return 0;
    else
        return 1;

}

int TapiocaIO::readImagePairs(QString homolPath, QMap<QString, QVector<QString> > &imagePairs)
{
    QDir input(homolPath);
    Q_FOREACH(QFileInfo infoA, input.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs)) {
        if (infoA.isDir()) {
            QVector<QString> imageVector;
            QDir imageDir(infoA.filePath());
            Q_FOREACH(QFileInfo infoB, imageDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files)) {
                if (infoB.isFile() && infoB.suffix().toLower() == "txt") {
                    imageVector.append(infoB.completeBaseName());
                }
            }
            imagePairs.insert(infoA.fileName().remove("Pastis"),imageVector);
        }
    }
    return 0;
}
