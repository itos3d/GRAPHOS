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
#ifndef TABSHORTCUTS_H
#define TABSHORTCUTS_H

#include <QWidget>
#include <QHBoxLayout>
#include <QTableView>

#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QCheckBox>
#include <QRadioButton>

#include <QStandardItem>

#include <QHeaderView>
#include <QLineEdit>
#include <QShortcut>
#include <QtDebug>
#include <QDir>
#include <QFile>
#include <QMessageBox>
#include <QApplication>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDesktopWidget>

/***************************************/
// This class provides a widget for detecting key combinations
class Key : public QDialog {

	Q_OBJECT
public:
	Key(QDialog *parent = 0);

	QLabel *det;
	QString key;

	// This integer is set to 1 at the end when the shortcut is already there and makes the widget reappear and refocus
	int everythingsokay;

public slots:
	// No update
	void quitNoKeys();

signals:
	// Send new key combinations
	void gotKeys(QString);

protected:
	void keyPressEvent(QKeyEvent *);
	void closeEvent(QCloseEvent *);
};

/***************************************/
// This class adds an adidtional function to the normal QTableView (needed for hover effect)
class Table : public QTableView {

	Q_OBJECT

protected:
	void mouseMoveEvent(QMouseEvent *);

signals:
	void hoverPos(QPoint);

};

/***************************************/
// This is the main class, responsible for the tab widget
class Shortcuts : public QWidget {

	Q_OBJECT

private:
	// The main layout
	QHBoxLayout *shview;

	// Some of the layout setup ismoved to their own functions (simplify code)
	void setupTableView();
	void setupWidget();

public:
	Shortcuts(QWidget *parent = 0);
	~Shortcuts();

	// The Shortcuts Table
	Table *thisview;
	// The key detection widget
	Key *key;
	// The shortcut editor window
	QWidget *editor;

	// The model used for the shortcuts table
	QStandardItemModel *model;

	// Holds the row currently hovered
	int hovRow;

	// The elements in the editor widget on the right
	QPushButton *shEdit;
	QComboBox *exeIntern;
	QLineEdit *exeExtern;
	QCheckBox *clEdit;
	QLabel *clEditLabel;
	QLabel *exeExternPlaceholder;
	QRadioButton *exeInternButton;
	QRadioButton *exeExternButton;

	// These are holding all the internal function, their short version and longer one (this one is displayed)
	QStringList allIntern;
	QStringList allInternRead;

	// The resizing function, called from resizeEvent() and also from the mainwindow once (that's why the code was moved out of the resizeEvent() function)
	void doresizing();

	// A string holding the current version (updated from the mainwindow.cpp)
	QString version;

	QList<bool> toClose;

public slots:
	// Add a new row for a new shortcut to the table
	void addNewShortcut();

	// Load all the existingshortcuts from file
	void loadShortcuts();

	// Set the focus on the last row
	void focusLastRow();

	// A new row is hovered (called from the subclass Table)
	void hoverRow(QPoint);

	// A selection of a new shortcut row (either by mouse or keyboard)
	void loadRow(QModelIndex, QModelIndex);

	// Either the internal or external command section is enabled/disabled
	void DisEnableCommands(int);

	// This function syncs the table with the editor widget
	void updateData();

	// Saving the changes to file
	void saveData();

	// Remove the currently selected shortcut
	void removeShortcut();

	// A click on the editor button for detecting a new shortcut
	void getNewKeys();

	// Called by subclass key with new key combination
	void gotNewKeys(QString);

	// Delete all current shortcuts and enter the default shortcuts set
	void restoreDefaultShortcuts();

signals:
	// The shortcuts have been changed need to be updated
	void updateShortcuts();

	// Tell the mainwindow to make sure to regain focus again
	void focusParentWindow();

protected:
	void resizeEvent(QResizeEvent *);
	void closeEvent(QCloseEvent *);


};

#endif // TABSHORTCUTS_H
