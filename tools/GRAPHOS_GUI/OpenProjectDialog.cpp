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
#include <QSqlTableModel>
#include <QItemSelectionModel>
#include <QMessageBox>

#include "OpenProjectDialog.h"
#include "ui_openprojectdialog.h"

using namespace PW;

OpenProjectDialog::OpenProjectDialog(PersistenceManager *pm, QWidget *parent, bool forSave) :
    QDialog(parent),
    ui(new Ui::OpenProjectDialog),
    mPm(pm),
    mForSave(forSave)

{
    ui->setupUi(this);

    QSqlDatabase *database = mPm->getDataBase();

    QSqlTableModel *model = new QSqlTableModel(this, *database);
    model->setTable("pw_projects");
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    connect(ui->tableView->selectionModel(),SIGNAL(selectionChanged(QItemSelection,QItemSelection)),this,SLOT(onSelectionChanged(QItemSelection,QItemSelection)));
}

OpenProjectDialog::~OpenProjectDialog()
{
    delete ui;
}

void OpenProjectDialog::on_buttonBox_accepted()
{
    if(mForSave){
        emit projectSelected(ui->lineEditName->text());
    }else
        if(ui->tableView->selectionModel()->hasSelection()){
            int row = ui->tableView->selectionModel()->selectedIndexes().at(0).row();
            QString projectName = ui->tableView->model()->data(ui->tableView->model()->index(row,1)).toString();
            emit projectSelected(projectName);
        }
}

void OpenProjectDialog::setNameVisible(bool visible)
{
    ui->lineEditName->setVisible(visible);
    ui->labelName->setVisible(visible);
}

void OpenProjectDialog::setProjectName(QString projectName)
{
    ui->lineEditName->setText(projectName);
}

void OpenProjectDialog::setForSave(bool forSave)
{
    mForSave = forSave;
}

void OpenProjectDialog::refreshData()
{
    QSqlTableModel *model = (QSqlTableModel*)ui->tableView->model();
    model->select();
}

void OpenProjectDialog::onSelectionChanged(QItemSelection selected, QItemSelection deselected)
{
    if(ui->tableView->selectionModel()->hasSelection()){
        int row = ui->tableView->selectionModel()->selectedIndexes().at(0).row();
        QString projectName = ui->tableView->model()->data(ui->tableView->model()->index(row,1)).toString();
        ui->lineEditName->setText(projectName);
    }
}

void OpenProjectDialog::on_pushButton_clicked()
{
    QSqlTableModel *model = ( QSqlTableModel *)ui->tableView->model();

    int ret = QMessageBox::warning(this, tr("Delete project"),
                                   tr("The project will be deleted permanently!!!\nDo you want to continue?"),
                                   QMessageBox::Yes | QMessageBox::No);
    switch (ret) {
    case QMessageBox::Yes:
        mPm->deleteProject(ui->lineEditName->text());
        model->select();
        break;
    case QMessageBox::No:
        break;
    default:
        break;
    }
}

void OpenProjectDialog::on_tableView_doubleClicked(const QModelIndex &index)
{
    if(ui->tableView->selectionModel()->hasSelection()){
        int row = ui->tableView->selectionModel()->selectedIndexes().at(0).row();
        QString projectName = ui->tableView->model()->data(ui->tableView->model()->index(row,1)).toString();
        emit projectSelected(projectName);
    }
//    close();
    accept();
}
