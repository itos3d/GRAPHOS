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
#include "ImagesWizard.h"
#include "ui_ImagesWizard.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QIcon>
#include <QLineEdit>
#include <QLine>
#include <QComboBox>
#include <QCheckBox>
#include <QPixmap>
#include <QtConcurrentMap>
#include "Tools/Video2ImagesProcess.h"
#include <QDirIterator>
#include "FrameRateDialog.h"
QImage scale(const QString &imageFileName)
{
    QImage image(imageFileName);
    return image.scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation);
}

ImagesWizard::ImagesWizard(QWidget *parent, QStringList *imagesList,ProgressDialog *progressDialog) :
    QDialog(parent),
    ui(new Ui::ImagesWizard),
    mImagesList(imagesList),
    mProgressDialog(progressDialog)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    setWindowTitle("Add images");
    setMaximumSize(600,400);
    setMinimumSize(600,400);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mStackedWidget = new QStackedWidget();
    QWidget *page1 = new QWidget();
    QVBoxLayout *page1Layout = new QVBoxLayout();
    QFrame *imagesFrame = new QFrame();
    QVBoxLayout *imagesFrameLayout = new QVBoxLayout();
    imagesFrameLayout->setMargin(0);
    imagesFrameLayout->addWidget(new QLabel("Add images:"));
    localPathList = new QListWidget();
    imagesFrameLayout->addWidget(localPathList);
    imagesFrame->setLayout(imagesFrameLayout);
    page1Layout->addWidget(imagesFrame);


    QFrame *buttonsFrame = new QFrame();
    QHBoxLayout *buttonsFrameLayout = new QHBoxLayout();
    buttonsFrameLayout->setMargin(0);
    QPushButton *pbAddImages = new QPushButton("Add images");
    pbAddImages->setFocus();
    connect(pbAddImages,SIGNAL(clicked()),this,SLOT(on_pbAddImages_clicked()));
    QPushButton *pbRemoveImage = new QPushButton("Remove");
    connect(pbRemoveImage,SIGNAL(clicked()),this, SLOT(on_pbRemoveImage_clicked()));
    QPushButton *pbRemoveAllImages = new QPushButton("Remove all");
    connect(pbRemoveAllImages,SIGNAL(clicked()),this,SLOT(on_pbRemoveAllImages_clicked()));
    buttonsFrameLayout->addWidget(pbAddImages);
    buttonsFrameLayout->addWidget(pbRemoveImage);
    buttonsFrameLayout->addWidget(pbRemoveAllImages);
    buttonsFrame->setLayout(buttonsFrameLayout);
    page1Layout->addWidget(buttonsFrame);

    page1->setLayout(page1Layout);
    mStackedWidget->addWidget(page1);

    QFrame *navigationButtonsFrame = new QFrame();
    QHBoxLayout *navigationButtonsFrameLayout = new QHBoxLayout();
    navigationButtonsFrameLayout->setAlignment(Qt::AlignRight);
    navigationButtonsFrameLayout->addStretch(0);
    pbBack = new QPushButton("Back");
    pbBack->setFixedWidth(100);
    connect(pbBack,SIGNAL(clicked()),this,SLOT(on_pbBack_clicked()));
    pbBack->setVisible(false);
    pbNext = new QPushButton("Next");
    pbNext->setFixedWidth(100);
    connect(pbNext,SIGNAL(clicked()),this,SLOT(on_pbNext_clicked()));
    QPushButton *pbCancel = new QPushButton("Cancel");
    pbCancel->setFixedWidth(100);
    connect(pbCancel,SIGNAL(clicked()),this,SLOT(on_pbCancel_clicked()));
    navigationButtonsFrameLayout->addWidget(pbCancel);
    navigationButtonsFrameLayout->addWidget(pbBack);
    navigationButtonsFrameLayout->addWidget(pbNext);
    navigationButtonsFrame->setLayout(navigationButtonsFrameLayout);

    mainLayout->addWidget(mStackedWidget);
    mainLayout->addWidget(navigationButtonsFrame);

    setLayout(mainLayout);

    mImageScalingFutureWatcher = new QFutureWatcher<QImage>(this);
    connect(mImageScalingFutureWatcher, SIGNAL(resultReadyAt(int)), SLOT(showImage(int)));
    connect(mImageScalingFutureWatcher, SIGNAL(finished()), SLOT(finished()));

}

ImagesWizard::~ImagesWizard()
{
    delete ui;
}



