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
#include "tabshortcuts.h"

Shortcuts::Shortcuts(QWidget *parent) : QWidget(parent) {

	// This variable holds the row number marked as "hovered"
	hovRow = -1;

	// The key-window for detecting key combinations
	key = new Key;

	// These two stringlists hold info about the internal functions
	allIntern << "__open";
	allInternRead << tr("Open new file");
	allIntern << "__next";
	allInternRead << tr("Next Image");
	allIntern << "__prev";
	allInternRead << tr("Previous Image");
	allIntern << "__zoomIn";
	allInternRead << tr("Zoom In");
	allIntern << "__zoomOut";
	allInternRead << tr("Zoom Out");
	allIntern << "__zoomReset";
	allInternRead << tr("Reset Zoom");
	allIntern << "__settings";
	allInternRead << tr("Show settings");
	allIntern << "__about";
	allInternRead << tr("About photo");
	allIntern << "__noThumb";
	allInternRead << tr("Hide/Show Thumbnails");
	allIntern << "__stopThb";
	allInternRead << tr("Interrupt Thumbnail creation");
	allIntern << "__reloadThb";
	allInternRead << tr("Reload Thumbnails");
	allIntern << "__close";
	allInternRead << tr("Quit photo");

	// The main layout of this tab
	shview = new QHBoxLayout;
	this->setLayout(shview);

	// Setup the tableview and model
	setupTableView();

	// Load all the existing shortcuts
	loadShortcuts();

	// Setup the editor area on the right
	setupWidget();

	// Select and load the first shortcut
	thisview->selectRow(0);
	loadRow(model->index(0,0),model->index(0,0));

	// A new key combination is passed on to the tab widget
	connect(key, SIGNAL(gotKeys(QString)), this, SLOT(gotNewKeys(QString)));

}

// Sets up the table with the shortcuts
void Shortcuts::setupTableView() {

	// The class "Table" is a subclass of QTableView providing an additional mousemoveevent function and a signal
	thisview = new Table;//	set->show();


	// We don't need the vertical headers
	thisview->verticalHeader()->hide();

	// The vertical header has plain informational purpose
	thisview->horizontalHeader()->setClickable(false);

	// Some styling optionseditor
	thisview->setShowGrid(false);
	thisview->setAlternatingRowColors(true);
	thisview->setStyleSheet("background: transparent");

	// Exactly one row can be selected at a time
	thisview->setSelectionMode(QTableView::SingleSelection);
	thisview->setSelectionBehavior(QTableView::SelectRows);

	// Editing is not possible
	thisview->setEditTriggers(QTableView::NoEditTriggers);

	// The mouse-tracking is needed for the hover effect
	thisview->setMouseTracking(true);

	// We make use of Qt's model/view system
	model = new QStandardItemModel;

	// The model has a total of 3 columns
	model->setColumnCount(3);

	thisview->setModel(model);

	// The tableview is packed in a VBoxLayout, cause we add two buttons below it for adding/removing shortcuts
	QVBoxLayout *tableLay = new QVBoxLayout;
	tableLay->addWidget(thisview);

	// This is the layout of the total tab, containing the table (and more)
	shview->addLayout(tableLay);

	// Two buttons below the table for adding/removing shortcuts
	QHBoxLayout *shButtons = new QHBoxLayout;
	QPushButton *add = new QPushButton(tr("Add Shortcut (Ctrl++)"));
	add->setShortcut(QKeySequence("Ctrl++"));
	QPushButton *rem = new QPushButton(tr("Remove Shortcut (Ctrl+-)"));
	rem->setShortcut(QKeySequence("Ctrl+-"));
	shButtons->addWidget(add);
	shButtons->addWidget(rem);
	shButtons->addStretch();
	tableLay->addLayout(shButtons);

	// Adding a row at the end and setting the focus into it
	connect(add, SIGNAL(clicked()), this, SLOT(addNewShortcut()));
	connect(add, SIGNAL(clicked()), this, SLOT(focusLastRow()));

	// Removing the currently selected row
	connect(rem, SIGNAL(clicked()), this, SLOT(removeShortcut()));

	// Mark the whole row when hovering an item
	connect(thisview, SIGNAL(hoverPos(QPoint)),this, SLOT(hoverRow(QPoint)));

	// Load a shortcut into editor window at the right on click
	connect(thisview->selectionModel(), SIGNAL(currentRowChanged(QModelIndex,QModelIndex)), this, SLOT(loadRow(QModelIndex,QModelIndex)));

}

