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
#include <QTextOStream>

#include "AppuisWriter.h"

using namespace PW;
AppuisWriter::AppuisWriter()
{
}

int PW::AppuisWriter::writeDicoAppuis(Project *project, QString url)
{
    QFile file(url);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << "<?xml version=\"1.0\" ?> \n";
    out << "<Global>\n";
    out << "\t<DicoAppuisFlottant>\n";

    QList<PW3dPoint *> *controlPoints = project->getModelCPoints();
    for(int i= 0; i<controlPoints->count(); i++){
        PW3dPoint *point =  controlPoints->at(i);
        if(point->getCoord(0) != 0 || point->getCoord(1) != 0 || point->getCoord(2) != 0){
            out << "\t\t<OneAppuisDAF>\n";
            out << "\t\t\t<Pt>    " << QString::number(controlPoints->at(i)->getCoord(0),'f',5) << "    " <<
                   QString::number(controlPoints->at(i)->getCoord(1),'f',5) << "    " <<
                   QString::number(controlPoints->at(i)->getCoord(2),'f',5) << "</Pt>\n";
            out << "\t\t\t<NamePt>" << "    " << controlPoints->at(i)->getName() << "</NamePt>\n";
            out << "\t\t\t<Incertitude>       0.002       0.002       0.002</Incertitude>\n";  //******************TODO; Parametrizar.***********************
            out << "\t\t</OneAppuisDAF>\n";
        }
    }

    out << "\t</DicoAppuisFlottant>\n";
    out << "</Global>";

    return 0;
}

int PW::AppuisWriter::writeMesureAppuis(Project *project, QString url)
{
    //Mapping zerro model points:
    QList<PW3dPoint *> *controlPoints = project->getModelCPoints();
    QMap<QString, PW3dPoint *> zeroPoints;
    for(int i= 0; i<controlPoints->count(); i++){
        PW3dPoint *point =  controlPoints->at(i);
        if(point->getCoord(0) == 0 && point->getCoord(1) == 0 && point->getCoord(2) == 0){
            zeroPoints.insert(point->getName(),point);
        }
    }

    QFile file(url);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << "<?xml version=\"1.0\" ?> \n";
    out << "<SetOfMesureAppuisFlottants>\n";
    QList<PW::PWImage *> images = project->getImages();
    for (int i = 0; i< images.count(); i++){
        out << "\t<MesureAppuiFlottant1Im>\n";
        out << "\t\t<NameIm>" << images.at(i)->getFileName() << "</NameIm>\n";
        for (int p = 0; p< images.at(i)->getControlPoints()->count(); p++){
            if(!zeroPoints.contains(images.at(i)->getControlPoints()->at(p)->getName())){
                out << "\t\t\t<OneMesureAF1I>\n";
                out << "\t\t\t\t<NamePt>" << images.at(i)->getControlPoints()->at(p)->getName() << "</NamePt>\n";
                out << "\t\t\t\t<PtIm> " << images.at(i)->getControlPoints()->at(p)->getCoord(0) <<
                       " "<< images.at(i)->getControlPoints()->at(p)->getCoord(1) << "</PtIm>\n";
                out << "\t\t\t</OneMesureAF1I>\n";
            }
        }
        out << "\t</MesureAppuiFlottant1Im>\n";
    }
    out << "</SetOfMesureAppuisFlottants>";

    return 0;
}

