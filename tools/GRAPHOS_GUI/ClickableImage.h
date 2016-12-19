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
#ifndef CLICKABLEIMAGE_H_
#define CLICKABLEIMAGE_H_
#include <QLabel>
#include <QMouseEvent>

using namespace Qt;

class ClickableImage:public QLabel
{
    Q_OBJECT
public:
    ClickableImage(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *eve );
    void mouseReleaseEvent(QMouseEvent *eve );
    void enterEvent(QEvent* eve );
    void leaveEvent(QEvent* eve );

signals:
    void leftButtonPressed(ClickableImage* sender);
    void rightButtonPressed(ClickableImage* sender);
    void middleButtonPressed(ClickableImage* sender);
    void leftButtonReleased(ClickableImage* sender);
    void rightButtonReleased(ClickableImage* sender);
    void middleButtonReleased(ClickableImage* sender);
    void mouseEntered(ClickableImage* sender );
    void mouseLeft(ClickableImage* sender);
};

#endif /*CLICKABLEIMAGE_H_*/
