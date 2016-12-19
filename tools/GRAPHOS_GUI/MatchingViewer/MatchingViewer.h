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
#ifndef MATCHINGVIEWER_H
#define MATCHINGVIEWER_H

#include <QObject>
#include <QMainWindow>
#include <qgraphicsscene.h>
#include <QGraphicsPixmapItem>
#include "MatchigGraphicsView.h"
#include "PWImage.h"

class MatchingViewer : public QObject
{
    Q_OBJECT
public:
    explicit MatchingViewer(QWidget * parentWidget, QObject *parent = 0);

    void loadImagesPair(PW::PWImage *leftImage, PW::PWImage *rightImage);
    void loadImagesPair(PW::PWImage *leftImage, PW::PWImage *rightImage,
                        QList<QVector<float>> matching_coords,
                        double accuracyTolerance = 0, bool drawOutlierMatches = false);
    QWidget *getView();
    void clearAll();

signals:

public slots:
    void onScaleChanged(float scaleFactor);

private:
    QWidget *                   mParentWidget;
    MatchigGraphicsView *       mView;
    QGraphicsScene              mScene;
    QPixmap *                   mPixmap;
    QGraphicsPixmapItem *       mPixmapItem;
    QPainter *                  mPainter;
    float                       mLastScaleFactor;
    float                       mAccumulatedScaleFactor;

};

#endif // MATCHINGVIEWER_H
