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

#include <QDir>
#include <QDomDocument>
#include <QDebug>

#include "PSMarkersIO.h"

using namespace PW;

PSMarkersIO::PSMarkersIO()
{
}

void PSMarkersIO::read(QString url,
                       QList<PW3dPoint> &groudPoints,
                       QMap<QString,QList<PW2dPoint *> *> &imagePoints)
{
    groudPoints = readGroundPoinst(url);
    imagePoints = readImagePointsByImage(url);
}

void PSMarkersIO::read(QString url,
                       QMap<QString,QVector<double> > &groundPoints,
                       QMap<QString,QList<PW2dPoint *> *> &imagePoints)
{
    readGroundPoinst(url,groundPoints);
    imagePoints = readImagePointsByImage(url);
}

QList<PW::PW3dPoint> PSMarkersIO::readGroundPoinst(QString url)
{
    QList<PW::PW3dPoint> points3D;

    QDomDocument domDocument;

    QString errorStr;
    int errorLine;
    int errorColumn;

    QIODevice *device = new QFile(url);
    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn)) {
        qCritical() << tr("Parse error at line %1, column %2:\n%3")
                    .arg(errorLine)
                    .arg(errorColumn)
                    .arg(errorStr);
        return points3D;
    }

    QDomElement root = domDocument.documentElement();

    if (root.tagName() != "document") {
        qCritical() << tr("The file is not an PS Markers file (1)");
        return points3D;
    }

    root = root.firstChildElement("chunk");
    if (root.tagName() != "chunk") {
        qCritical() << tr("The file is not an PS Markers file (2)");
        return points3D;
    }

    //-------------- Markers: -------------------------------
    QDomElement markers = root.firstChildElement("markers");
    if (markers.tagName() != "markers") {
        qCritical() << tr("The file is not an PS Markers file (5)");
        return points3D;
    }

    QDomElement marker = markers.firstChildElement("marker");
    if (marker.tagName() != "marker") {
        qCritical() << tr("The file is not an PS Markers file (6)");
        return points3D;
    }
    while (marker.tagName()=="marker"){
        QDomElement reference = marker.firstChildElement("reference");
        if(reference.attribute("enabled").compare("true",Qt::CaseInsensitive)==0){
            points3D.append(PW3dPoint(reference.attribute("x").toDouble(),
                                      reference.attribute("y").toDouble(),
                                      reference.attribute("z").toDouble(),
                                      marker.attribute("label")));
        }
        marker = marker.nextSiblingElement("marker");
    }

    return points3D;
}

bool PSMarkersIO::readGroundPoinst(QString url,
                                   QMap<QString,QVector<double> >& points3D)
{
    points3D.clear();
    QDomDocument domDocument;
    QString errorStr;
    int errorLine;
    int errorColumn;

    QIODevice *device = new QFile(url);
    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn)) {
        qCritical() << tr("Parse error at line %1, column %2:\n%3")
                    .arg(errorLine)
                    .arg(errorColumn)
                    .arg(errorStr);
        return(false);
    }

    QDomElement root = domDocument.documentElement();

    if (root.tagName() != "document") {
        qCritical() << tr("The file is not an PS Markers file (1)");
        return(false);
    }

    root = root.firstChildElement("chunk");
    if (root.tagName() != "chunk") {
        qCritical() << tr("The file is not an PS Markers file (2)");
        return(false);
    }

    //-------------- Markers: -------------------------------
    QDomElement markers = root.firstChildElement("markers");
    if (markers.tagName() != "markers") {
        qCritical() << tr("The file is not an PS Markers file (5)");
        return(false);
    }

    QDomElement marker = markers.firstChildElement("marker");
    if (marker.tagName() != "marker") {
        qCritical() << tr("The file is not an PS Markers file (6)");
        return(false);
    }
    while (marker.tagName()=="marker"){
        QDomElement reference = marker.firstChildElement("reference");
        if(reference.attribute("enabled").compare("true",Qt::CaseInsensitive)==0)
        {
            QString pointId=marker.attribute("label").trimmed();
//            if(pointId.contains(' '))
//            {
//                pointId.replace(' ','_');
//            }
            if(!points3D.contains(pointId))
            {
                QVector<double> coordinates(3);
                coordinates[0]=reference.attribute("x").toDouble();
                coordinates[1]=reference.attribute("y").toDouble();
                coordinates[2]=reference.attribute("z").toDouble();
                points3D[pointId]=coordinates;
            }
        }
        marker = marker.nextSiblingElement("marker");
    }
    return(true);
}

