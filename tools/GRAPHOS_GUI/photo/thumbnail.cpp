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
#include "thumbnail.h"

Thumbnails::Thumbnails() : QGraphicsView() {

	// Set the QGraphicsScene
	this->setScene(&scene);

	// Mouse Tracking is needed for showing tooltips
	this->setMouseTracking(true);

	// The background is transparent
	this->setStyleSheet("background-color: transparent");


	currentfile = "";   // The currently viewed image
	counttot = 0;       // Total amount of images in directory
	height = 0;       // Storring the Thumbnail view height (Note: The Thumbnails themself have a different height!) - Adjusted from mainwindow.cpp
	previousHover = -1; // The position of the previous hovered item
	currentHover = -1;  // The position of the currently hovered item
	cacheEnabled = false;	// Wether the thumbnail cache is enabled or not (adjusted from mainwindow.cpp)

	// The Thumbnails are created in a thread and displayed via a SIGNAL-SLOT
	thread = new ThumbThread;
	connect(thread, SIGNAL(updateThb(QImage,QString,int)), this, SLOT(addThumbnail(QImage,QString,int)));

	// This enables/disables the menu item "Interrupt Thumbnail creation"
	connect(thread, SIGNAL(finished()), this, SLOT(enableMenuInterrupt()));

}

// Adding a Thumbnail to the Thumbnail View
void Thumbnails::addThumbnail(QImage p, QString f, int pos) {

	qDebug() << "Creating Thumbnail:" << pos+1;

	// Get the position of the thumbnails on the thumbnail item (=thumbnail + background)
	int x = 5;
	if(p.width() < height*4/3.0-2*x)
		x += (height*4/3.0-2*x-p.width())/2.0;
	int y = 2.5;
	if(p.height() < height-2*y)
		y += (height-2*y-p.height())/2.0;

	// This QPixmap is displayed for the selected image
	QPixmap select(height*4/3.0,height);
	select.fill(Qt::transparent);
	QPainter painter(&select);
	painter.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter.drawImage(x,y,p);
	QRadialGradient gradient(height/2,height/2,height*2/3.0);
	gradient.setColorAt(0,QColor::fromRgba(qRgba(255,255,255,10)));
	gradient.setColorAt(1,QColor::fromRgba(qRgba(255,255,255,220)));
	QBrush brush(gradient);
	painter.fillRect(select.rect(),brush);
	painter.end();

	// This QPixmap is displayed as hover item
	QPixmap hover(height*4/3.0,height);
	hover.fill(Qt::transparent);
	QPainter painter2(&hover);
	painter2.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter2.drawImage(x,y,p);
	QRadialGradient gradient2(height/2,height/2,height*2/3.0);
	gradient2.setColorAt(0,QColor::fromRgba(qRgba(0,0,0,0)));
	gradient2.setColorAt(1,QColor::fromRgba(qRgba(0,0,0,180)));
	QBrush brush2(gradient2);
	painter2.fillRect(hover.rect(),brush2);
	painter2.end();

	// The normal QPixmap, not hovered, not selected
	QPixmap normal(height*4/3.0,height);
	normal.fill(Qt::transparent);
	QPainter painter3(&normal);
	painter3.setCompositionMode(QPainter::CompositionMode_SourceOver);
	painter3.drawImage(x,y,p);
	painter3.end();

	// Set the QPixmap
	if(pos == allimgs.indexOf(currentfile)) {
		allPixItem.at(pos)->setPixmap(select);
	} else {
		allPixItem.at(pos)->setPixmap(normal);
	}
	allPixItem.at(pos)->setData(123,f);
	allPixItem.at(pos)->setData(234,pos);

	// Set the Tooltip
	allPixItem.at(pos)->setToolTip("<span style=\"color: white; background-color: black; white-space: nowrap\">" + QFileInfo(f).fileName() + "</span>");

	// Store QPixmaps in lists
	allPixImg.replace(pos,normal);
	allPixSel.replace(pos,select);
	allPixHov.replace(pos,hover);

}

