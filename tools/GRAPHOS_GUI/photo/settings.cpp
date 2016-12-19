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
#include "settings.h"

Settings::Settings(QDialog *parent) : QDialog(parent) {

	// Set window title
	this->setWindowTitle(tr("Photo Settings"));

	// the main central layout
	QVBoxLayout *centralLayout = new QVBoxLayout;
	this->setLayout(centralLayout);

	// The tab widget (for "Shortcuts" and "General Settings" Tabs)
	tabs = new QTabWidget;
	centralLayout->addWidget(tabs);
	tabs->setTabPosition(QTabWidget::North);

	// Tab 1: Shortcuts
	shortcuts = new Shortcuts;
	tabs->addTab(shortcuts,tr("&Shortcuts"));

	// Tab 2 : General Settings
	general = new General;
	tabs->addTab(general,tr("&General Settings"));

	// The two buttons on the bottom of the setting window (always present)
	QPushButton *cancel = new QPushButton(tr("Cancel (Escape)"));
	cancel->setShortcut(QKeySequence("Escape"));
	QPushButton *save = new QPushButton(tr("Save and close (Ctrl+S)"));
	save->setShortcut(QKeySequence("Ctrl+S"));
	QHBoxLayout *buttBot = new QHBoxLayout;
	buttBot->addStretch();
	buttBot->addWidget(cancel);
	buttBot->addWidget(save);
	buttBot->addStretch();
	centralLayout->addLayout(buttBot);

	// Cancel and reverse changes
	connect(cancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(cancel, SIGNAL(clicked()), shortcuts, SLOT(loadShortcuts()));
	connect(cancel, SIGNAL(clicked()), general, SLOT(loadSettings()));

	// Save changes and close window
	connect(save, SIGNAL(clicked()), shortcuts, SLOT(saveData()));
	connect(save, SIGNAL(clicked()), general, SLOT(saveSettings()));
	connect(save, SIGNAL(clicked()), this, SLOT(close()));

}

// Focus the first tab on close
void Settings::closeEvent(QCloseEvent *) {
	tabs->setCurrentIndex(0);
}

Settings::~Settings() { }
