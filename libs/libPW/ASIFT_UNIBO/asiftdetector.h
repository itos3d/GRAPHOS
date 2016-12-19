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
#ifndef ASIFTDETECTOR_H
#define ASIFTDETECTOR_H
#endif

#include <vector>
#include <vl/host.h>
#include <opencv/cv.h>

using namespace cv;
using namespace std;

class ASiftDetector
{
    public:
        ASiftDetector(int peakTh, float edgeTh,int nOctaves,int tilts);
        ~ASiftDetector();
        void computeAsift(const Mat &img, std::vector<KeyPoint> & keypoints, vector<vector<int> >  & descriptors,int maxTiepoints);

    private:
      void affineSkew(double tilt, double phi, Mat& img, Mat& mask, Mat& Ai);
      vector<vector<int> > vedaldiDetect(const IplImage* Image, vector< KeyPoint >& keypoints);
      int mPeakTh;
          float mEdgeTh;
          int mOctaves;
          int mTilts;
};
