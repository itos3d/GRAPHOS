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
#ifndef IMAGE_H
#define IMAGE_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QtDebug>
#include <QTimer>
#include <QApplication>
#include <QDesktopWidget>

class Image : public QGraphicsView {

	Q_OBJECT

public:
	Image();

	// The timer checks at startup in short intervals if the graphicsscene is correctly set up, and whenever that's the case it's calling the drawImg() function (see mainwindow.cpp)
	QTimer *t;

protected:
	// This events are used for zooming and menu opening/closing
	void wheelEvent(QWheelEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);

//        void paintEvent(QPaintEvent *event);

signals:
	void zoom(int);
	void mousePos(QPoint);
};

#endif // IMAGE_H