// Setting up the editor widget at the right (for editing shortcuts)
void Shortcuts::setupWidget() {

	// Some layout stuff
	editor = new QWidget(this);
	editor->setFixedWidth(250);
	editor->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	shview->addWidget(editor);

	// A title on top of the widget
	QLabel *eT = new QLabel("<center><h1>" + tr("Edit Shortcut") + "</h1></center>");
	eT->setWordWrap(true);
	QVBoxLayout *eLay = new QVBoxLayout;
	eLay->addWidget(eT);
	eLay->addSpacing(20);

	// The button for the shortcut button (and label)
	QLabel *shEditLabel = new QLabel("<b>" + tr("Click to change shortcut: (Ctrl+B)") + "</b>");
	shEditLabel->setWordWrap(true);
	eLay->addWidget(shEditLabel);
	shEdit = new QPushButton;
	shEdit->setFixedWidth(editor->width()/2.0);
	QHBoxLayout *sheditLay = new QHBoxLayout;
	sheditLay->addStretch();
	sheditLay->addWidget(shEdit);
	sheditLay->addStretch();
	eLay->addLayout(sheditLay);
	eLay->addSpacing(20);

	// The command can be either internal or external
	QLabel *exeEditLabel = new QLabel("<b>" + tr("Current command:") + "</b>");
	exeEditLabel->setWordWrap(true);
	exeInternButton = new QRadioButton(tr("&Internal commands"));
	exeInternButton->setChecked(true);
	exeIntern = new QComboBox;
	exeExternButton = new QRadioButton(tr("&External command"));
	exeExtern = new QLineEdit;
	eLay->addWidget(exeEditLabel);
	eLay->addSpacing(5);
	eLay->addWidget(exeInternButton);
	eLay->addWidget(exeIntern);
	eLay->addSpacing(5);
	eLay->addWidget(exeExternButton);
	eLay->addWidget(exeExtern);
	eLay->addSpacing(10);

	// A short text informing about the two possible placeholders
	exeExternPlaceholder = new QLabel(tr("You can use the following placeholders for external commands:<br>%f = current file<br>%d = current directory"));
	exeExternPlaceholder->setWordWrap(true);
	eLay->addWidget(exeExternPlaceholder);
	eLay->addSpacing(20);

	// Inserting all internal commans into the combobox
	for(int i = 0; i < allIntern.length(); ++i)
		exeIntern->addItem(allInternRead.at(i),allIntern.at(i));

	// Checkbox, quitting photo after executing above command (only at external commands)
	clEdit = new QCheckBox(tr("&Quit after executing command?"));
	eLay->addWidget(clEdit);
	eLay->addStretch();

	// A button that replaces the current set of shortcuts with a default one
	QPushButton *restoreDefault = new QPushButton(tr("Restore default shortcuts (Ctrl+R)"));
	restoreDefault->setShortcut(QKeySequence("Ctrl+R"));
	QHBoxLayout *restoreLay = new QHBoxLayout;
	restoreLay->addStretch();
	restoreLay->addWidget(restoreDefault);
	eLay->addLayout(restoreLay);

	// Set this layout to the editor widget
	editor->setLayout(eLay);

	// The radio buttons en-/disable each other's lineedit
	connect(exeInternButton, SIGNAL(toggled(bool)), exeIntern, SLOT(setEnabled(bool)));
	connect(exeExternButton, SIGNAL(toggled(bool)), exeExtern, SLOT(setEnabled(bool)));
	connect(exeExternButton, SIGNAL(toggled(bool)), clEdit, SLOT(setEnabled(bool)));
	connect(exeExternButton, SIGNAL(toggled(bool)), exeExternPlaceholder, SLOT(setEnabled(bool)));

	// A click on the button with the shortcut opens a small widget for detecting a new key combination
	connect(shEdit, SIGNAL(clicked()), this, SLOT(getNewKeys()));
	QShortcut *edSh = new QShortcut(QKeySequence("Ctrl+B"),editor);
	connect(edSh, SIGNAL(activated()), this, SLOT(getNewKeys()));

	// The table is kept in sync with changes in the editor widget
	connect(exeIntern, SIGNAL(activated(int)), this, SLOT(updateData()));
	connect(exeInternButton, SIGNAL(clicked()),this, SLOT(updateData()));
	connect(exeExtern, SIGNAL(textEdited(QString)), this, SLOT(updateData()));
	connect(exeExternButton, SIGNAL(clicked()), this, SLOT(updateData()));
	connect(clEdit, SIGNAL(clicked()), this, SLOT(updateData()));

	// Restoring the default shortcut set
	connect(restoreDefault, SIGNAL(clicked()), this, SLOT(restoreDefaultShortcuts()));

}

