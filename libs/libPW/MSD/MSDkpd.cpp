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
#include "MSDkpd.h"
#include <QDir>
#include <math.h>

#define _USE_MATH_DEFINES
#define ABS(x)    (((x) > 0) ? (x) : (-(x)))
#define M_PI 3.14159265358979323846

using namespace cv;
using namespace PW;
using namespace std;

struct sortByStrength
{
    inline bool operator() (const std::pair<KeyPoint,std::vector<int>>& a, const std::pair<KeyPoint,std::vector<int>>& b)
    {
        return (a.first.size < b.first.size);
    }
};

// make sure vectorA and vectorB are of the same size, before calling function
template <typename T, typename R, typename Compare>
void sortVecPair(std::vector<T>& vecA, std::vector<R>& vecB, Compare cmp)
{

    std::vector<pair<T,R>> vecC;
    vecC.reserve(vecA.size());
    for(int i=0; i<vecA.size(); i++)
     {
        vecC.push_back(std::make_pair(vecA[i],vecB[i]));
     }

    std::sort(vecC.begin(), vecC.end(), cmp);

    vecA.clear();
    vecB.clear();
    vecA.reserve(vecC.size());
    vecB.reserve(vecC.size());
    for(int i=0; i<vecC.size(); i++)
     {
        vecA.push_back(vecC[i].first);
        vecB.push_back(vecC[i].second);
     }
}

MSDkpd::MSDkpd(QString inputFile, QString outputDir, ProcessedImageData *metadata,int patchRadius,
               int SearchAreaRadius, int NMSRadius, int NMSScaleRadius, float ThSaliency,int KNN, float ScaleFactor,
               int NScales, int imageResizeValue, bool computeOrientations,int maxTiepoints,bool affine,int affineTilts):
    mInputFile(inputFile),
    mOtputDir(outputDir),
    mImageMetadata(metadata),
    msdPatchRadius(patchRadius),
    msdSearchAreaRadius(SearchAreaRadius),
    msdNMSRadius(NMSRadius),
    msdNMSScaleRadius(NMSScaleRadius),
    msdThSaliency(ThSaliency),
    msdKNN(KNN),
    msdScaleFactor(ScaleFactor),
    msdNScales(NScales),
    msdImageResizeValue(imageResizeValue),
    msdComputeOrientations(computeOrientations),
    mMaxTiepoints(maxTiepoints),
    mAffine(affine),
    mAffineTilts(affineTilts)
{
}

