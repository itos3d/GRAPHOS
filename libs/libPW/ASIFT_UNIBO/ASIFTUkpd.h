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
#ifndef ASIFTUKPD_H
#define ASIFTUKPD_H

#include "ProcessConcurrent.h"
#include "MSD/ProcessedImageData.h"
#include "opencv/cv.h"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/xfeatures2d.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv/highgui.h"
#include "opencv/cv.hpp"
#include <QFileInfo>
#include <QDir>

namespace PW {
class ASIFTUkpd : public ProcessConcurrent
{
public:
    ASIFTUkpd(QString inputFile, QString outputDir, ProcessedImageData *metadata,int imageResizeValue,int peakTh,float edgeTh, int octaves,int maxTiepoints,int tilts);
    ~ASIFTUkpd();
protected:
    virtual void run();
private:
    QString mInputFile;
    QString mOtputDir;
    ProcessedImageData *mImageMetadata;
    int ASIFTImageResizeValue;
    int mPeakTh;
    float mEdgeTh;
    int mOctaves;
    int mMaxTiepoints;
    int mtilts;

};
}
#endif // ASIFTUKPD_H