// Loading all the current shortcuts (from file)
void Shortcuts::loadShortcuts() {

	toClose.clear();

    qDebug() << "Setup: Loading all shortcuts";

	QFile file(QDir::homePath() + "/.photo/shortcuts");

	if(file.open(QIODevice::ReadOnly)) {

		// Clear the model and set column count to 3 again (needed for reloading the shortcuts)
		model->clear();
		model->setColumnCount(3);

		// Go through the file line by line
		QTextStream in(&file);
		QStringList sh = in.readAll().split("\n");

		// The integer j counts the actual shortcuts (the int i is counting the lines -> not reliable)
		int j = 0;
		for(int i = 0; i < sh.length(); ++i) {

			// If the line is a valid shortcut
			if(sh.at(i).trimmed() != "" && sh.at(i).contains("::")) {

				// 3 strings: close, shortcut, command
				QString c = sh.at(i).split("::").at(0);
				if(c.toInt()) {
					c = tr("Quit");
					toClose.append(true);
				} else {
					c = tr("Don't quit");
					toClose.append(false);
				}

				QString shortcut = sh.at(i).split("::").at(1);

				// In the table, all internal function get a "::" prepended to make is easily visible that they are internal functions
				QString todo = "";
				int readable = allIntern.indexOf(sh.at(i).split("::").at(2));
				if(readable != -1 && readable < allInternRead.length())
					todo = ":: " + allInternRead.at(readable);
				else
					todo = sh.at(i).split("::").at(2);

				// Add a new row to the table
				addNewShortcut();

				// Set up the items
				QStandardItem *one = new QStandardItem(shortcut);
				one->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
				QStandardItem *two = new QStandardItem(todo);
				QStandardItem *three = new QStandardItem(c);
				three->setData(Qt::AlignCenter, Qt::TextAlignmentRole);

				// The "and close" option doesn't apply for internal functions
				if(todo.startsWith("::")) {
					three->setEnabled(false);
					three->setText("N/A");
				}

				// Set items to table
				model->setItem(model->rowCount()-1,0,one);
				model->setItem(model->rowCount()-1,1,two);
				model->setItem(model->rowCount()-1,2,three);

				++j;

			}

		}

	// File couldn't be read
	} else
		qDebug() << "Couldn't read existing shortcuts...";

}

// When the widget is resized, the column width needs to be adjusted
void Shortcuts::resizeEvent(QResizeEvent *) {

	// The resize code ismoved to a normal function, cause it is also called at other places programmatically
	doresizing();

}

// The actualy column resizing
void Shortcuts::doresizing() {

	thisview->setColumnWidth(0,thisview->width()*0.15);
	thisview->setColumnWidth(1,thisview->width()*0.65);
	thisview->setColumnWidth(2,thisview->width()*0.01);
	thisview->horizontalHeader()->setStretchLastSection(true);

	// The width is fixed
	thisview->horizontalHeader()->setResizeMode(0,QHeaderView::Fixed);
	thisview->horizontalHeader()->setResizeMode(1,QHeaderView::Fixed);
	thisview->horizontalHeader()->setResizeMode(2,QHeaderView::Fixed);

	// Set the text on the header items
	model->setHeaderData(0, Qt::Horizontal, tr("Shortcut"), Qt::DisplayRole);
	model->setHeaderData(1, Qt::Horizontal, tr("Execute"), Qt::DisplayRole);
	model->setHeaderData(2, Qt::Horizontal, tr("Quit?"), Qt::DisplayRole);

}

// Add a new row to the table
void Shortcuts::addNewShortcut() {

	model->setRowCount(model->rowCount()+1);

	QStandardItem *one = new QStandardItem(tr("[Detect]"));
	one->setData(Qt::AlignCenter, Qt::TextAlignmentRole);
	QStandardItem *two = new QStandardItem(tr("[Execute]"));
	QStandardItem *three = new QStandardItem(tr("Don't quit"));
	three->setData(Qt::AlignCenter, Qt::TextAlignmentRole);

	model->setItem(model->rowCount()-1,0,one);
	model->setItem(model->rowCount()-1,1,two);
	model->setItem(model->rowCount()-1,2,three);

}

