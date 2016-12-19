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
#include "MatchigGraphicsView.h"

MatchigGraphicsView::MatchigGraphicsView() :
    QGraphicsView()
{
}

void MatchigGraphicsView::wheelEvent(QWheelEvent *event)
{
    // Check if ctrl is pressed
    int ctrlPressed = 0;

    switch(event->modifiers()) {
    case(Qt::ControlModifier):
        ctrlPressed = 1;
        break;
    }

    // if ctrl is pressed, zoom in/out
    if(ctrlPressed) {
        setTransformationAnchor(AnchorUnderMouse);
        if(event->delta() > 0)
            emit scaleChanged(1.25);
//            scale(1.25,1.25);
        else
            emit scaleChanged(0.8);
//            scale(0.8,0.8);

    } else
        QGraphicsView::wheelEvent(event);
}
