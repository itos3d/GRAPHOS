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
#include "NewGCPDialog.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QDoubleValidator>
#include <QPushButton>
NewGCPDialog::NewGCPDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    setWindowTitle("New GCP");
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(new QLabel("New GCP:"));

    QFrame *valuesFrame = new QFrame();
    QHBoxLayout *valuesFrameLayout = new QHBoxLayout();

    mGCP_Name = new QLineEdit();
    mGCP_x = new QLineEdit();
    mGCP_x->setValidator(new QDoubleValidator());
    mGCP_y = new QLineEdit();
    mGCP_y->setValidator(new QDoubleValidator());
    mGCP_z = new QLineEdit();
    mGCP_z->setValidator(new QDoubleValidator());
    valuesFrameLayout->addWidget(new QLabel("Name: "));
    valuesFrameLayout->addWidget(mGCP_Name);
    valuesFrameLayout->addWidget(new QLabel("X: "));
    valuesFrameLayout->addWidget(mGCP_x);
    valuesFrameLayout->addWidget(new QLabel("Y: "));
    valuesFrameLayout->addWidget(mGCP_y);
    valuesFrameLayout->addWidget(new QLabel("Z: "));
    valuesFrameLayout->addWidget(mGCP_z);
    valuesFrame->setLayout(valuesFrameLayout);

    QFrame *btFrame = new QFrame();
    QHBoxLayout *btFrameLayout = new QHBoxLayout();
    btFrameLayout->setAlignment(Qt::AlignRight);
    mBtCancel= new QPushButton("Cancel");
    connect(mBtCancel,SIGNAL(clicked()),this,SLOT(on_btCancel_triggered()));
    mBtAdd=new QPushButton("Add");
    connect(mBtAdd,SIGNAL(clicked()),this,SLOT(on_btAdd_triggered()));
    btFrameLayout->addWidget(mBtCancel);
    btFrameLayout->addWidget(mBtAdd);
    btFrame->setLayout(btFrameLayout);

    mainLayout->addWidget(valuesFrame);
    mainLayout->addWidget(btFrame);

    setLayout(mainLayout);
    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    mBtAdd->setFocus();
}

NewGCPDialog::~NewGCPDialog()
{
}

void NewGCPDialog::on_btAdd_triggered(){
    this->accept();
}
void NewGCPDialog::on_btCancel_triggered(){
    this->close();
}
QString NewGCPDialog::getGCPName(){
    return mGCP_Name->text();
}
double NewGCPDialog::getGCPx(){
    return mGCP_x->text().toDouble();
}
double NewGCPDialog::getGCPy(){
    return mGCP_y->text().toDouble();
}
double NewGCPDialog::getGCPz(){
    return mGCP_z->text().toDouble();
}
