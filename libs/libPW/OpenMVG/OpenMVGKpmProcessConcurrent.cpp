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
#include <QFile>
#include <QMap>
#include "OPENMVGParametersDefinitions.h"
#include "OpenMVGKpmProcessConcurrent.h"
#include "OpenMVGKpProcess.h"
#include "OpenMVGMatchingProcess.h"
#include "MultiProcessConcurrent.h"
#include "Tools/ConvertProcess.h"
//#include "ConvertProcess2.h"
#include "ImagePairsFileIO.h"
#include "libPW.h"

using namespace PW;

OpenMVGKpmProcessConcurrent::OpenMVGKpmProcessConcurrent(QList<PWImage *>& inputImages,
                                                         QString pairsFileName,
                                                         QString tiePointsDensity):
    MultiProcess(true),
    mInputImages(inputImages)
{
    setStartupMessage("Searching for tie points and matches (KPMEpipolar)...");
    if(pairsFileName.isEmpty())
    {
        qCritical() << QObject::tr("Error: pairs file name is empty");
        return;
    }
//    QStringList fullPaths;
    QString aFilename = inputImages.at(0)->getFileName();
    QString imagesFilePath=inputImages.at(0)->getFullPath();
    QFileInfo fileInfo(imagesFilePath);
    imagesFilePath=fileInfo.absolutePath();
    QString outputPath=imagesFilePath+"/"+MATCHING_PATH;
    QDir auxDir=QDir::currentPath();
    if(!auxDir.exists(outputPath))
    {
        if(!auxDir.mkdir(outputPath))
        {
            qCritical() << QObject::tr("Error making directory:\n%1").arg(outputPath);
            return;
        }
    }
    outputPath+="/";
    outputPath+=OPENMVGPARAMETERSDEFINITIONS_MATCHES_PATH;
    if(!auxDir.exists(outputPath))
    {
        if(!auxDir.mkdir(outputPath))
        {
            qCritical() << QObject::tr("Error making directory:\n%1").arg(outputPath);
            return;
        }
    }

    QString extension = aFilename.right(aFilename.length()-aFilename.lastIndexOf(".")-1);

    QVector<QString> imagesFileToProcess;
    QMap<QString,QVector<QString> > imagePairs;
    QMap<QString,PWImage *> imagesToProcessByBasefilename;
    ImagePairsFileIO imagePairsFileIO;
    if(IMAGEPAIRSFILEIO_ERROR==imagePairsFileIO.readStandarAsciiFile(pairsFileName))
    {
        qCritical() << QObject::tr("Error reading image pairs file");
        return;
    }
    if(IMAGEPAIRSFILEIO_ERROR==imagePairsFileIO.getImagePairs(imagePairs))
    {
        qCritical() << QObject::tr("Error getting image pairs");
        return;
    }
    QMap<QString,QVector<QString> >::const_iterator iter=imagePairs.constBegin();
    while(iter!=imagePairs.constEnd())
    {
        QString imageFile=imagesFilePath+"/"+iter.key();
        QVector<QString> imagePairsFile=iter.value();
        if(!imagesFileToProcess.contains(imageFile))
            imagesFileToProcess.push_back(imageFile);
        for(int nFile=0;nFile<imagePairsFile.size();nFile++)
        {
            QString auxFile=imagesFilePath+"/"+imagePairsFile[nFile];
            if(!imagesFileToProcess.contains(auxFile))
                imagesFileToProcess.push_back(auxFile);
        }
        iter++;
    }
    // Compruebo que estan en el proyecto las imagenes
    for(int nFile=0;nFile<imagesFileToProcess.size();nFile++)
    {
        QString imageFileInPair=imagesFileToProcess[nFile];
        QFileInfo auxFileInfo(imageFileInPair);
        QString imageFileInPairBaseName=auxFileInfo.fileName();
        bool findImage=false;
        for(int kk=0;kk<inputImages.count();kk++)
        {
            PWImage * ptrImage=inputImages[kk];
            QString imageFileInProject = ptrImage->getFullPath();
            QFileInfo fileInfo(imageFileInProject);
            QString imageFileInProjectBaseName=fileInfo.fileName();
            if(imageFileInProjectBaseName.compare(imageFileInPairBaseName,Qt::CaseInsensitive)==0)
            {
                findImage=true;
                if(!imagesToProcessByBasefilename.contains(imageFileInProjectBaseName))
                {
                    imagesToProcessByBasefilename[imageFileInProjectBaseName]=ptrImage;
                }
                break;
            }
        }
        if(!findImage)
        {
            qCritical() << QObject::tr("Not found in project image:\n  %1").arg(imageFileInPair);
            return;
        }
    }
//    else // si es fromXmlFile aquí no puede entrar
//    {
//        for(int kk=0;kk<inputImages.count();kk++)
//        {
//            QString imageFileInProject = inputImages.at(kk)->getFileName();
//            imagesFileToProcess.push_back(inputImages.at(kk)->getFullPath());
//            imagesToProcessByBasefilename[imageFileInProject]=inputImages[kk];
//            if(kk<(inputImages.count()-1))
//            {
//                QVector<QString> pairs;
//                for(int tt=kk+1;tt<inputImages.count();tt++)
//                {
//                    QString auxImageFileInProject = inputImages.at(tt)->getFileName();
//                    pairs.push_back(auxImageFileInProject);
//                }
//                imagePairs[imageFileInProject]=pairs;
//            }
//        }
//    }
    QString listFileName=outputPath+"/"+OPENMVGPARAMETERSDEFINITIONS_IMAGE_LIST_FILE_KEYPOINTS;
    QFile listFile(listFileName);
    if(!listFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << QObject::tr("Error opening list file:\n  %1").arg(listFileName);
        return;
    }
    else
    {
        QTextStream out(&listFile);
        for (int i=0; i<imagesFileToProcess.size(); i++)
        {
            QString imageFileNameWithPath=imagesFileToProcess[i];
            QFileInfo auxFileInfo(imageFileNameWithPath);
            QString baseName=auxFileInfo.fileName();
            PWImage* ptrImage=NULL;
            if(imagesToProcessByBasefilename.contains(baseName))
                ptrImage=imagesToProcessByBasefilename[baseName];
            else
            {
                qCritical() << QObject::tr("Not found in project image:\n  %1").arg(imageFileNameWithPath);
                return;
            }
            //QString baseName=image->getFileName();
            double focal_mm=ptrImage->getCamera()->getDeclaredFocal();
            double sensorHeight_mm=ptrImage->getCamera()->getSensorHeight();
            double sensorWidht_mm=ptrImage->getCamera()->getSensorWidth();
            QSize imageSize=ptrImage->getSize();
            int sensorColumns=imageSize.width();
            int sensorRows=imageSize.height();
            double focalInPixelsByColumns=focal_mm*((double)sensorColumns)/sensorWidht_mm;
            double focalInPixelsByRows=focal_mm*((double)sensorRows)/sensorHeight_mm;
            double focalInPixels=(focalInPixelsByColumns+focalInPixelsByRows)/2.0;
            QString strFocal=QString::number(focalInPixels,'f',OPENMVGPARAMETERSDEFINITIONS_IMAGE_LIST_FILE_FOCAL_PRECISION);
            //IMGP2476.JPG;4000;3000;4388.9;0;2000;0;4388.9;1500;0;0;1
            out<<baseName<<";"<<QString::number(sensorColumns)<<";"<<QString::number(sensorRows)<<";";
            out<<strFocal<<";0;"<<QString::number(sensorColumns/2)<<";";
            out<<"0;"<<strFocal<<";"<<QString::number(sensorRows/2)<<";";
            out<<"0;0;1";
            out<<"\n";
        }
        listFile.close();
    }

    double peakThreshold=0.0;
    if(tiePointsDensity.compare(OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_LOW,Qt::CaseInsensitive)==0)
        peakThreshold=OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_LOW_VALUE;
    else if(tiePointsDensity.compare(OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_HIGH,Qt::CaseInsensitive)==0)
        peakThreshold=OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_HIGH_VALUE;

    //Convert to jpg or png
    MultiProcess *convertProcess = new MultiProcess(false);  // Porque son concurrentes
    if(extension.toLower() != "png"
            &&extension.toLower() != "jpg")
    {
        bool applyConvertProcess=false;
        for (int i=0; i<imagesFileToProcess.size(); i++)
        {
            QString jpgFilePath=imagesFileToProcess[i];
            jpgFilePath = jpgFilePath.left(jpgFilePath.lastIndexOf(".")+1)+ "jpg";
            if(!QFile::exists(jpgFilePath))
            {
                convertProcess->appendProcess(new ConvertProcess(imagesFileToProcess[i],
                                                                 jpgFilePath));
                if(!applyConvertProcess)
                    applyConvertProcess=true;
            }
        }
        if(applyConvertProcess)
            appendProcess(convertProcess);
    }

    // key points detection:
    OpenMVGKpProcess *kpProcess = new OpenMVGKpProcess(imagesFilePath,outputPath,peakThreshold);
    //MultiProcess *kpMultiProcess = new MultiProcess(false);  // Porque son concurrentes
    //kpMultiProcess->appendProcess(kpProcess);
    //appendProcess(kpMultiProcess);
    appendProcess(kpProcess);

    //MultiProcess *matchingProcess = new MultiProcess(false);  // Porque son concurrentes
    iter=imagePairs.constBegin();
    while(iter!=imagePairs.constEnd())
    {
        QString imageBaseName=iter.key();
        QString imageFile=imagesFilePath+"/"+iter.key();
        QVector<QString> imagePairsFile=iter.value();
        if(imagesFileToProcess.contains(imageFile))
        {
            for(int nFile=0;nFile<imagePairsFile.size();nFile++)
            {
                QString auxFile=imagesFilePath+"/"+imagePairsFile[nFile];
                if(imagesFileToProcess.contains(auxFile))
                {
                    QString imagePairBaseName=imagePairsFile[nFile];
                    OpenMVGMatchingProcess *imagePairMatchingProcess = new OpenMVGMatchingProcess(imagesFilePath,
                                                                                                  imageBaseName,
                                                                                                  imagePairBaseName,
                                                                                                  outputPath);
                    //matchingProcess->appendProcess(imagePairMatchingProcess);
                    appendProcess(imagePairMatchingProcess);
                }
            }
        }
        iter++;
    }
    //appendProcess(matchingProcess);
}

