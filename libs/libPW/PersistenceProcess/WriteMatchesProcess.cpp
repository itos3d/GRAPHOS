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
#include "WriteMatchesProcess.h"

using namespace PW;

WriteMatchesProcess::WriteMatchesProcess(PersistenceManager *persistenceManager,
                                         Project *project,
                                         QString tiePointsMetadata,
                                         QString tiePointsDescription,
                                         QString timeCalculation,
                                         QString tiePointsPath):
    mProject(project),
    mTiePointsMetadata(tiePointsMetadata),
    mTiePointsDescription(tiePointsDescription),
    mTimeCalculation(timeCalculation),
    mTiePointsPath(tiePointsPath),
    mPersistenceManager(persistenceManager)
{
}

void WriteMatchesProcess::run()
{

    mPersistenceManager->writeMatches(mProject,mTiePointsMetadata,mTiePointsDescription,mTimeCalculation,mTiePointsPath);

}