// Set the focus to the last row and ensure it's visible
void Shortcuts::focusLastRow() {

	if(model->rowCount() > 0) {
		thisview->selectionModel()->clearSelection();
		thisview->selectionModel()->select(model->index(model->rowCount()-1,0), QItemSelectionModel::Select);
		thisview->selectionModel()->select(model->index(model->rowCount()-1,1), QItemSelectionModel::Select);
		thisview->selectionModel()->select(model->index(model->rowCount()-1,2), QItemSelectionModel::Select);
		loadRow(model->index(model->rowCount()-1,0),model->index(model->rowCount()-1,0));
		thisview->scrollToBottom();
	}

}

// A hover effect
void Shortcuts::hoverRow(QPoint p) {

	// A brush with background color
	QBrush b(Qt::SolidPattern);
	b.setColor(qRgba(85, 181, 235,200));

	int row = thisview->indexAt(p).row();

	// Reset the previous hovered row
	if(hovRow != -1) {
		model->item(hovRow,0)->setBackground(QBrush());
		model->item(hovRow,1)->setBackground(QBrush());
		model->item(hovRow,2)->setBackground(QBrush());
	}
	// Mark the currently hovered row
	if(row != -1) {
		model->item(row,0)->setBackground(b);
		model->item(row,1)->setBackground(b);
		model->item(row,2)->setBackground(b);
	}

	hovRow = row;

}

// Load a new row
void Shortcuts::loadRow(QModelIndex index,QModelIndex) {

	if(index.row() != -1) {

		// Get the current shortcut
		shEdit->setText(model->item(index.row(),0)->text());

		// Get the execute command
		QString todocommand = model->item(index.row(),1)->text().remove(0,3);
		if(allInternRead.indexOf(todocommand) == -1) {
			exeExternButton->setChecked(true);
			exeIntern->setCurrentIndex(0);
			exeExtern->setText(model->item(index.row(),1)->text());
		} else {
			exeIntern->setCurrentIndex(allInternRead.indexOf(todocommand));
			exeExtern->setText("");
			exeInternButton->setChecked(true);
		}

		// Get the "and quit" status
		clEdit->setChecked(toClose.at(index.row()));

		// Set the checkboxes/lineedits/... depending on internal or external function
		DisEnableCommands(index.row());

	}

}

// Update elements depending on internal/external function
void Shortcuts::DisEnableCommands(int row) {

	if(exeInternButton->isChecked()) {
		exeIntern->setEnabled(true);
		exeExtern->setEnabled(false);
		clEdit->setEnabled(false);
		exeExternPlaceholder->setEnabled(false);
		if(row > -1)
			model->item(row,2)->setEnabled(false);
	} else {
		exeIntern->setEnabled(false);
		exeExtern->setEnabled(true);
		clEdit->setEnabled(true);
		exeExternPlaceholder->setEnabled(true);
		if(row > -1)
			model->item(row,2)->setEnabled(true);
	}


}

// Syncs the editor data with the table data
void Shortcuts::updateData() {

	// Get the currently selected (and thus loaded) row
	int row = thisview->selectionModel()->selectedIndexes().at(0).row();

	// Set the (possibly new) shortcut
	model->item(row,0)->setText(shEdit->text());

	// Set the command and quit status
	if(exeInternButton->isChecked()) {
		model->item(row,1)->setText(":: " + exeIntern->currentText());
		model->item(row,2)->setText("N/A");
		model->item(row,2)->setEnabled(false);
	} else {
		model->item(row,1)->setText(exeExtern->text());
		model->item(row,2)->setEnabled(true);
		if(clEdit->isChecked()) {
			model->item(row,2)->setText(tr("Quit"));
			toClose.replace(row,true);
		} else {
			model->item(row,2)->setText(tr("Don't quit"));
			toClose.replace(row,false);
		}
	}

}