void MSDkpd::run()
{

    QFileInfo fileInfo(mInputFile);
    QString *stdData = new QString();

    stdData->clear();
    stdData->append("Starting MSD keypoint detection for image:  ");
    stdData->append(fileInfo.fileName());
    emit newStdData(stdData->toAscii());

    QString matchesFolder = mOtputDir;

    QDir matchingMethodDir(matchesFolder+"/tapioca");
    QString imageMatchings = matchesFolder+"/tapioca/Pastis"+mInputFile.split("/").last();
    if(!matchingMethodDir.exists(imageMatchings))
    {
        matchingMethodDir.mkdir(imageMatchings);
    }
    cv::String cvImageFileName = mInputFile.toAscii().constData();

    cv::Mat cvImg = cv::imread(cvImageFileName, CV_LOAD_IMAGE_GRAYSCALE);

    if (msdImageResizeValue!=-1 && (cvImg.size[1]> msdImageResizeValue || cvImg.size[0]> msdImageResizeValue)) {

        if (cvImg.size[1]>cvImg.size[0] && cvImg.size[1]>msdImageResizeValue) {
            //Scale

            int newImageHeight = (int)(cvImg.rows*msdImageResizeValue/cvImg.cols);

            Size newSize(msdImageResizeValue,newImageHeight);

            cv::resize(cvImg,cvImg,newSize,INTER_NEAREST   ); //resize image

            stdData->clear();
            stdData->append("Image ");
            stdData->append(fileInfo.fileName());
            stdData->append(" downsampled.");
            emit newStdData(stdData->toAscii());
        }else if (cvImg.size[0]>cvImg.size[1] && cvImg.size[0]>msdImageResizeValue) {
            //Scale

            int newImageWidth = (int)(cvImg.cols*msdImageResizeValue/cvImg.rows);

            Size newSize(newImageWidth,msdImageResizeValue);

            cv::resize(cvImg,cvImg,newSize,INTER_NEAREST   ); //resize image

            stdData->clear();
            stdData->append("Image ");
            stdData->append(fileInfo.fileName());
            stdData->append(" downlampled.");
            emit newStdData(stdData->toAscii());
        }
    }

    std::vector<cv::KeyPoint> cvImg_keyPoints;
    cvImg_keyPoints.clear();

    if (mAffine) {

        vector<vector<int> > descriptorsOK;
        descriptorsOK.clear();

        int i = 0;
        for(int tl = 1; tl <= mAffineTilts; tl++)//for(int tl = 1; tl < 6; tl++)//for(int tl = 1; tl < 6; tl++)//for(int tl = 1; tl < 6; tl++)
        {
          double t = pow(2, 0.5*tl);
          for(int phi = 0; phi < 180; phi += 72.0/t)
          {
            i++;
            std::vector<KeyPoint> kps;
            kps.clear();
            vector<vector<int>> descriptorsAUX;
            descriptorsAUX.clear();
            Mat timg, mask, Ai;

            cvImg.copyTo(timg);
            affineSkew(t,phi,timg,mask,Ai);

            descriptorsAUX = detectMSD(timg,kps);

            for(unsigned int i = 0; i < kps.size(); i++)
            {
              Point3f kpt(kps[i].pt.x, kps[i].pt.y, 1);
              Mat kpt_t = Ai*Mat(kpt);

              kps[i].pt.x = kpt_t.at<float>(0,0);
              kps[i].pt.y = kpt_t.at<float>(1,0);
              if(phi == 0 || pointIsAcceptable(kps[i],cvImg.cols,cvImg.rows)){
                  cvImg_keyPoints.push_back(kps[i]);
                  descriptorsOK.push_back(descriptorsAUX[i]);
              }
              kpt_t.release();
            }


            timg.release();
            mask.release();
            Ai.release();
          }
        }
        //Convert vector of vectors to cv::Mat

        //tiepoints Filter
        if (mMaxTiepoints!=-1 && mMaxTiepoints<cvImg_keyPoints.size()) {
            //Sort tiepoints by strength
            sortVecPair(cvImg_keyPoints, descriptorsOK, sortByStrength());
            std::vector<KeyPoint>  *keypointsAux = new std::vector<KeyPoint>(cvImg_keyPoints.end() - mMaxTiepoints, cvImg_keyPoints.end());
            vector<vector<int> >  *descriptorsAux= new vector<vector<int> >(descriptorsOK.end() - mMaxTiepoints, descriptorsOK.end());
            cvImg_keyPoints.clear();
            descriptorsOK.clear();
            cvImg_keyPoints.reserve( keypointsAux->size()); // preallocate memory
            descriptorsOK.reserve( descriptorsAux->size()); // preallocate memory

            cvImg_keyPoints.insert( cvImg_keyPoints.end(), keypointsAux->begin(), keypointsAux->end() );
            descriptorsOK.insert( descriptorsOK.end(), descriptorsAux->begin(), descriptorsAux->end() );
        }

        cv::Mat cvDescriptorsConverted(descriptorsOK.size(), descriptorsOK.at(0).size(), CV_32F);
        for(int i=0; i<cvDescriptorsConverted.rows; ++i)
             for(int j=0; j<cvDescriptorsConverted.cols; ++j){
                 cvDescriptorsConverted.at<float>(i, j) = descriptorsOK.at(i).at(j);
        }
        emit statusChangedNext();

        stdData->clear();
        stdData->append(QString::number(cvImg_keyPoints.size()));
        stdData->append(" keypoints found for image ");
        stdData->append(fileInfo.fileName());
        emit newStdData(stdData->toAscii());

        emit statusChangedNext();



        mImageMetadata->setTiepoints(cvImg_keyPoints);
        mImageMetadata->setDescriptors(cvDescriptorsConverted);

    }else {
        MsdDetector msdLeft;

        msdLeft.setPatchRadius(msdPatchRadius);
        msdLeft.setSearchAreaRadius(msdSearchAreaRadius);

        msdLeft.setNMSRadius(msdNMSRadius);
        msdLeft.setNMSScaleRadius(msdNMSScaleRadius);

        msdLeft.setThSaliency(msdThSaliency);
        msdLeft.setKNN(msdKNN);

        msdLeft.setScaleFactor(msdScaleFactor);
        msdLeft.setNScales(msdNScales);

        msdLeft.setComputeOrientation(msdComputeOrientations);
            stdData->clear();
            stdData->append("Searching keypoints for image ");
            stdData->append(fileInfo.fileName());
            emit newStdData(stdData->toAscii());

            cvImg_keyPoints = msdLeft.detect(cvImg,mMaxTiepoints);
            emit statusChangedNext();

            stdData->clear();
            stdData->append(QString::number(cvImg_keyPoints.size()));
            stdData->append(" keypoints found for image ");
            stdData->append(fileInfo.fileName());
            emit newStdData(stdData->toAscii());

            cv::Ptr<cv::xfeatures2d::SIFT> detector = cv::xfeatures2d::SIFT::create();
            cv::Mat cvDescriptors;

            stdData->clear();
            stdData->append("Starting SIFT description for image ");
            stdData->append(fileInfo.fileName());
            emit newStdData(stdData->toAscii());

            detector->compute(cvImg,cvImg_keyPoints,cvDescriptors);

            emit statusChangedNext();

            mImageMetadata->setTiepoints(cvImg_keyPoints);
            mImageMetadata->setDescriptors(cvDescriptors);
    }

    QFileInfo inputFileInfo (mInputFile);
    QString imageFileName = inputFileInfo.fileName();
    mImageMetadata->setImageName(imageFileName);

    stdData->clear();
    stdData->append("Image ");
    stdData->append(fileInfo.fileName());
    stdData->append(" processed successfull.");
    emit newStdData(stdData->toAscii());
}

