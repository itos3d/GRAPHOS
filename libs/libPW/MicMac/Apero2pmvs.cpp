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

#include "Apero2pmvs.h"
#include "libPW.h"

using namespace PW;

Apero2pmvs::Apero2pmvs(QString inputRegExp, QString orientation):
    ExternalProcess(LibPW::getMicMacBinPath() + "/" + APERO2PMVS_COMMAND)
{
    setStartupMessage("Generating PVMS files...");

    QFileInfo commandFileInfo(mCommandPath);
    QDir workingDir = commandFileInfo.absoluteDir();
    workingDir.cdUp();
    setWorkingDir(workingDir.absolutePath());

    setStdOutputFilePath(LibPW::getStdErrorPath() + "/Apero2PMVS.log");
    setStdErrorFilePath(LibPW::getStdErrorPath() + "/Apero2PMVSError.log");

    addIntputs(QStringList() << inputRegExp << orientation);
}