// Save shortcuts to file
void Shortcuts::saveData() {

	QString conf = "Version=" + version + "\n";

	for(int i = 0; i < model->rowCount(); ++i) {

		// Get the "and close" status
		QString close = "0";
		if(!model->item(i,2)->text().contains(" "))
			close = "1";

		// Get the execute command
		QString exe = model->item(i,1)->text();
		if(exe.startsWith("::")) {
			close = "0";
			exe = exe.remove(0,3);
			int index = allInternRead.indexOf(exe);
			if(index != -1 && index < allIntern.length())
				exe = allIntern.at(index);
			else
				exe = "?";
		}

		// Add data to file content string
		conf += close + "::" + model->item(i,0)->text() + "::" + exe + "\n";


	}

	// Create and write config file for shortcuts
	QFile file(QDir::homePath() + "/.photo/shortcuts");
	file.remove();
	if(file.open(QIODevice::ReadWrite)) {
		qDebug() << "Saving shortcuts";
		QTextStream out(&file);
		out << conf;
		file.close();
	} else
		qDebug() << "Couldn't save shortcuts";

	emit updateShortcuts();

}

// Remove the currently selected shortcut
void Shortcuts::removeShortcut() {

	// Ask for confirmation
	int msg = QMessageBox::information(this,tr("Delete Shortcut?"),tr("Do you really want to delete this shortcut? This step cannot be reversed."),QMessageBox::Yes | QMessageBox::Default, QMessageBox::No);

	if(msg == QMessageBox::Yes) {

		// Remove row and (if none selected) select the last row
		int row = thisview->selectionModel()->selectedIndexes().at(0).row();
		model->removeRow(row);
		if(thisview->selectionModel()->selectedIndexes().length() == 0) {
			thisview->selectRow(model->rowCount()-1);
		}

	}

}

// Open the "key" widget for detecting a new key combination
void Shortcuts::getNewKeys() {

	qDebug() << "Setup: Detecting new shortcut";

	key->det->setText(tr("Press Keys"));
	this->setEnabled(false);
	key->det->setFocus();

	QRect r = key->frameGeometry();
	r.moveCenter(QApplication::desktop()->availableGeometry().center());
	key->move(r.topLeft());

	key->exec();

}

// Handling the key combination submitted by "key" widget
void Shortcuts::gotNewKeys(QString k) {

	this->activateWindow();

	if(k == "") {

		qDebug() << "No new key combination detected.";
		this->setEnabled(true);

	} else {

		// Check if shortcut is either new or unchanged
		int there = 0;
		for(int i = 0; i < model->rowCount(); ++i) {
			if(model->item(i,0)->text() == k.trimmed() && i != thisview->selectionModel()->selectedIndexes().at(0).row())
				there = 1;
		}

		if(there == 1) {
			QMessageBox::critical(0,tr("Shortcut exists already"),QString(tr("Sorry, the shortcut '%1' is already occupied. Please choose another one.")).arg(k));
			key->everythingsokay = 0;
		} else {
			qDebug() << "Got new key combination";
			this->setEnabled(true);
			shEdit->setText(k);
			model->item(thisview->selectionModel()->selectedIndexes().at(0).row(),0)->setText(k);
		}

	}

}

// Deletes all current shortcuts and enters the default shortcut set
void Shortcuts::restoreDefaultShortcuts() {

	int msg = QMessageBox::warning(0,tr("Restore default shortcuts"),tr("<b>Warning!</b><br><br>This step <b>deletes</b> all you existing shortcuts and replaces them with the default set of shortcuts! This step cannot be reversed! Continue?"),QMessageBox::Yes | QMessageBox::Default, QMessageBox::No);

	if(msg == QMessageBox::Yes) {

		QFile file(QDir::homePath() + "/.photo/shortcuts");
		if(!file.open(QIODevice::ReadWrite))
			QMessageBox::critical(0,tr("Couldn't open file"),tr("<b>ERROR!</b><br>I wasn't able to open the file that stores your shortcuts. Please ensure, that you have both <b>read and write access</b> to your home directory!"));
		else {
			file.close();
			file.remove();
			file.open(QIODevice::ReadWrite);
			QTextStream out(&file);
			QString defShortcuts = "";
			defShortcuts += "Version=" + version + "\n";
			defShortcuts += "0::O::__open\n";
			defShortcuts += "0::Right::__next\n";
			defShortcuts += "0::Left::__prev\n";
			defShortcuts += "0::+::__zoomIn\n";
			defShortcuts += "0::-::__zoomOut\n";
			defShortcuts += "0::0::__zoomReset\n";
			defShortcuts += "0::E::__settings\n";
			defShortcuts += "0::I::__about\n";
			defShortcuts += "0::H::__noThumb\n";
			defShortcuts += "0::S::__stopThb\n";
			defShortcuts += "0::R::__reloadThb\n";
			defShortcuts += "0::Escape::__close\n";
			defShortcuts += "0::Q::__close";
			out << defShortcuts;
			file.close();
		}

		// Reload table list
		loadShortcuts();
		doresizing();
		thisview->selectRow(0);

	}

}

