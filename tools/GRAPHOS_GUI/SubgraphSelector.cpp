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
#include "SubgraphSelector.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QListWidget>
#include <QPixmap>
#include <QListWidgetItem>
#include <QMessageBox>



SubgraphSelector::SubgraphSelector(QWidget *parent,QList<QStringList> *subgraphs,PW::Project *Project) :
    QDialog(parent),
    mSubgraphs(subgraphs),
    mProject(Project)
{
    setWindowTitle("Disconnected graph for current dataset");
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    setFixedSize(800,600);
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(new QLabel("Select subgraph to process:"));

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QGroupBox *scrollAreaContent = new QGroupBox();
    rbGroup= new QButtonGroup();
    QGridLayout *scrollAreaContentLayout = new QGridLayout();
    //RenameImagePairs to original image extension if preprocesing methods were used.

    for (int i = 0; i < mSubgraphs->count(); ++i) {

        //Parse subgraph and add items
        QStringList subgraphItems = mSubgraphs->at(i);

        QRadioButton *rbSubgraph = new QRadioButton();
        scrollAreaContentLayout->addWidget(rbSubgraph,i,0);
        rbGroup->addButton(rbSubgraph,i);
        QListWidget *subgraphImagesList = new QListWidget();


        subgraphImagesList->setStyleSheet("border: 0px;");
        subgraphImagesList->setViewMode(QListWidget::IconMode );
        subgraphImagesList->setIconSize(QSize(100,100));
        subgraphImagesList->setResizeMode(QListWidget::Adjust);

        for (int j = 0; j < subgraphItems.count(); ++j) {
            QString subgraphItem=subgraphItems.at(j);
            QFileInfo iconPath(mProject->getBasePath()+"/"+subgraphItem);
            QListWidgetItem *listItem= new QListWidgetItem(QIcon(iconPath.absoluteFilePath()),iconPath.fileName());
            subgraphImagesList->addItem(listItem);
        }
        subgraphImagesList->setDragDropMode(QAbstractItemView::NoDragDrop);
        scrollAreaContentLayout->addWidget(subgraphImagesList,i,1);
   }
    rbGroup->buttons().first()->setChecked(true);
    scrollAreaContent->setLayout(scrollAreaContentLayout);
    scrollArea->setWidget(scrollAreaContent);
    mainLayout->addWidget(scrollArea);
    //Botones de navegación
    QFrame *navigationButtonsFrame = new QFrame();
    QHBoxLayout *navigationButtonsFrameLayout = new QHBoxLayout();
    navigationButtonsFrameLayout->setAlignment(Qt::AlignRight);

    navigationButtonsFrameLayout->addStretch(1);


    mPbProccess = new QPushButton("Process");
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
    mPbProccess->setFocus();
}

SubgraphSelector::~SubgraphSelector()
{
}
void SubgraphSelector::on_pbCancel_clicked(){
    this->close();
}

void SubgraphSelector::on_pbProccess_clicked(){
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Warning!");
    msgBox.setText("This action will remove the images outside the selected subgraph from the project.");
    msgBox.setInformativeText("Do you want to continue?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    int ret=QMessageBox::Ok;
    ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Ok:
        this->accept();

        break;
    case QMessageBox::Cancel:
        msgBox.close();
        break;

    }

}
int SubgraphSelector::getSubgraphIndex(){
    return rbGroup->checkedId();
}
