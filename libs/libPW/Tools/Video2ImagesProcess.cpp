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
#include "Video2ImagesProcess.h"

#include "libPW.h"

using namespace PW;

Video2ImagesProcess::Video2ImagesProcess(QString inputFile,int frameRate):
    ExternalProcess(LibPW::getToolsPath()+"/"+FFMPEG_COMMAND)
{
        QString workingDir = mCommandPath.left(mCommandPath.lastIndexOf(QRegExp("/")));
        workingDir = workingDir.left(workingDir.lastIndexOf(QRegExp("/"))+1);
        if(workingDir.isEmpty())
            workingDir = QDir::currentPath();

        setStartupMessage("Extracting frames...");
        setStdOutputFilePath(LibPW::getStdErrorPath() + "/Video2Images.log");
        setStdErrorFilePath(LibPW::getStdErrorPath() + "/Video2Images.log");

        QFileInfo inputFileInfo(inputFile);
        QFileInfo outputTemplate(inputFileInfo.absolutePath()+"/"+inputFileInfo.baseName()+"_%5d.png");

        QStringList inputs;

        inputs << "-i" << inputFileInfo.absoluteFilePath() << "-r"<<QString::number(frameRate) << outputTemplate.absoluteFilePath();
        addIntputs(inputs);
}

Video2ImagesProcess::~Video2ImagesProcess()
{

}

