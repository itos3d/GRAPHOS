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
#include <QFileDialog>
#include <QShowEvent>
#include <QMessageBox>

#include "SettingsDialog.h"
#include "ui_SettingsDialog.h"
#include "libPW.h"

SettingsDialog::SettingsDialog(QSettings *settings,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog),
    mSettings(settings)
{
    ui->setupUi(this);

    ui->lineEditAperoPath->setText(mSettings->value("micmac/binaries").toString());
    ui->lineEditASIFTPath->setText(mSettings->value("asift/binaries").toString());
    ui->lineEditPMVSPath->setText(mSettings->value("pmvs/binaries").toString());
    ui->lineEditOpenCV->setText(mSettings->value("openCV/binaries").toString());
    ui->lineEditOpenMVG->setText(mSettings->value("openMVG/binaries").toString());
    ui->lineEditSURE->setText(mSettings->value("sure/binaries").toString());
    ui->lineEditTools->setText(mSettings->value("tools/binaries").toString());

    if(!mSettings->value("app/cleanProjectAtClossingEvent").toString().isEmpty())
    {
        ui->checkBoxCleanProjectWhenClose->setChecked(mSettings->value("app/cleanProjectAtClossingEvent").toBool());
    }
    else
    {
        ui->checkBoxCleanProjectWhenClose->setChecked(PW::LibPW::getCleanProjectAtClossingEvent());
    }

    if(!mSettings->value("app/KeepMatchesInMemory").toString().isEmpty())
    {
        ui->checkBoxKeepMatchesInMemory->setChecked(mSettings->value("app/KeepMatchesInMemory").toBool());
    }
    else
    {
        ui->checkBoxKeepMatchesInMemory->setChecked(PW::LibPW::getKeepMatchesInMemory());
    }


    if(!mSettings->value("app/DefaultAccuracyToleranceForMatches").toString().isEmpty())
    {
        int pos=ui->comboBoxDefaultAccuracyToleranceForMatches->findText(mSettings->value("app/DefaultAccuracyToleranceForMatches").toString());
        if(pos==-1)
            pos=0;
        ui->comboBoxDefaultAccuracyToleranceForMatches->setCurrentIndex(pos);
    }
    else
    {
        QString value=QString::number(PW::LibPW::getDefaultAccuracyToleranceForMatches(),'f',1);
        int pos=ui->comboBoxDefaultAccuracyToleranceForMatches->findText(value);
        if(pos==-1)
            pos=0;
        ui->comboBoxDefaultAccuracyToleranceForMatches->setCurrentIndex(pos);
    }

    setModal(true);

    //Hide non used configuration GRAPHOS
    ui->frame_2->hide();
    ui->frame_4->hide();
    ui->frame_5->hide();
    ui->checkBoxKeepMatchesInMemory->hide();
    ui->frame_7->hide();
    ui->checkBox->hide();
    this->setFixedHeight(250);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::showEvent(QShowEvent *event)
{
    ui->lineEditAperoPath->setText(mSettings->value("micmac/binaries").toString());
    ui->lineEditASIFTPath->setText(mSettings->value("asift/binaries").toString());
    ui->lineEditPMVSPath->setText(mSettings->value("pmvs/binaries").toString());
    ui->lineEditOpenCV->setText(mSettings->value("openCV/binaries").toString());
    ui->lineEditOpenMVG->setText(mSettings->value("openMVG/binaries").toString());
    ui->lineEditSURE->setText(mSettings->value("sure/binaries").toString());
    ui->lineEditTools->setText(mSettings->value("tools/binaries").toString());
    ui->checkBoxCleanProjectWhenClose->setChecked(mSettings->value("app/cleanProjectAtClossingEvent").toBool());


    if(!mSettings->value("app/DefaultAccuracyToleranceForMatches").toString().isEmpty())
    {
        int pos=ui->comboBoxDefaultAccuracyToleranceForMatches->findText(mSettings->value("app/DefaultAccuracyToleranceForMatches").toString());
        if(pos==-1)
            pos=0;
        ui->comboBoxDefaultAccuracyToleranceForMatches->setCurrentIndex(pos);
    }
    else
    {
        QString value=QString::number(PW::LibPW::getDefaultAccuracyToleranceForMatches(),'f',1);
        int pos=ui->comboBoxDefaultAccuracyToleranceForMatches->findText(value);
        if(pos==-1)
            pos=0;
        ui->comboBoxDefaultAccuracyToleranceForMatches->setCurrentIndex(pos);
    }

    if(!mSettings->value("app/drawOutlierMatches").toString().isEmpty())
    {
        if (mSettings->value("app/drawOutlierMatches").toInt()==0)
            ui->checkBoxDrawOutliers->setChecked(false);
        else
            ui->checkBoxDrawOutliers->setChecked(true);
    }
    else{
        ui->checkBoxDrawOutliers->setChecked(false);
        mSettings->setValue("app/drawOutlierMatches",0);
    }

    event->accept();
}

void SettingsDialog::on_buttonBox_accepted()
{
    QString aperoPath = ui->lineEditAperoPath->text();
    QString asiftPath = ui->lineEditASIFTPath->text();
    QString pmvsPath = ui->lineEditPMVSPath->text();
    QString opencvPath = ui->lineEditOpenCV->text();
    QString openmvgPath = ui->lineEditOpenMVG->text();
    QString surePath = ui->lineEditSURE->text();
    QString toolsPath = ui->lineEditTools->text();

    if (!aperoPath.isEmpty()){
        while(aperoPath.at(aperoPath.length()-1) == '/')
            aperoPath = aperoPath.left(aperoPath.length()-1);
    }

    if (!asiftPath.isEmpty()){
        while(asiftPath.at(asiftPath.length()-1) == '/')
            asiftPath = asiftPath.left(asiftPath.length()-1);
    }

    if (!pmvsPath.isEmpty()){
        while(pmvsPath.at(pmvsPath.length()-1) == '/')
            pmvsPath = pmvsPath.left(pmvsPath.length()-1);
    }

    if (!opencvPath.isEmpty()){
        while(opencvPath.at(opencvPath.length()-1) == '/')
            opencvPath = opencvPath.left(opencvPath.length()-1);
    }

    if (!openmvgPath.isEmpty()){
        while(openmvgPath.at(openmvgPath.length()-1) == '/')
            openmvgPath = openmvgPath.left(openmvgPath.length()-1);
    }

    ui->lineEditASIFTPath->setText(asiftPath);
    ui->lineEditAperoPath->setText(aperoPath);
    ui->lineEditPMVSPath->setText(pmvsPath);
    ui->lineEditOpenCV->setText(opencvPath);
    ui->lineEditOpenMVG->setText(openmvgPath);

    if(PW::LibPW::validateAperoPath(aperoPath)){
        ui->lineEditAperoPath->setText(aperoPath);
        mSettings->setValue("micmac/binaries", aperoPath);
        PW::LibPW::setMicMacBinPath(mSettings->value("micmac/binaries").toString());
    }
    else
        QMessageBox::warning(this, tr("Photogrammetry Workbench"),
                         tr("Apero/MICMAC binaries path is not valid"));

//    if(PW::LibPW::validateAsiftPath(asiftPath)){
//        mSettings->setValue("asift/binaries", asiftPath);
//        PW::LibPW::setAsiftBinPath(mSettings->value("asift/binaries").toString());
//    }
//    else if (!asiftPath.isEmpty())
//        QMessageBox::warning(this, tr("Photogrammetry Workbench"),
//                             tr("ASFIT binaries path is not valid"));

    if(PW::LibPW::validatePMVSPath(pmvsPath)){
        mSettings->setValue("pmvs/binaries", pmvsPath);
        PW::LibPW::setPMVSBinPath(mSettings->value("pmvs/binaries").toString());
    }
    else if (!pmvsPath.isEmpty())
        QMessageBox::warning(this, tr("Photogrammetry Workbench"),
                             tr("PMVS binaries path is not valid"));

//    if(PW::LibPW::validateOpenCVPath(opencvPath)){
//        mSettings->setValue("OpenCV/binaries", opencvPath);
//        PW::LibPW::setOpenCVBinPath(mSettings->value("OpenCV/binaries").toString());
//    }
//    else if (!opencvPath.isEmpty())
//        QMessageBox::warning(this, tr("Photogrammetry Workbench"),
//                             tr("OpenCV binaries path is not valid"));

//    if(PW::LibPW::validateOpenMVGPath(openmvgPath)){
//        mSettings->setValue("OpenMVG/binaries", openmvgPath);
//        PW::LibPW::setOpenMVGBinPath(mSettings->value("OpenMVG/binaries").toString());
//    }
//    else if (!openmvgPath.isEmpty())
//        QMessageBox::warning(this, tr("Photogrammetry Workbench"),
//                             tr("OpenMVG binaries path is not valid"));

    if(PW::LibPW::validateSUREPath(surePath)){
        mSettings->setValue("sure/binaries", surePath);
        PW::LibPW::setSUREBinPath(mSettings->value("sure/binaries").toString());
    }
    else if (!surePath.isEmpty())
        QMessageBox::warning(this, tr("Photogrammetry Workbench"),
                             tr("SURE binaries path is not valid"));

    if(PW::LibPW::validateToolsPath(toolsPath)){
        mSettings->setValue("tools/binaries", toolsPath);
        PW::LibPW::setToolsPath(mSettings->value("tools/binaries").toString());
    }
    else if (!toolsPath.isEmpty())
        QMessageBox::warning(this, tr("Photogrammetry Workbench"),
                             tr("Tools binaries path is not valid"));

    if(ui->checkBoxKeepMatchesInMemory->isChecked())
    {
        mSettings->setValue("app/KeepMatchesInMemory","1");
        PW::LibPW::setKeepMatchesInMemory(true);
    }
    else
    {
        mSettings->setValue("app/KeepMatchesInMemory","0");
        PW::LibPW::setKeepMatchesInMemory(false);
    }

    if(ui->checkBoxCleanProjectWhenClose->isChecked())
    {
        mSettings->setValue("app/cleanProjectAtClossingEvent","1");
        PW::LibPW::setCleanProjectAtClossingEvent(true);
    }
    else
    {
        mSettings->setValue("app/cleanProjectAtClossingEvent","0");
        PW::LibPW::setCleanProjectAtClossingEvent(false);
    }

    PW::LibPW::setDefaultAccuracyToleranceForMatches(ui->comboBoxDefaultAccuracyToleranceForMatches->currentText().toFloat());
    mSettings->setValue("app/DefaultAccuracyToleranceForMatches",ui->comboBoxDefaultAccuracyToleranceForMatches->currentText());

    if(ui->checkBoxDrawOutliers->isChecked())
        mSettings->setValue("app/drawOutlierMatches",1);
    else
        mSettings->setValue("app/drawOutlierMatches",0);
}

void SettingsDialog::on_pushButtonAperoPath_clicked()
{
    QString initPath = mSettings->value("app/lastsettingspath").toString();
    if (initPath.isEmpty())
        initPath = QString("home");

    QString fileName = QFileDialog::getExistingDirectory(this,
                                    tr("Apero/MICMAC binaries path"), initPath);
    ui->lineEditAperoPath->setText(fileName);
    mSettings->setValue("app/lastsettingspath", fileName);
}

void SettingsDialog::on_pushButtonASIFTPath_clicked()
{
    QString initPath = mSettings->value("app/lastsettingspath").toString();
    if (initPath.isEmpty())
        initPath = QString("home");

    QString fileName = QFileDialog::getExistingDirectory(this,
                                    tr("ASIFT binaries path"), initPath);
    ui->lineEditASIFTPath->setText(fileName);
    mSettings->setValue("app/lastsettingspath", fileName);
}

void SettingsDialog::on_pushButtonPMVSPath_clicked()
{
    QString initPath = mSettings->value("app/lastsettingspath").toString();
    if (initPath.isEmpty())
        initPath = QString("home");

    QString fileName = QFileDialog::getExistingDirectory(this,
                                    tr("PMVS binaries path"), initPath);
    ui->lineEditPMVSPath->setText(fileName);
    mSettings->setValue("app/lastsettingspath", fileName);
}

void SettingsDialog::on_pushButtonOpenCV_clicked()
{
    QString initPath = mSettings->value("app/lastsettingspath").toString();
    if (initPath.isEmpty())
        initPath = QString("home");

    QString fileName = QFileDialog::getExistingDirectory(this,
                                    tr("OpenCV binaries path"), initPath);
    ui->lineEditOpenCV->setText(fileName);
    mSettings->setValue("app/lastsettingspath", fileName);
}

void SettingsDialog::on_pushButtonOpenMVG_clicked()
{
    QString initPath = mSettings->value("app/lastsettingspath").toString();
    if (initPath.isEmpty())
        initPath = QString("home");

    QString fileName = QFileDialog::getExistingDirectory(this,
                                    tr("OpenMVG binaries path"), initPath);
    ui->lineEditOpenMVG->setText(fileName);
    mSettings->setValue("app/lastsettingspath", fileName);
}

//void SettingsDialog::on_checkBoxcleanProjectWhenClose_clicked()
//{
//    QString cleanProjectWhenClose="1";
//    if(!ui->checkBoxCleanProjectWhenClose->isChecked())
//        cleanProjectWhenClose="0";
//    mSettings->setValue("app/cleanProjectAtClossingEvent", cleanProjectWhenClose);
//}

void SettingsDialog::on_checkBoxKeepMatchesInMemory_clicked()
{
    QString keepMatchesInMemory="1";
    if(!ui->checkBoxKeepMatchesInMemory->isChecked())
        keepMatchesInMemory="0";
    mSettings->setValue("app/KeepMatchesInMemory", keepMatchesInMemory);
}

void SettingsDialog::on_comboBoxDefaultAccuracyToleranceForMatches_currentIndexChanged(const QString &arg1)
{
    QString strAccuracy=ui->comboBoxDefaultAccuracyToleranceForMatches->currentText();
    mSettings->setValue("app/DefaultAccuracyToleranceForMatches", strAccuracy);
}

void SettingsDialog::on_pushButtonSURE_clicked()
{
    QString initPath = mSettings->value("app/lastsettingspath").toString();
    if (initPath.isEmpty())
        initPath = QString("home");

    QString fileName = QFileDialog::getExistingDirectory(this,
                                    tr("SURE binaries path"), initPath);
    ui->lineEditSURE->setText(fileName);
    mSettings->setValue("app/lastsettingspath", fileName);
}

void SettingsDialog::on_pushButtonTools_clicked()
{
    QString initPath = mSettings->value("app/lastsettingspath").toString();
    if (initPath.isEmpty())
        initPath = QString("home");

    QString fileName = QFileDialog::getExistingDirectory(this,
                                    tr("Tools binaries path"), initPath);
    ui->lineEditTools->setText(fileName);
    mSettings->setValue("app/lastsettingspath", fileName);
}

void SettingsDialog::on_checkBoxCleanProjectWhenClose_clicked()
{
    QString cleanProjectWhenClose="1";
    if(!ui->checkBoxCleanProjectWhenClose->isChecked())
        cleanProjectWhenClose="0";
    mSettings->setValue("app/cleanProjectAtClossingEvent", cleanProjectWhenClose);
}
