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
#ifndef TIEPOINTSMANAGER_H
#define TIEPOINTSMANAGER_H

#include <QObject>
#include <QMap>
#include <QVector>

#include "libPW_global.h"
#include "TiePoint.h"

#define TIEPOINTSMANAGER_GRID_MAXIMUM_NUMBER_OF_CELLS                   10000 // 100*100
#define TIEPOINTSMANAGER_GRID_SIZE_DEFAULT                              100

namespace PW{

class LIBPWSHARED_EXPORT TiePointsManager
{
public:
    TiePointsManager(int precision,
                     int imageColumns,
                     int imageRows,
                     int gridSize,
                     QVector<QString> imageFileNames);
    TiePointsManager(int precision,
                     int imageColumns,
                     int imageRows,
                     int gridSize,
                     QMap<QString,int> imagesIds);
    bool addTiePoint(int firstImagePosition,
                     int firstColumn,
                     int firstRow,
                     int secondImagePosition,
                     int secondColumn,
                     int secondRow,
                     bool &addedTiePoint,
                     QString& strError,
                     int std=-1);
    int getGridColumns(){return mGridColumns;};
    int getGridRows(){return mGridRows;};
    QMap<QString,int>& getImagesIds(){return(mImagesIds);};
    QMap<int,QString>& getImagesByIds(){return(mImagesByIds);};
    double getIntegerToDoubleFactor(){return mIntegerToDoubleFactor;};
    bool getTiePoint(int imagePosition,
                     int column,
                     int row,
                     TiePoint* &tiePoint,
                     QString& strError);
    QMap<int,QVector<QVector<QVector<TiePoint*> > > >& getTiePoints(){return(mTiePoints);};
    QVector<TiePoint*>& getTiePointsById(){return(mTiePoinstById);};
    bool setFromMapContainers(QMap<QString,QVector<QString> >& imagesIdsTiePoints,
                              QMap<QString,QMap<QString,QVector<double> > >& imagesFirstColumnsTiePoints,
                              QMap<QString,QMap<QString,QVector<double> > >& imagesFirstRowsTiePoints,
                              QMap<QString,QMap<QString,QVector<double> > >& imagesSecondColumnsTiePoints,
                              QMap<QString,QMap<QString,QVector<double> > >& imagesSecondRowsTiePoints,
                              QMap<QString,QMap<QString,QVector<double> > >& matchesAccuracies,
                              QString& strError);
    bool setFromMapContainers(QMap<QString,QVector<QString> >& imagesIdsTiePoints,
                              QMap<QString,QMap<QString,QVector<bool> > >& matchesEnableds,
                              QMap<QString,QMap<QString,QVector<double> > >& imagesFirstColumnsTiePoints,
                              QMap<QString,QMap<QString,QVector<double> > >& imagesFirstRowsTiePoints,
                              QMap<QString,QMap<QString,QVector<double> > >& imagesSecondColumnsTiePoints,
                              QMap<QString,QMap<QString,QVector<double> > >& imagesSecondRowsTiePoints,
                              QMap<QString,QMap<QString,QVector<double> > >& matchesAccuracies,
                              QString& strError);
private:
    int mPrecision;
    int mImageColumns;  // la original multiplicada por 10^precision
    int mImageRows;     // la original multiplicada por 10^precision
    int mGridSize;      // multiplicado por 10^precision
    int mGridColumns;
    int mGridRows;
    QMap<QString,int> mImagesIds;
    QMap<int,QString> mImagesByIds;
    QMap<int,QVector<QVector<QVector<TiePoint*> > > > mTiePoints; // by image position
    QVector<TiePoint*> mTiePoinstById;
    double mDoubleToIntegerFactor;
    double mIntegerToDoubleFactor;
};
}
#endif // TIEPOINTSMANAGER_H