int AppuisWriter::write(QList<PW3dPoint> groudPoints,
                        QMap<QString, QList<PW2dPoint *> *> imagePoints,
                        QString dicoAppuisUrl,
                        QString MesureAppuisUrl,QVector<PW3dPoint *> *ptrControlPointsAccuracies)
{
    QFile fileDico(dicoAppuisUrl);
    fileDico.open(QIODevice::WriteOnly);
    QTextStream outDico(&fileDico);
    outDico << "<?xml version=\"1.0\" ?> \n";
    outDico << "<Global>\n";
    outDico << "\t<DicoAppuisFlottant>\n";

    for(int i= 0; i<groudPoints.count(); i++){
        PW3dPoint point =  groudPoints.at(i);

        QString pointId=point.getName();
        double x=point.getCoord(0);
        double y=point.getCoord(1);
        double z=point.getCoord(2);
        double stdX=0.02;
        double stdY=0.02;
        double stdZ=0.02;

        if(ptrControlPointsAccuracies!=NULL)
        {
            PW3dPoint *pointAccuracy=NULL;
            for(int i= 0; i<ptrControlPointsAccuracies->count(); i++)
            {
                PW3dPoint *auxPointAccuracy =  ptrControlPointsAccuracies->at(i);
                QString pointAccuracyId=auxPointAccuracy->getName();
                if(pointAccuracyId.compare(pointId,Qt::CaseInsensitive)==0)
                {
                    pointAccuracy=auxPointAccuracy;
                }
            }
            if(pointAccuracy!=NULL)
            {
                stdX=pointAccuracy->getCoord(0);
                stdY=pointAccuracy->getCoord(1);
                stdZ=pointAccuracy->getCoord(2);
            }
        }

        if(point.getCoord(0) != 0 || point.getCoord(1) != 0 || point.getCoord(2) != 0){
            outDico << "\t\t<OneAppuisDAF>\n";
            outDico << "\t\t\t<Pt>    " <<
                       QString::number(x,'f',5) << "    " <<
                       QString::number(y,'f',5) << "    " <<
                       QString::number(z,'f',5) << "</Pt>\n";
            outDico << "\t\t\t<NamePt>" << "    " << point.getName() << "</NamePt>\n";
            outDico << "\t\t\t<Incertitude>";
            outDico << QString::number(stdX,'f',3).rightJustified(12);
            outDico << QString::number(stdY,'f',3).rightJustified(12);
            outDico << QString::number(stdZ,'f',3).rightJustified(12);
            outDico <<"</Incertitude>\n";  //******************TODO; Parametrizar.***********************
            outDico << "\t\t</OneAppuisDAF>\n";
        }
    }

    outDico << "\t</DicoAppuisFlottant>\n";
    outDico << "</Global>";


    //Mapping zerro model points:
    QMap<QString, PW3dPoint> zeroPoints;
    for(int i= 0; i<groudPoints.count(); i++){
        PW3dPoint point =  groudPoints.at(i);
        if(point.getCoord(0) == 0 && point.getCoord(1) == 0 && point.getCoord(2) == 0){
            zeroPoints.insert(point.getName(),point);
        }
    }
    QFile fileMesure(MesureAppuisUrl);
    fileMesure.open(QIODevice::WriteOnly);
    QTextStream out(&fileMesure);
    out << "<?xml version=\"1.0\" ?> \n";
    out << "<SetOfMesureAppuisFlottants>\n";

    for (int i = 0; i< imagePoints.keys().count(); i++){
        out << "\t<MesureAppuiFlottant1Im>\n";
        out << "\t\t<NameIm>" << imagePoints.keys().at(i) << "</NameIm>\n";
        for (int p = 0; p< imagePoints.values().at(i)->count(); p++){
            if(!zeroPoints.contains(imagePoints.values().at(i)->at(p)->getName())){
                out << "\t\t\t<OneMesureAF1I>\n";
                out << "\t\t\t\t<NamePt>" << imagePoints.values().at(i)->at(p)->getName() << "</NamePt>\n";
                out << "\t\t\t\t<PtIm> " << imagePoints.values().at(i)->at(p)->getCoord(0) <<
                       " "<< imagePoints.values().at(i)->at(p)->getCoord(1) << "</PtIm>\n";
                out << "\t\t\t</OneMesureAF1I>\n";
            }
        }
        out << "\t</MesureAppuiFlottant1Im>\n";
    }
    out << "</SetOfMesureAppuisFlottants>";

    return 0;
}

int AppuisWriter::write(QMap<QString,QVector<double> >& groundPoints,
                        QMap<QString, QList<PW2dPoint *> *> imagePoints,
                        QString dicoAppuisUrl,
                        QString MesureAppuisUrl,QVector<PW3dPoint *> *ptrControlPointsAccuracies)
{
    QFile fileDico(dicoAppuisUrl);
    fileDico.open(QIODevice::WriteOnly);
    QTextStream outDico(&fileDico);
    outDico << "<?xml version=\"1.0\" ?> \n";
    outDico << "<Global>\n";
    outDico << "\t<DicoAppuisFlottant>\n";
    QMap<QString,QVector<double> >::const_iterator iterGroundPoints=groundPoints.begin();
    while(iterGroundPoints!=groundPoints.end())
    {
        QString pointId=iterGroundPoints.key();
        double x=iterGroundPoints.value()[0];
        double y=iterGroundPoints.value()[1];
        double z=iterGroundPoints.value()[2];
        double stdX=0.02;
        double stdY=0.02;
        double stdZ=0.02;

        if(ptrControlPointsAccuracies!=NULL)
        {
            PW3dPoint *pointAccuracy=NULL;
            for(int i= 0; i<ptrControlPointsAccuracies->count(); i++)
            {
                PW3dPoint *auxPointAccuracy =  ptrControlPointsAccuracies->at(i);
                QString pointAccuracyId=auxPointAccuracy->getName();
                if(pointAccuracyId.compare(pointId,Qt::CaseInsensitive)==0)
                {
                    pointAccuracy=auxPointAccuracy;
                }
            }
            if(pointAccuracy!=NULL)
            {
                stdX=pointAccuracy->getCoord(0);
                stdY=pointAccuracy->getCoord(1);
                stdZ=pointAccuracy->getCoord(2);
            }
        }

        // No entiendo esta condición
//        if(point.getCoord(0) != 0 || point.getCoord(1) != 0 || point.getCoord(2) != 0)
//        {
            outDico << "\t\t<OneAppuisDAF>\n";
            outDico << "\t\t\t<Pt>    " <<
                       QString::number(x,'f',5) << "    " <<
                       QString::number(y,'f',5) << "    " <<
                       QString::number(z,'f',5) << "</Pt>\n";
            outDico << "\t\t\t<NamePt>" << "    " << pointId << "</NamePt>\n";
            outDico << "\t\t\t<Incertitude>";
            outDico << QString::number(stdX,'f',3).rightJustified(12);
            outDico << QString::number(stdY,'f',3).rightJustified(12);
            outDico << QString::number(stdZ,'f',3).rightJustified(12);
            outDico <<"</Incertitude>\n";  //******************TODO; Parametrizar.***********************
            outDico << "\t\t</OneAppuisDAF>\n";
//        }
        iterGroundPoints++;
    }

    outDico << "\t</DicoAppuisFlottant>\n";
    outDico << "</Global>";

    // No entiendo esto
    //Mapping zerro model points:
    QMap<QString, PW3dPoint> zeroPoints;
//    for(int i= 0; i<groudPoints.count(); i++){
//        PW3dPoint point =  groudPoints.at(i);
//        if(point.getCoord(0) == 0 && point.getCoord(1) == 0 && point.getCoord(2) == 0){
//            zeroPoints.insert(point.getName(),point);
//        }
//    }
    QFile fileMesure(MesureAppuisUrl);
    fileMesure.open(QIODevice::WriteOnly);
    QTextStream out(&fileMesure);
    out << "<?xml version=\"1.0\" ?> \n";
    out << "<SetOfMesureAppuisFlottants>\n";

    for (int i = 0; i< imagePoints.keys().count(); i++){
        out << "\t<MesureAppuiFlottant1Im>\n";
        out << "\t\t<NameIm>" << imagePoints.keys().at(i) << "</NameIm>\n";
        for (int p = 0; p< imagePoints.values().at(i)->count(); p++){
            if(!zeroPoints.contains(imagePoints.values().at(i)->at(p)->getName())){
                out << "\t\t\t<OneMesureAF1I>\n";
                out << "\t\t\t\t<NamePt>" << imagePoints.values().at(i)->at(p)->getName() << "</NamePt>\n";
                out << "\t\t\t\t<PtIm> " << imagePoints.values().at(i)->at(p)->getCoord(0) <<
                       " "<< imagePoints.values().at(i)->at(p)->getCoord(1) << "</PtIm>\n";
                out << "\t\t\t</OneMesureAF1I>\n";
            }
        }
        out << "\t</MesureAppuiFlottant1Im>\n";
    }
    out << "</SetOfMesureAppuisFlottants>";

    return 0;
}

