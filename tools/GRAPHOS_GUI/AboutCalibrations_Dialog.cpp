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
#include "AboutCalibrations_Dialog.h"
#include "ui_AboutCalibrations_Dialog.h"
#include <QVBoxLayout>
#include <QTextEdit>
AboutCalibrations_Dialog::AboutCalibrations_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutCalibrations_Dialog)
{
    ui->setupUi(this);
    setWindowTitle("Camera calibration info");
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout();


    //CameraCalibratioModel tab
    QTextEdit *CameraCalibratioModelTextArea= new QTextEdit();
    CameraCalibratioModelTextArea->setReadOnly(true);
    CameraCalibratioModelTextArea->setText("<font size=\"4\"><br><strong>Basic calibration</strong> is simplificated radial calibration model limited to 5 degrees of freedom:"
                                      " 1 for focal length , 2 for principal point and distortion center and 2 for coefficients of "
                                      "radial distortion (r^3 and r^5)."
                                      "<br><strong>Complete calibration</strong> is a extended radial calibration model complemented with decentric and affine parameters. The model includes "
                                      "12 degrees of freedom: 1 for focal length , 2 for principal point, 2 for distortion center , 3 for "
                                      "coefficients of radial distorsion (r^3, r^5 and r^7), 2 for decentric parameters and 2 for affine parameters "
                                      "<br><strong>Generic calibration</strong> is an user-configurable distortion model. The model allows the release of the calibration parameters linked to the focal lenght, principal point deviation, distortion center, decentric and affine parameters.</font>");



    mainLayout->addWidget(CameraCalibratioModelTextArea);
    setLayout(mainLayout);
    setFixedSize(550,400);
}

AboutCalibrations_Dialog::~AboutCalibrations_Dialog()
{
    delete ui;
}
