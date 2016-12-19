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
#include <QFileInfo>
#include <QDir>

#include "TapiocaProcess.h"
#include "libPW.h"

using namespace  PW;

TapiocaProcess::TapiocaProcess():
    ExternalProcess(LibPW::getMicMacBinPath() + "/" + TAPIOCA_COMMAND)
{
//    setStartupMessage("Runnig Tapioca...");
    setStartupMessage("Searching for tie points...");

    QFileInfo commandFileInfo(mCommandPath);
    QDir workingDir = commandFileInfo.absoluteDir();
    workingDir.cdUp();
    setWorkingDir(workingDir.absolutePath());

    setStdOutputFilePath(LibPW::getStdErrorPath() + "/Tapioca.log");
    setStdErrorFilePath(LibPW::getStdErrorPath() + "/TapiocaError.log");

    //    connect(this,SIGNAL(finished()),this,SLOT(onFinished()));
}

TapiocaProcess::TapiocaProcess(QString inputRegExp, QString imagesDir, QString mode, int range, int size, int mulScaleMin):
    ExternalProcess(LibPW::getMicMacBinPath() + "/" + TAPIOCA_COMMAND)
{
    setStartupMessage("Searching for tie points (Tapioca)...");

    QFileInfo commandFileInfo(mCommandPath);
    QDir workingDir = commandFileInfo.absoluteDir();
    workingDir.cdUp();
    setWorkingDir(workingDir.absolutePath());

    setStdOutputFilePath(LibPW::getStdErrorPath() + "/Tapioca.log");
    setStdErrorFilePath(LibPW::getStdErrorPath() + "/TapiocaError.log");

    QStringList inputs;
    if(mode == "File"){
        QString pairsFilePath = imagesDir + "MesCouples.xml";
        inputs << mode << pairsFilePath << QString::number(size);
    }
    else if(mode == "MulScale"){
        inputs << mode << inputRegExp << QString::number(mulScaleMin) << QString::number(size);
    }
    else{
        inputs << mode << inputRegExp <<QString::number(size);
        if(mode=="Line")
            inputs << QString::number(range);
    }
    inputs << "ExpTxt=1";

    addIntputs(inputs);
}


void TapiocaProcess::onFinished()
{
    write("\r");
    write("\r");
    write("\r");
    write("\r");
}
