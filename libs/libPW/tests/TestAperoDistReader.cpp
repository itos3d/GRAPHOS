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
#include <QtTest/QtTest>

#include "TestAperoDistReader.h"

using namespace PW;

void TestAperoDistReader::reading(){
    qDebug() << "Working dir:"+ QDir::currentPath();
    qDebug() << "Probando *************************************************";
//    QFile file("/home/dguerrero/desarrollo/USAL/Calibraciones/Apero/AutoCal170.xml");
    //qDebug() << file.fileName();
    Camera *camera = new Camera("Canon EOS 500D","",22.3,14.9);
    AperoModelReader reader(camera);
    CameraModel *cm = reader.read("/home/dguerrero/desarrollo/USAL/Calibraciones/Apero/AutoCal170.xml");
    bool readOk = (cm != NULL);
    qDebug() << "Probando *************************************************";
    QVERIFY(readOk);
}
