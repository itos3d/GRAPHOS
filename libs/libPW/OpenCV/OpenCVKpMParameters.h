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
#ifndef OPENCVKPMPARAMETERS_H
#define OPENCVKPMPARAMETERS_H

#include "libPW_global.h"
#include <QStringList>
#include <QMap>

#include <QParams.h>
#include "OpenCVKpMParametersDefinitions.h"

namespace PW
{

class LIBPWSHARED_EXPORT OpenCVKpMParameters
{
public:
    OpenCVKpMParameters();
    int checkMatcherParameters(QString& strError);
    int getApplyOutliersDetection(bool& applyOutliersDetection,
                                  QString& strError);
    int getDescriptorsByDetector(QString& detecgtorTag,
                                 QString& defaultDescriptor,
                                 QStringList& descriptors,
                                 QString& strError);
    int getDescriptor(QString& descriptorTag,
                      QStringList& descriptorParametersTag,
                      QStringList& descriptorParametersValues,
                      QStringList& descriptorParametersType,
                      QString& strError);
    int getDetector(QString& detectorTag,
                    QStringList& detectorParametersTag,
                    QStringList& detectorParametersValues,
                    QStringList& detectorParametersType,
                    QString& strError);
//    int getDetector(QString& detectorTag,
//                    QStringList& detectorParametersTag,
//                    QStringList& detectorParametersTagQParams,
//                    QStringList& detectorParametersValues,
//                    QStringList& detectorParametersType,
//                    QString& strError);
    int getDetectorsTag(QStringList& detectorsTag,
                        QString& strError);
    int getDescriptorParametersTagQParams(QString& descriptorTag,
                                          QStringList& descriptorParametersTagQParams,
                                          QString& strError);
    int getDetectorParametersTagQParams(QString& detectorTag,
                                        QStringList& detectorParametersTagQParams,
                                        QString& strError);
    int getImagesPath(QString& imagesPath,
                      QString& strError);
    int getImagePairsFileName(QString& imagePairsFileName,
                              QString& strError);
    int getMatcher(QString& matcherTag,
                   QStringList& matcherParametersTag,
                   QStringList& matcherParametersValues,
                   QStringList& matcherParametersType,
                   QString& strError);
    int getMatchersByDetectorAndDescriptor(QString& detectorTag,
                                           QString& descriptorTag,
                                           QString& defaultMatcher,
                                           QStringList& matchers,
                                           QString& strError);
    int getMatcherParametersTagQParams(QString matcherTag,
                                       QStringList& matchersTagQParams,
                                       QString &strError);
    int getMatchingDistance(int &normType,
                            QString& strError);
    int getOutliersDetector(QString& detectorTag,
                            QStringList& detectorParametersTag,
                            QStringList& detectorParametersValues,
                            QStringList& detectorParametersType,
                            QString& strError);
    QParams::Param* getParameterByCode(QString parameterCode,
                                       QVector<QParams::Param*>& parameters);
    QParams::Param* getParameterByName(QString parameterName,
                                       QVector<QParams::Param*>& parameters);
    int getParameterByGroupAndTag(QString parameterGroup,
                                  QString parameterTag,
                                  QString &parameterValue,
                                  QString& strError);
    bool getSaveImagesMatches(QString& pathForMatchesFiles);
    bool getBidirectionalMatches(void);
    bool isOk();
    bool setFromFile(QString& fileName,
                     QString& strError);
    int writeDatabase(QString& strError);
    int writeParametersFileFromEngine(QString& detector,
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
                                      QString& strError);
private:
    void initialize();
    QString mImagesPath;
    QString mImagePairsFileName;
    QString mPathForMatchesFiles;
    QString mDetector;
    QStringList mDetectorParametersTag;
    QStringList mDetectorParametersType;
    QStringList mDetectorParametersValue;
    QString mDescriptor;
    QStringList mDescriptorParametersTag;
    QStringList mDescriptorParametersType;
    QStringList mDescriptorParametersValue;
    QString mMatchingDistance;
    QString mMatcher;
    QStringList mMatcherParametersTag;
    QStringList mMatcherParametersType;
    QStringList mMatcherParametersValue;
    QString mOutliersDetector;
    QStringList mOutliersDetectorParametersTag;
    QStringList mOutliersDetectorParametersType;
    QStringList mOutliersDetectorParametersValue;
    QStringList mDetectors;
    QStringList mDescriptors;
    QStringList mMatchers;
    QStringList mMatchingDistances;
    QStringList mOutliersDetectors;
    QStringList mParameterTypes;
    QMap<QString,QStringList> mParametersTagsByGroup;
    QMap<QString,QStringList> mParametersTagsQParamsByGroup;
    QMap<QString,QStringList> mParametersTypeByGroup;
    QMap<QString,QStringList> mParametersDefaultValueByGroup;
    QMap<QString,QStringList> mParametersMinimumValueByGroup;
    QMap<QString,QStringList> mParametersMaximumValueByGroup;
    QMap<QString,QStringList> mParametersValueByGroup;
    QMap<QString,QStringList> mDescriptorsByDetector;
    QMap<QString,QString> mDefaultDescriptorByDetector;
    QMap<QString,QStringList> mMatchersByDetectorAndDescriptor;
    QMap<QString,QString> mDefaultMatcherByDetectorAndDescriptor;
    bool mSaveImagesMatches;
    bool mState;
    bool mBidirectionalMatches;
};

#endif // OPENCVKPMPARAMETERS_H
}
