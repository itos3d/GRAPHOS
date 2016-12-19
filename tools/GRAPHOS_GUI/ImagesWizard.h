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
#ifndef IMAGESWIZARD_H
#define IMAGESWIZARD_H

#include <QDialog>
#include <QString>
#include <QDir>
#include <QList>
#include <QListWidget>
#include <QStackedWidget>
#include <QCheckBox>
#include <QProgressBar>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QFutureWatcher>
#include "MultiProcess.h"
#include "ProgressDialog.h"

namespace Ui {
class ImagesWizard;
}

class ImagesWizard : public QDialog
{
    Q_OBJECT

public:
    QString mInitPath;
//    bool isWallisChecked();
    explicit ImagesWizard(QWidget *parent = 0,QStringList *ImagesList = new QStringList(), ProgressDialog *progressDialog=0);
//    float getWallisValue();
    ~ImagesWizard();


//    void getImagesList(QStringList &imagesList);


signals:
    void imagesSelected();

private slots:

    void on_pbAddImages_clicked();

    void on_pbRemoveImage_clicked();

    void on_pbRemoveAllImages_clicked();

    void on_pbNext_clicked();

    void on_pbCancel_clicked();

    void on_pbBack_clicked();

//    void setWallisValueVisibility();

    void showImage(int num);
    void finished();

    void video2ImagesFinished();

private:
    ProgressDialog *mProgressDialog;
    PW::MultiProcess *ImageExtractionProcess;
    QStringList *mImagesSelected;
    Ui::ImagesWizard *ui;
    QStringList mFilesToLoad;
    QDir *mImagesPath;
    QStringList *fileNamesList;
    QStringList *mImagesList;
    QListWidget *localPathList;
    QStackedWidget *mStackedWidget;
    QPushButton *pbBack;
    QPushButton *pbNext;
//    QCheckBox *mCbWallis;
//    QDoubleSpinBox *mWallisValue;
//    QLabel *mLbWallisContrast;
    QFutureWatcher<QImage> *mImageScalingFutureWatcher;
    void updateImagesView();
};

#endif // IMAGESWIZARD_H
