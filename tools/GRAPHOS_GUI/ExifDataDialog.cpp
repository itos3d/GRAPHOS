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
#include "ExifDataDialog.h"
#include "ui_ExifDataDialogdialog.h"

ExifDataDialog::ExifDataDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ExifDataDialog)
{
    ui->setupUi(this);
}

ExifDataDialog::~ExifDataDialog()
{
    delete ui;
}

QString ExifDataDialog::getCameraName()
{
    return ui->lineEditName->text();
}

void ExifDataDialog::setCameraName(QString name)
{
    ui->lineEditName->setText(name);
}

void ExifDataDialog::setFocal(QString focal)
{
    ui->lineEditFocal->setText(focal);
}

void ExifDataDialog::setScale35(QString scale)
{
    ui->lineEditScale->setText(scale);
}

QString ExifDataDialog::getFocal()
{
    return ui->lineEditFocal->text();
}

QString ExifDataDialog::getScale35()
{
    return ui->lineEditScale->text();
}

void ExifDataDialog::on_buttonBox_accepted()
{

}

void ExifDataDialog::on_buttonBox_rejected()
{
    ui->lineEditFocal->setText("");
    ui->lineEditName->setText("");
}
