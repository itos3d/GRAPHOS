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
#include "menu.h"

// A custom QLabel used for the menu
MenuItem::MenuItem(QString txt, QString icon, QString setData, int closeMe, bool clickable) : QLabel(txt) {

	// Enable mouse tracking for hover effect
	this->setMouseTracking(true);

	ssNormal = "QLabel { background: transparent; border: none; color: grey; } QLabel:disabled { color: white; font-weight: bold }";
	ssHover = "QLabel { background: transparent; border: none; color: white; } QLabel:disabled { color: white; font-weight: bold; }";

	// Set the default stylesheet
	MenuItem::setStyleSheet(ssNormal);

	// Set the transmitted data
	data = setData.trimmed();
	close = closeMe;
	this->setEnabled(clickable);
	setIcon(icon);

}

// Get all the needed events and connect them to the slots
bool MenuItem::event(QEvent *e) {

	if(e->type() == QEvent::MouseMove)
		MenuItem::setStyleSheet(ssHover);
	else if(e->type() == QEvent::Leave)
		MenuItem::setStyleSheet(ssNormal);

	if(e->type() == QEvent::MouseButtonPress)
		emit clicked();

	QList<QEvent::Type> types;
	types << QEvent::MouseButtonDblClick;
	types << QEvent::MouseButtonPress;
	types << QEvent::MouseButtonRelease;

	if(!types.contains(e->type()))
		QLabel::event(e);

	return e->isAccepted();

}

// Add an icon to the front of the string
void MenuItem::setIcon(QString icon) {

	if(icon != "")
		this->setText("<img height=\"13\" src=\"" + icon + "\">&nbsp;" + this->text());

}

MenuItem::~MenuItem() { }
