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
#include "CrossGraphicItem.h"

CrossGraphicItem::CrossGraphicItem(QPointF center):
    mCenter(center)
{
}

void CrossGraphicItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::blue);
    painter->drawLine(mCenter.x()-10, mCenter.y(), mCenter.x()+10, mCenter.y());
    painter->drawLine(mCenter.x(), mCenter.y()-10, mCenter.x(), mCenter.y()+10);
}

QRectF CrossGraphicItem::boundingRect() const
{
    return QRectF(mCenter.x()-10, mCenter.y()-10, 22, 22);
}

int CrossGraphicItem::type() const
{
//    return Type;
    return 9999;
}

QPainterPath CrossGraphicItem::shape() const
{
    QPainterPath path;
    path.addRect(mCenter.x()-10, mCenter.y()-10, 22, 22);
    return path;
}
