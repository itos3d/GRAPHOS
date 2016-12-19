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
#include "GCPWriter.h"
//#include "GeorefMicMac/GCP.h".
#include "PW3dPoint.h"
#include <QFile>
using namespace PW;

GCPWriter::GCPWriter(QList<PW3dPoint *> *GCPs,QString outputPath):mGCPs(GCPs),mOutputPath(outputPath)
{

}

GCPWriter::~GCPWriter()
{

}

void GCPWriter::run()
{

    QString stdTemplate ="<OneAppuisDAF><Pt>_X_Coord_ _Y_Coord_ _Z_Coord_</Pt><NamePt>_Desc_</NamePt><Incertitude>1 1 1</Incertitude></OneAppuisDAF>";
    /* Try and open a file for output */
      QFile outputFile(mOutputPath);
      outputFile.open(QIODevice::WriteOnly);

      /* Check it opened OK */
      if(!outputFile.isOpen()){
//          qDebug() << argv[0] << "- Error, unable to open" << outputFilename << "for output";
          return;
      }

      /* Point a QTextStream object at the file */
      QTextStream outStream(&outputFile);

      //Write xml header
      outStream << "<?xml version=\"1.0\" ?> <DicoAppuisFlottant>";
      for (int i = 0; i < mGCPs->count(); ++i) {
          /* Write the line to the file */
          QString outputString =stdTemplate;
          PW3dPoint *gcpToEvaluate = mGCPs->at(i);
          outputString.replace("_X_Coord_",QString::number(gcpToEvaluate->getCoord(0),'f',-1));
          outputString.replace("_Y_Coord_",QString::number(gcpToEvaluate->getCoord(1),'f',-1));
          outputString.replace("_Z_Coord_",QString::number(gcpToEvaluate->getCoord(2),'f',-1));
          outputString.replace("_Desc_",gcpToEvaluate->getName());

          outStream << outputString;
      }

      //Write footer
    outStream << "</DicoAppuisFlottant>";

    /* Close the file */
    outputFile.close();


}
