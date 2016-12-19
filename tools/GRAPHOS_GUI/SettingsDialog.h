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
#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QSettings *settings, QWidget *parent = 0);
    ~SettingsDialog();

protected:
    virtual void 	showEvent ( QShowEvent * event );
    
private slots:
    void on_buttonBox_accepted();

    void on_pushButtonAperoPath_clicked();

    void on_pushButtonASIFTPath_clicked();


    void on_pushButtonPMVSPath_clicked();

    void on_pushButtonOpenCV_clicked();

    void on_pushButtonOpenMVG_clicked();

    void on_checkBoxKeepMatchesInMemory_clicked();

//    void on_checkBoxcleanProjectWhenClose_clicked();

    void on_comboBoxDefaultAccuracyToleranceForMatches_currentIndexChanged(const QString &arg1);

    void on_pushButtonSURE_clicked();

    void on_pushButtonTools_clicked();

    void on_checkBoxCleanProjectWhenClose_clicked();

private:
    Ui::SettingsDialog *ui;
    QSettings *mSettings;
};

#endif // SETTINGSDIALOG_H
