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
#include "BatchProcessWizard.h"
#include <QGridLayout>
#include <QPushButton>
BatchProcessWizard::BatchProcessWizard(QWidget *parent,PW::Project *Project,QMap<QString, QImage> *mapImages,QSettings *settings,TiePointsWizard *tpWizard,OrientationWizard *orWizard,DensificationWizard *denWizard) :
    QDialog(parent),
    mProject(Project),
    mMapImages(mapImages),
    mSettings(settings),
    mTiePointsWizard(tpWizard),
    mDensificationWizard(denWizard),
    mOrientationWizard(orWizard)
{

    setWindowTitle("Batch process");
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QGridLayout *mainLayout = new QGridLayout();
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mComputeTiepoints = new QCheckBox("Tie points extraction and matching.");
    mainLayout->addWidget(mComputeTiepoints,0,0);
    connect(mComputeTiepoints,SIGNAL(clicked()),this, SLOT(on_computeTiepoints_clicked()));

    mBtEditTiepointsProcess = new QToolButton;
    connect(mBtEditTiepointsProcess,SIGNAL(clicked()),this,SLOT(on_EditTiepoints_clicked()));
    mBtEditTiepointsProcess->setIconSize(QSize(20,20));
    mBtEditTiepointsProcess->setIcon(QPixmap(":/PW/icons/img/editIcon.png"));
    mBtEditTiepointsProcess->setEnabled(false);

    mainLayout->addWidget(mBtEditTiepointsProcess,0,1);



    mComputeOrientations = new QCheckBox("Camera self-calibration and Orientation.");
    connect(mComputeOrientations,SIGNAL(clicked()),this, SLOT(on_computeOrientation_clicked()));
    mainLayout->addWidget(mComputeOrientations,1,0);   
    mBtEditOrientationProcess = new QToolButton;
    connect(mBtEditOrientationProcess,SIGNAL(clicked()),this,SLOT(on_EditOrientation_clicked()));
    mBtEditOrientationProcess->setIconSize(QSize(20,20));
    mBtEditOrientationProcess->setIcon(QPixmap(":/PW/icons/img/editIcon.png"));
    mainLayout->addWidget(mBtEditOrientationProcess,1,1);
    if (mProject->getCurrentOrientation().isEmpty()) {
        mComputeOrientations->setEnabled(false);
    }else {
        mComputeOrientations->setEnabled(true);
    }
    mBtEditOrientationProcess->setEnabled(false);

    mComputeDensification = new QCheckBox("Dense matching.");  
    connect(mComputeDensification,SIGNAL(clicked()),this,SLOT(on_computeDenseMatching_clicked()));
    mainLayout->addWidget(mComputeDensification,2,0);
    mBtEditDenseMatchingProcess = new QToolButton;
    connect(mBtEditDenseMatchingProcess,SIGNAL(clicked()),this,SLOT(on_EditDenseMatching_clicked()));
    mBtEditDenseMatchingProcess->setIconSize(QSize(20,20));
    mBtEditDenseMatchingProcess->setIcon(QPixmap(":/PW/icons/img/editIcon.png"));

    if (mProject->getDenseModelRelativePath().isEmpty()) {
        mComputeDensification->setEnabled(false);
    }else {
        mComputeDensification->setEnabled(true);
    }

    mBtEditDenseMatchingProcess->setEnabled(false);

    mainLayout->addWidget(mBtEditDenseMatchingProcess,2,1);

    //Botones de navegación
    QFrame *navigationButtonsFrame = new QFrame();
    QHBoxLayout *navigationButtonsFrameLayout = new QHBoxLayout();
    navigationButtonsFrameLayout->setContentsMargins(0,0,0,0);
    navigationButtonsFrameLayout->setAlignment(Qt::AlignJustify);

    mPbAccept = new QPushButton("Accept");
//    mPbAccept->setFixedWidth(100);
    connect(mPbAccept,SIGNAL(clicked()),this,SLOT(on_pbAccept_clicked()));
    QPushButton *pbCancel = new QPushButton("Cancel");
//    pbCancel->setFixedWidth(100);
    connect(pbCancel,SIGNAL(clicked()),this,SLOT(on_pbCancel_clicked()));
    navigationButtonsFrameLayout->addWidget(pbCancel);
    navigationButtonsFrameLayout->addWidget(mPbAccept);
    navigationButtonsFrame->setLayout(navigationButtonsFrameLayout);

    mainLayout->addWidget(navigationButtonsFrame,3,0,2,0);
    setLayout(mainLayout);
    mPbAccept->setFocus();
}

