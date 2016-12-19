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
#include "Process.h"

using namespace PW;

Process::Process() :
    mStopped(false)
{
}

void PW::Process::addIntputs(QStringList inputs)
{
    mInputs = inputs;
}

QString PW::Process::getStartupMessage()
{
    return mStartupMessage;
}

void PW::Process::setStartupMessage(QString message)
{
    mStartupMessage = message;
}

void PW::Process::stop()
{
    mStopped = true;
//    quit();
}

bool PW::Process::isStopped()
{
    return mStopped;
}

int Process::getSteps()
{
    return mSteps;
}

void Process::setSteps(int steps)
{
    mSteps = steps;
}
