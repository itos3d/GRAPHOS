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
#include "ASIFTUmatching.h"
#include <QFile>
#include <QDir>
#include <QTime>
#include <QMessageBox>
#include <QFutureWatcher>
#include <QtCore>
#include <QThread>
using namespace cv;
using namespace PW;

ASIFTUmatching::ASIFTUmatching(QString matchesFolder,
                               QStringList imagesPathList,
                               QMap<QString, ProcessedImageData*> imageMetadataMap,int imageResizeValue,int minimumMatches,
                               float RB_ratio, float RB_threshold_K,int matchingMethod):
    matchesFolder(matchesFolder),
    mImagesPathList(imagesPathList),
    mImageDataMap(imageMetadataMap),
    mImageResizeValue(imageResizeValue),
    mMinimumMatches(minimumMatches),
    ratio(RB_ratio),
    threshold_K(RB_threshold_K),
    mMatchingMethod(matchingMethod)
{
    stepsNumber=imagesPathList.count();
    mImageScaleFactorX=1;
    mImageScaleFactorY=1;
    for (int i = 0; i < imagesPathList.count(); ++i) {
        stepsNumber+=imagesPathList.count()-i;
    }
    statusChanged(10,QString("Number of steps: ").append(stepsNumber));
//    qDebug() <<"Number of steps: "<< stepsNumber;
}

ASIFTUmatching::~ASIFTUmatching()
{

}
void ASIFTUmatching::run(){
//    myTimer.start();

    computeMatching();

    writeMatchesToApero();
//    qDebug() <<"Execution time: "<< myTimer.elapsed()/1000 <<" seg";
}



