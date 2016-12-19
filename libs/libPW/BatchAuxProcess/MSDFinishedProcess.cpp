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
#include "MSDFinishedProcess.h"
#include "PWMatchesCategory.h"
#include "MicMac/TapiocaIO.h"
using namespace PW;


MSDFinishedProcess::MSDFinishedProcess(PW::Project *project,QString tiepointsMetadata):mProject(project),mTiepointsMetadata(tiepointsMetadata)
{

}

MSDFinishedProcess::~MSDFinishedProcess()
{

}

void MSDFinishedProcess::run(){
    mProject->setMatchingFormat(MATCHING_FORMAT_APERO_TXT);
    mProject->appendTiePointsSet("MSD");
    mProject->setNeedToSave(true);

    QDateTime dateTime=QDateTime::currentDateTime();
    QString timeCalculation=dateTime.toString(LIBPW_DATETIME_STRING_FORMAT);

    PWMatchesCategory * category = new PWMatchesCategory(mProject,
                          0,
                          "MSD",
                          mTiepointsMetadata,
                          timeCalculation);

    QMap<QString, QVector<QString> > imagePairs;
    TapiocaIO tapiocaIO;
    tapiocaIO.readImagePairs(mProject->getBasePath()+"/"+MATCHING_PATH+"/MSD", imagePairs);
    PWGraphImages* graphImages=new PWGraphImages();
        QVector<QString> wallisImageNames = mProject->getImagesFileName();
        for (int i = 0; i < wallisImageNames.count(); ++i) {
            wallisImageNames[i]=wallisImageNames[i].split(".").at(0)+".tif";
        }
        if(!graphImages->createGraph(wallisImageNames,
                                      imagePairs))
         {
             //TODO: graphIsConnected=false; ¿Que hacer?
         }


    category->setGraphImages(graphImages);
    category->setImagePairs(imagePairs);

    mProject->insertMatchesCategory(category); //Comprobar categorie
    mProject->setActiveTiePointsSet("MSD");
    //Rename folders and files if necessary.

    if (!QFileInfo(mProject->getImagesFileName().first()).suffix().contains("tif")) {
        QString matchesDirPath = mProject->getBasePath()+"/"+MATCHING_PATH+"/MSD";
        QDir *matchesDir = new QDir(matchesDirPath);
        QFileInfoList infoList = matchesDir->entryInfoList();
        for (int j = 2; j < infoList.count(); ++j) {
            QString subfolderName = infoList[j].absoluteFilePath();
            subfolderName =subfolderName.split(".").at(0)+"."+mProject->getImagesFileName().at(0).split(".").at(1);
            LibPW::copyDir(infoList[j].absoluteFilePath(),subfolderName);
            LibPW::removeDir(infoList[j].absoluteFilePath());
            QDir *pastirDir = new QDir(subfolderName);
            QFileInfoList infoPastisList = pastirDir->entryInfoList();
            for (int k = 2; k < infoPastisList.count(); ++k) {
                QString pastisFileName = infoPastisList[k].absoluteFilePath();
                pastisFileName =pastisFileName.split(".tif.txt").at(0)+"."+mProject->getImagesFileName().at(0).split(".").at(1)+".txt";
                QFile::rename(infoPastisList[k].absoluteFilePath(), pastisFileName);
            }
        }
    }

    if(!mProject->isValidMatchedCategory(mTiepointsMetadata) || !TIEPOINTS_VALIDATE_SETS){
        //Not valid graph

    }

    QString homolPath= mProject->getBasePath() + "/" + "Homol";
    QDir homolDir(homolPath);
    LibPW::removeDir(homolDir.absolutePath());
    //Copy "Homol" to project directory:
    if(!homolDir.exists())
    {
        if(!homolDir.mkdir(homolDir.absolutePath()))
        {
//            QMessageBox::critical(this,tr("GRAPHOS - Error"),tr("Error making homol dir"));
            return;
        }
    }
    QString sourceFolder=mProject->getBasePath()+"/"+MATCHING_PATH+"/"+mProject->getActiveTiePointsSet();

    QString targetFolder=mProject->getBasePath()+"/"+TAPIOCA_MATCHES_ORIGINAL_PATH;
    QDir souceDir(sourceFolder);
    QDir targetDir(targetFolder);
    while (!targetDir.exists()) {
        QDir().mkdir(targetDir.absolutePath());
    }

    if(!LibPW::copyDir(souceDir.absolutePath(),targetDir.absolutePath(),false))
    {
        QString title="MainWindow::onTiePointsFinished";
        QString strError=tr("Error moving matching files to Homol");
//        QMessageBox::critical(this,title,strError);
        return;
    }

    //tie point results;
//    drawTiePointsInfoView(imagePairs);

    //Save the project
//    mPersistenceManager->updateProject(mProject);
}
