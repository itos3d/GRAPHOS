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
#ifndef NEWCAMETADIALOG_H
#define NEWCAMETADIALOG_H

#include <QDialog>

#include "PersistenceManager.h"

namespace Ui {
    class NewCameraDialog;
}

class NewCameraDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewCameraDialog(PW::PersistenceManager *pm,QWidget *parent = 0);
    ~NewCameraDialog();
    bool isAcepted();
    void setData(QString cameraModel, QString lens);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::NewCameraDialog *ui;
    PW::PersistenceManager *mPm;
    QString mCameraModel;
    QString mLens;
    bool mAcepted;
};

#endif // NEWCAMETADIALOG_H
