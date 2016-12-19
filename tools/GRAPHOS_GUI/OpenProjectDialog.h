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
#ifndef OPENPROJECTDIALOG_H
#define OPENPROJECTDIALOG_H

#include <QDialog>
#include <QItemSelectionModel>

#include "PersistenceManager.h"

namespace Ui {
    class OpenProjectDialog;
}

class OpenProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenProjectDialog(PW::PersistenceManager *pm, QWidget *parent = 0, bool forSave = false);
    ~OpenProjectDialog();

    void setNameVisible(bool);
    void setProjectName(QString projectName);
    void setForSave(bool forSave);
    void refreshData();

private slots:
    void on_buttonBox_accepted();
    void onSelectionChanged(QItemSelection selected,QItemSelection deselected);

    void on_pushButton_clicked();

    void on_tableView_doubleClicked(const QModelIndex &index);

signals:
    void projectSelected(QString projectName);

private:
    Ui::OpenProjectDialog *ui;
    PW::PersistenceManager *mPm;
    bool mForSave;
};

#endif // OPENPROJECTDIALOG_H
