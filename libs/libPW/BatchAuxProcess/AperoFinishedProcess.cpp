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
#include "AperoFinishedProcess.h"
#include "TiePointsIO.h"
using namespace PW;

AperoFinishedProcess::AperoFinishedProcess(PW::Project *project,bool MatchestoDat,bool cleanOri):mProject(project),mMatchesToDat(MatchestoDat),mCleanOri(cleanOri)
{

}

AperoFinishedProcess::~AperoFinishedProcess()
{

}

void AperoFinishedProcess::run(){

    if (mCleanOri) {
        QDir projectPath(mProject->getBasePath());
        QStringList filters;
        filters << "Ori-*";
        QFileInfoList fileInfoList = projectPath.entryInfoList(filters,QDir::NoDotAndDotDot | QDir::Dirs);
        QFileInfo inputOriPathInfo(projectPath.absolutePath()+"/Ori-"+mProject->getCurrentOrientation());
        for (int i=0; i<fileInfoList.count();i++) {
            if( fileInfoList.at(i) != inputOriPathInfo )
                LibPW::removeDir(fileInfoList.at(i).absoluteFilePath());
        }
    }


    if (mMatchesToDat) {
        QDir homolDir(mProject->getBasePath()+"/Homol");
        if (homolDir.exists()) LibPW::removeDir(homolDir.absolutePath());
        QDir().mkdir(homolDir.absolutePath());

        QVector<double> firstImagePixelsColumn;
        QVector<double> firstImagePixelsRow;
        QVector<double> secondImagePixelsColumn;
        QVector<double> secondImagePixelsRow;
        QString error;
        QVector<QString> imageslist=mProject->getImagesFileName();
        foreach (QString imageName, imageslist) {
            QFileInfo imageFile(mProject->getBasePath()+imageName);
            QDir PastisDir(mProject->getBasePath()+"/Homol/Pastis"+imageName);
            if (!PastisDir.exists()) QDir().mkdir(PastisDir.absolutePath());

            QDir matchesDir(mProject->getBasePath()+"/Matches/"+mProject->getActiveTiePointsSet()+"/Pastis"+imageName);
            QDirIterator it(matchesDir.absolutePath(), QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
            while (it.hasNext()) {
                firstImagePixelsColumn.clear();
                firstImagePixelsRow.clear();
                secondImagePixelsColumn.clear();
                secondImagePixelsRow.clear();

                it.next();
                QFileInfo matchingsInputFileTxt = it.fileInfo();
                QFileInfo matchingsOutputFileDat(mProject->getBasePath()+"/Homol/Pastis"+imageName+"/"+matchingsInputFileTxt.baseName()+"."+imageFile.suffix()+".dat");
                TiePointsIO().readTiePointsFile(matchingsInputFileTxt.absoluteFilePath(),firstImagePixelsColumn,firstImagePixelsRow,secondImagePixelsColumn,secondImagePixelsRow,error);
                TiePointsIO().WriteDatTiePoints(matchingsOutputFileDat.absoluteFilePath(),firstImagePixelsColumn,firstImagePixelsRow,secondImagePixelsColumn,secondImagePixelsRow,error);
            }
        }
    }
}
