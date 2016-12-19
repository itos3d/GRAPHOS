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
#include "OpenMVGMatchingProcess.h"

using namespace  PW;

OpenMVGMatchingProcess::OpenMVGMatchingProcess(QString imagesPath,
                                               QString firstImageBaseName,
                                               QString secondImageBaseName,
                                               QString outputPath):
    ExternalProcess(LibPW::getOpenMVGBinPath() + "/" + OPENMVG_KPM_PROGRAM_MATCHING)
{
    setStartupMessage(tr("Searching for matches ..."));
//    QString workingDir = mCommandPath.left(mCommandPath.lastIndexOf(QRegExp("/")));
//    workingDir = workingDir.left(workingDir.lastIndexOf(QRegExp("/"))+1);
//    setWorkingDir(workingDir);
//    setStdOutputFilePath(LibPW::getStdErrorPath() + "/OpenCV.log");
//    setStdErrorFilePath(LibPW::getStdErrorPath() + "/OpenCVError.log");

    QStringList inputs;
    inputs<<"matching";
    inputs<<"-i";
    inputs<<imagesPath;
    inputs<<"-f";
    inputs<<firstImageBaseName;
    inputs<<"-s";
    inputs<<secondImageBaseName;
    inputs<<"-o";
    inputs<<outputPath;
    inputs<<"-g";
    inputs<<OPENMVGPARAMETERSDEFINITIONS_MATCHES_GEOMFILTER;
    addIntputs(inputs);
}

OpenMVGMatchingProcess::OpenMVGMatchingProcess(QMap<QString, QString> &imageFileNamesByName,
                                               QString firstImageId,
                                               QString secondImageId,
                                               QString outputPath):
    ExternalProcess(LibPW::getOpenMVGBinPath() + "/" + OPENMVG_KPM_PROGRAM_MATCHING)
{
    setStartupMessage(tr("Searching for matches ..."));
//    QString workingDir = mCommandPath.left(mCommandPath.lastIndexOf(QRegExp("/")));
//    workingDir = workingDir.left(workingDir.lastIndexOf(QRegExp("/"))+1);
//    setWorkingDir(workingDir);
//    setStdOutputFilePath(LibPW::getStdErrorPath() + "/OpenCV.log");
//    setStdErrorFilePath(LibPW::getStdErrorPath() + "/OpenCVError.log");

    mImageFileNamesByName=imageFileNamesByName;
    mFirstImageId=firstImageId;
    mSecondImageId=secondImageId;
    mOutputPath=outputPath;

    QString firstImageFileName=mImageFileNamesByName[firstImageId];
    QFileInfo firstImageFileInfo(firstImageFileName);
    QString firstImageFileNameWithoutPath=firstImageFileInfo.fileName();

    QString secondImageFileName=mImageFileNamesByName[secondImageId];
    QFileInfo secondImageFileInfo(secondImageFileName);
    QString secondImageFileNameWithoutPath=secondImageFileInfo.fileName();

    QStringList inputs;
    inputs<<"matching";
    inputs<<"-i";
    inputs<<outputPath;
    inputs<<"-f";
    inputs<<firstImageFileNameWithoutPath;
    inputs<<"-s";
    inputs<<secondImageFileNameWithoutPath;
    inputs<<"-o";
    inputs<<outputPath;
    inputs<<"-g";
    inputs<<OPENMVGPARAMETERSDEFINITIONS_MATCHES_GEOMFILTER;
    addIntputs(inputs);
}

bool OpenMVGMatchingProcess::removeDir(QString dirName)
{
    bool result = true;
    QDir dir(dirName);
    if (dir.exists(dirName)) {
        Q_FOREACH(QFileInfo info, dir.entryInfoList(QDir::NoDotAndDotDot | QDir::System | QDir::Hidden  | QDir::AllDirs | QDir::Files, QDir::DirsFirst)) {
            if (info.isDir()) {
                result = removeDir(info.absoluteFilePath());
            }
            else {
                result = QFile::remove(info.absoluteFilePath());
            }
            if (!result) {
                return result;
            }
        }
        result = dir.rmdir(dirName);
    }
    return result;
}

void OpenMVGMatchingProcess::start()
{
    QDir auxDir=QDir::currentPath();
    if(!auxDir.exists(mOutputPath))
    {
        qCritical() << QObject::tr("Not exists directory:\n%1").arg(mOutputPath);
        return;
    }

    QVector<QString> imageNames;
    imageNames.push_back(mFirstImageId);
    imageNames.push_back(mSecondImageId);
    // Copiar los ficheros .desc y .feat a la carpeta de salida
    // Eliminar los ficheros .desc y .feat
    for(int nI=0;nI<imageNames.size();nI++)
    {
        QString imageId=imageNames[nI];
        QString imageOutputPath=mOutputPath+"/"+imageId;
        if(!auxDir.exists(imageOutputPath))
        {
            continue;
        }
        QString imageFileName=mImageFileNamesByName[imageId];
        QFileInfo fileInfo(imageFileName);

        QString featuresBaseName=fileInfo.baseName();
        QString featuresFileName=imageOutputPath+"/"+featuresBaseName+OPENMVGPARAMETERSDEFINITIONS_FEATURES_FILE_EXTENSION;
        QString featuresNewFileName=mOutputPath+"/"+featuresBaseName+OPENMVGPARAMETERSDEFINITIONS_FEATURES_FILE_EXTENSION;

        QString descriptorsBaseName=fileInfo.baseName();
        QString descriptorsFileName=imageOutputPath+"/"+descriptorsBaseName+OPENMVGPARAMETERSDEFINITIONS_DESCRIPTORS_FILE_EXTENSION;
        QString descriptorsNewFileName=mOutputPath+"/"+descriptorsBaseName+OPENMVGPARAMETERSDEFINITIONS_DESCRIPTORS_FILE_EXTENSION;

        if(QFile::exists(featuresNewFileName)
                &&QFile::exists(descriptorsNewFileName))
        {
            continue;
        }
        if(QFile::exists(featuresFileName)
                &&QFile::exists(descriptorsFileName))
        {
            if(!QFile::copy(featuresFileName,featuresNewFileName))
            {
                qCritical() << QObject::tr("Error copying features file:\n%1\nto:\n%2").arg(featuresFileName).arg(featuresNewFileName);
                return;
            }
            if(!QFile::copy(descriptorsFileName,descriptorsNewFileName))
            {
                return;
            }
            if(!QFile::remove(featuresFileName))
            {
                qCritical() << QObject::tr("Error removing features file:\n%1").arg(featuresFileName);
                return;
            }
            if(!QFile::remove(descriptorsFileName))
            {
                qCritical() << QObject::tr("Error removing descriptors file:\n%1").arg(descriptorsFileName);
                return;
            }
            if(!removeDir(imageOutputPath))
            {
                qCritical() << QObject::tr("Error removing directory:\n%1").arg(imageOutputPath);
                return;
            }
        }
        else
        {
            if(!QFile::exists(featuresFileName))
            {
                qCritical() << QObject::tr("Not exists file:\n%1").arg(featuresFileName);
                return;
            }
            if(!QFile::exists(descriptorsFileName))
            {
                qCritical() << QObject::tr("Not exists file:\n%1").arg(descriptorsFileName);
                return;
            }
        }
    }
    ExternalProcess::start();
}

