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
#include "FrameRateDialog.h"
#include <QVBoxLayout>
#include <QFrame>
#include <QLabel>
FrameRateDialog::FrameRateDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowTitle("Frame rate");
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    QFrame *rateFrame = new QFrame();
    QHBoxLayout *rateFrameLayout = new QHBoxLayout();
    rateFrameLayout->addWidget(new QLabel("Images per second: "));
    mImagesPerSecond = new QSpinBox();
    mImagesPerSecond->setRange(1,10);
    mImagesPerSecond->setSingleStep(1);
    mImagesPerSecond->setValue(1);
    rateFrameLayout->addWidget(mImagesPerSecond);
    rateFrame->setLayout(rateFrameLayout);
    mainLayout->addWidget(rateFrame);

    QFrame *btFrame = new QFrame();
    QHBoxLayout *btFrameLayout = new QHBoxLayout();
    btFrameLayout->setContentsMargins(0,0,0,0);
    btFrameLayout->setAlignment(Qt::AlignRight);
    mBtCancel= new QPushButton("Cancel");
    connect(mBtCancel,SIGNAL(clicked()),this,SLOT(on_btCancel_triggered()));
    mBtProcess=new QPushButton("Process");
    connect(mBtProcess,SIGNAL(clicked()),this,SLOT(on_btProcess_triggered()));
    btFrameLayout->addWidget(mBtCancel);
    btFrameLayout->addWidget(mBtProcess);
    btFrame->setLayout(btFrameLayout);

    mainLayout->addWidget(btFrame);

    setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mBtProcess->setFocus();
}

FrameRateDialog::~FrameRateDialog()
{
}

void FrameRateDialog::on_btProcess_triggered(){
    this->accept();
}
void FrameRateDialog::on_btCancel_triggered(){

    this->close();
}

int FrameRateDialog::getFrameRate(){
    return mImagesPerSecond->value();
}