BatchProcessWizard::~BatchProcessWizard()
{
}

void BatchProcessWizard::on_pbCancel_clicked(){
    this->close();
}
void BatchProcessWizard::on_pbAccept_clicked(){

    this->accept();
//    if (methodSelected || mCbSURE->isChecked()) {
//        if (getDensificationMode().contains("MicMac master image")) {
//            if (mListWidget->selectedItems().count()==0 && !mCbSURE->isChecked()) {
//                QMessageBox::information(this,"MicMac dense matching","You must select the main image for the MicMac dense matching.",QMessageBox::Ok);
//                return;
//            }
//            QStringList selectedImages =getMainImages();
//            bool imagesWithoutMask=false;
//            QString msgText;
//            msgText.append("Some images (");
//            foreach (QString MainImageName, selectedImages) {
//                PW::PWImage *mainImage = mProject->getImageByName(MainImageName);
//                if(mainImage->getMask().isEmpty()){
//                    imagesWithoutMask=true;
//                    msgText.append(MainImageName);
//                    msgText.append(", ");
//                }
//            }
//            msgText.replace(msgText.length()-2,2,")");
//            msgText.append("have no asociated mask.\nDensification could be noisy.");
//            if (imagesWithoutMask) {
//                int res = QMessageBox::information(this,tr("Warning"),tr(msgText.toUtf8().constData()),QMessageBox::Ok|QMessageBox::Cancel);
//                if (res==QMessageBox::Cancel) {
//                    return;
//                }
//            }
//        }

//        this->accept();
//    }else {
//        QMessageBox msg;
//        msg.setText("Dense matching method not selected.");
//        msg.exec();
//    }

}

