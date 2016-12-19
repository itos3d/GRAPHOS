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
#ifndef IMAGEPOINTCLOUD_H
#define IMAGEPOINTCLOUD_H

#include "libPW_global.h"
#include <QVector>

#define IMAGEPOINTCLOUD_GRID_MAXIMUM_SIZE       10000

class LIBPWSHARED_EXPORT ImagePointCloud
{
public:
    ImagePointCloud(float pixelMinColumn,
                    float pixelMinRow,
                    float pixelMaxColumn,
                    float pixelMaxRow,
                    float gridDistance);
    bool insertPoint(float pixelColumn,
                     float pixelRow,
                     QString& strError);
    bool insertPair(float pixelColumn,
                    float pixelRow,
                    int pairId,
                    float pairPixelColumn,
                    float pairPixelRow,
                    QString& strError);
    bool getClosestPoint(float pixelColumn,
                         float pixelRow,
                         float tolerance,
                         float& closestPixelColumn,
                         float& closestPixelRow);
    bool getClosestPair(float pixelColumn,
                        float pixelRow,
                        int pairId,
                        float pairPixelColumn,
                        float pairPixelRow,
                        float tolerance,
                        float& closestPixelColumn,
                        float& closestPixelRow);
private:
    float mPixelMinColumn;
    float mPixelMinRow;
    float mPixelMaxColumn;
    float mPixelMaxRow;
    float mGridDistance;
    int mColumns;
    int mRows;
    QVector<QVector<QVector<float> > > mPixelColumns;
    QVector<QVector<QVector<float> > > mPixelRows;
    QVector<QVector<QVector<int> > > mPairIds;
    QVector<QVector<QVector<float> > > mPairPixelColumns;
    QVector<QVector<QVector<float> > > mPairPixelRows;
};

#endif // IMAGEPOINTCLOUD_H
