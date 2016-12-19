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
#include "NewCameraDialog.h"
#include "ui_NewCameraDialog.h"
#include "Camera.h"

using namespace PW;
NewCameraDialog::NewCameraDialog(PW::PersistenceManager *pm, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewCameraDialog),
    mPm(pm),
    mAcepted(false)
{
    ui->setupUi(this);
}

NewCameraDialog::~NewCameraDialog()
{
    delete ui;
}

void NewCameraDialog::on_buttonBox_accepted()
{
    mCameraModel = ui->ModelLineEdit->text();
    mLens = ui->LenslineEdit->text();
    double widht = ui->WidhtLineEdit->text().toDouble();
    double height = ui->WidhtLineEdit->text().toDouble();
    if (!mCameraModel.isEmpty() && widht && height){
        Camera camera(mCameraModel, mLens,ui->WidhtLineEdit->text().toDouble(), ui->HeightLineEdit->text().toDouble());
        mPm->writeCamera(&camera);
        mAcepted = true;
    }
    else
        mAcepted = false;
}

void NewCameraDialog::on_buttonBox_rejected()
{
    mAcepted = false;

}

bool NewCameraDialog::isAcepted()
{
    return mAcepted;
}

void NewCameraDialog::setData(QString cameraModel, QString lens)
{
    mCameraModel = cameraModel;
    mLens = lens;
    ui->ModelLineEdit->setText(cameraModel);
    ui->LenslineEdit->setText(lens);
    ui->WidhtLineEdit->setText("");
    ui->HeightLineEdit->setText("");
}
