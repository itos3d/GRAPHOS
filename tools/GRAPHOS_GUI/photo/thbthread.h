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
#ifndef THBTHREAD_H
#define THBTHREAD_H

#include <QThread>
#include <QImageWriter>
#include <QImageReader>
#include <QFileInfo>
#include <QtDebug>

#include <QDateTime>
#include <QDir>
#include <QBuffer>

#include <QCryptographicHash>

// This class creates the thumbnails in the background in a different thread
class ThumbThread : public QThread {

	Q_OBJECT

public:
	// Some variables for the needed information
	int counttot;
	QFileInfoList allimgs;
	int height;
	int breakme;
	bool cacheEnabled;

signals:
	// Whenever a thumbnail is succesfully created, send it to main thread
	void updateThb(QImage img,QString path, int pos);

protected:
	// This function is started from main thread
	void run() {

		qDebug() << "Thread started";

		for(int i = 0; i < counttot; ++i) {
            // Stop thumbnail creation
            if(breakme)
                break;

			// Create the md5 hash for the thumbnail file
			QByteArray path = "file://" + allimgs.at(i).absoluteFilePath().toAscii();
			QByteArray md5 = QCryptographicHash::hash(path,QCryptographicHash::Md5).toHex();

			// Prepare the QImage (QPixmap cannot be used, since its use is not safe outside main thread and would most likely lead to a crash)
			QImage p;

			// Depending on the set size of the thumbnails, choose the right thumbnail resolution
			int ts = 256;
			QString td = "large";
			if(height < 129) {
				ts = 128;
				td = "normal";
			}

			// If there exists a thumbnail of the current file already
			if(QFile(QDir::homePath() + "/.thumbnails/" + td + "/" + md5 + ".png").exists() && cacheEnabled) {

				p.load(QDir::homePath() + "/.thumbnails/" + td + "/" + md5 + ".png");

			// Otherwise load thumbnail from original (using QImageReader for better performance)
			} else {

				QImageReader reader(allimgs.at(i).absoluteFilePath());
				int readerWidth = reader.size().width();
				int readerHeight = reader.size().height();

				if(readerWidth > ts) {
					float q = ts/(readerWidth*1.0);
					readerWidth *= q;
					readerHeight *= q;
				}
				if(readerHeight > ts) {
					float q = ts/(readerHeight*1.0);
					readerWidth *= q;
					readerHeight *= q;
				}

				reader.setScaledSize(QSize(readerWidth,readerHeight));

				p = reader.read();

				// If the file itself wasn't read from the thumbnails folder, is not a temporary file, and if the original file isn't at thumbnail size itself
				if(cacheEnabled & !allimgs.at(i).absoluteFilePath().startsWith(QDir::homePath() + "/.thumbnails/") && !allimgs.at(i).absoluteFilePath().startsWith(QDir::tempPath()) && (p.height() > 127 || p.width() > 127)) {

					qDebug() << "Writing new thumbnail file";

					// We use a QImageWriter (fater, metainfo support) - the path is a temporary path (for reason, see below)
					QImageWriter writer(QDir::tempPath() + "/" + md5 + "__photo.png","png");

					// The following meta information is required by the standard
					writer.setText("Thumb::URI",path);
					writer.setText("Thumb::MTime",QString("%1").arg(allimgs.at(i).lastModified().toTime_t()));
					writer.setText("Thumb::Size",QString("%1").arg(allimgs.at(i).size()));

					// We write the temporary file
					writer.write(p);

					// If the file still doesn't exist, copy it to the right location (>> protection from concurrency)
					if(!QFile(QDir::homePath() + "/.thumbnails/" + td + "/" + md5 + ".png").exists()) {
						if(!QFile(QDir::tempPath() + "/" + md5 + "__photo.png").copy(QDir::homePath() + "/.thumbnails/" + td + "/" + md5 + ".png"))
							qDebug() << "ERROR CREATING NEW THUMBNAIL FILE";
					}
					// Delete temporary file
					QFile(QDir::tempPath() + "/" + md5 + "__photo.png").remove();
				}

			}

			// Scale image to the right size
			if(p.width() != height*4/3.0-10) {
				p = p.scaledToWidth((height*4/3.0-10)*2,Qt::SmoothTransformation);
				p = p.scaledToWidth(height*4/3.0-10,Qt::FastTransformation);
			}
			if(p.height() > height-5) {
				if(p.height() > (height)*2)
					p = p.scaledToHeight(height+50,Qt::SmoothTransformation);
				p = p.scaledToHeight(height-5,Qt::FastTransformation);
			}

			// Send out signal with all the data
			emit updateThb(p,allimgs.at(i).absoluteFilePath(),i);

		}

	}

};

#endif // THBTHREAD_H
