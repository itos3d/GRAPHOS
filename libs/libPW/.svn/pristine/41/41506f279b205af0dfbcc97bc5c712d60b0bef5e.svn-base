#ifndef IMAGEPOINTSMANAGER_H
#define IMAGEPOINTSMANAGER_H

#include <QObject>
#include <QString>
#include <QMap>
#include <QVector>

#include "libPW_global.h"
#include "TiePoint.h"

#define IMAGEPOINTSMANAGER_GRID_MAXIMUM_NUMBER_OF_CELLS       10000
#define IMAGEPOINTSMANAGER_GRID_SIZE_DEFAULT                  100

namespace PW{

class ImagePointsManager
{
public:
    ImagePointsManager(int precision,
                       int imageColumns,
                       int imageRows,
                       int gridSize,
                       QString imageId,
                       int imagePosition);
    bool getFirstImagePointTiePoint(int column,
                                    int row,
                                    TiePoint* tiePoint,
                                    int& cellColumn,
                                    int& cellRow,
                                    int& pos,
                                    QString &strError);
    bool getSecondImagePointTiePoint(int column,
                                     int row,
                                     TiePoint* tiePoint,
                                     int &cellColumn,
                                     int &cellRow,
                                     int& pos,
                                     QString &strError);
    bool addTiePoint(TiePoint* tiePoint,
                     QString& strError);
//    bool removeTiePointByPosition(int cellColumn,
//                                  int cellRow,
//                                  int pos,
//                                  QString& strError);
private:
    int mPrecision;
    int mImageColumns;
    int mImageRows;
    int mGridSize;
    int mGridColumns;
    int mGridRows;
    int mImagePosition;
    QString mImageId;
    QVector<QVector<QVector<TiePoint*> > > mTiePoints; // La posicion en el grid se determina por el primer punto
    double mFloatToIntegerFactor;
    double mIntegerToFloatFactor;

};
}
#endif // IMAGEPOINTSMANAGER_H
