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
#ifndef ABOUTCALIBRATIONS_DIALOG_H
#define ABOUTCALIBRATIONS_DIALOG_H

#include <QDialog>

namespace Ui {
class AboutCalibrations_Dialog;
}

class AboutCalibrations_Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutCalibrations_Dialog(QWidget *parent = 0);
    ~AboutCalibrations_Dialog();

private:
    Ui::AboutCalibrations_Dialog *ui;
};

#endif // ABOUTCALIBRATIONS_DIALOG_H