void ASIFTUmatching::computeMatching(){
    QString *stdData = new QString();
    bool mi = false;
//    qDebug() << "Starting matching process at " << myTimer.elapsed()/1000 <<" seg";

    stdData->clear();
    stdData->append("Starting matching process.");
    emit newStdData(stdData->toAscii());

    QList<QString> mapKeyList = mImageDataMap.keys();
    for (int m = 0; m < mapKeyList.count(); ++m) {
        for (int n = m+1; n < mapKeyList.count(); ++n) {
            if (m!=n) {
                 matchesltor.clear();
                 matchesrtol.clear();
                 std::vector<cv::DMatch> matches;
                 // from image 1 to image 2
                 // based on k nearest neighbours (with k=2)
                 ProcessedImageData *imageDataLeft = mImageDataMap.value(mapKeyList.at(m));
                 std::vector<cv::KeyPoint> tiePointsLeft = imageDataLeft->getTiepoints();
                 cv::Mat descriptorsLeft= imageDataLeft->getDescriptors();
                 ProcessedImageData *imageDataRight = mImageDataMap.value(mapKeyList.at(n));
                 std::vector<cv::KeyPoint> tiePointsRight = imageDataRight->getTiepoints();
                 cv::Mat descriptorsRight= imageDataRight->getDescriptors();
//                 if (tiePointsLeft.size()<30000 ||tiePointsRight.size()<30000) {
                 if (mMatchingMethod==0) {
                     cv::BFMatcher matcher(cv::NORM_L2);
                     //use BruteForceMatcher
                     matcher.knnMatch(descriptorsLeft,descriptorsRight,
                     matchesltor, // vector of matches (up to 2 per entry)
                     2); // return 2 nearest neighbours
                     // from image 2 to image 1
                     // based on k nearest neighbours (with k=2)
                     matcher.knnMatch(descriptorsRight,descriptorsLeft,
                     matchesrtol, // vector of matches (up to 2 per entry)
                     2); // return 2 nearest neighbours

//                     qDebug() << "Left to Right: " << matchesltor.size() <<" matches found."<< "Right to Left: " << matchesrtol.size() <<" matches found." ;
//                     qDebug() << "Starting matching refinement" ;

                     std::vector<std::vector< cv::DMatch > > good_matchesl;
                     std::vector< std::vector< cv::DMatch > > good_matchesr;

                     int refinementMethod = CV_FM_LMEDS; //CV_FM_LMEDS || CV_FM_RANSAC || CV_FM_8POINT;


                     for (size_t i = 0; i < matchesltor.size(); ++i)
                     {
                         std::vector<cv::DMatch> aux =  matchesltor[i];
                         for (size_t j = 0; j < aux.size(); ++j)
                         {
                             cv::DMatch aux_dis = aux[j];
                             double dist = aux_dis.distance;
                             if( dist > max_dist ) max_dist = dist;

                         }
                     }
                     for (size_t i = 0; i < matchesrtol.size(); ++i)
                     {
                         std::vector<cv::DMatch> aux =  matchesrtol[i];
                         for (size_t j = 0; j < aux.size(); ++j)
                         {
                             cv::DMatch aux_dis = aux[j];
                             double dist = aux_dis.distance;
                             if( dist > max_dist ) max_dist = dist;
                         }
                     }

                     //find the "good" matches
                     for (size_t i = 0; i < matchesltor.size(); ++i)
                     {
                         std::vector<cv::DMatch> aux =  matchesltor[i];
                         std::vector<cv::DMatch> good_matchesr_aux;
                         for (size_t j = 0; j < aux.size(); ++j)
                         {

                             cv::DMatch aux_dos = aux[j];
                             if (aux_dos.distance < threshold_K*max_dist) good_matchesr_aux.push_back(aux_dos);

                         }
                         if(good_matchesr_aux.size()>0)good_matchesl.push_back(good_matchesr_aux);
                     }


                     for (size_t i = 0; i < matchesrtol.size(); ++i)
                     {
                         std::vector<cv::DMatch> aux =  matchesrtol[i];
                         std::vector<cv::DMatch> good_matchesr_aux;
                         for (size_t j = 0; j < aux.size(); ++j)
                         {
                             cv::DMatch aux_dos = aux[j];
                             if (aux_dos.distance < threshold_K*max_dist) good_matchesr_aux.push_back(aux_dos);
                         }
                           if(good_matchesr_aux.size()>0)good_matchesr.push_back(good_matchesr_aux);
                     }

//                     qDebug() << "Good matches. Left to Right: " << good_matchesl.size() <<" matches found."<< "Right to Left: " << good_matchesr.size() <<" matches found." ;

                     if (good_matchesl.size()>0&&good_matchesr.size()>0)
                     {
                        // clean image 1 -> image 2 matches
                        int removed= ratioTest(good_matchesl);
                        removed = ratioTest(good_matchesr);

//                        qDebug() << "End ratio test at " << myTimer.elapsed()/1000 <<" seg";;
//                        qDebug() << "Left to Right: " << good_matchesl.size() <<" matches found."<< "Right to Left: " << good_matchesr.size() <<" matches found." ;

//                        // 4. Remove non-symmetrical matches

                        std::vector<cv::DMatch> symMatches;
                        symmetryTest(good_matchesl,good_matchesr,symMatches);

//                        qDebug() << "End symetry test at " << myTimer.elapsed()/1000 <<" seg";;
//                        qDebug() << symMatches.size() <<" symmetric matches found.";

                        // 5. Validate matches using RANSAC
                 //       int method;
                 //       switch (refinementMethod)
                 //       {
                 //       case 0:
                 //           method =CV_FM_LMEDS;
                 //           break;
                 //       case 1:
                 //           method=CV_FM_RANSAC;
                 //           break;
                 //       case 2:
                 //           method=CV_FM_8POINT;
                 //           break;
                 //       }


                          ransacTest(symMatches,tiePointsLeft, tiePointsRight, matches,CV_FM_LMEDS);

                     }
                 }else{
                       //Matching descriptor vectors using FLANN matcher
                       FlannBasedMatcher matcher;
                       matcher.match( descriptorsLeft, descriptorsRight, matches);

                 }
                 std::vector<std::vector<float>> imageMatchings;
                 std::vector<float> imageCoordinates;

                 cv::String cvImageFileName = mImagesPathList.first().toStdString();

                 cv::Mat cvImg = cv::imread(cvImageFileName, CV_LOAD_IMAGE_COLOR);
                 mOriginalImageWidth=cvImg.cols;
                 mOriginalImageHeight=cvImg.rows;

                 if (mImageResizeValue!=-1) {
                     if (cvImg.size[1]>cvImg.size[0] && cvImg.size[1]>mImageResizeValue) {
                         //Scale factor
                         int newImageHeight = (int)(cvImg.rows*mImageResizeValue/cvImg.cols);

                         mImageScaleFactorX = (float)mImageResizeValue/(float)mOriginalImageWidth;
                         mImageScaleFactorY = (float)newImageHeight/(float)mOriginalImageHeight;

                     }else if (cvImg.size[0]>cvImg.size[1] && cvImg.size[0]>mImageResizeValue) {
                         //Scale factor
                         int newImageWidth = (int)(cvImg.cols*mImageResizeValue/cvImg.rows);

                         mImageScaleFactorX = (float)newImageWidth/(float)mOriginalImageWidth;
                         mImageScaleFactorY = (float)mImageResizeValue/(float)mOriginalImageHeight;

                     }
                 }else {
                     mImageScaleFactorX = 1;
                     mImageScaleFactorY = 1;
                 }

                 for (int i=0;i<matches.size();i++)
                 {
                     imageCoordinates.clear();
                     imageCoordinates.push_back(round(tiePointsLeft[matches[i].queryIdx].pt.x/mImageScaleFactorX,4));
                     imageCoordinates.push_back(round(tiePointsLeft[matches[i].queryIdx].pt.y/mImageScaleFactorY,4));
                     imageCoordinates.push_back(round(tiePointsRight[matches[i].trainIdx].pt.x/mImageScaleFactorX,4));
                     imageCoordinates.push_back(round(tiePointsRight[matches[i].trainIdx].pt.y/mImageScaleFactorY,4));
//                     if (imageCoordinates[0] >=0 && imageCoordinates[0]<=mOriginalImageWidth &&
//                         imageCoordinates[2] >=0 && imageCoordinates[2]<=mOriginalImageWidth &&
//                         imageCoordinates[1] >=0 && imageCoordinates[1]<=mOriginalImageHeight &&
//                         imageCoordinates[3] >=0 && imageCoordinates[3]<=mOriginalImageHeight)
//                     {
//                         imageMatchings.push_back(imageCoordinates);
//                     }
                     int borderH=(int)mOriginalImageHeight*0.01;
                     int borderW=(int)mOriginalImageWidth*0.01;
                     if (imageCoordinates[0] >=borderW && imageCoordinates[0]<=(mOriginalImageWidth-borderW) &&
                         imageCoordinates[2] >=borderH && imageCoordinates[2]<=(mOriginalImageWidth-borderH) &&
                         imageCoordinates[1] >=borderW && imageCoordinates[1]<=(mOriginalImageHeight-borderW) &&
                         imageCoordinates[3] >=borderH && imageCoordinates[3]<=(mOriginalImageHeight-borderH))
                     {
                         imageMatchings.push_back(imageCoordinates);
                     }//Aqui

                 }
                 mMatchingsMap.insert(mapKeyList.at(m)+"_"+mapKeyList.at(n),imageMatchings);


//                qDebug() << "End Matching refinement  at " << myTimer.elapsed()/1000 <<" seg";;
//                qDebug() << matches.size() <<" matches found." ;

                stdData->clear();
                stdData->append(QString::number(matches.size()));
//                stdData->append(" matches found between ");
                stdData->append(" matches found between image ");
                stdData->append(mapKeyList.at(m));
                stdData->append(" and image ");
                stdData->append(mapKeyList.at(n));
                emit newStdData(stdData->toAscii());
                emit statusChangedNext();

            }
        }

    }

    stdData->clear();
    stdData->append("End matching process.");
    emit newStdData(stdData->toAscii());

}


