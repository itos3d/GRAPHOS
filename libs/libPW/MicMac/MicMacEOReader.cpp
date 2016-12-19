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
#include <QXmlSchema>
#include <QDir>
#include <QXmlSchemaValidator>
#include <QDomDocument>
#include <QDebug>

#include "MicMacEOReader.h"


using namespace PW;

MicMacEOReader::MicMacEOReader()
{
}

ExteriorOrientation * MicMacEOReader::read(QString filePath)
{
    ExteriorOrientation * externalOrientation = new ExteriorOrientation();

    QDomDocument domDocument;

    QString errorStr;
    int errorLine;
    int errorColumn;

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly))
    {
        qCritical() << tr("Error opening file %1")
                    .arg(filePath);
        return NULL;
    }
    if (!domDocument.setContent(&file, true, &errorStr, &errorLine,
                                 &errorColumn)) {
        qCritical() << tr("Parse error at line %1, column %2:\n%3")
                       .arg(errorLine)
                       .arg(errorColumn)
                       .arg(errorStr);
        file.close();
        return NULL;
    }
    file.close();

    QDomElement root = domDocument.documentElement();

    QDomNodeList aux = root.elementsByTagName("Centre");
    QDomNode centre;

    if (aux.count() > 0)
        centre = aux.at(0);
    else
        return NULL;

    QString centreText = centre.toElement().text();
    externalOrientation->setCP(QVector<double>() << centreText.split(" ").at(0).toDouble() <<
                                               centreText.split(" ").at(1).toDouble() <<
                                               centreText.split(" ").at(2).toDouble());

    aux = root.elementsByTagName("CodageMatr");
    QDomNode rotation;

    if (aux.count() > 0)
        rotation = aux.at(0);
    else
        return NULL;

    QVector<double> l1;
    l1 << rotation.firstChildElement("L1").text().split(" ").at(0).toDouble()
          << rotation.firstChildElement("L1").text().split(" ").at(1).toDouble()
             << rotation.firstChildElement("L1").text().split(" ").at(2).toDouble();
    QVector<double> l2;
    l2 << rotation.firstChildElement("L2").text().split(" ").at(0).toDouble()
          << rotation.firstChildElement("L2").text().split(" ").at(1).toDouble()
             << rotation.firstChildElement("L2").text().split(" ").at(2).toDouble();
    QVector<double> l3;
    l3 << rotation.firstChildElement("L3").text().split(" ").at(0).toDouble()
           << rotation.firstChildElement("L3").text().split(" ").at(1).toDouble()
               << rotation.firstChildElement("L3").text().split(" ").at(2).toDouble();
    externalOrientation->setR(QVector<QVector<double> >() << l1 << l2 << l3 );


    return externalOrientation;
}

ExteriorOrientation *MicMacEOReader::read(QDomElement &root)
{
    ExteriorOrientation * externalOrientation = new ExteriorOrientation();

    QDomNodeList aux = root.elementsByTagName("Centre");
    QDomNode centre;

    if (aux.count() > 0)
        centre = aux.at(0);
    else
        return NULL;

    QString centreText = centre.toElement().text();
    externalOrientation->setCP(QVector<double>() << centreText.split(" ").at(0).toDouble() <<
                                               centreText.split(" ").at(1).toDouble() <<
                                               centreText.split(" ").at(2).toDouble());

    aux = root.elementsByTagName("CodageMatr");
    QDomNode rotation;

    if (aux.count() > 0)
        rotation = aux.at(0);
    else
        return NULL;

    QVector<double> l1;
    l1 << rotation.firstChildElement("L1").text().split(" ").at(0).toDouble()
          << rotation.firstChildElement("L1").text().split(" ").at(1).toDouble()
             << rotation.firstChildElement("L1").text().split(" ").at(2).toDouble();
    QVector<double> l2;
    l2 << rotation.firstChildElement("L2").text().split(" ").at(0).toDouble()
          << rotation.firstChildElement("L2").text().split(" ").at(1).toDouble()
             << rotation.firstChildElement("L2").text().split(" ").at(2).toDouble();
    QVector<double> l3;
    l3 << rotation.firstChildElement("L3").text().split(" ").at(0).toDouble()
           << rotation.firstChildElement("L3").text().split(" ").at(1).toDouble()
               << rotation.firstChildElement("L3").text().split(" ").at(2).toDouble();
    externalOrientation->setR(QVector<QVector<double> >() << l1 << l2 << l3 );


    return externalOrientation;
}
