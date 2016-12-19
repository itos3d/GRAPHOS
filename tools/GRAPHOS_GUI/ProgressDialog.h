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
#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QTextEdit>

#include "Process.h"

namespace Ui {
    class ProgressDialog;
}

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QSettings *settings, QWidget *parent = 0);
    ~ProgressDialog();

    void setStatusText(QString text);
    void setRange(int min, int max);
    void setValue(int value);
    void setProcess(PW::Process *process);
    void setFinished(bool finished);
    void setConsole(QTextEdit *console);
    void setConsoleVisible(bool visible);
    void writeinConsole(QString text);
    void clearConsole();
public slots:
    void onSatutsChanged(int step, QString message);
    void onSatutsChangedNext();

private slots:
    void on_pushButton_clicked();


    void on_pushButton_save_clicked();

private:
    Ui::ProgressDialog *ui;
    PW::Process *mProcess;
    QSettings * mSettings;
    QTextEdit *mConsole;

signals:
    void cancel();
};

#endif // PROGRESSDIALOG_H