int ASIFTUmatching::ratioTest(std::vector<std::vector<cv::DMatch>>& matches) {

  int removed=0;

  // for all matches
  for (std::vector<std::vector<cv::DMatch>>::iterator matchIterator= matches.begin();
       matchIterator!= matches.end(); ++matchIterator) {

           // if 2 NN has been identified
           if (matchIterator->size() > 1) {

               // check distance ratio
               if ((*matchIterator)[0].distance/(*matchIterator)[1].distance > ratio) {

                   matchIterator->clear(); // remove match
                   removed++;
               }

           } else { // does not have 2 neighbours

               matchIterator->clear(); // remove match
               removed++;
           }
  }

  return removed;
}

// Insert symmetrical matches in symMatches vector
void ASIFTUmatching::symmetryTest(const std::vector<std::vector<cv::DMatch>>& matches1,
                  const std::vector<std::vector<cv::DMatch>>& matches2,
                  std::vector<cv::DMatch>& symMatches) {

  // for all matches image 1 -> image 2
  for (std::vector<std::vector<cv::DMatch>>::const_iterator matchIterator1= matches1.begin();
       matchIterator1!= matches1.end(); ++matchIterator1) {

      if (matchIterator1->size() < 2) // ignore deleted matches
          continue;

      // for all matches image 2 -> image 1
      for (std::vector<std::vector<cv::DMatch>>::const_iterator matchIterator2= matches2.begin();
          matchIterator2!= matches2.end(); ++matchIterator2) {

          if (matchIterator2->size() < 2) // ignore deleted matches
              continue;

          // Match symmetry test
          if ((*matchIterator1)[0].queryIdx == (*matchIterator2)[0].trainIdx  &&
              (*matchIterator2)[0].queryIdx == (*matchIterator1)[0].trainIdx) {

                  // add symmetrical match
                  symMatches.push_back(cv::DMatch((*matchIterator1)[0].queryIdx,
                                                  (*matchIterator1)[0].trainIdx,
                                                  (*matchIterator1)[0].distance));
                  break; // next match in image 1 -> image 2
          }
      }
  }
}

