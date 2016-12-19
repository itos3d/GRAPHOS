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
#include "ScaleProcess.h"
#include "libPW.h"

using namespace PW;
ScaleProcess::ScaleProcess(QString inputFile,float scalex,float scaley,float scalez):
    ExternalProcess(LibPW::getToolsPath()+"/"+LASSCALE_COMMAND)
{
        QString workingDir = mCommandPath.left(mCommandPath.lastIndexOf(QRegExp("/")));
        workingDir = workingDir.left(workingDir.lastIndexOf(QRegExp("/"))+1);
        if(workingDir.isEmpty())
            workingDir = QDir::currentPath();
    //    setWorkingDir(outputPath);

        setStartupMessage("Scaling cloud...");
        setStdOutputFilePath(LibPW::getStdErrorPath() + "/lasscale.log");
        setStdErrorFilePath(LibPW::getStdErrorPath() + "/lasscale.log");

        QFileInfo inputFileInfo(inputFile);
        QStringList inputs;

        inputs << inputFileInfo.absoluteFilePath() << "-scale_x" << QString::number(scalex)<<"-scale_y"<<QString::number(scaley) <<"-scale_z" << QString::number(scalez);

        QFileInfo outputFile(inputFileInfo.absolutePath()+"/"+inputFileInfo.baseName()+"_scaled.las");
        inputs << "-o" << outputFile.absoluteFilePath();
        addIntputs(inputs);
}

ScaleProcess::~ScaleProcess()
{

}