OpenMVGKpmProcessConcurrent::OpenMVGKpmProcessConcurrent(QMap<QString, PWImage *> &imagesByName,
                                                         QMap<QString, QString> &imageFileNamesByName,
                                                         QString pairsFileName,
                                                         QString tiePointsDensity):
    MultiProcess(true)
{
    setStartupMessage("Searching for tie points and matches (KPMEpipolar)...");
    if(pairsFileName.isEmpty())
    {
        qCritical() << QObject::tr("Error: pairs file name is empty");
        return;
    }
    if(!QFile::exists(pairsFileName))
    {
        qCritical() << QObject::tr("Error: pairs file name is not exists");
        return;
    }
    QFileInfo filePairs(pairsFileName);
    QString outputPath=filePairs.absolutePath();

    // mInputImages
    QVector<QString> imagesIdToProcess;
    QMap<QString,QVector<QString> > imagePairs;
    QMap<QString,PWImage *> imagesToProcess;
    ImagePairsFileIO imagePairsFileIO;
    if(IMAGEPAIRSFILEIO_ERROR==imagePairsFileIO.readStandarAsciiFile(pairsFileName))
    {
        qCritical() << QObject::tr("Error reading image pairs file");
        return;
    }
    if(IMAGEPAIRSFILEIO_ERROR==imagePairsFileIO.getImagePairs(imagePairs))
    {
        qCritical() << QObject::tr("Error getting image pairs");
        return;
    }
    QMap<QString,QVector<QString> >::const_iterator iter=imagePairs.constBegin();
    while(iter!=imagePairs.constEnd())
    {
        QString imageId=iter.key();
        QVector<QString> pairs=iter.value();
        if(!imagesIdToProcess.contains(imageId))
            imagesIdToProcess.push_back(imageId);
        for(int nFile=0;nFile<pairs.size();nFile++)
        {
            QString imagePairId=pairs[nFile];
            if(!imagesIdToProcess.contains(imagePairId))
                imagesIdToProcess.push_back(imagePairId);
        }
        iter++;
    }
    // Compruebo que estan en el proyecto las imagenes
    for(int nImg=0;nImg<imagesIdToProcess.size();nImg++)
    {
        QString imageId=imagesIdToProcess[nImg];
        if(!imageFileNamesByName.contains(imageId))
        {
            qCritical() << QObject::tr("Not found in imageFileNamesByName image:\n  %1").arg(imageId);
            return;
        }
        if(!imagesByName.contains(imageId))
        {
            qCritical() << QObject::tr("Not found in imagesByName image:\n  %1").arg(imageId);
            return;
        }
        QString imageFileName=imageFileNamesByName[imageId];
        if(!QFile::exists(imageFileName))
        {
            qCritical() << QObject::tr("Not exists image file:\n  %1").arg(imageFileName);
            return;
        }
    }

    double peakThreshold=0.0;
    if(tiePointsDensity.compare(OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_LOW,Qt::CaseInsensitive)==0)
        peakThreshold=OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_LOW_VALUE;
    else if(tiePointsDensity.compare(OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_HIGH,Qt::CaseInsensitive)==0)
        peakThreshold=OPENMVGPARAMETERSDEFINITIONS_TIEPOINTSDENSITY_HIGH_VALUE;

    //Convert to jpg or png
    MultiProcess *convertProcess = new MultiProcess(false);  // Porque son concurrentes
    bool applyConvertProcess=false;
    for(int nImg=0;nImg<imagesIdToProcess.size();nImg++)
    {
        QString imageId=imagesIdToProcess[nImg];
        QString imageFileName=imageFileNamesByName[imageId];
        QString extension = imageFileName.right(imageFileName.length()-imageFileName.lastIndexOf(".")-1);
        if(extension.toLower() != "png"
                &&extension.toLower() != "jpg")
        {
            QString jpgFilePath=imageFileName;
            jpgFilePath = jpgFilePath.left(jpgFilePath.lastIndexOf(".")+1)+ "jpg";
            if(!QFile::exists(jpgFilePath))
            {
                convertProcess->appendProcess(new ConvertProcess(imageFileName,
                                                                 jpgFilePath));
                if(!applyConvertProcess)
                    applyConvertProcess=true;
            }
        }
    }
    if(applyConvertProcess)
        appendProcess(convertProcess);

    // Keypoint process
    QString listFileName=outputPath+"/"+OPENMVGPARAMETERSDEFINITIONS_IMAGE_LIST_FILE_KEYPOINTS;
    QFile listFile(listFileName);
    if(!listFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qCritical() << QObject::tr("Error opening list file:\n  %1").arg(listFileName);
        return;
    }
    QTextStream out(&listFile);
    for(int nImg=0;nImg<imagesIdToProcess.size();nImg++)
    {
        QString imageId=imagesIdToProcess[nImg];
        QString imageOutputPath=outputPath+"/"+imageId;
        QDir auxDir=QDir::currentPath();
        if(!auxDir.exists(imageOutputPath))
        {
            if(!auxDir.mkdir(imageOutputPath))
            {
                qCritical() << QObject::tr("Error making directory:\n%1").arg(imageOutputPath);
                return;
            }
        }
        QString imageFileName=imageFileNamesByName[imageId];
        QFileInfo fileInfo(imageFileName);
        QString fileNameWithoutPath=fileInfo.fileName();
        QString imageFilePath=fileInfo.absolutePath();
        PWImage* ptrImage=imagesByName[imageId];
        double focal_mm=ptrImage->getCamera()->getDeclaredFocal();
        double sensorHeight_mm=ptrImage->getCamera()->getSensorHeight();
        double sensorWidht_mm=ptrImage->getCamera()->getSensorWidth();
        QSize imageSize=ptrImage->getSize();
        int sensorColumns=imageSize.width();
        int sensorRows=imageSize.height();
        double focalInPixelsByColumns=focal_mm*((double)sensorColumns)/sensorWidht_mm;
        double focalInPixelsByRows=focal_mm*((double)sensorRows)/sensorHeight_mm;
        double focalInPixels=(focalInPixelsByColumns+focalInPixelsByRows)/2.0;
        QString strFocal=QString::number(focalInPixels,'f',OPENMVGPARAMETERSDEFINITIONS_IMAGE_LIST_FILE_FOCAL_PRECISION);
        //IMGP2476.JPG;4000;3000;4388.9;0;2000;0;4388.9;1500;0;0;1
        QString strListFile=fileNameWithoutPath+";"+QString::number(sensorColumns)+";"+QString::number(sensorRows)+";";
        strListFile+=(strFocal+";0;"+QString::number(sensorColumns/2)+";"+"0;"+strFocal+";"+QString::number(sensorRows/2)+";");
        strListFile+="0;0;1";//<<"\n";
        out<<strListFile<<"\n";
        OpenMVGKpProcess *kpProcess = new OpenMVGKpProcess(imageFilePath,imageOutputPath,peakThreshold,strListFile);
        //MultiProcess *kpMultiProcess = new MultiProcess(false);  // Porque son concurrentes
        //kpMultiProcess->appendProcess(kpProcess);
        //appendProcess(kpMultiProcess);
        appendProcess(kpProcess);
    }
    listFile.close();

    //MultiProcess *matchingProcess = new MultiProcess(false);  // Porque son concurrentes
    iter=imagePairs.constBegin();
    while(iter!=imagePairs.constEnd())
    {
        QString imageId=iter.key();
//        QString imageFile=imagesFilePath+"/"+iter.key();
        if(imagesIdToProcess.contains(imageId))
        {
            QVector<QString> imagePairsIds=iter.value();
            for(int nImageId=0;nImageId<imagePairsIds.size();nImageId++)
            {
                QString imagePairId=imagePairsIds[nImageId];
                if(imagesIdToProcess.contains(imagePairId))
                {
                    OpenMVGMatchingProcess *imagePairMatchingProcess = new OpenMVGMatchingProcess(imageFileNamesByName,
                                                                                                  imageId,
                                                                                                  imagePairId,
                                                                                                  outputPath);
                    //matchingProcess->appendProcess(imagePairMatchingProcess);
                    appendProcess(imagePairMatchingProcess);
                }
            }
        }
        iter++;
    }
    //appendProcess(matchingProcess);
}
