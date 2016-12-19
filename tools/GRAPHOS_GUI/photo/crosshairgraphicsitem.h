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
#ifndef CROSSHAIRGRAPHICSITEM_H
#define CROSSHAIRGRAPHICSITEM_H

#include <QGraphicsEllipseItem>

#include "PW2dPoint.h"

class CrosshairGraphicsItem : public QObject, public QGraphicsEllipseItem
{

    Q_OBJECT

public:
    CrosshairGraphicsItem(PW::PW2dPoint *point);
    int type () const;
    void setCrossColor(QColor color);

protected:
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = 0 );
    QRectF boundingRect() const;
    void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );
    QVariant itemChange ( GraphicsItemChange change, const QVariant & value );

private:
    PW::PW2dPoint *mPoint;
    QColor mCrossColor;

signals:
    void pointChanged(PW::PW2dPoint *point, QPointF pos);
};

#endif // CROSSHAIRGRAPHICSITEM_H
