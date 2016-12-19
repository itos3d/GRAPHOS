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
#include "NewProjectDialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
NewProjectDialog::NewProjectDialog(QWidget *parent, PW::Project *project,QStringList *projectsNames) :
    QDialog(parent),
    mProject(project),
    mProjectsNames(projectsNames)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);

    setWindowTitle("New project");
    setMaximumSize(600,300);
    setMinimumSize(600,300);


    QVBoxLayout *mainLayout = new QVBoxLayout();

    mainLayout->addWidget(new QLabel("Project name:"));
    txtProjectName = new QLineEdit();
    txtProjectName->resize(txtProjectName->width(),20);
    mainLayout->addWidget(txtProjectName);

    mainLayout->addWidget(new QLabel("Project description:"));
    txtProjectDescription = new QTextEdit();
    mainLayout->addWidget(txtProjectDescription);

    QFrame *btFrame = new QFrame();
    QHBoxLayout *btFrameLayout = new QHBoxLayout();
    btFrameLayout->setMargin(0);
    btFrameLayout->setAlignment(Qt::AlignRight);
    QPushButton *pbNext1 = new QPushButton("Next");
    QPushButton *pbCancel = new QPushButton("Cancel");
    btFrameLayout->addWidget(pbCancel);
    btFrameLayout->addWidget(pbNext1);
    btFrame->setLayout(btFrameLayout);

    mainLayout->addWidget(btFrame);

    this->setLayout(mainLayout);
    connect(txtProjectName,SIGNAL(textChanged()),this,SLOT(on_txtProjectNameTextChanged()));
    connect(pbCancel,SIGNAL(clicked()),this,SLOT(on_btCancelTrigered()));
    connect(pbNext1,SIGNAL(clicked()),this,SLOT(on_btNext1Trigered()));
    pbNext1->setDefault(true);
    pbNext1->setDefault(true);
}

NewProjectDialog::~NewProjectDialog()
{
    delete ui;
}


void NewProjectDialog::on_btNext1Trigered(){
    if (txtProjectName->text().count()==0) {
        QMessageBox msgBox;
        msgBox.setText("Type a name for your project to proceed.");
        msgBox.exec();
        return;
    }
    if (mProjectsNames->contains(txtProjectName->text())) {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle("GRAPHOS");
        msgBox.setText("The project \""+txtProjectName->text()+"\" already exists in the database.");
        msgBox.exec();
        return;
    }
    mProject->setName(txtProjectName->text());
    mProject->setDescription(txtProjectDescription->toPlainText());
    this->accept();

}

void NewProjectDialog::on_btCancelTrigered(){
    this->close();
}

