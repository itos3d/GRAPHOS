#include <math.h>

#include "ImagePointsManager.h"

using namespace PW;

ImagePointsManager::ImagePointsManager(int precision,
                                       int imageColumns,
                                       int imageRows,
                                       int gridSize,
                                       QString imageId,
                                       int imagePosition):
    mPrecision(precision),
    mImageId(imageId),
    mImagePosition(imagePosition)
{
    mFloatToIntegerFactor=pow(10.0,precision);;
    mIntegerToFloatFactor=1.0/mFloatToIntegerFactor;
    mImageColumns=qRound(imageColumns*mFloatToIntegerFactor);
    mImageRows=qRound(imageRows*mFloatToIntegerFactor);
    mGridSize=qRound(gridSize*mFloatToIntegerFactor);
    bool control=false;
    while(!control)
    {
        mGridColumns=ceil((float)(mImageColumns/mGridSize));
        mGridRows=ceil((float)(mImageRows/mGridSize));
        int numberOfCells=mGridColumns*mGridRows;
        if(numberOfCells>(IMAGEPOINTSMANAGER_GRID_MAXIMUM_NUMBER_OF_CELLS*mFloatToIntegerFactor))
        {
            mGridSize*=2.0;
        }
        else
        {
            control=true;
        }
    }
    for(int nCol=0;nCol<mGridColumns;nCol++)
    {
        QVector<QVector<TiePoint*> > vectorRow;
        for(int nRow=0;nRow<mGridRows;nRow++)
        {
            QVector<TiePoint*> tiePoints;
            vectorRow.push_back(tiePoints);
        }
        mTiePoints.push_back(vectorRow);
    }
}

bool ImagePointsManager::getFirstImagePointTiePoint(int column,
                                                    int row,
                                                    TiePoint *tiePoint,
                                                    int &cellColumn,
                                                    int &cellRow,
                                                    int &pos,
                                                    QString &strError)
{
    if(column>mImageColumns||row>mImageRows)
    {
        strError=QObject::tr("ImagePointsManager::getTiePoint, point out of domain (%1,%2)")
                .arg(QString::number((float)column*mIntegerToFloatFactor,'f',mPrecision))
                .arg(QString::number((float)row*mIntegerToFloatFactor,'f',mPrecision));
        return(false);
    }
    tiePoint=NULL;
    cellColumn=floor((double)column/mImageColumns);
    cellRow=floor((double)row/mImageRows);
    pos=-1;
    for(int nTp=0;nTp<mTiePoints[cellColumn][cellRow].size();nTp++)
    {
        TiePoint* ptrTiePoint=mTiePoints[cellColumn][cellRow][nTp];
        ImagePoint* imagePoint=ptrTiePoint->firstPoint();
        if(imagePoint->column()==column
                &&imagePoint->row()==row)
        {
            tiePoint=ptrTiePoint;
            pos=nTp;
            break;
        }
    }
    return(true);
}

bool ImagePointsManager::getSecondImagePointTiePoint(int column,
                                                     int row,
                                                     TiePoint *tiePoint,
                                                     int &cellColumn,
                                                     int &cellRow,
                                                     int& pos,
                                                     QString &strError)
{
    if(column>mImageColumns||row>mImageRows)
    {
        strError=QObject::tr("ImagePointsManager::getTiePoint, point out of domain (%1,%2)")
                .arg(QString::number((float)column*mIntegerToFloatFactor,'f',mPrecision))
                .arg(QString::number((float)row*mIntegerToFloatFactor,'f',mPrecision));
        return(false);
    }
    tiePoint=NULL;
    cellColumn=floor((double)column/mImageColumns);
    cellRow=floor((double)row/mImageRows);
    pos=-1;
    for(int nTp=0;nTp<mTiePoints[cellColumn][cellRow].size();nTp++)
    {
        TiePoint* ptrTiePoint=mTiePoints[cellColumn][cellRow][nTp];
        ImagePoint* imagePoint=ptrTiePoint->secondPoint();
        if(imagePoint->column()==column
                &&imagePoint->row()==row)
        {
            tiePoint=ptrTiePoint;
            pos=nTp;
            break;
        }
    }
    return(true);
}

bool ImagePointsManager::addTiePoint(TiePoint *tiePoint,
                                     QString &strError)
{
    bool isFirstImage=false;
    if(tiePoint->firstPoint()->imagePosition()==mImagePosition)
        isFirstImage=true;
    bool isSecondImage=false;
    if(tiePoint->secondPoint()->imagePosition()==mImagePosition)
        isSecondImage=true;
    if(!isFirstImage&&!isSecondImage)
    {
        strError=QObject::tr("ImagePointsManager::addTiePoint, image position %1 is different to value in tie point %2")
                .arg(QString::number(mImagePosition))
                .arg(QString::number(tiePoint->firstPoint()->imagePosition()));
        return(false);
    }
    if(isFirstImage&&isSecondImage)
    {
        strError=QObject::tr("ImagePointsManager::addTiePoint, equals first and secon image position %1 tie point")
                .arg(QString::number(tiePoint->firstPoint()->imagePosition()));
        return(false);
    }
    int column,row;
    if(isFirstImage)
    {
        column=tiePoint->firstPoint()->column();
        row=tiePoint->firstPoint()->row();
    }
    if(isSecondImage)
    {
        column=tiePoint->secondPoint()->column();
        row=tiePoint->secondPoint()->row();
    }
    int cellColumn=floor((double)column/mImageColumns);
    int cellRow=floor((double)row/mImageRows);
    mTiePoints[cellColumn][cellRow].push_back(tiePoint);
    return(true);
}
/*
bool ImagePointsManager::removeTiePointByPosition(int cellColumn,
                                                  int cellRow,
                                                  int pos,
                                                  QString &strError)
{
    if(cellColumn>mGridColumns||cellRow>mGridRows)
    {
        strError=QObject::tr("ImagePointsManager::removeTiePointByPosition, tie point out of domain cell (%1,%2)")
                .arg(QString::number(cellColumn))
                .arg(QString::number(cellRow));
        return(false);
    }
    if(pos>mTiePoints[cellColumn][cellRow].size())
    {
        strError=QObject::tr("ImagePointsManager::removeTiePointByPosition, tie point out of domain in vector cell (%1,%2), position %3")
                .arg(QString::number(cellColumn))
                .arg(QString::number(cellRow))
                .arg(QString::number(pos));
        return(false);
    }
    mTiePoints[cellColumn][cellRow].remove(pos);
}
*/
