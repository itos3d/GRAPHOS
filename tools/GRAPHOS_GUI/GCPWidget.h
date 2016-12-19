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
#ifndef GCPWIDGET_H
#define GCPWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QSettings>
//#include "GeorefMicMac/GCP.h"
//#include "GeorefMicMac/imgPoint.h"
#include "PW2dPoint.h"
#include "PW3dPoint.h"
#include <QDockWidget>
#include "MultiProcess.h"
#include "ProcessConcurrent.h"
#include "ProgressDialog.h"
#include "Project.h"
#include <QMap>
#include "photo/photoviewer.h"
#include "PersistenceManager.h"
#include <QCheckBox>
#include <QDoubleSpinBox>
using namespace PW;
class GCPWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GCPWidget(QWidget *parent = 0,QSettings *settings=0,QDockWidget *dockGeorref=0,PW::Project *project=0,PhotoViewer *photoViewer=0, PersistenceManager *persistenceManager = 0);
    ~GCPWidget();

    QString getActiveGCP();
    bool isBundleChecked();
    float getImagePrec();
    float getGCPPrec();
signals:
    void computeGeorref();
public slots:
private:
    PW::PersistenceManager *mPersistenceManager;

    PhotoViewer *mPhotoViewer;
    QTableWidget *mPointsList;
    QPushButton *mAddGCP, *mLoadGCPList,*mLoadImgPtsList,*mRemoveGCP,*mProcessGeorref,*mClose,*mCleanImagePts,*mRmPointOnImage;
    QFrame *mButtonsFrame, *mBundlePrecisionsFrame;
    QSettings *mSettings;
    QList<PW3dPoint *> *GCPList;
//    QMap<QString,QVector<PW2dPoint>*> *ImgPtsMap;
    QMap<QString,QList<PW2dPoint *>*> *imagePointsMap;
    QDockWidget *mDockGeorref;
    QTextEdit *mConsole;
    ProgressDialog *mProgressDialog;
    PW::Project *mProject;
    QCheckBox *mChBundleProcess;
    QDoubleSpinBox *mImageMarkingPrec, *mGCPPrec;
    void updateGCPView(QList <PW3dPoint*> *GCPListToShow);

private slots:
    void manageProccesStdOutput(QString data);
    void manageProccesErrorOutput(QString data);

    void on_loadGCPList_triggered();
    void on_loadImgPtsList_triggered();
    void on_btClose_triggered();
    void on_btAddGCP_triggered();
    void on_btRemoveGCP_triggered();
    void on_btGeorref_triggered();

    void on_GCPList_selectionChanged();
    void onPointPicked(QPointF point);
    void on_btCleanImage_triggered();
    void on_btRemovePointOnImage_triggered();

    void imageHovered();

    void imageLeft();
    void showGCPListInfo();
    void showImgPointListInfo();
};

#endif // GCPWIDGET_H