void MSDkpd::compensate_affine_coor1(float *x0, float *y0, int w1, int h1, float t1, float t2, float Rtheta)
{
  float x_ori, y_ori;
  float x_tmp, y_tmp;

  float x1 = *x0;
  float y1 = *y0;


  Rtheta = Rtheta*M_PI/180;

  if ( Rtheta <= M_PI/2 )
  {
    x_ori = 0;
    y_ori = w1 * sin(Rtheta) / t1;
  }
  else
  {
    x_ori = -w1 * cos(Rtheta) / t2;
    y_ori = ( w1 * sin(Rtheta) + h1 * sin(Rtheta-M_PI/2) ) / t1;
  }

  float sin_Rtheta = sin(Rtheta);
  float cos_Rtheta = cos(Rtheta);


  /* project the coordinates of im1 to original image before tilt-rotation transform */
  /* Get the coordinates with respect to the 'origin' of the original image before transform */
  x1 = x1 - x_ori;
  y1 = y1 - y_ori;
  /* Invert tilt */
  x1 = x1 * t2;
  y1 = y1 * t1;
  /* Invert rotation (Note that the y direction (vertical) is inverse to the usual concention. Hence Rtheta instead of -Rtheta to inverse the rotation.) */
  x_tmp = cos_Rtheta*x1 - sin_Rtheta*y1;
  y_tmp = sin_Rtheta*x1 + cos_Rtheta*y1;
  x1 = x_tmp;
  y1 = y_tmp;

  *x0 = x1;
  *y0 = y1;
}



bool MSDkpd::pointIsAcceptable( KeyPoint vl_keypoint, int width, int height){
    bool retVal= false;
    double x0, y0, vx1, vy1, vx2, vy2, vx3, vy3 ,vx4, vy4, d1, d2, d3, d4, scale1, BorderTh;

    x0 = vl_keypoint.pt.x;
    y0 = vl_keypoint.pt.y;
    scale1= vl_keypoint.size;

    if(x0<=0 || y0<=0 || x0>=width || y0>=height){
        return false;
    }

    vx1=0;
    vy1=0;

    vx2=0;
    vy2=height;

    vx3=width;
    vy3=0;

    vx4=width;
    vy4=height;

    d1 = sqrt(pow((x0-vx1),2)+pow((y0-vy1),2));
    d2 = sqrt(pow((x0-vx2),2)+pow((y0-vy2),2));
    d3 = sqrt(pow((x0-vx3),2)+pow((y0-vy3),2));
    d4 = sqrt(pow((x0-vx4),2)+pow((y0-vy4),2));

    float BorderFact=width/100*sqrt(2.);
    //if (scale1 < 1){ scale1 = 1;}
    BorderTh = BorderFact*scale1;

    if (d1<BorderTh || d2<BorderTh || d3<BorderTh || d4<BorderTh){
      retVal = false;
    } else {
      retVal = true;
    }
    return retVal;
}

