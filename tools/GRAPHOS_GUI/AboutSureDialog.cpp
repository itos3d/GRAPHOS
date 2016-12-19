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
#include "AboutSureDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QLineEdit>
#include <QDesktopServices>
#include <QUrl>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include "libPW.h"

AboutSureDialog::AboutSureDialog(QSettings *settings,QWidget *parent) :
    QDialog(parent),
    mSettings(settings)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowTitle("About SURE");
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);

    QLabel *lbNframes= new QLabel();
    lbNframes->setAlignment(Qt::AlignHCenter);
    QPixmap pxNframes(":/PW/icons/img/nframes.png");
    lbNframes->setPixmap(pxNframes);

    mainLayout->addWidget(lbNframes,Qt::AlignHCenter);

    QLabel *lbSUREIntro= new QLabel();
    lbSUREIntro->setAlignment(Qt::AlignHCenter);

    QPixmap pxSUREIntro(":/PW/icons/img/SureIntro.png");
    lbSUREIntro->setPixmap(pxSUREIntro);

    mainLayout->addWidget(lbSUREIntro,Qt::AlignHCenter);



    QGroupBox *gbSetSure = new QGroupBox(tr("Already have sure?"));

    QVBoxLayout *vboxSET = new QVBoxLayout;

    vboxSET->addWidget(new QLabel("Set SURE path:"));
    QFrame *pathFrame = new QFrame();
    QHBoxLayout *pathFrameLayout = new QHBoxLayout();
    pathFrameLayout->setContentsMargins(0,0,0,0);
    mTxtPath= new QLineEdit();

    if (!PW::LibPW::getSUREBinPath().isEmpty()) {
        if (PW::LibPW::getSUREBinPath().toAscii().contains("SURE_BIN")) {
            mTxtPath->setText("");
        }else {
            mTxtPath->setText(PW::LibPW::getSUREBinPath());
        }
    }

    QPushButton *pbSearchPath = new QPushButton("Search");
    connect(pbSearchPath,SIGNAL(clicked()),this,SLOT(on_bpSetSure()));
    QPushButton *pbSavePath = new QPushButton("Save");
    connect(pbSavePath,SIGNAL(clicked()),this,SLOT(on_pbSaveSUREPath()));
    pathFrameLayout->addWidget(mTxtPath);
    pathFrameLayout->addWidget(pbSearchPath);
    pathFrameLayout->addWidget(pbSavePath);
    pathFrame->setLayout(pathFrameLayout);
    vboxSET->addWidget(pathFrame);
    gbSetSure->setLayout(vboxSET);
    mainLayout->addWidget(gbSetSure);


    QGroupBox *gbGetSure = new QGroupBox(tr("Interested to get sure?"));
    QPushButton *pbGetSURE = new QPushButton("Get SURE");
    connect(pbGetSURE,SIGNAL(clicked()),this,SLOT(on_pbGetSURE()));
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(pbGetSURE);
    gbGetSure->setLayout(vbox);
    mainLayout->addWidget(gbGetSure);

    mainLayout->addStretch(10000);

    setLayout(mainLayout);

    this->layout()->setSizeConstraint( QLayout::SetFixedSize );


}

AboutSureDialog::~AboutSureDialog()
{
}

void AboutSureDialog::on_pbGetSURE(){
    QString link = "http://nframes.com/";
    QDesktopServices::openUrl(QUrl(link));
}

void AboutSureDialog::on_bpSetSure(){

        QString initPath = QString("home");

        QString SUREPath = QFileDialog::getExistingDirectory(this,
                                        tr("SURE binaries path"), initPath);
        mTxtPath->setText(SUREPath);
}

void AboutSureDialog::on_pbSaveSUREPath(){
    QString surePath = mTxtPath->text();


    QFileInfo checkFile(surePath+"/SURE.exe");
        // check if file exists and if yes: Is it really a file and no directory?
        if (surePath.length()==0 || !checkFile.exists() || !checkFile.isFile()) {
            QMessageBox::information(this,"Warning!","The directory does not contain a SURE distribution",QMessageBox::Close);
            return;
        }


    if(PW::LibPW::validateSUREPath(surePath)){
        mSettings->setValue("sure/binaries", surePath);
        PW::LibPW::setSUREBinPath(mSettings->value("sure/binaries").toString());
    }
    else if (!surePath.isEmpty())
        QMessageBox::warning(this, tr("Photogrammetry Workbench"),
                             tr("SURE binaries path is not valid"));

    this->close();
}