void ImagesWizard::on_pbAddImages_clicked()
{
    QFileDialog dialog(this);
    dialog.setDirectory(mInitPath);
    dialog.setFileMode(QFileDialog::ExistingFiles);
    dialog.setNameFilter(trUtf8("Images (*.jpg *.png *.tif *.tiff *.bmp);;Videos (*.mov *.mp4);; JPG (*.jpg);; PNG (*.png);; TIF (*.tif *.tiff);; BMP (*.bmp);;MOV (*.mov);;MP4 (*.mp4);;All (*.*)"));

    mFilesToLoad.clear();
    mImagesSelected  = new QStringList();

    if (dialog.exec() && dialog.selectedFiles().count()>0){
        mImagesSelected->append(dialog.selectedFiles());
    }else{
        return;
    }
    QFileInfo fileInfo(mImagesSelected->first());
    if (fileInfo.suffix().compare("mov",Qt::CaseInsensitive)==0 || fileInfo.suffix().compare("avi",Qt::CaseInsensitive)==0 || fileInfo.suffix().compare("mp4",Qt::CaseInsensitive)==0) {
        FrameRateDialog *frameRateDialog = new FrameRateDialog(this);
        if (!frameRateDialog->exec()) {
            return;
        }

        ImageExtractionProcess = new PW::MultiProcess(false);
        for (int i = 0; i < mImagesSelected->count(); ++i) {
            PW::Video2ImagesProcess *video2images = new PW::Video2ImagesProcess(mImagesSelected->at(i),frameRateDialog->getFrameRate());
            ImageExtractionProcess->appendProcess(video2images);
        }
        connect(ImageExtractionProcess, SIGNAL(newStdData(QString)),this,SLOT(manageProccesStdOutput(QString)));
        connect(ImageExtractionProcess, SIGNAL(newErrorData(QString)),this,SLOT(manageProccesErrorOutput(QString)));
        connect(ImageExtractionProcess, SIGNAL(finished()),this,SLOT(video2ImagesFinished()));

        connect(ImageExtractionProcess, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
        connect(mProgressDialog,SIGNAL(cancel()),ImageExtractionProcess,SLOT(stop()));

        mProgressDialog->clearConsole();
        mProgressDialog->setModal(true);
        mProgressDialog->setRange(0,0);
        mProgressDialog->setWindowTitle("Frame extraction");
        mProgressDialog->setStatusText("Extracting images from video file...");
        mProgressDialog->setFinished(false);
        mProgressDialog->show();
        ImageExtractionProcess->start();
        return;
    }

    updateImagesView();
}

void ImagesWizard::on_pbRemoveImage_clicked()
{
    QModelIndexList indexes = localPathList->selectionModel()->selectedIndexes();

    std::vector<int> indexList;
    foreach(QModelIndex index, indexes)
    {
        localPathList->takeItem(index.row());
        mImagesList->removeAt(index.row());
    }
}

void ImagesWizard::on_pbRemoveAllImages_clicked()
{
    localPathList->clear();
    mImagesList->clear();
}
void ImagesWizard::on_pbNext_clicked()
{

    switch (mStackedWidget->currentIndex()) {
    case 0:
        this->accept();
        break;
    }

}

void ImagesWizard::on_pbCancel_clicked()
{
    if (mImageScalingFutureWatcher->isRunning()) {
        mImageScalingFutureWatcher->cancel();
    }
    this->close();
}

void ImagesWizard::on_pbBack_clicked(){
    mStackedWidget->setCurrentIndex(mStackedWidget->currentIndex()-1);
    if (mStackedWidget->currentIndex()==0) {
        pbBack->setVisible(false);
        setWindowTitle("Add images");
    }
}


void ImagesWizard::showImage(int num)
{
    QListWidgetItem *listItem = new QListWidgetItem(QIcon(QPixmap::fromImage(mImageScalingFutureWatcher->resultAt(num))),mFilesToLoad.at(num).split("/").last());
    localPathList->addItem(listItem);
    mImagesList->append(mFilesToLoad.at(num));
}

void ImagesWizard::finished()
{
    localPathList->sortItems();
    pbNext->setEnabled(true);
    pbNext->setFocus();
}

void ImagesWizard::updateImagesView(){
    for (int i = 0; i < mImagesSelected->count(); ++i) {
        if (!mImagesList->contains(mImagesSelected->at(i))) {
            mFilesToLoad.append(mImagesSelected->at(i));
        }
    }
    if (mFilesToLoad.count()!=0) {
        localPathList->setViewMode(QListWidget::IconMode );
        localPathList->setIconSize(QSize(100,100));
        localPathList->setResizeMode(QListWidget::Adjust);
        localPathList->setSelectionMode(QAbstractItemView::MultiSelection);

        // Use mapped to run the thread safe scale function on the files.
            mImageScalingFutureWatcher->setFuture(QtConcurrent::mapped(mFilesToLoad, scale));

            pbNext->setEnabled(false);

    }
    localPathList->setDragEnabled(false);
    localPathList->viewport()->setAcceptDrops(false);
    localPathList->setDropIndicatorShown(false);

    localPathList->setDragDropMode(QAbstractItemView::NoDragDrop);
}

void ImagesWizard::video2ImagesFinished(){
    QStringList imagesOfVideo;
    QStringList VideoBaseNames;
    for (int i = 0; i < mImagesSelected->count(); ++i) {
        VideoBaseNames.append(QFileInfo(mImagesSelected->at(i)).baseName());
    }

    QDirIterator directories(QFileInfo(mImagesSelected->at(0)).absolutePath(), QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);

    while(directories.hasNext()){
        directories.next();
        for (int i = 0; i < mImagesSelected->count(); ++i) {
            if (QFileInfo(directories.filePath()).suffix().compare("png",Qt::CaseInsensitive)==0 && QFileInfo(directories.filePath()).baseName().contains(QFileInfo(mImagesSelected->at(i)).baseName())) {
                imagesOfVideo.append(directories.filePath());
            }
        }
    }
    mImagesSelected->clear();
    mImagesSelected->append(imagesOfVideo);
    mProgressDialog->close();

    updateImagesView();
    disconnect(mProgressDialog,SIGNAL(cancel()),ImageExtractionProcess,SLOT(stop()));
}
