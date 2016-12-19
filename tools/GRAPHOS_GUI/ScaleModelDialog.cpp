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
#include "ScaleModelDialog.h"
#include <QVBoxLayout>
#include <QDoubleValidator>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
ScaleModelDialog::ScaleModelDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setFixedWidth(350);
    this->setFixedHeight(200);
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("Scale model");
    QVBoxLayout *mainLayout = new QVBoxLayout();

    mObjectDistanceFrame = new QFrame();
    QHBoxLayout *objectDistanceFrameLayout = new QHBoxLayout();
    objectDistanceFrameLayout->addWidget(new QLabel("Object distance:"));
    mDistanceObject = new QLineEdit();
    mDistanceObject->setValidator(new QDoubleValidator());

    objectDistanceFrameLayout->addWidget(mDistanceObject);
    connect(mDistanceObject,SIGNAL(textChanged(QString)),this,SLOT(on_writeInMethod1(QString)));
    btDistanceTool = new QToolButton();
    connect(btDistanceTool,SIGNAL(clicked()),this,SLOT(on_btDistance_triggered()));
    btDistanceTool->setIconSize(QSize(25,30));
    btDistanceTool->setIcon(QPixmap(":/PW/icons/img/cota.png").scaled(80,80,Qt::KeepAspectRatio));
    objectDistanceFrameLayout->addWidget(btDistanceTool);
    mObjectDistanceFrame->setLayout(objectDistanceFrameLayout);

    mRealityDistanceFrame = new QFrame();
    QHBoxLayout *realityDistanceFrameLayout = new QHBoxLayout();
    realityDistanceFrameLayout->addWidget(new QLabel("Reality distance:"));
    mDistanceReality = new QLineEdit();
    mDistanceReality->setValidator(new QDoubleValidator());

    connect(mDistanceReality,SIGNAL(textChanged(QString)),this,SLOT(on_writeInMethod1(QString)));

    realityDistanceFrameLayout->addWidget(mDistanceReality);
    mRealityDistanceFrame->setLayout(realityDistanceFrameLayout);

    mainLayout->addWidget(mObjectDistanceFrame);
    mainLayout->addWidget(mRealityDistanceFrame);

    QFrame* line = new QFrame();
    line->setFrameShape(QFrame::HLine);


    mainLayout->addWidget(line);
    mScaleValuesFrame = new QFrame();
    QHBoxLayout *mScaleValuesFrameLayout = new QHBoxLayout();

    mScale_x = new QLineEdit();
    mScale_x->setValidator(new QDoubleValidator());
    mScale_y = new QLineEdit();
    mScale_y->setValidator(new QDoubleValidator());
    mScale_z = new QLineEdit();
    mScale_z->setValidator(new QDoubleValidator());
    connect(mScale_x,SIGNAL(textChanged(QString)),this,SLOT(on_writeInMethod2(QString)));
    connect(mScale_y,SIGNAL(textChanged(QString)),this,SLOT(on_writeInMethod2(QString)));
    connect(mScale_z,SIGNAL(textChanged(QString)),this,SLOT(on_writeInMethod2(QString)));

    mScaleValuesFrameLayout->addWidget(new QLabel("Scale X: "));
    mScaleValuesFrameLayout->addWidget(mScale_x);
    mScaleValuesFrameLayout->addWidget(new QLabel("Scale Y: "));
    mScaleValuesFrameLayout->addWidget(mScale_y);
    mScaleValuesFrameLayout->addWidget(new QLabel("Scale Z: "));
    mScaleValuesFrameLayout->addWidget(mScale_z);
    mScaleValuesFrame->setLayout(mScaleValuesFrameLayout);

    QFrame *btFrame = new QFrame();
    QHBoxLayout *btFrameLayout = new QHBoxLayout();
    btFrameLayout->setAlignment(Qt::AlignRight);
    mBtCancel= new QPushButton("Cancel");
    connect(mBtCancel,SIGNAL(clicked()),this,SLOT(on_btCancel_triggered()));
    mBtProcess=new QPushButton("Process");
    connect(mBtProcess,SIGNAL(clicked()),this,SLOT(on_btProcess_triggered()));
    btFrameLayout->addWidget(mBtCancel);
    btFrameLayout->addWidget(mBtProcess);
    btFrame->setLayout(btFrameLayout);

    mainLayout->addWidget(mScaleValuesFrame);
    mainLayout->addWidget(btFrame);

    setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mBtProcess->setFocus();
}

ScaleModelDialog::~ScaleModelDialog()
{
}

void ScaleModelDialog::on_btProcess_triggered(){
    this->accept();
}
void ScaleModelDialog::on_btCancel_triggered(){

    this->close();
}

double ScaleModelDialog::getScalex(){
    return mScale_x->text().toDouble();
}

double ScaleModelDialog::getScaley(){
    return mScale_y->text().toDouble();
}

double ScaleModelDialog::getScalez(){
    return mScale_z->text().toDouble();
}

void ScaleModelDialog::on_btDistance_triggered(){
    emit readDistanceToScale();
    this->hide();
}

void ScaleModelDialog::setObjectDistance(float distance){
    mDistanceObject->setText(QString::number(distance));
}

void ScaleModelDialog::on_writeInMethod2(QString text){
    if (!mScale_x->text().isEmpty()||!mScale_x->text().isEmpty()||!mScale_z->text().isEmpty()) {
        mObjectDistanceFrame->setEnabled(false);
        mRealityDistanceFrame->setEnabled(false);
        mscaleMethod=2;
    }else {
        mObjectDistanceFrame->setEnabled(true);
        mRealityDistanceFrame->setEnabled(true);
    }
}
void ScaleModelDialog::on_writeInMethod1(QString text){
    if (!mDistanceObject->text().isEmpty()||!mDistanceReality->text().isEmpty()) {
        mScaleValuesFrame->setEnabled(false);
        mscaleMethod=1;
    }else {
        mScaleValuesFrame->setEnabled(true);
    }
}

int ScaleModelDialog::getScaleMethod(){
    return mscaleMethod;
}
double ScaleModelDialog::getDistanceObject(){
    return mDistanceObject->text().toDouble();
}
double ScaleModelDialog::getDistanceReality(){
    return mDistanceReality->text().toDouble();
}
