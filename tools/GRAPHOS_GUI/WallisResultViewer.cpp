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
#include "WallisResultViewer.h"
#include <QHBoxLayout>
#include <QToolButton>
#include <QDesktopWidget>
WallisResultViewer::WallisResultViewer(QWidget *parent,QString wallisImagesURL,QVector<QString> imageNames) :
    QDialog(parent),
    mWallisImageURL(wallisImagesURL),
    mImageNames(imageNames)
{
    //Rename images to .tif wallis output
    for (int i = 0; i < mImageNames.count(); ++i) {
        mImageNames[i]=mWallisImageURL+"/"+mImageNames[i].split("/").last().split(".").first().append(".tif");
    }
    setWindowTitle("Wallis result preview");
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    QVBoxLayout *mainLayout = new QVBoxLayout();

    mLbWallisImage = new QLabel();
    mImageToShowPos=0;
    QPixmap wallisPixmap(mImageNames.at(mImageToShowPos));
    QDesktopWidget widget;
    mainScreenSize = widget.availableGeometry(widget.primaryScreen());

//    if (wallisPixmap.height()>=wallisPixmap.width()) {
        mLbWallisImage->setPixmap(wallisPixmap.scaled(mainScreenSize.height()*0.8,mainScreenSize.height()*0.8,Qt::KeepAspectRatio));
//    }else {
//        mLbWallisImage->setPixmap(wallisPixmap.scaled(800,800,Qt::KeepAspectRatio));
//    }

    mainLayout->addWidget(mLbWallisImage);

    mLbImageName = new QLabel("<strong>"+mImageNames.at(mImageToShowPos).split("/").last()+"</strong>");
    QFont lbFont(mLbImageName->font().family(), 12, QFont::Bold);
    mLbImageName->setFont(lbFont);
    mainLayout->addWidget(mLbImageName,0,Qt::AlignHCenter);
    //Botones de navegación entre imágenes
    QFrame *imageNavigationFrame = new QFrame();
    QHBoxLayout *imageNavigationFrameLayout = new QHBoxLayout();
    imageNavigationFrameLayout->setAlignment(Qt::AlignHCenter);
    QToolButton *leftArrow = new QToolButton;
    connect(leftArrow,SIGNAL(clicked()),this,SLOT(on_leftArrow_clicked()));
    leftArrow->setIconSize(QSize(30,30));
    leftArrow->setIcon(QPixmap(":/PW/icons/img/arrowLeft.png").scaled(200,200,Qt::KeepAspectRatio));

    imageNavigationFrameLayout->addWidget(leftArrow);

    mLbImageToShowNum = new QLabel(QString::number(mImageToShowPos+1));
    imageNavigationFrameLayout->addWidget(mLbImageToShowNum);
    imageNavigationFrameLayout->addWidget(new QLabel(" / "+QString::number(mImageNames.count())));
    QToolButton *rightArrow = new QToolButton;
    connect(rightArrow,SIGNAL(clicked()),this,SLOT(on_rightArrow_clicked()));
    rightArrow->setIconSize(QSize(30,30));
    rightArrow->setIcon(QPixmap(":/PW/icons/img/arrowRight.png").scaled(200,200,Qt::KeepAspectRatio));

    imageNavigationFrameLayout->addWidget(rightArrow);
    imageNavigationFrame->setLayout(imageNavigationFrameLayout);

    mainLayout->addWidget(imageNavigationFrame);

    //Botones de navegación
    QFrame *navigationButtonsFrame = new QFrame();
    QHBoxLayout *navigationButtonsFrameLayout = new QHBoxLayout();
    navigationButtonsFrameLayout->setAlignment(Qt::AlignRight);

    mPbProccess = new QPushButton("Continue");
    mPbProccess->setFixedWidth(100);
    connect(mPbProccess,SIGNAL(clicked()),this,SLOT(on_pbProccess_clicked()));
    QPushButton *pbCancel = new QPushButton("Cancel");
    pbCancel->setFixedWidth(100);
    connect(pbCancel,SIGNAL(clicked()),this,SLOT(on_pbCancel_clicked()));
    navigationButtonsFrameLayout->addWidget(pbCancel);
    navigationButtonsFrameLayout->addWidget(mPbProccess);
    navigationButtonsFrame->setLayout(navigationButtonsFrameLayout);

    mainLayout->addWidget(navigationButtonsFrame);

    setLayout(mainLayout);
    this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    mPbProccess->setFocus();

}

WallisResultViewer::~WallisResultViewer()
{
}

void WallisResultViewer::on_pbCancel_clicked(){
    this->close();
}

void WallisResultViewer::on_pbProccess_clicked(){
    this->accept();
}
void WallisResultViewer::on_leftArrow_clicked(){
    if (mImageToShowPos>0) {
        mImageToShowPos--;
    }else{
        mImageToShowPos = mImageNames.count()-1;
    }
    mLbImageToShowNum->setText(QString::number(mImageToShowPos+1));
    QPixmap wallisPixmap(mImageNames.at(mImageToShowPos));
    mLbWallisImage->setPixmap(wallisPixmap.scaled(mainScreenSize.height()*0.8,mainScreenSize.height()*0.8,Qt::KeepAspectRatio));
    mLbImageName->setText("<strong>"+mImageNames.at(mImageToShowPos).split("/").last()+"</strong>");

}
void WallisResultViewer::on_rightArrow_clicked(){
    if (mImageToShowPos<mImageNames.count()-1) {
        mImageToShowPos++;
    }else{
        mImageToShowPos = 0;
    }
    mLbImageToShowNum->setText(QString::number(mImageToShowPos+1));
    QPixmap wallisPixmap(mImageNames.at(mImageToShowPos));
    mLbWallisImage->setPixmap(wallisPixmap.scaled(mainScreenSize.height()*0.8,mainScreenSize.height()*0.8,Qt::KeepAspectRatio));
    mLbImageName->setText("<strong>"+mImageNames.at(mImageToShowPos).split("/").last()+"</strong>");

}
