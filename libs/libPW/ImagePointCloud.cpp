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
#include <math.h>

#include <QObject>
#include <QString>

#include "ImagePointCloud.h"

ImagePointCloud::ImagePointCloud(float pixelMinColumn,
                                 float pixelMinRow,
                                 float pixelMaxColumn,
                                 float pixelMaxRow,
                                 float gridDistance) :
    mPixelMinColumn(pixelMinColumn),
    mPixelMinRow(pixelMinRow),
    mPixelMaxColumn(pixelMaxColumn),
    mPixelMaxRow(pixelMaxRow)
{
    bool control=false;
    while(!control)
    {
        int columns=fabs((mPixelMaxColumn-mPixelMinColumn)/(gridDistance));
        int rows=fabs((mPixelMaxRow-mPixelMinRow)/(gridDistance));
        int gridSize=columns*rows;
        if(gridSize>IMAGEPOINTCLOUD_GRID_MAXIMUM_SIZE)
        {
            gridDistance*=10.0;
        }
        else
        {
            mColumns=columns+1;
            mRows=rows+1;
            mGridDistance=gridDistance;
            control=true;
        }
    }
    for(int nCol=0;nCol<mColumns;nCol++)
    {
        QVector<QVector<float> > vectorRow;
        QVector<QVector<int> > ids;
        for(int nRow=0;nRow<mRows;nRow++)
        {
            QVector<float> vector;
            vectorRow.push_back(vector);
            QVector<int> intVector;
            ids.push_back(intVector);
        }
        mPixelColumns.push_back(vectorRow);
        mPixelRows.push_back(vectorRow);
        mPairIds.push_back(ids);
        mPairPixelColumns.push_back(vectorRow);
        mPairPixelRows.push_back(vectorRow);
    }
}

bool ImagePointCloud::insertPoint(float pixelColumn,
                                  float pixelRow,
                                  QString &strError)
{
    QString functionName="ImagePointCloud::insertPoint";
    if(pixelColumn<mPixelMinColumn||pixelColumn>mPixelMaxColumn||pixelRow<mPixelMinRow||pixelRow>mPixelMaxRow)
    {
        QString msg=QObject::tr("Point out of domain");
        strError+=functionName;
        strError+="\n\tError:";
        strError+=msg;
        return(false);
    }
    int posColumn=int((pixelColumn-mPixelMinColumn)/mGridDistance);
    int posRow=int((pixelRow-mPixelMinRow)/mGridDistance);
    if(posColumn>=mColumns
       ||posRow>=mRows)
    {
        QString msg=QObject::tr("Point out of domain");
        strError+=functionName;
        strError+="\n\tError:";
        strError+=msg;
        return(false);
    }
    mPixelColumns[posColumn][posRow].push_back(pixelColumn);
    mPixelRows[posColumn][posRow].push_back(pixelRow);
    return(true);
}

bool ImagePointCloud::insertPair(float pixelColumn,
                                 float pixelRow,
                                 int pairId,
                                 float pairPixelColumn,
                                 float pairPixelRow,
                                 QString &strError)
{
    QString functionName="ImagePointCloud::insertPair";
    if(pixelColumn<mPixelMinColumn||pixelColumn>mPixelMaxColumn||pixelRow<mPixelMinRow||pixelRow>mPixelMaxRow)
    {
        QString msg=QObject::tr("Point out of domain");
        strError+=functionName;
        strError+="\n\tError:";
        strError+=msg;
        return(false);
    }
    int posColumn=int((pixelColumn-mPixelMinColumn)/mGridDistance);
    int posRow=int((pixelRow-mPixelMinRow)/mGridDistance);
    if(posColumn>=mColumns
       ||posRow>=mRows)
    {
        QString msg=QObject::tr("Point out of domain");
        strError+=functionName;
        strError+="\n\tError:";
        strError+=msg;
        return(false);
    }
    mPixelColumns[posColumn][posRow].push_back(pixelColumn);
    mPixelRows[posColumn][posRow].push_back(pixelRow);
    mPairIds[posColumn][posRow].push_back(pairId);
    mPairPixelColumns[posColumn][posRow].push_back(pairPixelColumn);
    mPairPixelRows[posColumn][posRow].push_back(pairPixelRow);
    return(true);
}

