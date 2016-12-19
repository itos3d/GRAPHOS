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
#include <QPainter>
#include <QDebug>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

#include "crosshairgraphicsitem.h"

CrosshairGraphicsItem::CrosshairGraphicsItem(PW::PW2dPoint *point):
    QGraphicsEllipseItem(point->getCoord(0)-10,point->getCoord(1)-10,20, 20),
    mPoint(point),
    mCrossColor(Qt::blue)
{
    setFlag(ItemSendsGeometryChanges, true);
    setFlag(ItemSendsScenePositionChanges, true);
    setFlag(ItemIgnoresTransformations, true);
}

void CrosshairGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(mCrossColor);
    painter->drawLine(mPoint->getCoord(0)-10, mPoint->getCoord(1), mPoint->getCoord(0)+10, mPoint->getCoord(1));
    painter->drawLine(mPoint->getCoord(0), mPoint->getCoord(1)-10, mPoint->getCoord(0), mPoint->getCoord(1)+10);

    painter->setPen(Qt::red);
    painter->drawText(QRect(mPoint->getCoord(0)+12,mPoint->getCoord(1)-12,100, 100),mPoint->getName());

    QGraphicsEllipseItem::paint(painter,option,widget);
}

QRectF CrosshairGraphicsItem::boundingRect() const
{
    QRectF ellipseBounding = QGraphicsEllipseItem::boundingRect();
    return QRectF(ellipseBounding.topLeft().x(), ellipseBounding.topLeft().y(),
                  ellipseBounding.width()+100, ellipseBounding.height()+22);
}

void CrosshairGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mouseReleaseEvent(event);
    emit pointChanged(mPoint, this->scenePos());
}

QVariant CrosshairGraphicsItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    return QGraphicsEllipseItem::itemChange(change,value);
}

int CrosshairGraphicsItem::type() const
{
    int type = QGraphicsEllipseItem::type();
    return type;
}

void CrosshairGraphicsItem::setCrossColor(QColor color)
{
    mCrossColor = color;
}