// Identify good matches using RANSAC
// Return fundemental matrix
void ASIFTUmatching::ransacTest(const std::vector<cv::DMatch>& matches,
                   const std::vector<cv::KeyPoint>& keypoints1,
                   const std::vector<cv::KeyPoint>& keypoints2,
                   std::vector<cv::DMatch>& outMatches,int method) {

  // Convert keypoints into Point2f
  std::vector<cv::Point2f> points1, points2;
  for (std::vector<cv::DMatch>::const_iterator it= matches.begin();
       it!= matches.end(); ++it) {

       // Get the position of left keypoints
       float x= keypoints1[it->queryIdx].pt.x;
       float y= keypoints1[it->queryIdx].pt.y;
       points1.push_back(cv::Point2f(x,y));
       // Get the position of right keypoints
       x= keypoints2[it->trainIdx].pt.x;
       y= keypoints2[it->trainIdx].pt.y;
       points2.push_back(cv::Point2f(x,y));
  }

  // Compute F matrix using RANSAC
  std::vector<uchar> inliers(points1.size(),0);
  if (method==2)
  {
//      cv::Mat fundemental= cv::findFundamentalMat(
//          cv::Mat(points1),cv::Mat(points2), // matching points
//          inliers,      // match status (inlier ou outlier)
//          method, // RANSAC method
//          distance);
  }else if(method==0){
      cv::Mat fundemental= cv::findFundamentalMat(
          cv::Mat(points1),cv::Mat(points2), // matching points
          inliers,      // match status (inlier ou outlier)
          method, // RANSAC method
          0,     // distance to epipolar line
          0);  // confidence probability
  }
  else{
  cv::Mat fundemental= cv::findFundamentalMat(
      cv::Mat(points1),cv::Mat(points2), // matching points
      inliers,      // match status (inlier ou outlier)
      method, // RANSAC method
      0,     // distance to epipolar line
      0);  // confidence probability
}
  // extract the surviving (inliers) matches
  std::vector<uchar>::const_iterator itIn= inliers.begin();
  std::vector<cv::DMatch>::const_iterator itM= matches.begin();
  // for all matches
  for ( ;itIn!= inliers.end(); ++itIn, ++itM) {

      if (*itIn) { // it is a valid match

          outMatches.push_back(*itM);
      }
  }
}

