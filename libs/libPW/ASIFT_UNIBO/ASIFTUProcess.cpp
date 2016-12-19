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
#include <QDir>
#include "ASIFTUProcess.h"
#include "ASIFTUkpd.h"
#include "ASIFTUMatching.h"

using namespace PW;

ASIFTUProcess::ASIFTUProcess(QString matchesFolder, QStringList imagesPathList, QString outputPath,  QMap<QString, QString> ASIFTParameters):
    MultiProcess(true),
    matchesFolder(matchesFolder),
    mImagesPathList(imagesPathList),
    mASIFTParameters(ASIFTParameters)
{
    setStartupMessage("Searching for tie points (ASIFT)...");

    //Parse ASIFT parameters

    int peakTh= mASIFTParameters.value("PeakTh").toInt();
    float edgeTh= mASIFTParameters.value("EdgeTh").toFloat();
    int octaves= mASIFTParameters.value("Octaves").toInt();
//    int levels= mASIFTParameters.value("Levels").toInt();
    int maxTiepoints = mASIFTParameters.value("MaxTiepoints").toInt();
    int tilts = mASIFTParameters.value("Tilts").toInt();

    float RB_ratio= mASIFTParameters.value("RB_ratio").toFloat();
//    float RB_distance= mASIFTParameters.value("RB_distance").toFloat();
//    float RB_confidence= mASIFTParameters.value("RB_confidence").toFloat();
    float RB_threshold_K= mASIFTParameters.value("RB_threshold_K").toFloat();
    int ImageResizeValue= mASIFTParameters.value("ResizeValue").toInt();

    int matchingMethod=0;  //BFMatcher matchingMethod=0
    if (ASIFTParameters.value("matchingMethod").contains("FLANN")) {
        matchingMethod=1;
    }
    int minimumMatches = mASIFTParameters.value("minimumMatches").toInt();


    mKPDProcess = new MultiProcess(false); //concurrent
    foreach (QString imagePath, imagesPathList) {
        ProcessedImageData * metadata = new ProcessedImageData();
        ASIFTUkpd *kpmProcess = new ASIFTUkpd(imagePath,outputPath,metadata,ImageResizeValue,peakTh,edgeTh,octaves,maxTiepoints,tilts);
        mKPDProcess->appendProcess(kpmProcess);
        QFileInfo inputFileInfo (imagePath);
        QString imageFileName = inputFileInfo.fileName();
        mImageMetadataMap.insert(imageFileName, metadata);
    }

    mMatchingProcess = new ASIFTUmatching(matchesFolder, imagesPathList,mImageMetadataMap,ImageResizeValue,minimumMatches, RB_ratio, RB_threshold_K,matchingMethod);
    appendProcess(mKPDProcess);
    appendProcess(mMatchingProcess);

}


ASIFTUProcess::~ASIFTUProcess()
{
    foreach (ProcessedImageData * metadata, mImageMetadataMap.values()){
        delete metadata;
    }
    delete mKPDProcess;
    delete mMatchingProcess;
}

bool ASIFTUProcess::removeDir(QString dirName)
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



