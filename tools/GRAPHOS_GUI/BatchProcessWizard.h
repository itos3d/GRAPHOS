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
#ifndef BATCHPROCESSWIZARD_H
#define BATCHPROCESSWIZARD_H

#include <QDialog>
#include "libPW.h"
#include "QCheckBox"
#include <QToolButton>
#include "TiePointsWizard.h"
#include "OrientationWizard.h"
#include "DensificationWizard.h"

class BatchProcessWizard : public QDialog
{
    Q_OBJECT

public:
    explicit BatchProcessWizard(QWidget *parent = 0,PW::Project *mProject=0,QMap<QString, QImage> *mapImages=0,
                                QSettings *settings=0,TiePointsWizard *tpWizard=0,OrientationWizard *orWizard =0,DensificationWizard *denWizard=0);
    ~BatchProcessWizard();


    bool isComputeTiePointsChecked();
    bool isComputeOrientationsChecked();
    bool isComputeDenseMatchingChecked();
private:
    PW::Project *mProject;
    QMap<QString, QImage> *mMapImages;
    QSettings *mSettings;
    QCheckBox *mComputeTiepoints,*mComputeOrientations,*mComputeDensification;
    QPushButton *mPbAccept,*pbCancel;
    QToolButton *mBtEditOrientationProcess,*mBtEditDenseMatchingProcess,*mBtEditTiepointsProcess;
    TiePointsWizard *mTiePointsWizard;
    OrientationWizard *mOrientationWizard;
    DensificationWizard *mDensificationWizard;
private slots:
    void on_pbAccept_clicked();
    void on_pbCancel_clicked();
    void on_EditTiepoints_clicked();
    void on_EditOrientation_clicked();
    void on_EditDenseMatching_clicked();
    void on_computeTiepoints_clicked();
    void on_computeOrientation_clicked();
    void on_computeDenseMatching_clicked();
};

#endif // BATCHPROCESSWIZARD_H
