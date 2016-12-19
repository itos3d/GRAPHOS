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
#include "C3DCProcess.h"
#include <QFileInfo>
#include <QDir>
#include "libPW.h"
using namespace  PW;

C3DCProcess::C3DCProcess():
    ExternalProcess(LibPW::getMicMacBinPath() + "/" + C3DC_COMMAND)
{
    setStartupMessage("Generating Dense Model...");

    QFileInfo commandFileInfo(mCommandPath);
    QDir workingDir = commandFileInfo.absoluteDir();
    workingDir.cdUp();
    setWorkingDir(workingDir.absolutePath());
    addIntputs(QStringList() << "C3DC");
    setStdOutputFilePath(LibPW::getStdErrorPath() + "/C3DC.log");
    setStdErrorFilePath(LibPW::getStdErrorPath() + "/C3DC.log");
}

C3DCProcess::~C3DCProcess()
{

}