// Gather information about all the images in the current directory
void Thumbnails::allImgs() {

	// Get the current directory (and if for some reason photo got a directory, don't go up a level)
	QString currentdir = "";
	if(QFileInfo(currentfile).isFile())
		currentdir = QFileInfo(currentfile).absoluteDir().absolutePath();
	else
		currentdir = currentfile;

	qDebug() << "Getting infos of all images in current dir:" << currentdir;

	// Get QDir instance
	QDir *dir = new QDir(currentdir);

	// These are the images known by photo
	QStringList flt;
	flt << "*.html" << "*.bmp" << "*.gif" << "*.tif" << "*.jpg" << "*.jpeg" << "*.jpeg2000" << "*.png" << "*.pbm" << "*.pgm" << "*.ppm" << "*.xbm" << "*.xpm" << "*.tiff";
	dir->setNameFilters(flt);

	// Store a QFileInfoList and a QStringList with the filenames
	allimgs = dir->entryInfoList(QDir::NoFilter,QDir::IgnoreCase);
	allThumbs = dir->entryList();

	// Storing number of images
	counttot = allimgs.length();

	// Start to load the thumbnails
	loadThumbs();
}

// Gather information about all the images in the current directory
void Thumbnails::allImgs(QStringList imageURLs) {
    imageURLs.sort();
    // Store a QFileInfoList and a QStringList with the filenames

    for (int i = 0; i< imageURLs.count();i++){
        allimgs.append(QFileInfo(imageURLs.at(i)));
    }
    allThumbs = imageURLs;
    // Storing number of images
    counttot = allimgs.length();

    // Start to load the thumbnails
    loadThumbs();
}

// Starting to load the thumbnails
void Thumbnails::loadThumbs() {

	if(counttot != 0) {

		qDebug() << "Loading Thumbnails in Background";

		// If thread is running, stop it first
		thread->breakme = 1;
		thread->wait(500);

		// Reset Thumbnails related variables
		scene.clear();
		allPixItem.clear();
		allPixImg.clear();
		allPixSel.clear();
		allPixHov.clear();

		// Reduce Size of sceneRect (size increases automatically, but doesn't shrink automatically)
		scene.setSceneRect(scene.itemsBoundingRect());

		// For each thumbnail to be created:
		for(int i = 0; i < counttot; ++i) {

			// That's a dummy thumbnail (black border, grey background, filename as label)
			QPixmap blind(height*4/3.0,height);
			blind.fill(Qt::transparent);
			QPainter paint(&blind);
			paint.setCompositionMode(QPainter::CompositionMode_SourceOver);
			QRadialGradient gradient(height/2,height/2,height*2/3.0);
			gradient.setColorAt(0,QColor::fromRgba(qRgba(0,0,0,120)));
			gradient.setColorAt(1,QColor::fromRgba(qRgba(0,0,0,90)));
			QBrush brush(gradient);
			paint.fillRect(blind.rect(),brush);
			paint.drawLine(0,0,0,height);
			paint.drawLine(0,0,height*4/3.0,0);
			paint.drawLine(height*4/3.0,0,height*4/3.0,height);
			paint.drawLine(0,height,height*4/3.0,height);
			QTextDocument txt;
			txt.setHtml("<center><div style=\"text-align: center; font-size: 8pt; font-wight: bold; color: white; background: black\">" + allThumbs.at(i) + "</div></center>");
			txt.setTextWidth(94);
			paint.translate(3,height*2/3.0);
			txt.drawContents(&paint);
			paint.end();

			// The same dummy thumbnail, but in select mode
			QPixmap blindSel = blind.copy(0,0,height*4/3.0,height);
			QPainter paint2(&blindSel);
			paint2.setCompositionMode(QPainter::CompositionMode_SourceOver);
			QRadialGradient gradient2(height/2,height/2,height*2/3.0);
			gradient2.setColorAt(0,QColor::fromRgba(qRgba(0,0,0,100)));
			gradient2.setColorAt(1,QColor::fromRgba(qRgba(0,0,0,210)));
			QBrush brush2(gradient2);
			paint2.fillRect(blindSel.rect(),brush2);
			paint2.end();

			// The same dummy thumbnail, but in hover mode
			QPixmap blindHov = blind.copy(0,0,height*4/3.0,height);
			QPainter paint3(&blindHov);
			paint3.setCompositionMode(QPainter::CompositionMode_SourceOver);
			QRadialGradient gradient3(height/2,height/2,height*2/3.0);
			gradient3.setColorAt(0,QColor::fromRgba(qRgba(0,0,0,100)));
			gradient3.setColorAt(1,QColor::fromRgba(qRgba(0,0,0,20)));
			QBrush brush3(gradient3);
			paint3.fillRect(blindHov.rect(),brush3);
			paint3.end();


			// Set up the QGraphicsPixmapItem (used for real thumbnail lateron as well)
			QGraphicsPixmapItem *pix_blind = new QGraphicsPixmapItem;

			// Set dummy thumbnail
			if(allimgs.at(i) == currentfile)
				pix_blind->setPixmap(blindSel);
			else
				pix_blind->setPixmap(blind);

			// Set dummy position
			pix_blind->setPos(i*height*4/3.0,0);
			pix_blind->setData(123,allimgs.at(i).absoluteFilePath());
			pix_blind->setData(234,i);

			// Append data to lists
			allPixItem.append(pix_blind);
			allPixImg.append(blind);
			allPixSel.append(blindSel);
			allPixHov.append(blindHov);

			// Add dummy to thumbnail view
			scene.addItem(pix_blind);

		}

		// Adjust sceneRect
		scene.setSceneRect(scene.itemsBoundingRect());

		// Center the opened file
		if(allimgs.indexOf(currentfile) != -1 && allimgs.indexOf(currentfile) < allPixItem.length())
			this->centerOn(allPixItem.at(allimgs.indexOf(currentfile)));

		// Reset the thread
		thread->breakme = 0;

		// Set the needed information
		thread->counttot = counttot;
		thread->allimgs = allimgs;
		thread->height = height;
		thread->cacheEnabled = cacheEnabled;

		// Enable the menu item "Interrupt Thumbnail creation"
		emit disEnableMenuInterrupt(true);

		// And start creating thumbnails
		thread->start();
	}

}

