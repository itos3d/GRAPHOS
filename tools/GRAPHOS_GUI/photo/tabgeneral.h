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
#ifndef TABGENERAL_H
#define TABGENERAL_H

#include <QWidget>

#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>

#include <QCheckBox>
#include <QComboBox>

#include <QSlider>
#include <QSpinBox>

#include <QFile>
#include <QDir>

#include <QMessageBox>
#include <QTextStream>

#include <QtDebug>

class General : public QWidget {

	Q_OBJECT
public:
	General(QWidget *parent = 0);
	~General();

	// The central scroll area
	QScrollArea *centralScroll;

	// ComboBox for choosing language
	QComboBox *trans;

	// CheckBox for enabling composite
	QCheckBox *composite;

	// Slider for adjusting the menu sensitivity
	QSlider *menu;

	// Changing the thumbnail size
	QSlider *thumbSizeSlider;
	QSpinBox *thumbSizeSpin;

	// Disabling the thumbnail cache
	QCheckBox *thumbCache;

	// Holding the current version (set from mainwindow.cpp)
	QString version;

public slots:
	// Load ans save settings
	void loadSettings();
	void saveSettings();

};

#endif // TABGENERAL_H
