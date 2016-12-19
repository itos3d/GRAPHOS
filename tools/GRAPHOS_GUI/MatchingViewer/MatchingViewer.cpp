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
#include "MatchingViewer.h"
#include "photo/CrosshairGraphicsItem.h"

#include <QImageReader>
#include <QLayout>
#include <QtAlgorithms>

MatchingViewer::MatchingViewer(QWidget *parentWidget, QObject *parent) :
    QObject(parent),
    mParentWidget(parentWidget),
    mPixmap(0),
    mPixmapItem(0),
    mPainter(0),
    mLastScaleFactor(0.0),
    mAccumulatedScaleFactor(1)
{
    mView = new MatchigGraphicsView();
    mView->setScene(&mScene);
    mView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mView->setDragMode(QGraphicsView::ScrollHandDrag);
    mView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    connect(mView, SIGNAL(scaleChanged(float)),this, SLOT(onScaleChanged(float)));
}

void MatchingViewer::loadImagesPair(PW::PWImage *leftImage, PW::PWImage *rightImage)
{
    QImageReader reader(leftImage->getFullPath());
    QImage image1 = reader.read();
    reader.setFileName(rightImage->getFullPath());
    QImage image2 = reader.read();

    if(mPainter)
        delete mPainter;
    if(mPixmap)
        delete mPixmap;

    mPixmap = new QPixmap(image1.width()+image2.width(), image1.height());
    mPixmap->fill(Qt::transparent);
    mPainter = new QPainter(mPixmap);
    mPainter->drawImage(0,0,image1,0,0);
    mPainter->drawImage(image1.width(),0,image2,0,0);
    mPixmapItem->setPixmap(*mPixmap);

    mView->invalidateScene();
}

void MatchingViewer::loadImagesPair(PW::PWImage *leftImage, PW::PWImage *rightImage,
                                    QList<QVector<float>> matching_coords,
                                    double accuracyTolerance, bool drawOutlierMatches)
{
    QImageReader reader(leftImage->getFullPath());
    QImage image1 = reader.read();
    reader.setFileName(rightImage->getFullPath());
    QImage image2 = reader.read();

    if(mPainter){
        delete mPainter;
        mPainter = 0;
    }
    if(mPixmap){
        delete mPixmap;
        mPixmap = 0;
    }
    if(mPixmapItem){
        delete mPixmapItem;
    }
    mScene.clear();
    mPixmapItem = 0;
    mPixmapItem = new QGraphicsPixmapItem();
    mScene.addItem(mPixmapItem);

    mPixmap = new QPixmap(image1.width()+image2.width(), image1.height());
    mPixmap->fill(Qt::transparent);
    mPainter = new QPainter(mPixmap);
    mPainter->drawImage(0,0,image1,0,0);
    mPainter->drawImage(image1.width(),0,image2,0,0);
    mPixmapItem->setPixmap(*mPixmap);

    if(mLastScaleFactor)
        mView->scale(1.0/mLastScaleFactor, 1.0/mLastScaleFactor);
    int prueba = mView->viewport()->width();
    int prueba2 = mView->width();
    float scaleFactor = ((float)mView->viewport()->width()) / mPixmap->width();
    mView->scale(scaleFactor,scaleFactor);
    mLastScaleFactor= scaleFactor;
    float prueba3 = qreal(mPixmap->width())/qreal(leftImage->getSize().width()+rightImage->getSize().width());
    float prueba4=qreal(mPixmap->height())/qreal(leftImage->getSize().height()+rightImage->getSize().height());
    QTransform trans;
    trans.translate(qreal(mPixmapItem->sceneBoundingRect().left()),qreal(mPixmapItem->sceneBoundingRect().top()));
    trans=trans.scale(qreal(mPixmap->width())/qreal(leftImage->getSize().width()+rightImage->getSize().width()),
                      qreal(mPixmap->height())/qreal(leftImage->getSize().height()+rightImage->getSize().height()));

    for (int i=0; i<matching_coords.size(); i++){
        if (matching_coords.at(i)[4] <= accuracyTolerance || drawOutlierMatches){

            QPointF transPoint = trans.map(QPointF(0.0,0.0));
            PW::PW2dPoint *point = new PW::PW2dPoint(transPoint.x(),transPoint.y(),"");

            QGraphicsLineItem *lineItem = new QGraphicsLineItem(matching_coords.at(i)[0],matching_coords.at(i)[1],
                    matching_coords.at(i)[2] + image1.width(),matching_coords.at(i)[3]);
            int red = 50;
            int green = 50;
            int blue = 255;
            if (accuracyTolerance && matching_coords.at(i)[4]>=0){
                red = matching_coords.at(i)[4] * 255 / accuracyTolerance;
                green = 255 - red;
                blue = 0;
                if (red>255) red = green = blue = 0;
            }
            lineItem->setPen(QPen(QColor(red, green , blue),2));
            QGraphicsEllipseItem *leftEllipseItem = new QGraphicsEllipseItem(matching_coords.at(i)[0]-10,
                    matching_coords.at(i)[1]-10,
                    20,
                    20);
            leftEllipseItem->setPen(QPen(QColor(119, 221 , 119),2));
            QGraphicsEllipseItem *rightEllipseItem = new QGraphicsEllipseItem(matching_coords.at(i)[2]+ image1.width()-10,
                    matching_coords.at(i)[3]-10,
                    20,
                    20);
            rightEllipseItem->setPen(QPen(QColor(119, 221 , 119),2));

            mScene.addItem(lineItem);
            lineItem->moveBy(point->x(),point->y());

            mScene.addItem(rightEllipseItem);
            mScene.addItem(leftEllipseItem);
        }
    }
//    mView->scale(mAccumulatedScaleFactor, mAccumulatedScaleFactor);
    mScene.invalidate();
}

QWidget *MatchingViewer::getView()
{
    return mView;
}

void MatchingViewer::clearAll()
{
    mScene.clear();
    mScene.invalidate();
    mPixmapItem = 0;
}

void MatchingViewer::onScaleChanged(float scaleFactor)
{
    mView->scale(scaleFactor, scaleFactor);
    mAccumulatedScaleFactor*=(1/scaleFactor);
}