// Disable the menu item "Interrupt Thumbnail creation"
void Thumbnails::enableMenuInterrupt() {
	emit disEnableMenuInterrupt(false);
}

// Stop the thumbnail creation
void Thumbnails::stopThread() {
	thread->breakme = 1;
}

// A mouse click on a thumbnail
void Thumbnails::mouseReleaseEvent(QMouseEvent *e) {

	// Get the filename of the clicked item
	QString img = this->itemAt(e->pos())->data(123).toString();

	// If the click wasn't on an item, do nothing. Otherwise:
	if(img != "") {

		// Get list position of clicked item
		int pos = this->itemAt(e->pos())->data(234).toInt();

		// Store the old position
//		int oldpos = allThumbs.indexOf(QFileInfo(currentfile).fileName());
        int oldpos = allThumbs.indexOf(currentfile);

		// Load the new image and update the marking
		emit loadImg(img, pos);
		updImgMark(oldpos,pos);

	}
}

// Mouse hovering thumbnails
void Thumbnails::mouseMoveEvent(QMouseEvent *e) {

    // Get the filename of hovered item
    QString img = this->itemAt(e->pos())->data(123).toString();

    // If actual item was hovered:
    if(img != "") {

        // Adjust hover variables
        previousHover = currentHover;
        currentHover = this->itemAt(e->pos())->data(234).toInt();

        // And update QPixmap
        updImgHov();

    }

}

// Unselect old item, select new one
void Thumbnails::updImgMark(int oldpos, int newpos) {

	// If positions are valid and in range (they should always be, but just to be on the safe side)
	if(oldpos != -1 && newpos != -1 && oldpos < allPixItem.length() && newpos < allPixItem.length()) {

		allPixItem.at(oldpos)->setPixmap(allPixImg.at(oldpos));
		allPixItem.at(newpos)->setPixmap(allPixSel.at(newpos));
		this->ensureVisible(allPixItem.at(newpos));

	}

}

// Update the hovering thumbnails
void Thumbnails::updImgHov() {

	// If hovered item is valid and in range (they should always be, but just to be on the safe side)
	if(previousHover != -1 && currentHover != -1 && previousHover < allPixItem.length() && currentHover < allPixItem.length()) {
		if(previousHover != allimgs.indexOf(currentfile))
			allPixItem.at(previousHover)->setPixmap(allPixImg.at(previousHover));
		if(currentHover != allimgs.indexOf(currentfile))
			allPixItem.at(currentHover)->setPixmap(allPixHov.at(currentHover));
	}

}

// Toggle the Thumbnail view
void Thumbnails::toggle() {
	if(this->isVisible()) {
		this->hide();
	} else {
		this->show();
	}
}


Thumbnails::~Thumbnails() { }