// When settings window is closed, ensure, that the mainwindow is focussed again
void Shortcuts::closeEvent(QCloseEvent *) {
	emit focusParentWindow();
}

Shortcuts::~Shortcuts() {
}




/****************************************
  #######################################
  #######################################

  THIS CLASS ADDS ADDITIONAL FUNCTIONALITY
	    TO THE QTABLEVIEW

  #######################################
  #######################################
  ***************************************/

// Function to recognise and handle the row hover effect
void Table::mouseMoveEvent(QMouseEvent *e) {
	emit hoverPos(e->pos());
}




/****************************************
  #######################################
  #######################################

    THIS CLASS PROVIDES A WIDGET THAT IS
     ABLE TO RECONIZE KEY COMBINATIONS

  #######################################
  #######################################
  ***************************************/

Key::Key(QDialog *parent) : QDialog(parent) {

	// Set window title
	this->setWindowTitle(tr("Detect Keys"));

	// The appearence of the widget
	QVBoxLayout *layout = new QVBoxLayout;
	this->setLayout(layout);
	this->setFixedWidth(150);
	this->setFixedHeight(80);
	this->setWindowFlags(this->windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);

	// If a key combo already exists, then this variable ensures, that the "key" widget is re-focussed
	everythingsokay = 1;

	// The detection label showing the detected keys
	det = new QLabel(tr("Press Keys"));
	det->setAlignment(Qt::AlignCenter);
	layout->addWidget(det);

	// The Label needs to be focussed (not the button), otherwise some keys couldn't be detected (like arrows, space, ...)
	det->setFocus();

	// A click on here cancels the operation
	QPushButton *cancel = new QPushButton(tr("Cancel"));
	layout->addWidget(cancel);
	connect(cancel, SIGNAL(clicked()), this, SLOT(quitNoKeys()));

}

// Re-Enable the layout of the settings window and close
void Key::quitNoKeys() {

	qDebug() << "Exiting without new key combination";

	emit gotKeys("");
	this->close();
}

// A pressed key
void Key::keyPressEvent(QKeyEvent *e) {

	qDebug() << "Setup: Got Key Combination";

	// Get the modifier key (if there is one)
	QString key = "";
	switch(e->modifiers()) {
	case (Qt::ShiftModifier):
		key += tr("Shift");
		break;
	case(Qt::ControlModifier):
		key += tr("Ctrl");
		break;
	case(Qt::AltModifier):
		key += tr("Alt");
		break;
	}

	// If a modifier is pressed, add a "+"
	if(key != "")
		key += "+";

	// Get the second key pressed
	if(e->key() == Qt::Key_Escape)
		key += tr("Escape");
	else if(e->key() == Qt::Key_Right)
		key += tr("Right");
	else if(e->key() == Qt::Key_Left)
		key += tr("Left");
	else if(e->key() == Qt::Key_Up)
		key += tr("Up");
	else if(e->key() == Qt::Key_Down)
		key += tr("Down");
	else if(e->key() == Qt::Key_Space)
		key += tr("Space");
	else if(e->key() != 16777251 && e->key() != 16777248 && e->key() != 16777249)
		key += e->key();

	// If for some reason an empty string is passed on, show a quotation mark (should never happen)
	if(key == "")
		key = "?";

	// Set key combo
	det->setText(key);

	// If just a normal key or a modifier+normal key is pressed: emit key combo and exit
	if(e->key() != 16777251 && e->key() != 16777248 && e->key() != 16777249) {

		// Emit Key Combo
		emit gotKeys(key);

		// Exit if key combo didn't exist (checked in main program above)
		if(everythingsokay)
			this->close();
		else {
			everythingsokay = 1;
			this->activateWindow();
			det->setFocus();
			det->setText(tr("Press Keys"));
		}
	}

}

// When the widget is closed manually, we need to re-enable the seetings window layout
void Key::closeEvent(QCloseEvent *e) {
	emit gotKeys("");
	e->accept();
}

