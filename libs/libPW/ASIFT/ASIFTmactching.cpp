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
#include "ASIFTmactching.h"
#include "libPW.h"

using namespace  PW;

ASIFTmactching::ASIFTmactching(QString input1, QString input2,
                               QString outputV, QString outputH,
                               QString outputMatch,
                               QString keys1, QString keys2, bool generateImages):
     ExternalProcess(LibPW::getAsiftBinPath() + "/" + ASIFT_MATCHING_COMMAND)
{
    setStartupMessage("Computing ASIFT matching...");
    setStdOutputFilePath(LibPW::getStdErrorPath() + "/AsiftMatching.log");
    setStdErrorFilePath(LibPW::getStdErrorPath() + "/AsiftMatchingError.log");

    QStringList args;
    args.append(input1);
    args.append(input2);

    args.append(outputV);

    args.append(outputH);

    args.append(outputMatch);
    if(keys1.isEmpty())
        args.append(input1 + ".keys");
    else
        args.append(keys1);
    if(keys2.isEmpty())
        args.append(input2 + ".keys");
    else
        args.append(keys2);

    if(generateImages)
        args.append("1");
    else
        args.append("0");

    addIntputs(args);
}
