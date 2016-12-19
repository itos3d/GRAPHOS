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
#include "Apero2SureProcess.h"
#include "libPW.h"

using namespace PW;

//Apero2SureProcess::Apero2SureProcess(QString inputOriPath):
//    ExternalProcess(LibPW::getToolsPath() + "/" + APERO2SURE_COMMAND)
//{
//    QString workingDir = mCommandPath.left(mCommandPath.lastIndexOf(QRegExp("/")));
//    workingDir = workingDir.left(workingDir.lastIndexOf(QRegExp("/"))+1);
//    if(workingDir.isEmpty())
//        workingDir = QDir::currentPath();
//    setWorkingDir(workingDir);

//    setStartupMessage("Apero to SURE transformation...");
//    setStdOutputFilePath(LibPW::getStdErrorPath() + "/apero2sure.log");
//    setStdErrorFilePath(LibPW::getStdErrorPath() + "/apero2sureError.log");

//    QDir inputOriDir(inputOriPath);
//    inputOriDir.cdUp();
//    QString projectPath = inputOriDir.absolutePath();
//    QStringList filters;
//    filters << "Ori-*";
//    QFileInfoList fileInfoList = inputOriDir.entryInfoList(filters,QDir::NoDotAndDotDot | QDir::Dirs);
//    int oriIndex = -1;
//    QFileInfo inputOriPathInfo(inputOriPath);
//    for (int i=0; i<fileInfoList.count();i++) {
//        if( fileInfoList.at(i) == inputOriPathInfo)
//            oriIndex = i;
//    }

//    QStringList inputs;
//    inputs << projectPath << QString::number(oriIndex+1);
//    addIntputs(inputs);
//}

Apero2SureProcess::Apero2SureProcess(QString inputOriPath,bool takeFirst):
    ExternalProcess(LibPW::getToolsPath() + "/" + APERO2SURE_COMMAND)
{
    QString workingDir = mCommandPath.left(mCommandPath.lastIndexOf(QRegExp("/")));
    workingDir = workingDir.left(workingDir.lastIndexOf(QRegExp("/"))+1);
    if(workingDir.isEmpty())
        workingDir = QDir::currentPath();
    setWorkingDir(workingDir);

    setStartupMessage("Apero to SURE transformation...");
    setStdOutputFilePath(LibPW::getStdErrorPath() + "/apero2sure.log");
    setStdErrorFilePath(LibPW::getStdErrorPath() + "/apero2sureError.log");

    QDir inputOriDir(inputOriPath);
    inputOriDir.cdUp();
    QString projectPath = inputOriDir.absolutePath();
    QStringList inputs;
    if (!takeFirst) {
        QStringList filters;
        filters << "Ori-*";
        QFileInfoList fileInfoList = inputOriDir.entryInfoList(filters,QDir::NoDotAndDotDot | QDir::Dirs);
        int oriIndex = -1;
        QFileInfo inputOriPathInfo(inputOriPath);
        for (int i=0; i<fileInfoList.count();i++) {
            if( fileInfoList.at(i) == inputOriPathInfo)
                oriIndex = i;
        }
        inputs << projectPath << QString::number(oriIndex+1);

    }else {
        inputs << projectPath << QString::number(1);

    }
    addIntputs(inputs);
}
