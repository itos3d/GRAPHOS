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
#include "TestCalculateImagePoints.h"
#include "Project.h"
#include "PhotogrammetricModel.h"
#include "ExternalOrientation.h"
#include "MicMac/AperoModelReader.h"
#include "MicMac/MicMacEOReader.h"
#include "Camera.h"
#include "PW2dPoint.h"


void TestCalculateImagePoints::calculate()
{
    PW::Project project;
    PW::Camera camera("Canon","", 4752, 3168);
    PW::AperoModelReader pmReader(&camera);
    PW::MicMacEOReader extReader;
    PW::PhotogrammetricModel * pm = pmReader.read("/home/dguerrero/desarrollo/USAL/PW/PW/testData/TestCalculateImagePoints/Calib.xml");
    PW::ExteriorOrientation * ext = extReader.read("/home/dguerrero/desarrollo/USAL/PW/PW/testData/TestCalculateImagePoints/Orientation-IMG_Canon_0001.tif.xml");

    QList <PW::PW3dPoint *> inputPoints;
    QList <PW::PW2dPoint *> outputPoints;

    inputPoints.append(new PW::PW3dPoint(1005.01821768340767, 1004.49484999428751, 101.539394144144936));
    inputPoints.append(new PW::PW3dPoint(1005.30851714132086, 1010.26249297799063, 98.3758629693027586));
    inputPoints.append(new PW::PW3dPoint(1001.64881871413832, 1013.73203368004738, 97.6447707373463061));

    project.calculateImagePoints(&inputPoints,pm, ext,&outputPoints);
}
