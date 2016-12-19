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
#include "tabgeneral.h"

General::General(QWidget *parent) : QWidget(parent) {

	// Setup the central scroll area
	QVBoxLayout *centralScrollLay = new QVBoxLayout();
	centralScroll = new QScrollArea;
	centralScrollLay->addWidget(centralScroll);
	this->setLayout(centralScrollLay);

	// And the layout for the scroll area
	QVBoxLayout *central = new QVBoxLayout(centralScroll);
	QWidget *centralScrollWidget = new QWidget(centralScroll->widget());
	centralScrollWidget->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	centralScrollWidget->setLayout(central);
	centralScroll->setWidget(centralScrollWidget);
	centralScrollWidget->show();
	centralScroll->setWidgetResizable(true);
	centralScroll->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	// The title of the tab
	QLabel *title = new QLabel("<center><h1>" + tr("General Settings") + "</h1></center>");
	central->addWidget(title);
	central->addSpacing(20);

	// It's possible to choose between English and German
	QLabel *transLabel = new QLabel("<b><span style=\"font-size: 12pt\">" + tr("Language") + "</span></b> " + tr("(Change requires restart of photo)") + "<hr>" + tr("Choose language of photo. A change will take effect the next time you start photo."));
	trans = new QComboBox;
	trans->addItem("English");
	trans->addItem("Deutsch");
	trans->addItem(QString::fromUtf8("Ελληνικά"));
	trans->addItem(QString::fromUtf8("Čeština"));
	QHBoxLayout *transLay = new QHBoxLayout;
	transLay->addStretch();
	transLay->addWidget(trans);
	transLay->addStretch();
	central->addWidget(transLabel);
	central->addSpacing(5);
	central->addLayout(transLay);
	central->addSpacing(20);

	// Option to enable composite
	QLabel *compLabel = new QLabel("<b><span style=\"font-size: 12pt\">" + tr("Composite") + "</span></b> " + tr("(Change requires restart of photo)") + "<hr>" + tr("If composite is enabled, then it is used to make the background of photo real half tranparent. If it is <b>dis</b>abled (default), then photo is just making a screenshot before starting up and sets that as background.<br><b>Warning:</b> When the checkbox below is enabled, but composite is disabled/no compositing available, then the background of photo will be all black!"));
	compLabel->setWordWrap(true);
	QHBoxLayout *compLay = new QHBoxLayout;
	composite = new QCheckBox(tr("Use Composite"));
	compLay->addStretch();
	compLay->addWidget(composite);
	compLay->addStretch();
	central->addWidget(compLabel);
	central->addSpacing(5);
	central->addLayout(compLay);
	central->addSpacing(20);

	// Option to adjust the menu sensitivity
	QLabel *menuLabel = new QLabel("<b><span style=\"font-size: 12pt\">" + tr("Menu Sensitivity") + "</span></b><hr>" + tr("Here you can adjust the sensitivity of the menu. The menu open when your mouse cursor is inside of a certain area. A higher value increases this area and causes the menu to open easier. But if the value is too high, then it can affect the usability of Photo; the menu may then open also when it's not supposed to."));
	menuLabel->setWordWrap(true);
	QHBoxLayout *menuLay = new QHBoxLayout;
	QLabel *menuLabelLeft = new QLabel(tr("Low Sensitivity"));
	QLabel *menuLabelRight = new QLabel(tr("High Sensitivity"));
	menu = new QSlider;
	menu->setMinimum(1);
	menu->setMaximum(10);
	menu->setOrientation(Qt::Horizontal);
	menu->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
	menu->setTickPosition(QSlider::TicksBelow);
	menu->setPageStep(1);
	menuLay->addStretch();
	menuLay->addWidget(menuLabelLeft);
	menuLay->addWidget(menu);
	menuLay->addWidget(menuLabelRight);
	menuLay->addStretch();
	central->addWidget(menuLabel);
	central->addSpacing(5);
	central->addLayout(menuLay);
	central->addSpacing(20);

	// Option to change thumbnail size
	QLabel *thumbSizeLabel = new QLabel("<b><span style=\"font-size: 12pt\">" + tr("Thumbnail Size") + "</span></b> " + tr("(Change requires restart of photo)") + "<hr>" + tr("Here you can adjust the thumbnail size. You can set it to any size between 20 and 256 pixel. Per default it is set to 80 pixel, but with different screen resolutions it might be nice to have them larger/smaller."));
	thumbSizeLabel->setWordWrap(true);
	QHBoxLayout *thumbSizeLay = new QHBoxLayout;
	thumbSizeSlider = new QSlider;
	thumbSizeSlider->setMinimum(20);
	thumbSizeSlider->setMaximum(256);
	thumbSizeSlider->setOrientation(Qt::Horizontal);
	thumbSizeSlider->setFixedWidth(150);
	thumbSizeSpin = new QSpinBox;
	thumbSizeSpin->setMinimum(20);
	thumbSizeSpin->setMaximum(256);
    thumbSizeSlider->setValue(80);
	thumbSizeSpin->setValue(80);
	thumbSizeLay->addStretch();
	thumbSizeLay->addWidget(thumbSizeSlider);
	thumbSizeLay->addWidget(thumbSizeSpin);
	thumbSizeLay->addStretch();
	central->addWidget(thumbSizeLabel);
	central->addSpacing(5);
	central->addLayout(thumbSizeLay);
	central->addSpacing(20);
	// The slider and spinbox are connected to each other
	connect(thumbSizeSlider, SIGNAL(valueChanged(int)), thumbSizeSpin, SLOT(setValue(int)));
	connect(thumbSizeSpin, SIGNAL(valueChanged(int)), thumbSizeSlider, SLOT(setValue(int)));

	// Option to disable the thumbnail cache
	QLabel *thumbCacheLabel = new QLabel("<b><span style=\"font-size:12pt\">" + tr("Thumbnail Cache") + "</span></b><hr>" + tr("Thumbnail creation can sometimes take a long time and slows down the computer a lot. Therefore photo is able to use a thumbnail cache. It follows the freedesktop.org specifications for thumbnails, and thus shares thumbnails with many other apps (not only qt, but also gtk, ...).<br>Although everybody is strongly encouraged to leave this option enabled, it can be disabled for one or the other reason (maybe saving harddrive space?).<br><b>Note:</b> If this option is <b>disabled</b>, the use of photo (and your whole computer) can be slowed down significantly while thumbnails are being recreated again (assumed they have been created already once)!"));
	thumbCacheLabel->setWordWrap(true);
	QHBoxLayout *thumbCacheLay = new QHBoxLayout;
	thumbCache = new QCheckBox(tr("Enable Thumbnail Cache"));
	thumbCacheLay->addStretch();
	thumbCacheLay->addWidget(thumbCache);
	thumbCacheLay->addStretch();
	central->addWidget(thumbCacheLabel);
	central->addSpacing(5);
	central->addLayout(thumbCacheLay);
	central->addSpacing(50);

	central->addStretch();


	// And load the settings
	loadSettings();

}

