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
#ifndef PWGRAPHIMAGES_H
#define PWGRAPHIMAGES_H

#include <QMap>
#include <QVector>

#include "libPW_global.h"

namespace PW{

class LIBPWSHARED_EXPORT PWGraphImages
{
public:
    PWGraphImages();
    bool createGraph(QVector<QString> images,
                     QMap<QString, QVector<QString> > &imagePairs);
    bool isValid(){return mGraphIsConnected;}
    void getImagePairs(QMap<QString, QVector<QString> >& imagePairs);
    bool getOrderedImages(int nGraph,QVector<QString>& orderedImages);
    bool getNthOrderedImages(int nImages,QVector<QString>& orderedImages);
    void getInvalidMatchedCategoryExplanation(QString& title,
                                              QStringList &subgraphs);
private:
    bool getCandidates(int nG,
                       QVector<QString>& candidates);
    bool getCandidate(int nG,
                      QVector<QString> candidates,
                      QString& candidate);
    void getConnections(int &initialPos,
                        QVector<QString>& connections,
                        QVector<QString>& connectedImages);
    QVector<QString> mImages;
    QMap<QString, QVector<QString> > mImagePairs;
    QVector<QVector<QString> > mOrderedImages;
    QVector<QVector<QString> > mUnorderedImages;
    QVector<QMap<QString,int> > mLevelImages;
    QVector< QVector<QVector<QString> > > mLevels;
    bool mGraphIsConnected;

    // Para ortoSky

};

}

#endif // PWGRAPHIMAGES_H
