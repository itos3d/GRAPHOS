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
#include "CustomSureProcess.h"
#include "libPW.h"
#include "Apero2SureProcess.h"
#include "MicMac/DrunkProcess.h"
#include "SURE/SUREProcess.h"
#include "SURE/MergeLasResultsProcess.h"
#include <QDir>

using namespace PW;

CustomSureProcess::CustomSureProcess(Project *project, int pyr,int fold, int maxModels, bool useGPU):
    mProject(project),
    mPyr(pyr),
    mFold(fold),
    mMaxModels(maxModels),
    mUseGPU(useGPU)
{
    setStartupMessage("SURE densification...");
    //apero2SURE
    QDir aperoOriDir(mProject->getBasePath()+"/Ori-"+mProject->getCurrentOrientation());
    appendProcess(new PW::Apero2SureProcess(aperoOriDir.absolutePath()));

    //DRUNK
    QString drunkInputRegExp = QString("(");
    QString fileName;
    for(int i=0; i< mProject->getImages().count(); i++){
        fileName = mProject->getImages().at(i)->getFullPath();
        fileName = fileName.right(fileName.length()-fileName.lastIndexOf(QRegExp("/"))-1);
        drunkInputRegExp = drunkInputRegExp + fileName + QString("|");
    }
    drunkInputRegExp.replace(drunkInputRegExp.length()-1,1,")");
    drunkInputRegExp =mProject->getBasePath()+"/"+drunkInputRegExp;
    QDir drunkImagesPath =mProject->getBasePath()+"/DRUNK";
    PW::DrunkProcess *mDrunkProcess = new PW::DrunkProcess(drunkInputRegExp,mProject->getCurrentOrientation());
    mDrunkProcess->setWorkingDir(mProject->getBasePath());
    appendProcess(mDrunkProcess);
    //Sure prep process
    QString prjPath =mProject->getBasePath()+"/Ori-"+ mProject->getCurrentOrientation()+"/conversion.prj";
    QFileInfo prjFileInfo(prjPath);
    SUREProcess *mSureProcess = new PW::SUREProcess(prjFileInfo.absoluteFilePath(),drunkImagesPath.absolutePath(),mPyr,mFold,mMaxModels,mUseGPU);
//    mSureProcess->setWorkingDir(LibPW::getSUREBinPath());
    mSureProcess->setWorkingDir(mProject->getBasePath());
    appendProcess(mSureProcess);
}

CustomSureProcess::~CustomSureProcess()
{

}

