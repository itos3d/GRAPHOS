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
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QVector>

#include <opencv2/core/core.hpp>
#include "libPW.h"
#include "OpenCVKpMParametersDefinitions.h"
#include "OpenCVKpMParameters.h"

using namespace PW;

OpenCVKpMParameters::OpenCVKpMParameters()
{
    initialize();
}

int OpenCVKpMParameters::checkMatcherParameters(QString &strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::checkMatcherParameters, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    bool findMatcher=false;
    QString matcherTag=mMatcher;
    QStringList matcherParametersTag=mParametersTagsByGroup[matcherTag];
    QStringList matcherParametersValue=mParametersValueByGroup[matcherTag];
    QStringList matcherParametersType=mParametersTypeByGroup[matcherTag];
    if(matcherTag.compare(OPENCV_KPM_MATCHER_BRUTEFORCE_TAG,Qt::CaseSensitive)==0)
    {
        QString parameterTag=OPENCV_KPM_BRUTEFORCE_CROSSCHECK_TAG;
        int parameterPos=matcherParametersTag.indexOf(parameterTag);
        if(parameterPos==-1)
        {
            strError=QObject::tr("OpenCVKpMParameters::checkMatcherParameters, matcher %1 parameter % 2 not found").arg(matcherTag).arg(parameterTag);
            return(OPENCV_KPM_ERROR);
        }
        bool crossCheck=false;
        int intValue=matcherParametersValue[parameterPos].toInt();
        if(intValue==1)
        {
            crossCheck=true;
        }

//        parameterTag=OPENCV_KPM_BRUTEFORCE_KBESTMATCHES_TAG;
//        parameterPos=matcherParametersTag.indexOf(parameterTag);
//        if(parameterPos==-1)
//        {
//            strError=QObject::tr("OpenCVKpMParameters::checkMatcherParameters, matcher %1 parameter % 2 not found").arg(matcherTag).arg(parameterTag);
//            return(OPENCV_KPM_ERROR);
//        }
//        int kBestMatches=matcherParametersValue[parameterPos].toInt();

//        parameterTag=OPENCV_KPM_BRUTEFORCE_RATIOTESTDISTANCE_TAG;
//        parameterPos=matcherParametersTag.indexOf(parameterTag);
//        if(parameterPos==-1)
//        {
//            strError=QObject::tr("OpenCVKpMParameters::checkMatcherParameters, matcher %1 parameter % 2 not found").arg(matcherTag).arg(parameterTag);
//            return(OPENCV_KPM_ERROR);
//        }
//        double ratioTestDistance=matcherParametersValue[parameterPos].toDouble();
        findMatcher=true;

        // Controles
//        if(crossCheck&&kBestMatches)
//        {
//            strError=QObject::tr("OpenCVKpMParameters::checkMatcherParameters, matcher %1\n").arg(matcherTag);
//            strError+=QObject::tr("parameters values %1==true and %2>1 is not valid").arg(OPENCV_KPM_BRUTEFORCE_CROSSCHECK_TAG).arg(OPENCV_KPM_BRUTEFORCE_KBESTMATCHES_TAG);
//            return(OPENCV_KPM_ERROR);
//        }
    }
    else //if()
    {
        findMatcher=true;
    }
    if(!findMatcher)
    {
        strError=QObject::tr("OpenCVKpM::getMacher, descriptor: %1 is not implemented").arg(matcherTag);
        return(OPENCV_KPM_ERROR);
    }
    // Los parámetros generales
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getApplyOutliersDetection(bool& applyOutliersDetection,
                                                   QString &strError)
{
    applyOutliersDetection=false;
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::getApplyOutliersDetection, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    QString outliersDetectorTag=mOutliersDetector;
    QStringList auxList=mParametersTagsByGroup[outliersDetectorTag];
    int pos=auxList.indexOf(OPENCV_KPM_OUTLIERS_DHL_KMEANS_APPLYDETECTION_TAG);
    if(pos==-1)
    {
        strError=QObject::tr("OpenCVKpMParameters::getApplyOutliersDetection, outliers apply detection tag not exists");
        return(OPENCV_KPM_ERROR);
    }
    int intApplyOutliersDetection=mParametersValueByGroup[outliersDetectorTag].at(pos).toInt();
    if(intApplyOutliersDetection==1)
        applyOutliersDetection=true;
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getDescriptorsByDetector(QString &detectorTag,
                                                  QString &defaultDescriptor,
                                                  QStringList &descriptors,
                                                  QString &strError)
{
    if(!mDefaultDescriptorByDetector.contains(detectorTag))
    {
        strError=QObject::tr("OpenCVKpMParameters::getDescriptorsByDetector, There is not default descriptor for detector: %1").arg(detectorTag);
        return(OPENCV_KPM_ERROR);
    }
    if(!mDescriptorsByDetector.contains(detectorTag))
    {
        strError=QObject::tr("OpenCVKpMParameters::getDescriptorsByDetector, There is not descriptors for detector: %1").arg(detectorTag);
        return(OPENCV_KPM_ERROR);
    }
    defaultDescriptor=mDefaultDescriptorByDetector[detectorTag];
    if(!descriptors.isEmpty())
        descriptors.clear();
    descriptors=mDescriptorsByDetector[detectorTag];
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getDescriptor(QString &descriptorTag,
                                       QStringList &descriptorParametersTag,
                                       QStringList &descriptorParametersValues,
                                       QStringList &descriptorParametersType,
                                       QString &strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::getDetector, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    descriptorTag=mDescriptor;
    descriptorParametersTag=mDescriptorParametersTag;
    //detectorParametersTagQParams=mParametersTagsQParamsByGroup[detectorTag];
    descriptorParametersValues=mDescriptorParametersValue;
    descriptorParametersType=mDescriptorParametersType;
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getDetector(QString &detectorTag,
                                     QStringList &detectorParametersTag,
                                     QStringList &detectorParametersValues,
                                     QStringList &detectorParametersType,
                                     QString &strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::getDetector, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    detectorTag=mDetector;
    detectorParametersTag=mDetectorParametersTag;
    //detectorParametersTagQParams=mParametersTagsQParamsByGroup[detectorTag];
    detectorParametersValues=mDetectorParametersValue;
    detectorParametersType=mDetectorParametersType;
    return(OPENCV_KPM_NO_ERROR);
}
/*
int OpenCVKpMParameters::getDetector(QString& detectorTag,
                                     QStringList& detectorParametersTag,
                                     QStringList& detectorParametersTagQParams,
                                     QStringList& detectorParametersValues,
                                     QStringList& detectorParametersType,
                                     QString& strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::getDetector, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    detectorTag=mDetector;
    detectorParametersTag=mParametersTagsByGroup[detectorTag];
    detectorParametersTagQParams=mParametersTagsQParamsByGroup[detectorTag];
    detectorParametersValues=mParametersValueByGroup[detectorTag];
    detectorParametersType=mParametersTypeByGroup[detectorTag];
    return(OPENCV_KPM_NO_ERROR);
}
*/
int OpenCVKpMParameters::getDetectorsTag(QStringList &detectorsTag,
                                         QString &strError)
{
    detectorsTag.clear();
    detectorsTag=mDetectors;
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getDescriptorParametersTagQParams(QString &descriptorTag,
                                                           QStringList &descriptorParametersTagQParams,
                                                           QString &strError)
{
    if(!mParametersTagsQParamsByGroup.contains(descriptorTag))
    {
        strError=QObject::tr("OpenCVKpMParameters::getDescriptorParametersTagQParams, There is not descriptor: %1").arg(descriptorTag);
        return(OPENCV_KPM_ERROR);
    }
    descriptorParametersTagQParams=mParametersTagsQParamsByGroup[descriptorTag];
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getDetectorParametersTagQParams(QString &detectorTag,
                                                         QStringList &detectorParametersTagQParams,
                                                         QString &strError)
{
//    if(!mState)
//    {
//        strError=QObject::tr("OpenCVKpMParameters::getDetectorParametersTagQParams, The object has not been initialized");
//        return(OPENCV_KPM_ERROR);
//    }
    if(!mParametersTagsQParamsByGroup.contains(detectorTag))
    {
        strError=QObject::tr("OpenCVKpMParameters::getDetectorParametersTagQParams, There is not detector: %1").arg(detectorTag);
        return(OPENCV_KPM_ERROR);
    }
    detectorParametersTagQParams=mParametersTagsQParamsByGroup[detectorTag];
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getImagesPath(QString& imagesPath,
                                       QString& strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::getImagesPath, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    imagesPath=mImagesPath;
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getImagePairsFileName(QString& imagePairsFileName,
                                               QString& strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::getImagePairsFileName, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    imagePairsFileName=mImagePairsFileName;
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getMatcher(QString &matcherTag,
                                    QStringList &matcherParametersTag,
                                    QStringList &matcherParametersValues,
                                    QStringList &matcherParametersType,
                                    QString &strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::getMatcher, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    if(OPENCV_KPM_NO_ERROR!=checkMatcherParameters(strError))
    {
        strError=QObject::tr("OpenCVKpMParameters::getMatcher, ")+strError;
        return(OPENCV_KPM_ERROR);
    }
    matcherTag=mMatcher;
    matcherParametersTag=mMatcherParametersTag;
    matcherParametersValues=mMatcherParametersValue;
    matcherParametersType=mMatcherParametersType;
//    matcherTag=mMatcher;
//    matcherParametersTag=mParametersTagsByGroup[matcherTag];
//    matcherParametersValues=mParametersValueByGroup[matcherTag];
//    matcherParametersType=mParametersTypeByGroup[matcherTag];
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getMatchersByDetectorAndDescriptor(QString &detectorTag,
                                                            QString &descriptorTag,
                                                            QString &defaultMatcher,
                                                            QStringList &matchers,
                                                            QString &strError)
{
    QString aux=detectorTag;
    aux+=descriptorTag;
    if(!mMatchersByDetectorAndDescriptor.contains(aux))
    {
        strError=QObject::tr("OpenCVKpMParameters::getMatchersByDetectorAndDescriptor, There is not matchers for detector: %1 and descriptor: %2").arg(detectorTag).arg(descriptorTag);
        return(OPENCV_KPM_ERROR);
    }
    if(!mDefaultMatcherByDetectorAndDescriptor.contains(aux))
    {
        strError=QObject::tr("OpenCVKpMParameters::getMatchersByDetectorAndDescriptor, There is not default matcher for detector: %1 and descriptor: %2").arg(detectorTag).arg(descriptorTag);
        return(OPENCV_KPM_ERROR);
    }
    defaultMatcher=mDefaultMatcherByDetectorAndDescriptor[aux];
    if(!matchers.isEmpty())
        matchers.clear();
    matchers=mMatchersByDetectorAndDescriptor[aux];
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getMatcherParametersTagQParams(QString matcherTag,
                                                        QStringList &matchersTagQParams,
                                                        QString &strError)
{
    if(!mParametersTagsQParamsByGroup.contains(matcherTag))
    {
        strError=QObject::tr("OpenCVKpMParameters::getMatcherParametersTagQParams, There is not matcher: %1").arg(matcherTag);
        return(OPENCV_KPM_ERROR);
    }
    matchersTagQParams=mParametersTagsQParamsByGroup[matcherTag];
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getMatchingDistance(int& normType,
                                             QString &strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::getMatchingDistance, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    bool findMatchingDistance=false;
//    if(mMatchingDistance.compare(OPENCV_KPM_MATCHINGDISTANCE_NORM_INF_TAG,Qt::CaseSensitive)==0)
//    {
//        normType=cv::NORM_INF;
//        findMatchingDistance=true;
//    }
//    if(mMatchingDistance.compare(OPENCV_KPM_MATCHINGDISTANCE_NORM_L1_TAG,Qt::CaseSensitive)==0)
//    {
//        normType=cv::NORM_L1;
//        findMatchingDistance=true;
//    }
    if(mMatchingDistance.compare(OPENCV_KPM_MATCHINGDISTANCE_NORM_L2_TAG,Qt::CaseSensitive)==0)
    {
        normType=cv::NORM_L2;
        findMatchingDistance=true;
    }
//    if(mMatchingDistance.compare(OPENCV_KPM_MATCHINGDISTANCE_NORM_L2SQR_TAG,Qt::CaseSensitive)==0)
//    {
//        normType=cv::NORM_L2SQR;
//        findMatchingDistance=true;
//    }
    if(mMatchingDistance.compare(OPENCV_KPM_MATCHINGDISTANCE_NORM_HAMMING_TAG,Qt::CaseSensitive)==0)
    {
        normType=cv::NORM_HAMMING;
        findMatchingDistance=true;
    }
//    if(mMatchingDistance.compare(OPENCV_KPM_MATCHINGDISTANCE_NORM_HAMMING2_TAG,Qt::CaseSensitive)==0)
//    {
//        normType=cv::NORM_HAMMING2;
//        findMatchingDistance=true;
//    }
//    if(mMatchingDistance.compare(OPENCV_KPM_MATCHINGDISTANCE_NORM_TYPE_MASK_TAG,Qt::CaseSensitive)==0)
//    {
//        normType=cv::NORM_TYPE_MASK;
//        findMatchingDistance=true;
//    }
//    if(mMatchingDistance.compare(OPENCV_KPM_MATCHINGDISTANCE_NORM_RELATIVE_TAG,Qt::CaseSensitive)==0)
//    {
//        normType=cv::NORM_RELATIVE;
//        findMatchingDistance=true;
//    }
//    if(mMatchingDistance.compare(OPENCV_KPM_MATCHINGDISTANCE_NORM_MINMAX_TAG,Qt::CaseSensitive)==0)
//    {
//        normType=cv::NORM_MINMAX;
//        findMatchingDistance=true;
//    }
    if(!findMatchingDistance)
    {
        strError=QObject::tr("OpenCVKpMParameters::getMatchingDistance, Matching distance: %1 is not valid").arg(mMatchingDistance);
        return(OPENCV_KPM_ERROR);
    }
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::getOutliersDetector(QString &outliersDetectorTag,
                                             QStringList &outliersDetectorParametersTag,
                                             QStringList &outliersDetectorParametersValues,
                                             QStringList &outliersDetectorParametersType,
                                             QString &strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::getOutliersDetector, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    outliersDetectorTag=mOutliersDetector;
    outliersDetectorParametersTag=mOutliersDetectorParametersTag;
    outliersDetectorParametersValues=mOutliersDetectorParametersValue;
    outliersDetectorParametersType=mOutliersDetectorParametersType;
//    outliersDetectorParametersTag=mParametersTagsByGroup[outliersDetectorTag];
//    outliersDetectorParametersValues=mParametersValueByGroup[outliersDetectorTag];
//    outliersDetectorParametersType=mParametersTypeByGroup[outliersDetectorTag];
    return(OPENCV_KPM_NO_ERROR);
}

QParams::Param *OpenCVKpMParameters::getParameterByCode(QString parameterCode,
                                                        QVector<QParams::Param *> &parameters)
{
    for(int i=0;i<parameters.size();i++)
    {
        if(parameters[i]->getCode()==parameterCode)
        {
            return(parameters[i]);
        }
    }
    return(NULL);
}

QParams::Param *OpenCVKpMParameters::getParameterByName(QString parameterName,
                                                        QVector<QParams::Param *> &parameters)
{
    for(int i=0;i<parameters.size();i++)
    {
        if(parameters[i]->getName()==parameterName)
        {
            return(parameters[i]);
        }
    }
    return(NULL);
}

int OpenCVKpMParameters::getParameterByGroupAndTag(QString parameterGroup,
                                                   QString parameterTag,
                                                   QString &parameterValue,
                                                   QString &strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::getParameterByGroupAndTag, The object has not been initialized");
        return(OPENCV_KPM_ERROR);
    }
    if(!mParametersTagsByGroup.contains(parameterGroup))
    {
        strError=QObject::tr("OpenCVKpMParameters::getParameterByGroupAndTag, Group parameters: %1 is not valid").arg(parameterGroup);
        return(OPENCV_KPM_ERROR);
    }
    if(!mParametersTagsByGroup[parameterGroup].contains(parameterTag))
    {
        strError=QObject::tr("OpenCVKpMParameters::getParameterByGroupAndTag, Group parameters: %1 not contains parameter: %2").arg(parameterGroup).arg(parameterTag);
        return(OPENCV_KPM_ERROR);
    }
    int pos=mParametersTagsByGroup[parameterGroup].indexOf(parameterTag);
    parameterValue=mParametersValueByGroup[parameterGroup][pos];
    return(OPENCV_KPM_NO_ERROR);
}

bool OpenCVKpMParameters::getSaveImagesMatches(QString& pathForMatchesFiles)
{
    pathForMatchesFiles=mPathForMatchesFiles;
    return(mSaveImagesMatches);
}

bool OpenCVKpMParameters::getBidirectionalMatches()
{
    return(mBidirectionalMatches);
}

bool OpenCVKpMParameters::setFromFile(QString& fileName,
                                      QString& strError)
{
    initialize();
    if(!QFile::exists(fileName))
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, file not exists:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    QFile parametersFile(fileName);
    if(!parametersFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, error opening file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    int nLine=0;
    mImagesPath=OPENCV_KPM_NO_STRING_VALUE;
    mImagePairsFileName=OPENCV_KPM_NO_STRING_VALUE;
    mDetector=OPENCV_KPM_NO_STRING_VALUE;
    mDescriptor=OPENCV_KPM_NO_STRING_VALUE;
    mOutliersDetector=OPENCV_KPM_NO_STRING_VALUE;
    mMatcher=OPENCV_KPM_NO_STRING_VALUE;
    mSaveImagesMatches=false;
    mBidirectionalMatches=false;
    mPathForMatchesFiles=OPENCV_KPM_NO_STRING_VALUE;
    QStringList detectorParametersTag;
    QStringList detectorParametersType;
    QStringList detectorParametersValue;
    QStringList descriptorParametersTag;
    QStringList descriptorParametersType;
    QStringList descriptorParametersValue;
    QStringList matcherParametersTag;
    QStringList matcherParametersType;
    QStringList matcherParametersValue;
    QStringList outliersDetectorParametersTag;
    QStringList outliersDetectorParametersType;
    QStringList outliersDetectorParametersValue;
    while (!parametersFile.atEnd())
    {
        nLine++;
        QString line = parametersFile.readLine();
        QStringList splitedLine = line.simplified().split(OPENCV_KPM_VALUE_STRING_SEPARATOR);
        if(splitedLine.count() != 2)
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the string %2 not contains two strings separated by %3 \n in parameters file:\n%4").arg(nLine).arg(line).arg(OPENCV_KPM_VALUE_STRING_SEPARATOR).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString leftStrValue=splitedLine.at(0).trimmed();
        if(leftStrValue.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the string %2 contains empty strings at left \n in parameters file:\n%3").arg(nLine).arg(line).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString rightStrValue=splitedLine.at(1).trimmed();
        if(rightStrValue.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the string %2 contains empty strings at right \n in parameters file:\n%3").arg(nLine).arg(line).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString tag=splitedLine.at(0).trimmed();
        if(tag.compare(OPENCV_KPM_TAG_IMAGES_PATH,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, images path is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            QDir auxDir=QDir::current();
            if(!auxDir.exists(strValue))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, not exists images path parameter:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mImagesPath=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_IMAGE_PAIRS_FILENAME,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, image pairs filename parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!QFile::exists(strValue))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, not exists image pairs file name parameter:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mImagePairsFileName=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_SAVE_IMAGE_MATCHES,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            bool okToInt=false;
            int value=strValue.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, save images matches parameter no int value: %1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value<0&&value>1)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, save images matches must be 0 or 1, not %1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value==1)
                mSaveImagesMatches=true;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_BIDIRECTIONAL_MATCHES,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            bool okToInt=false;
            int value=strValue.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, bidirectional matches parameter no int value: %1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value<0&&value>1)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, bidirectional matches must be 0 or 1, not %1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value==1)
                mBidirectionalMatches=true;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_PATH_FOR_MATCHES_FILES,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, path for matches files parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mPathForMatchesFiles=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_DETECTORS,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, detector selected parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!mDetectors.contains(strValue,Qt::CaseInsensitive))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, detector selected parameter is not valid:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mDetector=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_DESCRIPTORS,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, descriptor selected parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!mDescriptors.contains(strValue,Qt::CaseSensitive))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, descriptor selected parameter is not valid:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mDescriptor=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_MATCHERS,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, matcher selected parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!mMatchers.contains(strValue,Qt::CaseInsensitive))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, matcher selected parameter is not valid:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mMatcher=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_OUTLIERSDETECTORS,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, outliers detector selected parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!mOutliersDetectors.contains(strValue,Qt::CaseSensitive))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, outliers detector selected parameter is not valid:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mOutliersDetector=strValue;
            continue;
        }
        QString firstTag=splitedLine.at(0).trimmed();
        QStringList splitedFirstTag = firstTag.simplified().split(OPENCV_KPM_TAG_STRING_SEPARATOR);
        if(splitedFirstTag.count() < 3
                ||splitedFirstTag.count() >4)
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 parameter tag %2 not contains three or four strings separated by %3 \n in parameters file:\n%4").arg(nLine).arg(firstTag).arg(OPENCV_KPM_TAG_STRING_SEPARATOR).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString parameterContainer;
        if(splitedFirstTag.count() ==3) //MATCHER_kBestMatches_int
            parameterContainer=splitedFirstTag.at(0).trimmed();
        if(splitedFirstTag.count() ==4)
            parameterContainer=splitedFirstTag.at(1).trimmed();
        if(parameterContainer.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter string %2 contains empty strings at left \n in parameters file:\n%3").arg(nLine).arg(firstTag).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        if(!mParametersTagsByGroup.contains(parameterContainer))
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter container %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterContainer).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        int posParameterTag=1;
        QString prefix;
        if(splitedFirstTag.count() ==4)
        {
            posParameterTag++;
            prefix=splitedFirstTag.at(0).trimmed();
            if(prefix.compare(OPENCV_KPM_TAG_DETECTOR,Qt::CaseInsensitive)==0)
            {
                if(parameterContainer.compare(mDetector,Qt::CaseInsensitive)!=0)
                {
                    strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the detector %2 is not equal previous value %3 \n in parameters file:\n%4").arg(nLine).arg(parameterContainer).arg(mDetector).arg(fileName);
                    return(OPENCV_KPM_ERROR);
                }
            }
            if(prefix.compare(OPENCV_KPM_TAG_DESCRIPTOR,Qt::CaseInsensitive)==0)
            {
                if(parameterContainer.compare(mDescriptor,Qt::CaseInsensitive)!=0)
                {
                    strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the descriptor %2 is not equal previous value %3 \n in parameters file:\n%4").arg(nLine).arg(parameterContainer).arg(mDescriptor).arg(fileName);
                    return(OPENCV_KPM_ERROR);
                }
            }
            if(prefix.compare(OPENCV_KPM_TAG_MATCHER,Qt::CaseInsensitive)==0)
            {
                if(parameterContainer.compare(mMatcher,Qt::CaseInsensitive)!=0)
                {
                    strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the matcher %2 is not equal previous value %3 \n in parameters file:\n%4").arg(nLine).arg(parameterContainer).arg(mMatcher).arg(fileName);
                    return(OPENCV_KPM_ERROR);
                }
            }
            if(prefix.compare(OPENCV_KPM_TAG_OUTLIERSDETECTOR,Qt::CaseInsensitive)==0)
            {
                if(parameterContainer.compare(mOutliersDetector,Qt::CaseInsensitive)!=0)
                {
                    strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the outliers detector %2 is not equal previous value %3 \n in parameters file:\n%4").arg(nLine).arg(parameterContainer).arg(mMatcher).arg(fileName);
                    return(OPENCV_KPM_ERROR);
                }
            }
        }
        QString parameterTag=splitedFirstTag.at(posParameterTag).trimmed();
        if(parameterTag.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter string %2 contains empty strings at center \n in parameters file:\n%3").arg(nLine).arg(firstTag).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        if(!mParametersTagsByGroup[parameterContainer].contains(parameterTag))
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter tag %2 is not valid \n in parameter container %3 in parameters file:\n%4").arg(nLine).arg(parameterTag).arg(parameterContainer).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString parameterType=splitedFirstTag.at(posParameterTag+1).trimmed();
        if(parameterType.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter string %2 contains empty strings at right \n in parameters file:\n%3").arg(nLine).arg(firstTag).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        if(!mParameterTypes.contains(parameterType,Qt::CaseSensitive))
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter type %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterType).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString strParameterValue=splitedLine.at(1).trimmed();
        if(strParameterValue.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter line %2 not contains value \n in parameters file:\n%3").arg(nLine).arg(line).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        if(strParameterValue.compare(OPENCV_KPM_DATABASE_TAG_TRUE,Qt::CaseInsensitive)==0)
            strParameterValue="1";
        if(strParameterValue.compare(OPENCV_KPM_DATABASE_TAG_FALSE,Qt::CaseInsensitive)==0)
            strParameterValue="0";
        int posInGroup=mParametersTagsByGroup[parameterContainer].indexOf(parameterTag);
        QString parameterTypeDefined=mParametersTypeByGroup[parameterContainer].at(posInGroup);
        QString parameterDefaultValueStr=mParametersDefaultValueByGroup[parameterContainer].at(posInGroup);
        QString parameterMinValueStr=mParametersMinimumValueByGroup[parameterContainer].at(posInGroup);
        QString parameterMaxValueStr=mParametersMaximumValueByGroup[parameterContainer].at(posInGroup);
        if(parameterTypeDefined.compare(parameterType,Qt::CaseSensitive)!=0)
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter type %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterType).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        if(parameterTypeDefined.compare(OPENCV_KPM_TAG_BOOL,Qt::CaseSensitive)==0)
        {
            bool okToInt=false;
            int value=strParameterValue.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value<0&&value>1)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is not valid (0/1) \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
        }
        else if(parameterTypeDefined.compare(OPENCV_KPM_TAG_INT,Qt::CaseSensitive)==0)
        {
            bool okToInt=false;
            int value=strParameterValue.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            int minValue=parameterMinValueStr.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter minimum value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterMinValueStr).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            int maxValue=parameterMaxValueStr.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter maximum value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterMaxValueStr).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value<minValue||value>maxValue)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is out of range \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
        }
        else if(parameterTypeDefined.compare(OPENCV_KPM_TAG_DOUBLE,Qt::CaseSensitive)==0)
        {
            bool okToDbl=false;
            double value=strParameterValue.toDouble(&okToDbl);
            if(!okToDbl)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            double minValue=parameterMinValueStr.toDouble(&okToDbl);
            if(!okToDbl)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter minimum value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterMinValueStr).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            double maxValue=parameterMaxValueStr.toDouble(&okToDbl);
            if(!okToDbl)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter maximum value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterMaxValueStr).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value<minValue||value>maxValue)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is out of range \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
        }
        if(splitedFirstTag.count() ==4)
        {
            if(prefix.compare(OPENCV_KPM_TAG_DETECTOR,Qt::CaseInsensitive)==0)
            {
                detectorParametersTag<<parameterTag;
                detectorParametersType<<parameterType;
                detectorParametersValue<<strParameterValue;
            }
            if(prefix.compare(OPENCV_KPM_TAG_DESCRIPTOR,Qt::CaseInsensitive)==0)
            {
                descriptorParametersTag<<parameterTag;
                descriptorParametersType<<parameterType;
                descriptorParametersValue<<strParameterValue;
            }
            if(prefix.compare(OPENCV_KPM_TAG_MATCHER,Qt::CaseInsensitive)==0)
            {
                matcherParametersTag<<parameterTag;
                matcherParametersType<<parameterType;
                matcherParametersValue<<strParameterValue;
            }
            if(prefix.compare(OPENCV_KPM_TAG_OUTLIERSDETECTOR,Qt::CaseInsensitive)==0)
            {
                outliersDetectorParametersTag<<parameterTag;
                outliersDetectorParametersType<<parameterType;
                outliersDetectorParametersValue<<strParameterValue;
            }
        }

        mParametersValueByGroup[parameterContainer][posInGroup]=strParameterValue;
    }
    if(mImagesPath.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, images path parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    if(mImagePairsFileName.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, image pairs file parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    QDir auxDir=QDir::currentPath();
    if(!auxDir.exists(mPathForMatchesFiles))
    {
        QString matchingPath=mImagesPath+"/"+MATCHING_PATH;
        if(!auxDir.exists(matchingPath))
        {
            if(!auxDir.mkdir(matchingPath))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, error making directory:\n%1").arg(matchingPath);
                return(OPENCV_KPM_ERROR);
            }
        }
        if(!auxDir.mkdir(mPathForMatchesFiles))
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, error making directory:\n%1").arg(mPathForMatchesFiles);
            return(OPENCV_KPM_ERROR);
        }
    }
    if(mSaveImagesMatches)
    {
        if(mPathForMatchesFiles.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, path for matches files parameter not exists \n in parameters file:\n%1").arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
    }
    if(mDetector.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, detector parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    if(mDescriptor.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, descriptor parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    if(mOutliersDetector.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, outliers detector parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    if(mMatcher.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, matcher parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    // Comprobar si son compatibles: detector, descriptor y matcher
    if(!mDescriptorsByDetector.contains(mDescriptor))
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, descriptor %1 is not valid for detector %2 \n in parameters file:\n%3").arg(mDescriptor).arg(mDetector).arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    QString detectorAndDescriptor=mDetector+mDescriptor;
    if(!mMatchersByDetectorAndDescriptor.contains(detectorAndDescriptor))
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, matcher %1 is not valid for detector %2 and descriptor %3 \n in parameters file:\n%3").arg(mMatcher).arg(mDetector).arg(mDescriptor).arg(fileName);
        return(OPENCV_KPM_ERROR);
    }

    QVector<QString> parametersToCheck;
    parametersToCheck.push_back(mDetector);
    parametersToCheck.push_back(mDescriptor);
    parametersToCheck.push_back(mMatcher);
    parametersToCheck.push_back(mOutliersDetector);
    // Comprobación de que se han leído todos los parámetros
    for(int i=0;i<parametersToCheck.size();i++)
    {
        QString parameterContainer=parametersToCheck[i];
        QStringList parameterValues=mParametersValueByGroup[parameterContainer];
        for(int i=0;i<parameterValues.size();i++)
        {
            QString parameterTag=mParametersTagsByGroup[parameterContainer].at(i);
            QString strValue=parameterValues.at(i);
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in group %1, not exists value for parameter %2 \n in parameters file:\n%1").arg(parameterContainer).arg(parameterTag).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
        }
    }
    mDetectorParametersTag=detectorParametersTag;
    mDetectorParametersType=detectorParametersType;
    mDetectorParametersValue=detectorParametersValue;
    mDescriptorParametersTag=descriptorParametersTag;
    mDescriptorParametersType=descriptorParametersType;
    mDescriptorParametersValue=descriptorParametersValue;
    mMatcherParametersTag=matcherParametersTag;
    mMatcherParametersType=matcherParametersType;
    mMatcherParametersValue=matcherParametersValue;
    mOutliersDetectorParametersTag=outliersDetectorParametersTag;
    mOutliersDetectorParametersType=outliersDetectorParametersType;
    mOutliersDetectorParametersValue=outliersDetectorParametersValue;
    mState=true;
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::writeDatabase(QString& strError)
{
    if(!mState)
    {
        strError=QObject::tr("OpenCVKpMParameters::writeDatabase, The object has not been initialized");

        return(OPENCV_KPM_ERROR);
    }
    return(OPENCV_KPM_NO_ERROR);
}

int OpenCVKpMParameters::writeParametersFileFromEngine(QString& detector,
                                                       QString& descriptor,
                                                       QString& matcher,
                                                       QVector<QParams::Param*>& detectorParameters,
                                                       QVector<QParams::Param*>& descriptorParameters,
                                                       QVector<QParams::Param*>& matcherParameters,
                                                       int& numberOfBestMatches,
                                                       bool& applyTestRatio,
                                                       double& testRatioValue,
                                                       bool& applyTestDistance,
                                                       double& testDistanceValue,
                                                       bool& applyOutliersDeteccion,
                                                       bool& applyOutliersAzimuth,
                                                       QVector<QParams::Param*>& outliersAzimuthParameters,
                                                       bool& applyOutliersDistance,
                                                       QVector<QParams::Param*>& outliersDistanceParameters,
                                                       QString& imagesBasePath,
                                                       QString &imagePairsFileName,
                                                       QString& parametersFileName,
                                                       QString& strError)
{
    QDir auxDir=QDir::currentPath();
    if(!auxDir.exists(imagesBasePath))
    {
        strError=QObject::tr("OpenCVKpM::writeParametersFileFromEngine, images base path does not exist:%1\n").arg(imagesBasePath);
        return(OPENCV_KPM_NO_ERROR);
    }
    if(!QFile::exists(imagePairsFileName))
    {
        strError=QObject::tr("OpenCVKpM::writeParametersFileFromEngine, images pairs file does not exist:%1\n").arg(imagePairsFileName);
        return(OPENCV_KPM_NO_ERROR);
    }
    QString targetPath=imagesBasePath+"/"+MATCHING_PATH;
    if(!auxDir.exists(targetPath))
    {
        if(!auxDir.mkdir(targetPath))
        {
            strError=QObject::tr("OpenCVKpMParameters::writeParametersFileFromEngine, error making directory:\n%1").arg(targetPath);
            return(OPENCV_KPM_ERROR);
        }
    }
    targetPath+="/";
    targetPath+=OPENCV_PREFIX_MATCHES_PATH;
    targetPath+=+MATCHING_PATH_STRING_SEPARATOR;
    targetPath+=detector;
    targetPath+=+MATCHING_PATH_STRING_SEPARATOR;
    targetPath+=descriptor;
    targetPath+=+MATCHING_PATH_STRING_SEPARATOR;
    targetPath+=matcher;
    if(!auxDir.exists(targetPath))
    {
        if(!auxDir.mkdir(targetPath))
        {
            strError=QObject::tr("OpenCVKpMParameters::writeParametersFileFromEngine, error making directory:\n%1").arg(targetPath);
            return(OPENCV_KPM_ERROR);
        }
    }
    parametersFileName=targetPath+"/"+OPENCV_KPM_PARAMETERSFILENAME;
    QFile parametersFile(parametersFileName);
    if(!parametersFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        strError=QObject::tr("OpenCVKpMParameters::writeParametersFileFromEngine, error opening file:\n%1").arg(parametersFileName);
        return(OPENCV_KPM_ERROR);
    }
    QTextStream out(&parametersFile);
    QString parameterCode;
    QParams::Param* ptrParam;
    int intValue;
    double dblValue;
    int precision;
    QString strValue;
    QString strPrefix;
    QString strLine;
    out<<"IMAGES-PATH #                                                                  "<<imagesBasePath<<endl;
    out<<"IMAGE-PAIRS-FILENAME  #                                                        "<<imagePairsFileName<<endl;
    out<<"SAVE-IMAGE-MATCHES #                                                           "<<OPENCV_KPM_SAVE_IMAGE_MATCHES_DEFAULT<<endl;
    out<<"BIDIRECTIONAL-MATCHES #                                                        "<<"1"<<endl;
    out<<"PATH-FOR-MATCHES-FILES  #                                                      "<<targetPath<<endl;
    out<<"DETECTOR-(FAST,ORB,SIFT,STAR,SURF,BRISK) #                                     "<<detector<<endl;
    out<<"DESCRIPTOR-(BRIEF,ORB,SIFT,SURF,BRISK) #                                       "<<descriptor<<endl;
    out<<"MATCHER-(BRUTEFORCE,FLANN) #                                                   "<<matcher<<endl;
    out<<"OUTLIERSDETECTOR-(OUTLIERS-DHL-KMEANS) #                                       "<<OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG<<endl;
    //out<<"MATCHINDISTANCE-(NORM_L2,NORM_HAMMING) #                       ";
    //<<OPENCV_KPM_MATCHINGDISTANCE_DEFAULT_TAG<<endl;

    // Detector
    strPrefix=OPENCV_KPM_TAG_DETECTOR;
    strPrefix+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    for(int i=0;i<detectorParameters.size();i++)
    {
        ptrParam=detectorParameters[i];
        QString parameterQParamsTag=ptrParam->getCode();
        strLine=strPrefix+parameterQParamsTag;
        strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
        if(dynamic_cast<QParams::ContinuousParam*>(ptrParam)!=NULL)
        {
            dblValue=dynamic_cast<QParams::ContinuousParam*>(ptrParam)->getValue();
            precision=dynamic_cast<QParams::ContinuousParam*>(ptrParam)->getPrecision();
            if(precision==0)
                strLine+=OPENCV_KPM_TAG_INT;
            else
                strLine+=OPENCV_KPM_TAG_DOUBLE;
            strValue=QString::number(dblValue,'f',precision);
        }
        if(dynamic_cast<QParams::DiscreteParam*>(ptrParam)!=NULL)
        {
            strValue=dynamic_cast<QParams::DiscreteParam*>(ptrParam)->getValue();
            strLine+=OPENCV_KPM_TAG_BOOL;
        }
        strLine+=" ";
        strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
        strLine=strLine.leftJustified(79,' ');
        strLine+=strValue;
        out<<strLine<<endl;
    }

    // Descriptor
    strPrefix=OPENCV_KPM_TAG_DESCRIPTOR;
    strPrefix+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    for(int i=0;i<descriptorParameters.size();i++)
    {
        ptrParam=descriptorParameters[i];
        QString parameterQParamsTag=ptrParam->getCode();
        strLine=strPrefix+parameterQParamsTag;
        strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
        if(dynamic_cast<QParams::ContinuousParam*>(ptrParam)!=NULL)
        {
            dblValue=dynamic_cast<QParams::ContinuousParam*>(ptrParam)->getValue();
            precision=dynamic_cast<QParams::ContinuousParam*>(ptrParam)->getPrecision();
            if(precision==0)
                strLine+=OPENCV_KPM_TAG_INT;
            else
                strLine+=OPENCV_KPM_TAG_DOUBLE;
            strValue=QString::number(dblValue,'f',precision);
        }
        if(dynamic_cast<QParams::DiscreteParam*>(ptrParam)!=NULL)
        {
            strValue=dynamic_cast<QParams::DiscreteParam*>(ptrParam)->getValue();
            strLine+=OPENCV_KPM_TAG_BOOL;
        }
        strLine+=" ";
        strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
        strLine=strLine.leftJustified(79,' ');
        strLine+=strValue;
        out<<strLine<<endl;
    }

    // Matcher
    strPrefix=OPENCV_KPM_TAG_MATCHER;
    strPrefix+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    for(int i=0;i<matcherParameters.size();i++)
    {
        ptrParam=matcherParameters[i];
        QString parameterQParamsTag=ptrParam->getCode();
        strLine=strPrefix+parameterQParamsTag;
        strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
        if(dynamic_cast<QParams::ContinuousParam*>(ptrParam)!=NULL)
        {
            dblValue=dynamic_cast<QParams::ContinuousParam*>(ptrParam)->getValue();
            precision=dynamic_cast<QParams::ContinuousParam*>(ptrParam)->getPrecision();
            if(precision==0)
                strLine+=OPENCV_KPM_TAG_INT;
            else
                strLine+=OPENCV_KPM_TAG_DOUBLE;
            strValue=QString::number(dblValue,'f',precision);
        }
        if(dynamic_cast<QParams::DiscreteParam*>(ptrParam)!=NULL)
        {
            strValue=dynamic_cast<QParams::DiscreteParam*>(ptrParam)->getValue();
            strLine+=OPENCV_KPM_TAG_BOOL;
        }
        strLine+=" ";
        strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
        strLine=strLine.leftJustified(79,' ');
        strLine+=strValue;
        out<<strLine<<endl;
    }
    //MATCHER_kBestMatches_int #                                     2
    strLine=OPENCV_KPM_TAG_MATCHER;
    strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    strLine+=OPENCV_KPM_MATCHER_KBESTMATCHES_TAG;
    strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    strLine+=OPENCV_KPM_TAG_INT;
    strLine+=" ";
    strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
    strLine=strLine.leftJustified(79,' ');
    strLine+=QString::number(numberOfBestMatches);
    out<<strLine<<endl;
    //MATCHER_applyRatioTestDistance_bool #                          1
    strLine=OPENCV_KPM_TAG_MATCHER;
    strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    strLine+=OPENCV_KPM_MATCHER_APPLYRATIOTESTDISTANCE_TAG;
    strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    strLine+=OPENCV_KPM_TAG_BOOL;
    strLine+=" ";
    strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
    strLine=strLine.leftJustified(79,' ');
    if(applyTestRatio)
        strLine+=QString::number(1);
    else
        strLine+=QString::number(0);
    out<<strLine<<endl;
//    if(applyTestRatio)//MATCHER_ratioTestDistance_dbl #                                0.80
//    {
        strLine=OPENCV_KPM_TAG_MATCHER;
        strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
        strLine+=OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_TAG;
        strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
        strLine+=OPENCV_KPM_TAG_DOUBLE;
        strLine+=" ";
        strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
        strLine=strLine.leftJustified(79,' ');
        strLine+=QString::number(testRatioValue,'f',2);
        out<<strLine<<endl;
//    }
    //MATCHER_applyMinimumTestDistance_bool #                        1
    strLine=OPENCV_KPM_TAG_MATCHER;
    strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    strLine+=OPENCV_KPM_MATCHER_APPLYMINIMUMTESTDISTANCE_TAG;
    strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    strLine+=OPENCV_KPM_TAG_BOOL;
    strLine+=" ";
    strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
    strLine=strLine.leftJustified(79,' ');
    if(applyTestDistance)
        strLine+=QString::number(1);
    else
        strLine+=QString::number(0);
    out<<strLine<<endl;
//    if(applyTestDistance)//MATCHER_minimumTestDistance_dbl #                              1.60
//    {
        strLine=OPENCV_KPM_TAG_MATCHER;
        strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
        strLine+=OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_TAG;
        strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
        strLine+=OPENCV_KPM_TAG_DOUBLE;
        strLine+=" ";
        strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
        strLine=strLine.leftJustified(79,' ');
        strLine+=QString::number(testDistanceValue,'f',2);
        out<<strLine<<endl;
//    }

    //Outliers
    strLine=OPENCV_KPM_TAG_OUTLIERSDETECTOR;
    strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    strLine+=OPENCV_KPM_OUTLIERS_DHL_KMEANS_APPLYDETECTION_QPARAMS_TAG;
    strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
    strLine+=OPENCV_KPM_TAG_BOOL;
    strLine+=" ";
    strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
    strLine=strLine.leftJustified(79,' ');
    if(applyOutliersDeteccion
            &&(applyOutliersAzimuth||applyOutliersDistance))
        strLine+=QString::number(1);
    else
        strLine+=QString::number(0);
    out<<strLine<<endl;
// *************************************************
    if(applyOutliersDeteccion
            &&(applyOutliersAzimuth||applyOutliersDistance))
    {
        if(applyOutliersAzimuth)
        {
// *************************************************
            for(int i=0;i<outliersAzimuthParameters.size();i++)
            {
                ptrParam=outliersAzimuthParameters[i];
                QString parameterQParamsTag=ptrParam->getCode();
                strLine=OPENCV_KPM_TAG_OUTLIERSDETECTOR;
                strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
                strLine+=parameterQParamsTag;
                strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
                if(dynamic_cast<QParams::ContinuousParam*>(ptrParam)!=NULL)
                {
                    dblValue=dynamic_cast<QParams::ContinuousParam*>(ptrParam)->getValue();
                    precision=dynamic_cast<QParams::ContinuousParam*>(ptrParam)->getPrecision();
                    if(precision==0)
                        strLine+=OPENCV_KPM_TAG_INT;
                    else
                        strLine+=OPENCV_KPM_TAG_DOUBLE;
                    strValue=QString::number(dblValue,'f',precision);
                }
                if(dynamic_cast<QParams::DiscreteParam*>(ptrParam)!=NULL)
                {
                    strValue=dynamic_cast<QParams::DiscreteParam*>(ptrParam)->getValue();
                    strLine+=OPENCV_KPM_TAG_BOOL;
                }
                strLine+=" ";
                strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
                strLine=strLine.leftJustified(79,' ');
                strLine+=strValue;
                out<<strLine<<endl;
            }
// *************************************************
        }
        if(applyOutliersDistance)
        {
// *************************************************
            for(int i=0;i<outliersDistanceParameters.size();i++)
            {
                ptrParam=outliersDistanceParameters[i];
                QString parameterQParamsTag=ptrParam->getCode();
                strLine=OPENCV_KPM_TAG_OUTLIERSDETECTOR;
                strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
                strLine+=parameterQParamsTag;
                strLine+=OPENCV_KPM_TAG_STRING_SEPARATOR;
                if(dynamic_cast<QParams::ContinuousParam*>(ptrParam)!=NULL)
                {
                    dblValue=dynamic_cast<QParams::ContinuousParam*>(ptrParam)->getValue();
                    precision=dynamic_cast<QParams::ContinuousParam*>(ptrParam)->getPrecision();
                    if(precision==0)
                        strLine+=OPENCV_KPM_TAG_INT;
                    else
                        strLine+=OPENCV_KPM_TAG_DOUBLE;
                    strValue=QString::number(dblValue,'f',precision);
                }
                if(dynamic_cast<QParams::DiscreteParam*>(ptrParam)!=NULL)
                {
                    strValue=dynamic_cast<QParams::DiscreteParam*>(ptrParam)->getValue();
                    strLine+=OPENCV_KPM_TAG_BOOL;
                }
                strLine+=" ";
                strLine+=OPENCV_KPM_VALUE_STRING_SEPARATOR;
                strLine=strLine.leftJustified(79,' ');
                strLine+=strValue;
                out<<strLine<<endl;
            }
// *************************************************
        }
    }
// *************************************************

    parametersFile.close();
    return(OPENCV_KPM_NO_ERROR);
}

bool OpenCVKpMParameters::isOk()
{
    return(mState);
}

void OpenCVKpMParameters::initialize()
{
    mBidirectionalMatches=false;
    mState=false;
    mImagesPath="";
    mImagePairsFileName="";
    mPathForMatchesFiles="";
    mDetector="";
    mDescriptor="";
    mMatchingDistance="";
    mMatcher="";
    mOutliersDetector="";
    mDetectors.clear();
    mDescriptors.clear();
    mMatchers.clear();
    mMatchingDistances.clear();
    mOutliersDetectors.clear();
    mParameterTypes.clear();
    mParametersTagsByGroup.clear();
    mParametersTypeByGroup.clear();
    mParametersDefaultValueByGroup.clear();
    mParametersMinimumValueByGroup.clear();
    mParametersMaximumValueByGroup.clear();
    mParametersValueByGroup.clear();
    mDescriptorsByDetector.clear();
    mDefaultDescriptorByDetector.clear();
    mSaveImagesMatches=false;

    //     mDetectors<<OPENCV_KPM_DETECTOR_DENSE_TAG;
    mDetectors<<OPENCV_KPM_DETECTOR_FAST_TAG;
    //     mDetectors<<OPENCV_KPM_DETECTOR_GFTT_TAG;
    //     mDetectors<<OPENCV_KPM_DETECTOR_MSER_TAG;
    mDetectors<<OPENCV_KPM_DETECTOR_ORB_TAG;
    mDetectors<<OPENCV_KPM_DETECTOR_SIFT_TAG;
    mDetectors<<OPENCV_KPM_DETECTOR_STAR_TAG;
    mDetectors<<OPENCV_KPM_DETECTOR_SURF_TAG;
    mDetectors<<OPENCV_KPM_DETECTOR_BRISK_TAG;

    //     mDescriptors<<OPENCV_KPM_DESCRIPTOR_FREAK_TAG;
    mDescriptors<<OPENCV_KPM_DESCRIPTOR_BRIEF_TAG;
    mDescriptors<<OPENCV_KPM_DESCRIPTOR_ORB_TAG;
    mDescriptors<<OPENCV_KPM_DESCRIPTOR_SIFT_TAG;
    mDescriptors<<OPENCV_KPM_DESCRIPTOR_SURF_TAG;
    mDescriptors<<OPENCV_KPM_DESCRIPTOR_BRISK_TAG;

    QStringList auxDescriptors;
    auxDescriptors<<OPENCV_KPM_DESCRIPTOR_BRIEF_TAG;
    auxDescriptors<<OPENCV_KPM_DESCRIPTOR_ORB_TAG;
    auxDescriptors<<OPENCV_KPM_DESCRIPTOR_SIFT_TAG;
    auxDescriptors<<OPENCV_KPM_DESCRIPTOR_SURF_TAG;
    auxDescriptors<<OPENCV_KPM_DESCRIPTOR_BRISK_TAG;

    mDescriptorsByDetector[OPENCV_KPM_DETECTOR_FAST_TAG]=auxDescriptors;
    mDescriptorsByDetector[OPENCV_KPM_DETECTOR_ORB_TAG]=auxDescriptors;
    mDescriptorsByDetector[OPENCV_KPM_DETECTOR_SIFT_TAG]=auxDescriptors;
    mDescriptorsByDetector[OPENCV_KPM_DETECTOR_STAR_TAG]=auxDescriptors;
    mDescriptorsByDetector[OPENCV_KPM_DETECTOR_SURF_TAG]=auxDescriptors;
    mDescriptorsByDetector[OPENCV_KPM_DETECTOR_BRISK_TAG]=auxDescriptors;

    mDefaultDescriptorByDetector[OPENCV_KPM_DETECTOR_FAST_TAG]=OPENCV_KPM_DESCRIPTOR_BRIEF_TAG;
    mDefaultDescriptorByDetector[OPENCV_KPM_DETECTOR_ORB_TAG]=OPENCV_KPM_DESCRIPTOR_ORB_TAG;
    mDefaultDescriptorByDetector[OPENCV_KPM_DETECTOR_SIFT_TAG]=OPENCV_KPM_DESCRIPTOR_SIFT_TAG;
    mDefaultDescriptorByDetector[OPENCV_KPM_DETECTOR_STAR_TAG]=OPENCV_KPM_DESCRIPTOR_SIFT_TAG;
    mDefaultDescriptorByDetector[OPENCV_KPM_DETECTOR_SURF_TAG]=OPENCV_KPM_DESCRIPTOR_SURF_TAG;
    mDefaultDescriptorByDetector[OPENCV_KPM_DETECTOR_BRISK_TAG]=OPENCV_KPM_DESCRIPTOR_BRISK_TAG;

    mMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
    mMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
    mMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
    mMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
    mMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
    mMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;

    QString detectorAndDescriptorDetector=OPENCV_KPM_DETECTOR_FAST_TAG;
    {
        QString detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRIEF_TAG;
        QStringList auxMatchers;
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_ORB_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SIFT_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SURF_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRISK_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
    }

    detectorAndDescriptorDetector=OPENCV_KPM_DETECTOR_ORB_TAG;
    {
        QString detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRIEF_TAG;
        QStringList auxMatchers;
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_ORB_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SIFT_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SURF_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRISK_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
    }

    detectorAndDescriptorDetector=OPENCV_KPM_DETECTOR_SIFT_TAG;
    {
        QString detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRIEF_TAG;
        QStringList auxMatchers;
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_ORB_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SIFT_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SURF_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRISK_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
    }

    detectorAndDescriptorDetector=OPENCV_KPM_DETECTOR_STAR_TAG;
    {
        QString detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRIEF_TAG;
        QStringList auxMatchers;
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_ORB_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SIFT_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SURF_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRISK_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
    }

    detectorAndDescriptorDetector=OPENCV_KPM_DETECTOR_SURF_TAG;
    {
        QString detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRIEF_TAG;
        QStringList auxMatchers;
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_ORB_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SIFT_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SURF_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRISK_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
    }

    detectorAndDescriptorDetector=OPENCV_KPM_DETECTOR_BRISK_TAG;
    {
        QString detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRIEF_TAG;
        QStringList auxMatchers;
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_ORB_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SIFT_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_SURF_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;

        detectorAndDescriptor=detectorAndDescriptorDetector;
        detectorAndDescriptor+=OPENCV_KPM_DESCRIPTOR_BRISK_TAG;
        auxMatchers.clear();
        auxMatchers<<OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG;
        auxMatchers<<OPENCV_KPM_MATCHER_FLANN_LSH_TAG;
        mMatchersByDetectorAndDescriptor[detectorAndDescriptor]<<auxMatchers;
        mDefaultMatcherByDetectorAndDescriptor[detectorAndDescriptor]=OPENCV_KPM_MATCHER_BRUTEFORCE_TAG;
    }

    //     mMatchingDistances<<OPENCV_KPM_MATCHINGDISTANCE_NORM_INF_TAG;
    //     mMatchingDistances<<OPENCV_KPM_MATCHINGDISTANCE_NORM_L1_TAG;
    mMatchingDistances<<OPENCV_KPM_MATCHINGDISTANCE_NORM_L2_TAG;
    //     mMatchingDistances<<OPENCV_KPM_MATCHINGDISTANCE_NORM_L2SQR_TAG;
    mMatchingDistances<<OPENCV_KPM_MATCHINGDISTANCE_NORM_HAMMING_TAG;
    //     mMatchingDistances<<OPENCV_KPM_MATCHINGDISTANCE_NORM_HAMMING2_TAG;
    //     mMatchingDistances<<OPENCV_KPM_MATCHINGDISTANCE_NORM_TYPE_MASK_TAG;
    //     mMatchingDistances<<OPENCV_KPM_MATCHINGDISTANCE_NORM_RELATIVE_TAG;
    //     mMatchingDistances<<OPENCV_KPM_MATCHINGDISTANCE_NORM_MINMAX_TAG;

    mOutliersDetectors<<OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG;

    mParameterTypes<<OPENCV_KPM_TAG_INT;
    mParameterTypes<<OPENCV_KPM_TAG_DOUBLE;
    mParameterTypes<<OPENCV_KPM_TAG_BOOL;
    mParameterTypes<<OPENCV_KPM_TAG_STRING;

    mParametersTagsByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_APPLYDETECTION_TAG;
    mParametersTypeByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_APPLYDETECTION_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_APPLYDETECTION_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<"";
    mParametersMaximumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<"";
    mParametersValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHNUMBEROFCLUSTERS_MAX;
    mParametersValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_TAG;
    mParametersTypeByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHEPSILONDEG_MAX;
    mParametersValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_AZIMUTHITERATIONS_MAX;
    mParametersValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCENUMBEROFCLUSTERS_MAX;
    mParametersValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_TAG;
    mParametersTypeByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEEPSILON_MAX;
    mParametersValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<OPENCV_KPM_OUTLIERS_DHL_KMEANS_DISTANCEITERATIONS_MAX;
    mParametersValueByGroup[OPENCV_KPM_OUTLIERSDETECTOR_DHL_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_OCTAVES_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_OCTAVES_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_OCTAVES_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_OCTAVES_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_OCTAVES_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_OCTAVES_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_PATTERSCALE_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_PATTERSCALE_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_PATTERSCALE_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_PATTERSCALE_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_PATTERSCALE_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_PATTERSCALE_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_THRESH_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_THRESH_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_THRESH_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_THRESH_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_THRESH_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<OPENCV_KPM_BRISK_THRESH_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_BRISK_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DESCRIPTOR_BRIEF_TAG]<<OPENCV_KPM_BRIEF_BYTES_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DESCRIPTOR_BRIEF_TAG]<<OPENCV_KPM_BRIEF_BYTES_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DESCRIPTOR_BRIEF_TAG]<<OPENCV_KPM_BRIEF_BYTES_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DESCRIPTOR_BRIEF_TAG]<<OPENCV_KPM_BRIEF_BYTES_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DESCRIPTOR_BRIEF_TAG]<<OPENCV_KPM_BRIEF_BYTES_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DESCRIPTOR_BRIEF_TAG]<<OPENCV_KPM_BRIEF_BYTES_MAX;
    mParametersValueByGroup[OPENCV_KPM_DESCRIPTOR_BRIEF_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALELEVELS_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALELEVELS_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALELEVELS_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALELEVELS_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALELEVELS_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALELEVELS_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALEMUL_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALEMUL_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALEMUL_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALEMUL_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALEMUL_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_FEATURESCALEMUL_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITFEATURESCALE_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITFEATURESCALE_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITFEATURESCALE_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITFEATURESCALE_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITFEATURESCALE_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITFEATURESCALE_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITIMGBOUND_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITIMGBOUND_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITIMGBOUND_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITIMGBOUND_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITIMGBOUND_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITIMGBOUND_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITXYSTEP_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITXYSTEP_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITXYSTEP_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITXYSTEP_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITXYSTEP_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_INITXYSTEP_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_VARYIMGBOUNDWITHSCALE_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_VARYIMGBOUNDWITHSCALE_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_VARYIMGBOUNDWITHSCALE_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_VARYIMGBOUNDWITHSCALE_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_VARYXYSTEPWITHSCALE_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_VARYXYSTEPWITHSCALE_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_VARYXYSTEPWITHSCALE_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<OPENCV_KPM_DENSE_VARYXYSTEPWITHSCALE_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_DENSE_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_NOCTAVES_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_NOCTAVES_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_NOCTAVES_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_NOCTAVES_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_NOCTAVES_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_NOCTAVES_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_ORIENTATIONNORMALIZED_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_ORIENTATIONNORMALIZED_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_ORIENTATIONNORMALIZED_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_ORIENTATIONNORMALIZED_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<"";
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<"";
    //     mParametersValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_PATTERNSCALE_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_PATTERNSCALE_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_PATTERNSCALE_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_PATTERNSCALE_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_PATTERNSCALE_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_PATTERNSCALE_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_SCALENORMALIZED_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_SCALENORMALIZED_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_SCALENORMALIZED_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<OPENCV_KPM_FREAK_SCALENORMALIZED_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<"";
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<"";
    //     mParametersValueByGroup[OPENCV_KPM_DESCRIPTOR_FREAK_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<OPENCV_KPM_FAST_NONMAXSUPPRESSION_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<OPENCV_KPM_FAST_NONMAXSUPPRESSION_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<OPENCV_KPM_FAST_NONMAXSUPPRESSION_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<OPENCV_KPM_FAST_NONMAXSUPPRESSION_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<"";
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<"";
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<OPENCV_KPM_FAST_THRESHOLD_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<OPENCV_KPM_FAST_THRESHOLD_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<OPENCV_KPM_FAST_THRESHOLD_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<OPENCV_KPM_FAST_THRESHOLD_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<OPENCV_KPM_FAST_THRESHOLD_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<OPENCV_KPM_FAST_THRESHOLD_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_FAST_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_BLOCKSIZE_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_BLOCKSIZE_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_BLOCKSIZE_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_BLOCKSIZE_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_BLOCKSIZE_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_BLOCKSIZE_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_K_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_K_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_K_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_K_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_K_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_K_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MAXCORNERS_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MAXCORNERS_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MAXCORNERS_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MAXCORNERS_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MAXCORNERS_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MAXCORNERS_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MINDISTANCE_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MINDISTANCE_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MINDISTANCE_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MINDISTANCE_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MINDISTANCE_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_MINDISTANCE_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_QUALITYLEVEL_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_QUALITYLEVEL_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_QUALITYLEVEL_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_QUALITYLEVEL_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_QUALITYLEVEL_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_QUALITYLEVEL_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_USEHARRISDETECTOR_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_USEHARRISDETECTOR_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_USEHARRISDETECTOR_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<OPENCV_KPM_GFTT_USEHARRISDETECTOR_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<"";
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<"";
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_GFTT_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_AREATHRESHOLD_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_AREATHRESHOLD_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_AREATHRESHOLD_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_AREATHRESHOLD_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_AREATHRESHOLD_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_AREATHRESHOLD_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_DELTA_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_DELTA_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_DELTA_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_DELTA_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_DELTA_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_DELTA_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_EDGEBLURSIZE_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_EDGEBLURSIZE_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_EDGEBLURSIZE_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_EDGEBLURSIZE_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_EDGEBLURSIZE_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_EDGEBLURSIZE_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXAREA_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXAREA_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXAREA_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXAREA_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXAREA_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXAREA_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXEVOLUTION_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXEVOLUTION_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXEVOLUTION_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXEVOLUTION_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXEVOLUTION_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXEVOLUTION_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXVARIATION_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXVARIATION_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXVARIATION_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXVARIATION_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXVARIATION_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MAXVARIATION_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINAREA_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINAREA_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINAREA_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINAREA_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINAREA_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINAREA_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINDIVERSITY_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINDIVERSITY_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINDIVERSITY_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINDIVERSITY_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINDIVERSITY_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINDIVERSITY_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<"";

    //     mParametersTagsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINMARGIN_TAG;
    //     mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINMARGIN_QPARAMS_TAG;
    //     mParametersTypeByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINMARGIN_TYPE;
    //     mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINMARGIN_DEFAULT;
    //     mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINMARGIN_MIN;
    //     mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<OPENCV_KPM_MSER_MINMARGIN_MAX;
    //     mParametersValueByGroup[OPENCV_KPM_DETECTOR_MSER_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_WTA_K_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_WTA_K_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_WTA_K_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_WTA_K_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_WTA_K_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_WTA_K_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_EDGETHRESHOLD_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_EDGETHRESHOLD_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_EDGETHRESHOLD_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_EDGETHRESHOLD_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_EDGETHRESHOLD_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_EDGETHRESHOLD_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_FIRSTLEVEL_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_FIRSTLEVEL_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_FIRSTLEVEL_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_FIRSTLEVEL_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_FIRSTLEVEL_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_FIRSTLEVEL_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NFEATURES_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NFEATURES_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NFEATURES_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NFEATURES_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NFEATURES_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NFEATURES_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NLEVELS_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NLEVELS_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NLEVELS_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NLEVELS_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NLEVELS_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_NLEVELS_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_PATCHSIZE_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_PATCHSIZE_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_PATCHSIZE_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_PATCHSIZE_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_PATCHSIZE_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_PATCHSIZE_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCALEFACTOR_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCALEFACTOR_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCALEFACTOR_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCALEFACTOR_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCALEFACTOR_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCALEFACTOR_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCORETYPE_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCORETYPE_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCORETYPE_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCORETYPE_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCORETYPE_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<OPENCV_KPM_ORB_SCORETYPE_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_ORB_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_CONTRASTTHRESHOLD_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_EDGETHRESHOLD_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_EDGETHRESHOLD_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_EDGETHRESHOLD_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_EDGETHRESHOLD_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_EDGETHRESHOLD_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_EDGETHRESHOLD_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NOCTAVELAYERS_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NOCTAVELAYERS_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NOCTAVELAYERS_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NOCTAVELAYERS_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NOCTAVELAYERS_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NOCTAVELAYERS_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NFEATURES_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NFEATURES_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NFEATURES_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NFEATURES_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NFEATURES_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_NFEATURES_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_SIGMA_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_SIGMA_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_SIGMA_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_SIGMA_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_SIGMA_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<OPENCV_KPM_SIFT_SIGMA_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_SIFT_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_EXTENDED_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_EXTENDED_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_EXTENDED_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_EXTENDED_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<"";
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<"";
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_HESSIANTHRESHOLD_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_HESSIANTHRESHOLD_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_HESSIANTHRESHOLD_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_HESSIANTHRESHOLD_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_HESSIANTHRESHOLD_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_HESSIANTHRESHOLD_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVELAYERS_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVELAYERS_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVELAYERS_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVELAYERS_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVELAYERS_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVELAYERS_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVES_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVES_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVES_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVES_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVES_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_NOCTAVES_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_UPRIGHT_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_UPRIGHT_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_UPRIGHT_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<OPENCV_KPM_SURF_UPRIGHT_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<"";
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<"";
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_SURF_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDBINARIZED_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_LINETHRESHOLDPROJECTED_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_MAXSIZE_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_MAXSIZE_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_MAXSIZE_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_MAXSIZE_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_MAXSIZE_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_MAXSIZE_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_RESPONSETHRESHOLD_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_RESPONSETHRESHOLD_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_RESPONSETHRESHOLD_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_RESPONSETHRESHOLD_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_RESPONSETHRESHOLD_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_RESPONSETHRESHOLD_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<OPENCV_KPM_STAR_SUPPRESSNONMAXSIZE_MAX;
    mParametersValueByGroup[OPENCV_KPM_DETECTOR_STAR_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_BRUTEFORCE_TAG]<<OPENCV_KPM_BRUTEFORCE_CROSSCHECK_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_BRUTEFORCE_TAG]<<OPENCV_KPM_BRUTEFORCE_CROSSCHECK_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_BRUTEFORCE_TAG]<<OPENCV_KPM_BRUTEFORCE_CROSSCHECK_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_BRUTEFORCE_TAG]<<OPENCV_KPM_BRUTEFORCE_CROSSCHECK_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_BRUTEFORCE_TAG]<<"";
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_BRUTEFORCE_TAG]<<"";
    mParametersValueByGroup[OPENCV_KPM_MATCHER_BRUTEFORCE_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_KBESTMATCHES_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_KBESTMATCHES_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_KBESTMATCHES_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_KBESTMATCHES_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_KBESTMATCHES_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_KBESTMATCHES_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_APPLYRATIOTESTDISTANCE_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_APPLYRATIOTESTDISTANCE_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_APPLYRATIOTESTDISTANCE_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_APPLYRATIOTESTDISTANCE_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_TAG]<<"";
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_TAG]<<"";
    mParametersValueByGroup[OPENCV_KPM_MATCHER_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_RATIOTESTDISTANCE_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_APPLYMINIMUMTESTDISTANCE_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_APPLYMINIMUMTESTDISTANCE_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_APPLYMINIMUMTESTDISTANCE_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_APPLYMINIMUMTESTDISTANCE_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_TAG]<<"";
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_TAG]<<"";
    mParametersValueByGroup[OPENCV_KPM_MATCHER_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_TAG]<<OPENCV_KPM_MATCHER_MINIMUMTESTDISTANCE_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG]<<OPENCV_KPM_FLANN_KDTREE_TREES_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG]<<OPENCV_KPM_FLANN_KDTREE_TREES_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG]<<OPENCV_KPM_FLANN_KDTREE_TREES_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG]<<OPENCV_KPM_FLANN_KDTREE_TREES_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG]<<OPENCV_KPM_FLANN_KDTREE_TREES_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG]<<OPENCV_KPM_FLANN_KDTREE_TREES_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_KDTREE_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_BRANCHING_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_BRANCHING_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_BRANCHING_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_BRANCHING_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_BRANCHING_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_BRANCHING_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CBINDEX_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CBINDEX_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CBINDEX_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CBINDEX_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CBINDEX_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CBINDEX_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_CENTERSINIT_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_ITERATIONS_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_ITERATIONS_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_ITERATIONS_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_ITERATIONS_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_ITERATIONS_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<OPENCV_KPM_FLANN_KMEANS_ITERATIONS_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_KMEANS_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_BRANCHING_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CBINDEX_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_CENTERSINIT_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_ITERATIONS_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_TREES_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_TREES_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_TREES_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_TREES_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_TREES_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<OPENCV_KPM_FLANN_COMPOSITE_TREES_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_COMPOSITE_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_BUILDWEIGHT_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_MEMORYWEIGHT_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_SAMPLEFRACTION_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<OPENCV_KPM_FLANN_AUTOTUNED_TARGETPRECISION_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_AUTOTUNED_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_KEYSIZE_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_KEYSIZE_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_KEYSIZE_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_KEYSIZE_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_KEYSIZE_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_KEYSIZE_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_MULTIPROBELEVEL_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<"";

    mParametersTagsByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_TABLENUMBER_TAG;
    mParametersTagsQParamsByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_TABLENUMBER_QPARAMS_TAG;
    mParametersTypeByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_TABLENUMBER_TYPE;
    mParametersDefaultValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_TABLENUMBER_DEFAULT;
    mParametersMinimumValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_TABLENUMBER_MIN;
    mParametersMaximumValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<OPENCV_KPM_FLANN_LSH_TABLENUMBER_MAX;
    mParametersValueByGroup[OPENCV_KPM_MATCHER_FLANN_LSH_TAG]<<"";

    /*
     mParametersTagsByGroup[]<<;
     mParametersTagsQParamsByGroup[]<<;
     mParametersTypeByGroup[]<<;
     mParametersDefaultValueByGroup[]<<;
     mParametersMinimumValueByGroup[]<<;
     mParametersMaximumValueByGroup[]<<;
     mParametersValueByGroup[]<<"";
     */
}

