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
#ifndef SCALEMODELDIALOG_H
#define SCALEMODELDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QToolButton>

class ScaleModelDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScaleModelDialog(QWidget *parent = 0);
    ~ScaleModelDialog();
    double getScalex();
    double getScaley();
    double getScalez();
    void setObjectDistance(float distance);
    double getDistanceReality();
    double getDistanceObject();
    int getScaleMethod();

signals:
    void readDistanceToScale();
private:
    QLineEdit *mScale_x,*mScale_y,*mScale_z,*mDistanceObject,*mDistanceReality;
    QPushButton *mBtProcess,*mBtCancel;
    QToolButton *btDistanceTool;
    QFrame *mObjectDistanceFrame, *mRealityDistanceFrame, *mScaleValuesFrame;
    int mscaleMethod;
private slots:
    void on_btProcess_triggered();
    void on_btCancel_triggered();
    void on_btDistance_triggered();
    void on_writeInMethod1(QString text);
    void on_writeInMethod2(QString text);

};

#endif // SCALEMODELDIALOG_H
