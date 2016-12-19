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
#ifndef MSDKPD_H
#define MSDKPD_H

#include "ProcessConcurrent.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
#include "MSD.h"
#include "processedImageData.h"
using namespace cv;
namespace PW {

class MSDkpd : public ProcessConcurrent
{
public:
    MSDkpd(QString inputFile, QString outputDir, ProcessedImageData *metadata,int patchRadius,
           int SearchAreaRadius, int NMSRadius, int NMSScaleRadius, float ThSaliency,int KNN, float ScaleFactor,
           int NScales, int imageResizeValue, bool computeOrientations,int maxTiepoints,bool affine=false,int affineTilts = 0);

protected:
    virtual void run();

private:
    QString mInputFile;
    QString mOtputDir;
    ProcessedImageData *mImageMetadata;
    // igual no necesitan ser miembros.
    int mOriginalImageHeight;
    int mOriginalImageWidth;
    float mImageScaleFactorX;
    float mImageScaleFactorY;
    int mMaxTiepoints;
    QString mProjectBasePath;  // !!!!!!
    QString matchesFolder; // !!!!!!


    //MSD parameters
    int msdPatchRadius;
    int msdSearchAreaRadius;
    int msdNMSRadius;
    int msdNMSScaleRadius;
    float msdThSaliency;
    int msdKNN;
    float msdScaleFactor;
    int msdNScales;
    int msdImageResizeValue;
    bool msdComputeOrientations;
    bool mAffine;
    int mAffineTilts;
    bool pointIsAcceptable( KeyPoint vl_keypoint, int width, int height);
    void compensate_affine_coor1(float *x0, float *y0, int w1, int h1, float t1, float t2, float Rtheta);
    void affineSkew(double tilt, double phi, Mat& img, Mat& mask, Mat& Ai);
    std::vector<std::vector<int>> MSDkpd::detectMSD(Mat img, std::vector< KeyPoint >& keypoints);
};
}

#endif // MSDKPD_H
