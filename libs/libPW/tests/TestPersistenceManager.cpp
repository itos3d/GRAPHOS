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
#include <QDir>
#include <QtTest/QtTest>

#include "TestPersistenceManager.h"
#include "Project.h"
#include "PersistenceManager.h"
#include "libPW.h"

using namespace PW;

TestPersistenceManager::TestPersistenceManager(QObject *parent) :
    QObject(parent)
{
//    LibPW::setPersistencePath(QDir::currentPath()+ "/pw_data.sqlite");
}

void TestPersistenceManager::writeProject()
{
    Project project;
    project.setName("project1");
    project.setDescription("Un proyecto");
//    project.setSparseModelPath("/home/dguerrero/desarrollo/USAL/PW/testData/SanSegundoCanon");
//    project.setDenseModelPath("/home/dguerrero/desarrollo/USAL/PW/testData/SanSegundoCanon");

//    project.getModelCPoints()->append(new PW3dPoint(10,20,30));

    project.addImputImages(QStringList() << "/home/dguerrero/desarrollo/USAL/PW/testData/SanSegundoCanon/IMG_7209.jpg" <<
                           "/home/dguerrero/desarrollo/USAL/PW/testData/SanSegundoCanon/IMG_7210.jpg" <<
                           "/home/dguerrero/desarrollo/USAL/PW/testData/SanSegundoCanon/IMG_7211.jpg" <<
                           "/home/dguerrero/desarrollo/USAL/PW/testData/SanSegundoCanon/IMG_7212.jpg");

    Camera *camera = new Camera("Canon", "",17,10);
    for (int i=0; i<project.getImages().count(); i++){
        project.getImages().at(i)->setCamera(camera);
//        project.getImages().at(i)->getControlPoints()->append(new PW2dPoint(100,500));
    }

//    project.readOrientations("/home/dguerrero/desarrollo/USAL/PW/testData/SanSegundoCanon/Ori-RadialExtended");

    PersistenceManager persistenceManager(QDir::currentPath()+ "/pw_data.sqlite");
    persistenceManager.openDatasource();
    int error = persistenceManager.writeProject(&project);
//    int error = LibPW::getPersistenceManager()->writeProject(&project);

    QVERIFY(error==0);
}

void TestPersistenceManager::readProject()
{
    PersistenceManager persistenceManager(QDir::currentPath()+ "/pw_data.sqlite");
    persistenceManager.openDatasource();
//    Project *project = LibPW::getPersistenceManager()->readProject("project1");
    Project *project = persistenceManager.readProject("project1");


    QVERIFY(true);
}
