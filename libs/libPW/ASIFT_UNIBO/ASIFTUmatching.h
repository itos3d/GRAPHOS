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
#ifndef ASIFTUMATCHING_H
#define ASIFTUMATCHING_H

#include "libPW_global.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
#include <time.h>
#include <iostream>
#include <QDebug>
#include <QTime>
#include <qstringlist.h>
#include "MSD/processedImageData.h"
#include "ProcessConcurrent.h"

namespace PW{
class LIBPWSHARED_EXPORT ASIFTUmatching : public ProcessConcurrent
{
public:
    ASIFTUmatching(QString matchesFolder,
                   QStringList imagesPathList,
                   QMap<QString, ProcessedImageData*> imageMetadataMap,int imageResizeValue,int minimumMatches,
                   float RB_ratio, float RB_threshold_K,int matchingMethod);
    ~ASIFTUmatching();
    std::vector<float> match;
    std::vector<std::vector<float>> aperoMatches;

    std::vector<cv::Mat> mDescriptors;
    std::vector<std::vector<cv::KeyPoint>> mTiePoints;

    QMap<QString, std::vector<std::vector<float>>> mMatchingsMap;

    QStringList mImagesPathList;
    float max_dist;
    float ratio;
    float threshold_K;
    int mOriginalImageHeight;
    int mOriginalImageWidth;
    int mMinimumMatches;
    float mImageScaleFactorX;
    float mImageScaleFactorY;
    QString matchesFolder;
    int mMatchingMethod;

    int stepsNumber;

    std::vector<std::vector<cv::DMatch>> matchesltor;
    std::vector<std::vector<cv::DMatch>> matchesrtol;

    cv::Mat img_left;
    cv::Mat img_right;
    std::vector<cv::KeyPoint> img_left_key;
    std::vector<cv::KeyPoint> img_right_key;
    virtual void run();
private:

//    bool MSDMatching::removeDir(QString dirName);
    QMap<QString, ProcessedImageData*> mImageDataMap;
    QTime myTimer;
    bool flann;
    std::vector< cv::DMatch > matchesFLANNLeftToRight;
    std::vector< cv::DMatch > matchesFLANNRightToLeft;
    int mImageResizeValue;
    cv::String leftImageFileName;
    cv::String rightImageFileName;
    void writeMatchesToApero();
    void computeMatching();
    void ransacTest(const std::vector<cv::DMatch>& matches,
                       const std::vector<cv::KeyPoint>& keypoints1,
                       const std::vector<cv::KeyPoint>& keypoints2,
                       std::vector<cv::DMatch>& outMatches,int method);
    void symmetryTest(const std::vector<std::vector<cv::DMatch>>& matches1,
                      const std::vector<std::vector<cv::DMatch>>& matches2,
                      std::vector<cv::DMatch>& symMatches);
    int ratioTest(std::vector<std::vector<cv::DMatch>>& matches);
    void startMatchingThread(ProcessedImageData imageDataLeft,ProcessedImageData imageDataRight);
    float round(float f,int precission);
//    void removeDuplicatedMatches();



};
}
#endif // ASIFTUMATCHING_H