void ASIFTUmatching::writeMatchesToApero(){
    QString *stdData= new QString();

    stdData->clear();
    stdData->append("Writing results for Pastis... ");
    emit newStdData(stdData->toAscii());

//    int totalDel =0;

//    QDir matchingMethodDir(matchesFolder+"/ASIFT");
//    if(!matchingMethodDir.exists())
//    {
//        QDir().mkdir(matchingMethodDir.absolutePath());
//    }

    for (int i = 0; i < mImagesPathList.count(); ++i) {
        for (int j = 0; j < mImagesPathList.count(); ++j) {
            int totalDel =0;

            QString matchingsKey;
            std::vector<std::vector<float>> matchingsVector;
//            if (i<j) {
            if(i!=j){
                QString imageLeft=mImagesPathList.at(i).split("/").last();
                QString imageRight=mImagesPathList.at(j).split("/").last();

                matchingsKey.append(mImagesPathList.at(i).split("/").last().append("_").append(mImagesPathList.at(j).split("/").last()));
                QString homolPath=matchesFolder+"/Matches/ASIFT/Pastis"+QFileInfo(mImagesPathList.at(i)).fileName();
                QString homolFileName=homolPath+"/"+mImagesPathList.at(j).split("/").last()+".txt";
                bool directMatching =true;
                if (!mMatchingsMap.contains(matchingsKey)) {
                    matchingsKey.clear();
                    matchingsKey.append(mImagesPathList.at(j).split("/").last().append("_").append(mImagesPathList.at(i).split("/").last()));
                    homolPath=matchesFolder+"/Matches/ASIFT/Pastis"+QFileInfo(mImagesPathList.at(i)).fileName();
                    homolFileName=homolPath+"/"+mImagesPathList.at(j).split("/").last()+".txt";
                    directMatching =false;

                    imageLeft=mImagesPathList.at(j).split("/").last();
                    imageRight=mImagesPathList.at(i).split("/").last();
                }
                matchingsVector = mMatchingsMap.value(matchingsKey);

                if (matchingsVector.size()>mMinimumMatches) {

                    if(!QDir(homolPath).exists())
                    {
                        QDir().mkdir(homolPath);
                    }
                    QFile file3( QFileInfo(homolFileName).absoluteFilePath());
                    if ( file3.open(QIODevice::ReadWrite) )
                    {
                        QTextStream stream( &file3 );
                        for (int k=0;k<matchingsVector.size();k++)
                        {

                            if (directMatching) {
                                for (int h = 0; h <= k ; ++h) {
                                    if (h==k) {
                                        stream << round(matchingsVector[k][0],4)<<" "<< round(matchingsVector[k][1],4)<< " " <<  round(matchingsVector[k][2],4)<< " " << round(matchingsVector[k][3],4) << endl;
                                    }else if ((round(matchingsVector[k][0],4) == round(matchingsVector[h][0],4))&& (round(matchingsVector[k][1],4) == round(matchingsVector[h][1],4))) {
                                        totalDel++;
                                        break;
                                    }
                                }
                            }else {
                                for (int h = 0; h <= k ; ++h) {
                                    if (h==k) {
                                        stream <<round(matchingsVector[k][2],4)<<" "<< round(matchingsVector[k][3],4)<< " " <<  round(matchingsVector[k][0],4)<< " " << round(matchingsVector[k][1],4) << endl;
                                    }else if ((round(matchingsVector[k][2],4) == round(matchingsVector[h][2],4))&& (round(matchingsVector[k][3],4) == round(matchingsVector[h][3],4))) {
                                        totalDel++;
                                        break;
                                    }
                                }
                            }

                        }
                        file3.close();
                        //Recheck matches after the remove of duplicated matchings. //No me gusta este metodo...
                        if ((matchingsVector.size()-totalDel)<mMinimumMatches) {
                            //remove matchings file
                            file3.remove();

                            stdData->clear();
                            stdData->append("Not enough matches between image ");
                            stdData->append(imageLeft);
                            stdData->append(" and image ");
                            stdData->append(imageRight);
                            stdData->append(" after removing duplicates.");
                            emit newStdData(stdData->toAscii());
                            emit statusChangedNext();
                        }else {
                            stdData->clear();
                            int totalMatches = matchingsVector.size()-totalDel;
                            stdData->append(QString::number(totalMatches));
                            stdData->append(" matches found between image ");
                            stdData->append(imageLeft);
                            stdData->append(" and image ");
                            stdData->append(imageRight);
                            stdData->append(" after removing duplicates.");
                            emit newStdData(stdData->toAscii());
                            emit statusChangedNext();
                        }
                    }

                }
            }
        }
    }

    stdData->clear();
    stdData->append("Matching process finished.");
    emit newStdData(stdData->toAscii());
}

float ASIFTUmatching::round(float f,int precission)
{
    return floor(f*(10*precission) + 0.5)/(10*precission);
}