void MSDkpd::affineSkew(double tilt, double phi, Mat& img, Mat& mask, Mat& Ai)
{
  int h = img.rows;
  int w = img.cols;

  mask = Mat(h, w, CV_8UC1, Scalar(255));

  Mat A = Mat::eye(2,3, CV_32F);

  if(phi != 0.0)
  {
    phi *= CV_PI/180.;
    double s = sin(phi);
    double c = cos(phi);

    A = (Mat_<float>(2,2) << c, -s, s, c);

    Mat corners = (Mat_<float>(4,2) << 0, 0, w, 0, w, h, 0, h);
    Mat tcorners = corners*A.t();
    Mat tcorners_x, tcorners_y;
    tcorners.col(0).copyTo(tcorners_x);
    tcorners.col(1).copyTo(tcorners_y);
    std::vector<Mat> channels;
    channels.push_back(tcorners_x);
    channels.push_back(tcorners_y);
    merge(channels, tcorners);

    Rect rect = boundingRect(tcorners);
    A =  (Mat_<float>(2,3) << c, -s, -rect.x, s, c, -rect.y);

    warpAffine(img, img, A, Size(rect.width, rect.height), INTER_LINEAR, BORDER_REPLICATE);
  }
  if(tilt != 1.0)
  {
    double s = 0.8*sqrt(tilt*tilt-1);
    GaussianBlur(img, img, Size(0,0), s, 0.01);
    resize(img, img, Size(0,0), 1.0/tilt, 1.0, INTER_NEAREST);
    A.row(0) = A.row(0)/tilt;
  }
  if(tilt != 1.0 || phi != 0.0)
  {
    h = img.rows;
    w = img.cols;
    warpAffine(mask, mask, A, Size(w, h), INTER_NEAREST);
  }
  invertAffineTransform(A, Ai);
}

vector<vector<int>> MSDkpd::detectMSD(Mat img, vector< KeyPoint >& keypoints){
    keypoints.clear();

    vector<vector<int> > descriptorsOut;

    MsdDetector msdLeft;


    msdLeft.setPatchRadius(msdPatchRadius);
    msdLeft.setSearchAreaRadius(msdSearchAreaRadius);

    msdLeft.setNMSRadius(msdNMSRadius);
    msdLeft.setNMSScaleRadius(msdNMSScaleRadius);

    msdLeft.setThSaliency(msdThSaliency);
    msdLeft.setKNN(msdKNN);

    msdLeft.setScaleFactor(msdScaleFactor);

    //Compute nscales max
    int maxNscales;
    maxNscales =cvFloor(std::log(cv::min(img.cols, img.rows) / ((msdPatchRadius + msdSearchAreaRadius)*2.0 + 1)) / std::log(msdScaleFactor));
    if (maxNscales<msdNScales) {
        msdLeft.setNScales(maxNscales);
    }else {
        msdLeft.setNScales(msdNScales);
    }


    msdLeft.setComputeOrientation(msdComputeOrientations);

//    cv::Mat auxImage;


//    keypoints = msdLeft.detectandcompute(img,auxImage,-1);
    keypoints = msdLeft.detect(img,-1);

    cv::Ptr<cv::xfeatures2d::SIFT> detector = cv::xfeatures2d::SIFT::create();
    cv::Mat cvDescriptors;


    detector->compute(img,keypoints,cvDescriptors);

//    descriptorsOut.assign(cvDescriptors.datastart,cvDescriptors.dataend);
    for (int i=0; i < cvDescriptors.rows; i++) {
        std::vector<int> descriptor;
        for (int j =0; j < cvDescriptors.cols; j++){
            descriptor.push_back(cvDescriptors.at<float>(i,j));
        }
        descriptorsOut.push_back(descriptor);
   }

    return descriptorsOut;
}
