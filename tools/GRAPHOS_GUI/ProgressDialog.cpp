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
#include <QDebug>
#include <QFileDialog>
#include <QFile>

#include "ProgressDialog.h"
#include "ui_ProgressDialog.h"

ProgressDialog::ProgressDialog(QSettings *settings, QWidget *parent):
    QDialog(parent),
    mSettings(settings),
    ui(new Ui::ProgressDialog)
{
    this->setWindowFlags(this->windowFlags() & ~Qt::WindowContextHelpButtonHint);
    ui->setupUi(this);
    setWindowIcon(QIcon(":/PW/icons/img/GraphosIcon.png"));
    setRange(0,3);
    ui->pushButton_save->setVisible(false);
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

void ProgressDialog::setStatusText(QString text)
{
    ui->labelStatus->setText(text);
}

void ProgressDialog::setRange(int min, int max)
{
    ui->progressBar->setRange(min,max);
}

void ProgressDialog::setValue(int value)
{
    ui->progressBar->setValue(value);
}

void ProgressDialog::setProcess(PW::Process *process)
{
    mProcess = process;

    connect(process, SIGNAL(finished()),this,SLOT(onProcessFinished()));
    connect(process, SIGNAL(statusChanged(int,QString)),this,SLOT(onSatutsChanged(int,QString)));
    connect(process, SIGNAL(statusChangedNext()),this,SLOT(onSatutsChangedNext()));
    connect(process, SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
    connect(this,SIGNAL(cancel()),process,SLOT(stop()));
}

void ProgressDialog::setFinished(bool finished)
{
    if(finished){
        ui->pushButton->setText(tr("Close"));
        ui->pushButton_save->setVisible(true);
    }
    else{
        ui->pushButton->setText(tr("Cancel"));
        ui->pushButton_save->setVisible(false);
    }
}

void ProgressDialog::setConsole(QTextEdit *console)
{
    mConsole = console;
    ui->frame_console->layout()->addWidget(console);
}

void ProgressDialog::setConsoleVisible(bool visible)
{
    ui->frame_console->setVisible(visible);
}

void ProgressDialog::onSatutsChanged(int step, QString message)
{
    ui->progressBar->setValue(step);
    ui->labelStatus->setText(message);
}
void ProgressDialog::onSatutsChangedNext(){
    ui->progressBar->setValue(ui->progressBar->value()+1);
}

void ProgressDialog::on_pushButton_clicked()
{
    emit cancel();
    close();
}


void ProgressDialog::on_pushButton_save_clicked()
{
    QString initPath = mSettings->value("app/lastoutputpath").toString();
    if (initPath.isEmpty())
        initPath = QDir::homePath();

    QString savePath = QFileDialog::getSaveFileName(this,
                                                    tr("Text file"),
                                                    initPath,
                                                    trUtf8("(*.txt)"));

    if(!savePath.isEmpty()){
        QFile file(savePath);
        file.open(QFile::WriteOnly);
        file.write(mConsole->toPlainText().toAscii());

        QString outputPath = savePath.left(savePath.lastIndexOf(QRegExp("/"))+1);
        mSettings->setValue("app/lastoutputpath", outputPath);
    }

}
void ProgressDialog::writeinConsole(QString text){
    mConsole->append(text+"\n");
}
void ProgressDialog::clearConsole(){
    mConsole->clear();
}
