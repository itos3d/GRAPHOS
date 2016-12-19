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
#include "image.h"

Image::Image() : QGraphicsView() {

	// Start a timer that calls the drawImg() function on startup whenever the scene is correctly set up
	t = new QTimer;
//	t->start(50);

        setMouseTracking(true);
        setContextMenuPolicy(Qt::CustomContextMenu);
}

// Zooming the image on ctrl+mouse wheel
void Image::wheelEvent(QWheelEvent *event) {

	// Check if ctrl is pressed
	int ctrlPressed = 0;

	switch(event->modifiers()) {
	case(Qt::ControlModifier):
		ctrlPressed = 1;
		break;
	}

	// if ctrl is pressed, zoom in/out
	if(ctrlPressed) {

		if(event->delta() > 0)
			emit zoom(1);
		else
			emit zoom(2);

	} else
		QGraphicsView::wheelEvent(event);

}

// ctrl+mouse wheel click resets the zooming position
void Image::mouseReleaseEvent(QMouseEvent *event) {

	int ctrlPressed = 0;

	switch(event->modifiers()) {
	case(Qt::ControlModifier):
		ctrlPressed = 1;
		break;
	}

	if(ctrlPressed) {

		if(event->type() == 3)
			emit zoom(0);

	} else
		QGraphicsView::mouseReleaseEvent(event);

}

// Get the current mouse position
void Image::mouseMoveEvent(QMouseEvent *event) {

        emit mousePos(event->pos());
        QGraphicsView::mouseMoveEvent(event);
}

void Image::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}