int PW::AppuisWriter::writeDicoAppuis(QString url,
                                      QVector<PW3dPoint *> controlPoints,
                                      QVector<PW3dPoint *> *ptrControlPointsAccuracies)
{
    if(controlPoints.size()==0)
        return 0;
    QFile file(url);
    file.open(QIODevice::WriteOnly);
    QTextStream out(&file);
    out << "<?xml version=\"1.0\" ?> \n";
    out << "<Global>\n";
    out << "\t<DicoAppuisFlottant>\n";
    for(int i= 0; i<controlPoints.count(); i++)
    {
        PW3dPoint *point =  controlPoints.at(i);
        QString pointId=point->getName();
        double x=point->getCoord(0);
        double y=point->getCoord(0);
        double z=point->getCoord(0);
        double stdX=0.02;
        double stdY=0.02;
        double stdZ=0.02;
        if(ptrControlPointsAccuracies!=NULL)
        {
            PW3dPoint *pointAccuracy=NULL;
            for(int i= 0; i<ptrControlPointsAccuracies->count(); i++)
            {
                PW3dPoint *auxPointAccuracy =  ptrControlPointsAccuracies->at(i);
                QString pointAccuracyId=auxPointAccuracy->getName();
                if(pointAccuracyId.compare(pointId,Qt::CaseInsensitive)==0)
                {
                    pointAccuracy=auxPointAccuracy;
                }
            }
            if(pointAccuracy!=NULL)
            {
                stdX=pointAccuracy->getCoord(0);
                stdY=pointAccuracy->getCoord(1);
                stdZ=pointAccuracy->getCoord(2);
            }
        }
        if(point->getCoord(0) != 0 || point->getCoord(1) != 0 || point->getCoord(2) != 0){
            out << "\t\t<OneAppuisDAF>\n";
            out << "\t\t\t<Pt>    " << QString::number(x,'f',5) << "    " <<
                   QString::number(y,'f',5) << "    " <<
                   QString::number(z,'f',5) << "</Pt>\n";
            out << "\t\t\t<NamePt>" << "    " << pointId << "</NamePt>\n";
//            out << "\t\t\t<Incertitude>       0.002       0.002       0.002</Incertitude>\n";  //******************TODO; Parametrizar.***********************
            out << "\t\t\t<Incertitude>";
            out << QString::number(stdX,'f',3).rightJustified(12);
            out << QString::number(stdY,'f',3).rightJustified(12);
            out << QString::number(stdZ,'f',3).rightJustified(12);
            out <<"</Incertitude>\n";  //******************TODO; Parametrizar.***********************
            out << "\t\t</OneAppuisDAF>\n";
        }
    }
    out << "\t</DicoAppuisFlottant>\n";
    out << "</Global>";
    return 0;
}
