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
#ifndef SUBGRAPHSELECTOR_H
#define SUBGRAPHSELECTOR_H

#include <QDialog>
#include <QStringList>
#include "libPW.h"
#include <QButtonGroup>

class SubgraphSelector : public QDialog
{
    Q_OBJECT

public:
    explicit SubgraphSelector(QWidget *parent = 0,QList<QStringList> *subgraphs= new QList<QStringList>(),PW::Project *Project=0);
    ~SubgraphSelector();
    int getSubgraphIndex();
private:
    QList<QStringList> *mSubgraphs;
    QPushButton *mPbProccess;
    PW::Project *mProject;
    QButtonGroup *rbGroup;

private slots:
    void on_pbCancel_clicked();
    void on_pbProccess_clicked();

};

#endif // SUBGRAPHSELECTOR_H
