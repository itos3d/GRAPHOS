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
#include "DependencyInfoWidget.h"
#include <QVBoxLayout>
#include <QTextEdit>

DependencyInfoWidget::DependencyInfoWidget(QWidget *parent) :
    QWidget(parent)
{
}

DependencyInfoWidget::~DependencyInfoWidget()
{
}

DependencyInfoWidget::DependencyInfoWidget(QString license, QString Description, QString URL){
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setAlignment(Qt::AlignTop);
    mainLayout->addWidget(new QLabel("<strong>License: </strong>"+license));

    QLabel *lbUrl = new QLabel("<a href=\""+URL+"\">"+URL+"</a>");
    lbUrl->setTextFormat(Qt::RichText);
    lbUrl->setTextInteractionFlags(Qt::TextBrowserInteraction);
    lbUrl->setOpenExternalLinks(true);

    mainLayout->addWidget(lbUrl);
    QTextEdit *txtDescription = new QTextEdit(Description);
    txtDescription->setReadOnly(true);
    txtDescription->setContentsMargins(0,0,0,0);
    mainLayout->addWidget(txtDescription);
    setLayout(mainLayout);
}
