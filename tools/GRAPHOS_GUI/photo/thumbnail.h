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
#ifndef THUMBNAIL_H
#define THUMBNAIL_H

#include "thbthread.h"

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QDir>
#include <QtDebug>
#include <QMouseEvent>

#include <QTextItem>
#include <QTextDocument>

#include <QRadialGradient>

class Thumbnails : public QGraphicsView {

	Q_OBJECT

public:
	Thumbnails();
	~Thumbnails();

	// Scene for the thumbnails
	QGraphicsScene scene;

	// Thread creating the thumbnails in the background
	ThumbThread *thread;

	// Diffferent variables
	int counttot;
	int height;
	int previousHover;
	int currentHover;
	bool cacheEnabled;

	// The path of the current file
	QString currentfile;

	// Storring info about images in current directory
	QFileInfoList allimgs;
	QStringList allThumbs;

	// Initialising the QLists for the QPixmaps(item)
	QList<QGraphicsPixmapItem*> allPixItem;
	QList<QPixmap> allPixImg;
	QList<QPixmap> allPixSel;
	QList<QPixmap> allPixHov;

	// Gathering information about all images in current directory
	void allImgs();
        void allImgs(QStringList imageURLs);

public slots:
	// Add a thumbnail to the scene
	void addThumbnail(QImage,QString,int);

	// Hide/Show thumbnail view
	void toggle();

	// Stop the thumbnail creation
	void stopThread();

	// Update the hovered/selected thumbnail items
	void updImgMark(int oldpos, int newpos);
	void updImgHov();

	// (Re-)Loading the thumbnails
	void loadThumbs();

	// Enable/disable the menu item "Interrupt Thumbnail creation"
	void enableMenuInterrupt();

signals:
	// Emitted at click on thumbnail
	void loadImg(QString, int);

	// Enable/disable the menu item "Interrupt Thumbnail creation"
	void disEnableMenuInterrupt(bool);

protected:
	// Detecting mouse clicks
	void mouseReleaseEvent(QMouseEvent*);
	// Detecting mouse moves
    void mouseMoveEvent(QMouseEvent *event);

};

#endif // THUMBNAIL_H