bool ImagePointCloud::getClosestPoint(float pixelColumn,
                                      float pixelRow,
                                      float tolerance,
                                      float &closestPixelColumn,
                                      float &closestPixelRow)
{
    QString functionName="ImagePointCloud::getClosestPoint";
    if(pixelColumn<mPixelMinColumn||pixelColumn>mPixelMaxColumn||pixelRow<mPixelMinRow||pixelRow>mPixelMaxRow)
    {
        return(false);
    }
    int posColumn=int((pixelColumn-mPixelMinColumn)/mGridDistance);
    int posRow=int((pixelRow-mPixelMinRow)/mGridDistance);
    if(posColumn>=mColumns
       ||posRow>=mRows)
    {
        return(false);
    }
    float xf=pixelColumn;
    float yf=pixelRow;
    QVector<int> columns;
    QVector<int> rows;
    columns.push_back(posColumn);
    rows.push_back(posRow);
    if((posColumn+1)<mColumns)
    {
        columns.push_back(posColumn+1);
        rows.push_back(posRow);
        if((posRow+1)<mRows)
        {
            columns.push_back(posColumn+1);
            rows.push_back(posRow+1);
        }
        if((posRow-1)>=0)
        {
            columns.push_back(posColumn+1);
            rows.push_back(posRow-1);
        }
    }
    if((posColumn-1)>=0)
    {
        columns.push_back(posColumn-1);
        rows.push_back(posRow);
        if((posRow+1)<mRows)
        {
            columns.push_back(posColumn-1);
            rows.push_back(posRow+1);
        }
        if((posRow-1)>=0)
        {
            columns.push_back(posColumn-1);
            rows.push_back(posRow-1);
        }
    }
    if((posRow+1)<mRows)
    {
        columns.push_back(posColumn);
        rows.push_back(posRow+1);
    }
    if((posRow-1)>=0)
    {
        columns.push_back(posColumn);
        rows.push_back(posRow-1);
    }
    int numberOfCells=columns.size();
    int numberOfPointsUnderTolerance=0;
    double minDistance2D=1000000.0;
    bool success=false;
    for(int nCell=0;nCell<numberOfCells;nCell++)
    {
        int posColumnCell=columns[nCell];
        int posRowCell=rows[nCell];
        int numberOfPointsInCell=mPixelColumns[posColumnCell][posRowCell].size();
        for(int nP=0;nP<numberOfPointsInCell;nP++)
        {
            float xP=mPixelColumns[posColumnCell][posRowCell][nP];
            float yP=mPixelRows[posColumnCell][posRowCell][nP];
            float distance2D=(float)sqrt((xf-xP)*(xf-xP)+(yf-yP)*(yf-yP));
            if(distance2D<tolerance
               &&distance2D<minDistance2D)
            {
                closestPixelColumn=xP;
                closestPixelRow=yP;
                success=true;
            }
            if(distance2D<tolerance)
                numberOfPointsUnderTolerance++;
        }
    }
    return(success);
}

bool ImagePointCloud::getClosestPair(float pixelColumn,
                                     float pixelRow,
                                     int pairId,
                                     float pairPixelColumn,
                                     float pairPixelRow,
                                     float tolerance,
                                     float &closestPixelColumn,
                                     float &closestPixelRow)
{
    QString functionName="ImagePointCloud::getClosestPoint";
    if(pixelColumn<mPixelMinColumn||pixelColumn>mPixelMaxColumn||pixelRow<mPixelMinRow||pixelRow>mPixelMaxRow)
    {
        return(false);
    }
    int posColumn=int((pixelColumn-mPixelMinColumn)/mGridDistance);
    int posRow=int((pixelRow-mPixelMinRow)/mGridDistance);
    if(posColumn>=mColumns
       ||posRow>=mRows)
    {
        return(false);
    }
    float xf=pixelColumn;
    float yf=pixelRow;
    float pairXf=pairPixelColumn;
    float pairYf=pairPixelRow;
    QVector<int> columns;
    QVector<int> rows;
    columns.push_back(posColumn);
    rows.push_back(posRow);
    if((posColumn+1)<mColumns)
    {
        columns.push_back(posColumn+1);
        rows.push_back(posRow);
        if((posRow+1)<mRows)
        {
            columns.push_back(posColumn+1);
            rows.push_back(posRow+1);
        }
        if((posRow-1)>=0)
        {
            columns.push_back(posColumn+1);
            rows.push_back(posRow-1);
        }
    }
    if((posColumn-1)>=0)
    {
        columns.push_back(posColumn-1);
        rows.push_back(posRow);
        if((posRow+1)<mRows)
        {
            columns.push_back(posColumn-1);
            rows.push_back(posRow+1);
        }
        if((posRow-1)>=0)
        {
            columns.push_back(posColumn-1);
            rows.push_back(posRow-1);
        }
    }
    if((posRow+1)<mRows)
    {
        columns.push_back(posColumn);
        rows.push_back(posRow+1);
    }
    if((posRow-1)>=0)
    {
        columns.push_back(posColumn);
        rows.push_back(posRow-1);
    }
    int numberOfCells=columns.size();
    int numberOfPointsUnderTolerance=0;
    double minDistance2D=1000000.0;
    bool success=false;
    for(int nCell=0;nCell<numberOfCells;nCell++)
    {
        int posColumnCell=columns[nCell];
        int posRowCell=rows[nCell];
        int numberOfPointsInCell=mPixelColumns[posColumnCell][posRowCell].size();
        for(int nP=0;nP<numberOfPointsInCell;nP++)
        {
            float xP=mPixelColumns[posColumnCell][posRowCell][nP];
            float yP=mPixelRows[posColumnCell][posRowCell][nP];
            int pairIdP=mPairIds[posColumnCell][posRowCell][nP];
            if(pairId!=pairIdP)
                continue;
            float pairXP=mPairPixelColumns[posColumnCell][posRowCell][nP];
            float pairYP=mPairPixelRows[posColumnCell][posRowCell][nP];
            float distance2D=(float)sqrt((xf-xP)*(xf-xP)+(yf-yP)*(yf-yP));
            float pairDistance2D=(float)sqrt((pairXf-pairXP)*(pairXf-pairXP)+(pairYf-pairYP)*(pairYf-pairYP));
            if(distance2D<tolerance
                    &&pairDistance2D<tolerance
               &&distance2D<minDistance2D)
            {
                closestPixelColumn=xP;
                closestPixelRow=yP;
                success=true;
            }
            if(distance2D<tolerance)
                numberOfPointsUnderTolerance++;
        }
    }
    return(success);
}


