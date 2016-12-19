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
#include <QDebug>

#include "AsiftToPastisProcess.h"
#include "AsiftMatchingIO.h"
#include "MicMac/TapiocaIO.h"

using namespace PW;

AsiftToPastisProcess::AsiftToPastisProcess(QString inputMatching, QString outputMatching, QString reversePath):
    mInputMatching(inputMatching),
    mOutputMatching(outputMatching),
    mReversePath(reversePath)
{
    setSteps(1);
}

void AsiftToPastisProcess::start()
{
    run();
}

void AsiftToPastisProcess::setWaitForFinished(bool wait)
{
}

bool AsiftToPastisProcess::isRunning()
{
    return false;
}

void AsiftToPastisProcess::run()
{
    AsiftMatchingIO asiftReader;
    QMap<QString, QPointF> matching;
    QMap<QString, QPointF> inverseMatching;
    if(mReversePath.isEmpty())
        asiftReader.read(mInputMatching, &matching);
    else
        asiftReader.read(mInputMatching, &matching, &inverseMatching);

    TapiocaIO aperoWriter;
    aperoWriter.write(&matching, mOutputMatching);
    if(!mReversePath.isEmpty())
        aperoWriter.write(&inverseMatching, mReversePath);
    emit statusChanged(1,getStartupMessage());
    qDebug() << QString(" ************** Finishing: ASIFT2Pastis");
    emit finished();
}

QByteArray AsiftToPastisProcess::readStdout()
{
    QByteArray b;
    return b;
}

QByteArray AsiftToPastisProcess::readStderr()
{
    QByteArray b;
    return b;
}