/*

bool OpenCVKpMParameters::setFromFile(QString& fileName,
                                      QString& strError)
{
    initialize();
    if(!QFile::exists(fileName))
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, file not exists:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    QFile parametersFile(fileName);
    if(!parametersFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, error opening file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    int nLine=0;
    mImagesPath=OPENCV_KPM_NO_STRING_VALUE;
    mImagePairsFileName=OPENCV_KPM_NO_STRING_VALUE;
    mRelativePathForMatchesFiles=OPENCV_KPM_NO_STRING_VALUE;
    mDetector=OPENCV_KPM_NO_STRING_VALUE;
    mDescriptor=OPENCV_KPM_NO_STRING_VALUE;
    mOutliersDetector=OPENCV_KPM_NO_STRING_VALUE;
    mMatcher=OPENCV_KPM_NO_STRING_VALUE;
    mMatchingDistance=OPENCV_KPM_NO_STRING_VALUE;
    mSaveImagesMatches=false;
    while (!parametersFile.atEnd())
    {
        nLine++;
        QString line = parametersFile.readLine();
        QStringList splitedLine = line.simplified().split(OPENCV_KPM_VALUE_STRING_SEPARATOR);
        if(splitedLine.count() != 2)
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the string %2 not contains two strings separated by %3 \n in parameters file:\n%4").arg(nLine).arg(line).arg(OPENCV_KPM_VALUE_STRING_SEPARATOR).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString leftStrValue=splitedLine.at(0).trimmed();
        if(leftStrValue.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the string %2 contains empty strings at left \n in parameters file:\n%3").arg(nLine).arg(line).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString rightStrValue=splitedLine.at(1).trimmed();
        if(rightStrValue.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the string %2 contains empty strings at right \n in parameters file:\n%3").arg(nLine).arg(line).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString tag=splitedLine.at(0).trimmed();
        if(tag.compare(OPENCV_KPM_TAG_IMAGES_PATH,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, images path is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            QDir auxDir=QDir::current();
            if(!auxDir.exists(strValue))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, not exists images path parameter:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mImagesPath=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_IMAGE_PAIRS_FILENAME,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, image pairs filename parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!QFile::exists(strValue))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, not exists image pairs file name parameter:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mImagePairsFileName=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_SAVE_IMAGE_MATCHES,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            bool okToInt=false;
            int value=strValue.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, save images matches parameter no int value: %1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value<0&&value>1)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, save images matches must be 0 or 1, not %1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value==1)
                mSaveImagesMatches=true;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_RELATIVE_PATH_FOR_MATCHES_FILES,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, relative path for matches files is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mRelativePathForMatchesFiles=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_DETECTORS,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, detector selected parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!mDetectors.contains(strValue,Qt::CaseSensitive))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, detector selected parameter is not valid:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mDetector=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_DESCRIPTORS,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, descriptor selected parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!mDescriptors.contains(strValue,Qt::CaseSensitive))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, descriptor selected parameter is not valid:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mDescriptor=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_OUTLIERSDETECTORS,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, outliers detector selected parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!mOutliersDetectors.contains(strValue,Qt::CaseSensitive))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, outliers detector selected parameter is not valid:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mOutliersDetector=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_MATCHERS,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, matcher selected parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!mMatchers.contains(strValue,Qt::CaseSensitive))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, matcher selected parameter is not valid:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mMatcher=strValue;
            continue;
        }
        if(tag.compare(OPENCV_KPM_TAG_MATCHINGDISTANCES,Qt::CaseInsensitive)==0)
        {
            QString strValue=splitedLine.at(1).trimmed();
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, matching distance selected parameter is empty \n in parameters file:\n%1").arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(!mMatchingDistances.contains(strValue,Qt::CaseSensitive))
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, matching distance selected parameter is not valid:\n%1 \n in parameters file:\n%2").arg(strValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            mMatchingDistance=strValue;
            continue;
        }
        QString firstTag=splitedLine.at(0).trimmed();
        QStringList splitedFirstTag = firstTag.simplified().split(OPENCV_KPM_TAG_STRING_SEPARATOR);
        if(splitedFirstTag.count() != 3)
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 parameter tag %2 not contains three strings separated by %3 \n in parameters file:\n%4").arg(nLine).arg(firstTag).arg(OPENCV_KPM_TAG_STRING_SEPARATOR).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString parameterContainer=splitedFirstTag.at(0).trimmed();
        if(parameterContainer.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter string %2 contains empty strings at left \n in parameters file:\n%3").arg(nLine).arg(firstTag).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        if(!mParametersTagsByGroup.contains(parameterContainer))
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter container %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterContainer).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString parameterTag=splitedFirstTag.at(1).trimmed();
        if(parameterTag.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter string %2 contains empty strings at center \n in parameters file:\n%3").arg(nLine).arg(firstTag).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        if(!mParametersTagsByGroup[parameterContainer].contains(parameterTag))
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter tag %2 is not valid \n in parameter container %3 in parameters file:\n%4").arg(nLine).arg(parameterTag).arg(parameterContainer).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString parameterType=splitedFirstTag.at(2).trimmed();
        if(parameterType.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter string %2 contains empty strings at right \n in parameters file:\n%3").arg(nLine).arg(firstTag).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        if(!mParameterTypes.contains(parameterType,Qt::CaseSensitive))
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter type %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterType).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        QString strParameterValue=splitedLine.at(1).trimmed();
        if(strParameterValue.isEmpty())
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter line %2 not contains value \n in parameters file:\n%3").arg(nLine).arg(line).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        int posInGroup=mParametersTagsByGroup[parameterContainer].indexOf(parameterTag);
        QString parameterTypeDefined=mParametersTypeByGroup[parameterContainer].at(posInGroup);
        QString parameterDefaultValueStr=mParametersDefaultValueByGroup[parameterContainer].at(posInGroup);
        QString parameterMinValueStr=mParametersMinimumValueByGroup[parameterContainer].at(posInGroup);
        QString parameterMaxValueStr=mParametersMaximumValueByGroup[parameterContainer].at(posInGroup);
        if(parameterTypeDefined.compare(parameterType,Qt::CaseSensitive)!=0)
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter type %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterType).arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
        if(parameterTypeDefined.compare(OPENCV_KPM_TAG_BOOL,Qt::CaseSensitive)==0)
        {
            bool okToInt=false;
            int value=strParameterValue.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value<0&&value>1)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is not valid (0/1) \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
        }
        else if(parameterTypeDefined.compare(OPENCV_KPM_TAG_INT,Qt::CaseSensitive)==0)
        {
            bool okToInt=false;
            int value=strParameterValue.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            int minValue=parameterMinValueStr.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter minimum value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterMinValueStr).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            int maxValue=parameterMaxValueStr.toInt(&okToInt);
            if(!okToInt)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter maximum value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterMaxValueStr).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value<minValue||value>maxValue)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is out of range \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
        }
        else if(parameterTypeDefined.compare(OPENCV_KPM_TAG_DOUBLE,Qt::CaseSensitive)==0)
        {
            bool okToDbl=false;
            double value=strParameterValue.toDouble(&okToDbl);
            if(!okToDbl)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            double minValue=parameterMinValueStr.toDouble(&okToDbl);
            if(!okToDbl)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter minimum value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterMinValueStr).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            double maxValue=parameterMaxValueStr.toDouble(&okToDbl);
            if(!okToDbl)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter maximum value %2 is not valid \n in parameters file:\n%3").arg(nLine).arg(parameterMaxValueStr).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
            if(value<minValue||value>maxValue)
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in line %1 the parameter value %2 is out of range \n in parameters file:\n%3").arg(nLine).arg(strParameterValue).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
        }
        mParametersValueByGroup[parameterContainer][posInGroup]=strParameterValue;
    }
    if(mImagesPath.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, images path parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    if(mImagePairsFileName.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, image pairs file parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    if(mSaveImagesMatches)
    {
        if(mRelativePathForMatchesFiles.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
        {
            strError=QObject::tr("OpenCVKpMParameters::setFromFile, relative path for matches files parameter not exists \n in parameters file:\n%1").arg(fileName);
            return(OPENCV_KPM_ERROR);
        }
    }
    if(mDetector.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, detector parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    if(mDescriptor.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, descriptor parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    if(mOutliersDetector.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, outliers detector parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    if(mMatcher.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, matcher parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    if(mMatchingDistance.compare(OPENCV_KPM_NO_STRING_VALUE,Qt::CaseInsensitive)==0)
    {
        strError=QObject::tr("OpenCVKpMParameters::setFromFile, matching distance parameter not exists \n in parameters file:\n%1").arg(fileName);
        return(OPENCV_KPM_ERROR);
    }
    // Comprobación de que se han leído todos los parámetros
    QMap<QString,QStringList>::iterator iter=mParametersTagsByGroup.begin();
    while(iter!=mParametersTagsByGroup.end())
    {
        QString parameterContainer=iter.key();
        QStringList parameterValues=mParametersValueByGroup[parameterContainer];
        for(int i=0;i<parameterValues.size();i++)
        {
            QString parameterTag=mParametersTagsByGroup[parameterContainer].at(i);
            QString strValue=parameterValues.at(i);
            if(strValue.isEmpty())
            {
                strError=QObject::tr("OpenCVKpMParameters::setFromFile, in group %1, not exists value for parameter %2 \n in parameters file:\n%1").arg(parameterContainer).arg(parameterTag).arg(fileName);
                return(OPENCV_KPM_ERROR);
            }
        }
        iter++;
    }
    mState=true;
    return(OPENCV_KPM_NO_ERROR);
}
*/
