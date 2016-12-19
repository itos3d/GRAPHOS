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
#ifndef NEWPROJECTDIALOG_H
#define NEWPROJECTDIALOG_H

#include <QDialog>
#include <QString>
#include <QList>
#include "Project.h"
#include <QTextEdit>
#include <QLineEdit>

namespace Ui {
class NewProjectDialog;
}

class NewProjectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NewProjectDialog(QWidget *parent = 0, PW::Project *project = 0, QStringList *projectsNames=new QStringList());
    ~NewProjectDialog();
//    int getResult();

private:
    Ui::NewProjectDialog *ui;
//    QString mProjectPath, mPathText;
    PW::Project *mProject;
    QStringList *mProjectsNames;
    QLineEdit *txtProjectName;
    QTextEdit *txtProjectDescription;
    QLineEdit *txtPath;

signals:
    void newProjectFinished();

private slots:
    void on_btNext1Trigered();
    void on_btCancelTrigered();
//    void on_btSearchPathTrigered();
//    void on_txtProjectNameTextChanged();
};

#endif // NEWPROJECTDIALOG_H
