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
#ifndef MENU_H
#define MENU_H

#include <QLabel>
#include <QtDebug>
#include <QEvent>

// A custom MenuItem used for the Menu
class MenuItem : public QLabel {

	Q_OBJECT
public:
	MenuItem(QString txt = "", QString icon = "", QString setData = "", int closeMe = 1, bool enabled = true);
	~MenuItem();

	// Setting an icon at the beginning of the item
	void setIcon(QString);

	// The look of the label when hovered/normal
	QString ssNormal;
	QString ssHover;

	// The data connected with this label
	QString data;

	// Closing setting for this label
	int close;

protected:
	bool event(QEvent *e);

signals:
	void clicked();

};

#endif // MENU_H
