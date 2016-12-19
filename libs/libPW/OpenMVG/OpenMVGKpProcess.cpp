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
#include "libPW.h"
#include "OpenMVGParametersDefinitions.h"
#include "OpenMVGKpProcess.h"

using namespace  PW;

OpenMVGKpProcess::OpenMVGKpProcess(QString imagesPath,
                                   QString outputPath,
                                   double peakThreshold):
    ExternalProcess(LibPW::getOpenMVGBinPath() + "/" + OPENMVG_KPM_PROGRAM_KPDETECTCION)
{
    setStartupMessage(tr("Searching for keypoints ..."));
//    QString workingDir = mCommandPath.left(mCommandPath.lastIndexOf(QRegExp("/")));
//    workingDir = workingDir.left(workingDir.lastIndexOf(QRegExp("/"))+1);
//    setWorkingDir(workingDir);
//    setStdOutputFilePath(LibPW::getStdErrorPath() + "/OpenCV.log");
//    setStdErrorFilePath(LibPW::getStdErrorPath() + "/OpenCVError.log");

    QStringList inputs;
    inputs<<"kp";
    inputs<<"-i";
    inputs<<imagesPath;
    inputs<<"-o";
    inputs<<outputPath;
    inputs<<"-p";
    inputs<<QString::number(peakThreshold,'f',OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_PRECISION);
    addIntputs(inputs);
}

OpenMVGKpProcess::OpenMVGKpProcess(QString imagesPath,
                                   QString outputPath,
                                   double peakThreshold,
                                   QString strListFile):
    ExternalProcess(LibPW::getOpenMVGBinPath() + "/" + OPENMVG_KPM_PROGRAM_KPDETECTCION)
{
    setStartupMessage(tr("Searching for keypoints ..."));
//    QString workingDir = mCommandPath.left(mCommandPath.lastIndexOf(QRegExp("/")));
//    workingDir = workingDir.left(workingDir.lastIndexOf(QRegExp("/"))+1);
//    setWorkingDir(workingDir);
//    setStdOutputFilePath(LibPW::getStdErrorPath() + "/OpenCV.log");
//    setStdErrorFilePath(LibPW::getStdErrorPath() + "/OpenCVError.log");
    QString listFileName=outputPath+"/"+OPENMVGPARAMETERSDEFINITIONS_IMAGE_LIST_FILE_KEYPOINTS;
    QFile listFile(listFileName);
    if(!listFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << QObject::tr("Error opening list file:\n  %1").arg(listFileName);
        return;
    }
    QTextStream out(&listFile);
    out<<strListFile;
    listFile.close();
    QStringList inputs;
    inputs<<"kp";
    inputs<<"-i";
    inputs<<imagesPath;
    inputs<<"-o";
    inputs<<outputPath;
    inputs<<"-p";
    inputs<<QString::number(peakThreshold,'f',OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_PRECISION);
    addIntputs(inputs);
}