// Loading the settings
void General::loadSettings() {

    QFile file(QDir::homePath() + "/.photo/settings");

    if(!file.open(QIODevice::ReadOnly))

		QMessageBox::critical(0,tr("Couldn't open settings file"),tr("<b>ERROR!</b><br><br>Couldn't open the settings file. Please ensure, that you have read and write access to your home directory!"));

	else {

		QTextStream in(&file);
		QString all = in.readAll();

		if(all.contains("Language=de"))
			trans->setCurrentIndex(1);
		else if(all.contains("Language=el"))
			trans->setCurrentIndex(2);
		else if(all.contains("Language=cz"))
			trans->setCurrentIndex(3);
		else
			trans->setCurrentIndex(0);

		if(all.contains("Composite=1"))
			composite->setChecked(true);
		else
			composite->setChecked(false);

		if(all.contains("MenuSensitivity="))
			menu->setValue(all.split("MenuSensitivity=").at(1).split("\n").at(0).toInt());
		else
			menu->setValue(4);

		if(all.contains("ThumbnailSize="))
			thumbSizeSlider->setValue(all.split("ThumbnailSize=").at(1).split("\n").at(0).toInt());
		else
			thumbSizeSlider->setValue(80);

		if(all.contains("ThumbnailCache=1"))
			thumbCache->setChecked(true);
		else
			thumbCache->setChecked(false);

		file.close();

	}

}

// Saving the settings
void General::saveSettings() {

	qDebug() << "Saving settings";

    QFile file(QDir::homePath() + "/.photo/settings");

	if(!file.open(QIODevice::ReadWrite))

		QMessageBox::critical(0,tr("Couldn't open settings file"),tr("<b>ERROR!</b><br><br>Couldn't open the settings file. Please ensure, that you have read and write access to your home directory!"));

	else {

		file.close();
		file.remove();
		file.open(QIODevice::ReadWrite);

		QTextStream out(&file);

		QMap<QString,QString> language;
		language["English"] = "en";
		language["Deutsch"] = "de";
		language[QString::fromUtf8("Ελληνικά")] = "el";
		language[QString::fromUtf8("Čeština")] = "cz";

		QString cont = "Version=" + version + "\n";
		cont += QString("Language=%1\n").arg(language[trans->currentText()]);
		cont += QString("Composite=%1\n").arg(int(composite->isChecked()));
		cont += QString("MenuSensitivity=%1\n").arg(menu->value());
		cont += QString("ThumbnailSize=%1\n").arg(thumbSizeSlider->value());
		cont += QString("ThumbnailCache=%1\n").arg(int(thumbCache->isChecked()));

		out << cont;
		file.close();

	}

}


General::~General() { }
