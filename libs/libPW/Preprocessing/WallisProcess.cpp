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
#include "WallisProcess.h"
#include "libPW.h"

using namespace PW;

WallisProcess::WallisProcess(QString imagePath,
                             QString outputPath,
                             float wallisParameterA,
                             float wallisParameterB,
                             unsigned short int kernelSize,
                             unsigned short int imposedAverage,
                             unsigned short int imposedStDeviation):
    ExternalProcess(LibPW::getToolsPath()+"/"+WALLIS_COMMAND)
{
    QString workingDir = mCommandPath.left(mCommandPath.lastIndexOf(QRegExp("/")));
    workingDir = workingDir.left(workingDir.lastIndexOf(QRegExp("/"))+1);
    if(workingDir.isEmpty())
        workingDir = QDir::currentPath();
    setWorkingDir(outputPath);

    setStartupMessage("Applying Wallis filter...");
    setStdOutputFilePath(LibPW::getStdErrorPath() + "/wallis.log");
    setStdErrorFilePath(LibPW::getStdErrorPath() + "/wallisError.log");

    QStringList inputs;
    inputs << imagePath <<
              outputPath <<
              QString::number(wallisParameterA) <<
              QString::number(wallisParameterB) <<
              QString::number(kernelSize) <<
              QString::number(imposedAverage) <<
              QString::number(imposedStDeviation);
    addIntputs(inputs);
}