QList<PW2dPoint *> PSMarkersIO::readImagePoints(QString url)
{
    QList<PW2dPoint *> list;
    return list;
}

QMap<QString, QList<PW2dPoint *> *> PSMarkersIO::readImagePointsByImage(QString url)
{
    QMap<QString, QList<PW2dPoint *> *> points;

    QDomDocument domDocument;

    QString errorStr;
    int errorLine;
    int errorColumn;

    QIODevice *device = new QFile(url);
    if (!domDocument.setContent(device, true, &errorStr, &errorLine,
                                &errorColumn)) {
        qCritical() << tr("Parse error at line %1, column %2:\n%3")
                    .arg(errorLine)
                    .arg(errorColumn)
                    .arg(errorStr);
        return points;
    }

    QMap<QString, QString> imageIDs;

    QDomElement root = domDocument.documentElement();

    if (root.tagName() != "document") {
        qCritical() << tr("The file is not an PS Markers file (1)");
        return points;
    }

    root = root.firstChildElement("chunk");
    if (root.tagName() != "chunk") {
        qCritical() << tr("The file is not an PS Markers file (2)");
        return points;
    }

    //-------------- Cameras IDs: -------------------------------
    QDomElement cameras = root.firstChildElement("cameras");
    if (cameras.tagName() != "cameras") {
        qCritical() << tr("The file is not an PS Markers file (3)");
        return points;
    }

    QDomElement child = cameras.firstChildElement("camera");
    if (child.tagName() != "camera") {
        qCritical() << tr("The file is not an PS Markers file (4)");
        return points;
    }
    while (child.tagName()=="camera"){
        imageIDs.insert(child.attribute("id") ,child.attribute("label"));
        child = child.nextSiblingElement("camera");
    }

    //-------------- Markers Labels: -------------------------------
    QMap<QString,QString> markersLabels;
    QDomElement markers = root.firstChildElement("markers");
    if (markers.tagName() != "markers") {
        qCritical() << tr("The file is not an PS Markers file (5)");
        return points;
    }

    QDomElement marker = markers.firstChildElement("marker");
    if (marker.tagName() != "marker") {
        qCritical() << tr("The file is not an PS Markers file (6)");
        return points;
    }
    while (marker.tagName()=="marker"){
        markersLabels.insert(marker.attribute("id"),marker.attribute("label"));
        marker = marker.nextSiblingElement("marker");
    }

    //-------------- Markers: -------------------------------
    markers = root.firstChildElement("frames");
    if (cameras.tagName() != "cameras") {
        qCritical() << tr("The file is not an PS Markers file (5)");
        return points;
    }
    markers = markers.firstChildElement("frame");
    if (cameras.tagName() != "cameras") {
        qCritical() << tr("The file is not an PS Markers file (5)");
        return points;
    }

    markers = markers.firstChildElement("markers");
    if (cameras.tagName() != "cameras") {
        qCritical() << tr("The file is not an PS Markers file (5)");
        return points;
    }

    marker = markers.firstChildElement("marker");
    if (marker.tagName() != "marker") {
        qCritical() << tr("The file is not an PS Markers file (6)");
        return points;
    }
    while (marker.tagName()=="marker"){
        QDomElement location = marker.firstChildElement("location");
        while (location.tagName()=="location"){
            if(location.attribute("pinned").compare("true",Qt::CaseInsensitive)==0){
                QString imageLabel = imageIDs.value(location.attribute("camera_id"));
                if (!points.contains(imageLabel))
                    points.insert(imageLabel,new QList<PW2dPoint *>());
                points.value(imageLabel)->append(new PW2dPoint(location.attribute("x").toDouble(),
                                                               location.attribute("y").toDouble(),
                                                               //                                                          marker.attribute("label")));
                                                               //                                                           marker.attribute("marker_id")));
                                                               markersLabels.value(marker.attribute("marker_id"))));
            }
            location = location.nextSiblingElement("location");
        }
        marker = marker.nextSiblingElement("marker");
    }

    return points;
}

int PSMarkersIO::writeGroudPoints(QString url, QList<PW3dPoint *> *points)
{
    return 1;
}

int PSMarkersIO::writeImagePoints(QString url, QList<PWImage *> images)
{
    return 1;
}
