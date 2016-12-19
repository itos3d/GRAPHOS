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
#include <QFile>

#include "WaitForResultsProcess.h"

using namespace PW;

WaitForResultsProcess::WaitForResultsProcess(QStringList pathList, WatcherModeFlag watcherMode):
    mElementList(pathList),
    mStop(false)
{
    mFileWatcher = new QFileSystemWatcher();

    //Monitorizamos los directorios:
    for (int i = 0; i < mElementList.size(); i++){
        if (QFile::exists(mElementList.at(i)))
            mElementChanged.append(mElementList.at(i));
        mFileWatcher->addPath(mElementList.at(0).left(mElementList.at(0).lastIndexOf(QRegExp("/"))+1));
    }

    if (mElementChanged.count() >= mElementList.count()){
        mStop = true;
    }

    connect(mFileWatcher,SIGNAL(directoryChanged(QString)),this,SLOT(onElementChange(QString)));
}

QByteArray WaitForResultsProcess::readStdout()
{
    return "";
}

QByteArray WaitForResultsProcess::readStderr()
{
    return "";
}

// SOLO IMPLEMENTADO EN MODO "Create" ****************************************************
void WaitForResultsProcess::onElementChange(QString path)
{
    for (int i = 0; i < mElementList.size(); i++){
        if (QFile::exists(mElementList.at(i)))
            mElementChanged.append(mElementList.at(i));
    }

    if (mElementChanged.count() >= mElementList.count()){
        mStop = true;
    }
}

void PW::WaitForResultsProcess::run()
{
    while (!mStop);
}


void WaitForResultsProcess::start()
{
    run();
}

void WaitForResultsProcess::setWaitForFinished(bool wait)
{
}

bool WaitForResultsProcess::isRunning()
{
    return false;
}
