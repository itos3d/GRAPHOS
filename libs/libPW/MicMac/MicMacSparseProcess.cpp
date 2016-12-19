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
#include "MicMacSparseProcess.h"
#include "TapiocaProcess.h"
#include "TapasProcess.h"
#include "AperiCloudProcess.h"
#include "TapiocaWaitResults.h"
#include "TapiocaShProcess.h"

using namespace PW;

MicMacSparseProcess::MicMacSparseProcess(QString inputRegExp, QString imagesDir, QString mode,
                                         int range, int size, QString model, QString outputName, QString inCal)
{
    setStartupMessage("Computing orientations...");

    ExternalProcess *tapioca = new TapiocaProcess();
    QStringList inputs;
    if(mode == "File"){
        QString pairsFilePath = imagesDir + "MesCouples.xml";
        inputs << mode << pairsFilePath << QString::number(size);
    }
    else{
        inputs << mode << inputRegExp <<QString::number(size);
        if(mode=="Line")
            inputs << QString::number(range);
    }
    tapioca->addIntputs(inputs);

//    mProcessList.append(tapioca);
//    mProcessList.append(new TapasProcess());
    appendProcess(tapioca);
    appendProcess(new TapasProcess());
    QString distModel = model;
    if (model == tr("No Distortion"))
        distModel = "Figee";
    QStringList tapasInputs;
    tapasInputs <<distModel<<inputRegExp<<"Out="+outputName;
    if (model == tr("No Distortion"))
       tapasInputs << "InCal=NoDist";
    else if(!inCal.isEmpty())
        tapasInputs << "InCal=" + inCal;
    at(1)->addIntputs(tapasInputs);

//    mProcessList.append(new AperiCloudProcess());
    appendProcess(new AperiCloudProcess());
    at(2)->addIntputs(QStringList()<<inputRegExp<<outputName);
}


