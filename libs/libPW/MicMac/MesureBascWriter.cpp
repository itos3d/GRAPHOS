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

#include "MesureBascWriter.h"

using namespace PW;


PW::MesureBascWriter::MesureBascWriter(PW::Project *project):
    mProject(project)
{
}

int PW::MesureBascWriter::write(QString url)
{
    QFile file(url);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << "<?xml version=\"1.0\" ?> \n";
    out << "<SetOfMesureAppuisFlottants> \n";

    out << "<MesureAppuiFlottant1Im> \n";
    out << "<NameIm>" << mProject->getOXImage()->getFileName() << "</NameIm> \n";
    out << "<OneMesureAF1I> \n";
    out << "<NamePt>Line1</NamePt> \n";
    out << "<PtIm>" << QString::number(mProject->getOX1().x()) << " " << QString::number(mProject->getOX1().y()) << "</PtIm> \n";
    out << "</OneMesureAF1I> \n";
    out << "<OneMesureAF1I> \n";
    out << "<NamePt>Line2</NamePt> \n";
    out << "<PtIm>" << QString::number(mProject->getOX2().x()) << " " << QString::number(mProject->getOX2().y()) << "</PtIm> \n";
    out << "</OneMesureAF1I> \n";
    out << "</MesureAppuiFlottant1Im> \n";

    out << "<MesureAppuiFlottant1Im> \n";
    out << "<NameIm>" << mProject->getOriginImage()->getFileName() << "</NameIm> \n";
    out << "<OneMesureAF1I> \n";
    out << "<NamePt>Origine</NamePt> \n";
    out << "<PtIm>" << QString::number(mProject->getOriginPoint().x()) << " " << QString::number(mProject->getOriginPoint().y()) << "</PtIm> \n";
    out << "</OneMesureAF1I> \n";
    out << "</MesureAppuiFlottant1Im> \n";

    out << "<MesureAppuiFlottant1Im> \n";
    out << "<NameIm>" << mProject->getScaleImageA()->getFileName() << "</NameIm> \n";
    out << "<OneMesureAF1I> \n";
    out << "<NamePt>Ech1</NamePt> \n";
    out << "<PtIm>" << QString::number(mProject->getScalePointA1().x()) << " " << QString::number(mProject->getScalePointA1().y()) << "</PtIm> \n";
    out << "</OneMesureAF1I> \n";
    out << "<OneMesureAF1I> \n";
    out << "<NamePt>Ech2</NamePt> \n";
    out << "<PtIm>" << QString::number(mProject->getScalePointA2().x()) << " " << QString::number(mProject->getScalePointA2().y()) << "</PtIm> \n";
    out << "</OneMesureAF1I> \n";
    out << "</MesureAppuiFlottant1Im> \n";

    out << "<MesureAppuiFlottant1Im> \n";
    out << "<NameIm>" << mProject->getScaleImageB()->getFileName() << "</NameIm> \n";
    out << "<OneMesureAF1I> \n";
    out << "<NamePt>Ech1</NamePt> \n";
    out << "<PtIm>" << QString::number(mProject->getScalePointB1().x()) << " " << QString::number(mProject->getScalePointB1().y()) << "</PtIm> \n";
    out << "</OneMesureAF1I> \n";
    out << "<OneMesureAF1I> \n";
    out << "<NamePt>Ech2</NamePt> \n";
    out << "<PtIm>" << QString::number(mProject->getScalePointB2().x()) << " " << QString::number(mProject->getScalePointB2().y()) << "</PtIm> \n";
    out << "</OneMesureAF1I> \n";
    out << "</MesureAppuiFlottant1Im> \n";

    out << "</SetOfMesureAppuisFlottants> \n";

    return 0;
}
