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
#include "imgPointWriter.h"
//#include "GeorefMicMac/imgPoint.h"
#include "PW2dPoint.h"
#include <QFile>
using namespace PW;

imgPointWriter::imgPointWriter(QMap<QString,QList<PW2dPoint *>*> *imagePoints,QString outputPath):mImagePoints(imagePoints),mOutputPath(outputPath)
{

}

imgPointWriter::~imgPointWriter()
{

}

void imgPointWriter::run()
{
    QString stdTemplate ="<OneMesureAF1I><NamePt>_Desc_</NamePt><PtIm>_X_Coord_ _Y_Coord_</PtIm></OneMesureAF1I>";

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
      outStream << "<?xml version=\"1.0\" ?><SetOfMesureAppuisFlottants>";
      QStringList mapKeys = mImagePoints->keys();
      foreach (QString key, mapKeys) {
          outStream << "<MesureAppuiFlottant1Im><NameIm>" <<key << "</NameIm>";
          QList<PW2dPoint*> *imgPointVect = mImagePoints->value(key);
          for (int i = 0; i < imgPointVect->count(); ++i) {
              /* Write the line to the file */
              QString outputString =stdTemplate;
              PW2dPoint *imgPtToEvaluate = imgPointVect->at(i);
              outputString.replace("_X_Coord_",QString::number(imgPtToEvaluate->getCoord(0)));
              outputString.replace("_Y_Coord_",QString::number(imgPtToEvaluate->getCoord(1)));
              outputString.replace("_Desc_",imgPtToEvaluate->getName());

              outStream << outputString;
          }

          outStream << "</MesureAppuiFlottant1Im>";
      }


      //Write footer
    outStream << "</SetOfMesureAppuisFlottants>";

    /* Close the file */
    outputFile.close();
}
