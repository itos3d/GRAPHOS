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
#include "MSDProcess.h"
#include "MSDkpd.h"
#include "MSDMatching.h"

using namespace PW;

MSDProcess::MSDProcess(QString matchesFolder, QStringList imagesPathList, QString outputPath,  QMap<QString, QString> MSDParameters,bool affine,int affineTilts):
    MultiProcess(true),
    matchesFolder(matchesFolder),
    mImagesPathList(imagesPathList),
    mMSDParameters(MSDParameters),
    mAffine(affine),
    mAffineTilts(affineTilts)
{
    setStartupMessage("Searching for tie points (MSD)...");

    //Parse msd parameters
    int msdPatchRadius= mMSDParameters.value("PatchRadius").toInt();
    int msdSearchAreaRadius= mMSDParameters.value("SearchAreaRadius").toInt();
    int msdNMSRadius= mMSDParameters.value("NMSRadius").toInt();
    int msdNMSScaleRadius= mMSDParameters.value("NMSScaleRadius").toInt();
    float msdThSaliency= mMSDParameters.value("ThSaliency").toFloat();
    int msdKNN= mMSDParameters.value("KNN").toInt();
    float msdScaleFactor= mMSDParameters.value("ScaleFactor").toFloat();
    int msdNScales= mMSDParameters.value("NScales").toInt();

    int maxTiepoints =mMSDParameters.value("MaxTiepoints").toInt();
    float RB_ratio= mMSDParameters.value("RB_ratio").toFloat();
//    float RB_distance= mMSDParameters.value("RB_distance").toFloat();
//    float RB_confidence= mMSDParameters.value("RB_confidence").toFloat();
    float RB_threshold_K= mMSDParameters.value("RB_threshold_K").toFloat();
    int ImageResizeValue= mMSDParameters.value("ResizeValue").toInt();
    bool msdComputeOrientations;
    if (mMSDParameters.value("ComputeOrientations").contains("true")) {
        msdComputeOrientations=true;
    }else {
        msdComputeOrientations=false;
    }
    int matchingMethod=0;  //BFMatcher matchingMethod=0
    if (MSDParameters.value("matchingMethod").contains("FLANN")) {
        matchingMethod=1;
    }
    int minimumMatches = mMSDParameters.value("minimumMatches").toInt();

//    matchesFolder=mProjectBasePath+"/Matches";
//    QDir auxDir(mProjectBasePath);

//    if(!auxDir.exists(matchesFolder))
//    {
//        auxDir.mkdir(matchesFolder);
//        QDir matchesDir(matchesFolder);
//        if (!matchesDir.exists(matchesFolder+"/tapioca"))
//            matchesDir.mkdir(matchesFolder+"/tapioca");
//    }

    mKPDProcess = new MultiProcess(false); //concurrent
    foreach (QString imagePath, imagesPathList) {
        ProcessedImageData * metadata = new ProcessedImageData();
        MSDkpd *kpmProcess = new MSDkpd(imagePath,outputPath,metadata,msdPatchRadius,msdSearchAreaRadius,msdNMSRadius,msdNMSScaleRadius,msdThSaliency,msdKNN,msdScaleFactor,msdNScales,ImageResizeValue,msdComputeOrientations,maxTiepoints,mAffine,mAffineTilts);
        mKPDProcess->appendProcess(kpmProcess);
        QFileInfo inputFileInfo (imagePath);
        QString imageFileName = inputFileInfo.fileName();
        mImageMetadataMap.insert(imageFileName, metadata);
    }

    mMatchingProcess = new MSDMatching(matchesFolder, imagesPathList,mImageMetadataMap,ImageResizeValue,minimumMatches, RB_ratio, RB_threshold_K,matchingMethod);
    appendProcess(mKPDProcess);
    appendProcess(mMatchingProcess);
//    connect(mKPDProcess,SIGNAL(newStdData(QString)),this, SIGNAL(newStdData(QString)));
//    connect(mMatchingProcess,SIGNAL(newStdData(QString)),this, SIGNAL(newStdData(QString)));

}


MSDProcess::~MSDProcess()
{
    foreach (ProcessedImageData * metadata, mImageMetadataMap.values()){
        delete metadata;
    }
    delete mKPDProcess;
    delete mMatchingProcess;
}

bool MSDProcess::removeDir(QString dirName)
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