void BatchProcessWizard::on_computeTiepoints_clicked(){
    if (mComputeTiepoints->isChecked()) {
        if (!mTiePointsWizard->exec()){
            mComputeTiepoints->setChecked(false);
            mBtEditTiepointsProcess->setEnabled(false);


            if (mProject->getCurrentOrientation().isEmpty()) {
                mComputeOrientations->setEnabled(false);
            }else {
                mComputeOrientations->setEnabled(true);
            }
            mBtEditOrientationProcess->setEnabled(false);

            if (mProject->getDenseModelFullPath().isEmpty()) {
                mComputeDensification->setEnabled(false);
                mComputeDensification->setChecked(false);

            }else {
                mComputeDensification->setEnabled(true);
            }

            mBtEditDenseMatchingProcess->setEnabled(false);
            return;
        }

        mBtEditTiepointsProcess->setEnabled(true);
        mComputeOrientations->setEnabled(true);
        if (!mComputeOrientations->isChecked()) {
            mBtEditDenseMatchingProcess->setEnabled(false);
            mComputeDensification->setEnabled(false);
            mComputeDensification->setChecked(false);

        }
    }else {
        mBtEditTiepointsProcess->setEnabled(false);

        if (mProject->getCurrentOrientation().isEmpty()) {
            mComputeOrientations->setEnabled(false);
        }else {
            mComputeOrientations->setEnabled(true);
        }
        mBtEditOrientationProcess->setEnabled(false);


        if (mProject->getDenseModelFullPath().isEmpty()) {
            mComputeDensification->setEnabled(false);
        }else {
            mComputeDensification->setEnabled(true);
        }

        mBtEditDenseMatchingProcess->setEnabled(false);

    }
}
void BatchProcessWizard::on_computeOrientation_clicked(){
    if (mComputeOrientations->isChecked()) {
        if (!mOrientationWizard->exec()) {
            mBtEditOrientationProcess->setEnabled(false);
            mComputeOrientations->setChecked(false);

//            mComputeDensification->setChecked(false);
//            mComputeDensification->setEnabled(false);

//            mBtEditDenseMatchingProcess->setEnabled(false);
            if (mProject->getDenseModelFullPath().isEmpty()) {
                mComputeDensification->setEnabled(false);
            }else {
                mComputeDensification->setEnabled(true);
            }

            mBtEditDenseMatchingProcess->setEnabled(false);
            return;
        }

        mBtEditOrientationProcess->setEnabled(true);
        mComputeDensification->setEnabled(true);
    }else {
//        if (mProject->getDenseModelFullPath().isEmpty()) {
//            mComputeDensification->setChecked(false);
//            mComputeDensification->setEnabled(false);

//            mBtEditDenseMatchingProcess->setEnabled(false);
//        }
        if (mProject->getDenseModelFullPath().isEmpty() || mComputeTiepoints->isChecked()) {
            mComputeDensification->setEnabled(false);
            mComputeDensification->setChecked(false);

        }else {
            mComputeDensification->setEnabled(true);
        }


        mBtEditDenseMatchingProcess->setEnabled(false);
        mBtEditOrientationProcess->setEnabled(false);

    }
}
void BatchProcessWizard::on_computeDenseMatching_clicked(){
    if (mComputeDensification->isChecked()) {
        if (!mDensificationWizard->exec()){
            mBtEditDenseMatchingProcess->setEnabled(false);

            mComputeDensification->setChecked(false);
            return;
        }
        mBtEditDenseMatchingProcess->setEnabled(true);
    }else {
        mBtEditDenseMatchingProcess->setEnabled(false);
    }
}

void BatchProcessWizard::on_EditTiepoints_clicked(){
    if (mComputeTiepoints->isChecked()) {
        if (!mTiePointsWizard->exec()) return;

        mBtEditTiepointsProcess->setEnabled(true);
        mComputeOrientations->setEnabled(true);
    }else {
        mBtEditTiepointsProcess->setEnabled(false);


        mComputeOrientations->setChecked(false);
        mComputeOrientations->setEnabled(false);
        mBtEditOrientationProcess->setEnabled(false);

        mComputeDensification->setChecked(false);
        mComputeDensification->setEnabled(false);
        mBtEditDenseMatchingProcess->setEnabled(false);
    }
}
void BatchProcessWizard::on_EditOrientation_clicked(){
    if (mComputeOrientations->isChecked()) {
        if (!mOrientationWizard->exec())return;

        mBtEditOrientationProcess->setEnabled(true);
        mComputeDensification->setEnabled(true);
    }else {
        mBtEditOrientationProcess->setEnabled(false);
        mComputeDensification->setChecked(false);
        mComputeDensification->setEnabled(false);

        mBtEditDenseMatchingProcess->setEnabled(false);
    }
}
void BatchProcessWizard::on_EditDenseMatching_clicked(){
    if (mComputeDensification->isChecked()) {
        if (!mDensificationWizard->exec())return;

        mBtEditDenseMatchingProcess->setEnabled(true);
    }else {
        mBtEditDenseMatchingProcess->setEnabled(false);
    }
}

bool BatchProcessWizard::isComputeTiePointsChecked(){
    return mComputeTiepoints->isChecked();
}
bool BatchProcessWizard::isComputeDenseMatchingChecked(){
    return mComputeDensification->isChecked();
}
bool BatchProcessWizard::isComputeOrientationsChecked(){
    return mComputeOrientations->isChecked();
}
