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
#include <QDebug>

#include "TapiocaWaitResults.h"

using namespace PW;

TapiocaWaitResults::TapiocaWaitResults(QString homolPath, int imagesCount):
    mImagesCount(imagesCount),
    mHomolPath(homolPath),
    mStop(false)
{
    setStartupMessage(tr("Waiting for Tapioca results..."));
    mFileWatcher = new QFileSystemWatcher();
}

TapiocaWaitResults::~TapiocaWaitResults(){
    delete mFileWatcher;
}

void PW::TapiocaWaitResults::run()
{
    //Watch all subdirs into homol dir:
    QDir homolDir(mHomolPath);
    if (homolDir.exists()){
        if(mImagesCount == 0)
            mImagesCount = homolDir.entryList().count() - 2; // . and ..
        mCounter = 0;
        for (int i = 0; i < homolDir.entryList().count(); i++){
            if (homolDir.entryList().at(i) != "." && homolDir.entryList().at(i) != ".."){
                mFileWatcher->addPath(mHomolPath + "/" + homolDir.entryList().at(i));
                QDir homolChild(mHomolPath + "/" + homolDir.entryList().at(i));
                if (homolChild.entryList().count() >= (mImagesCount - 2))
                        mCounter++;
            }
            //Check if results finished already:
            if (mCounter == mImagesCount)
                mStop = true;
        }
    }

    connect(mFileWatcher,SIGNAL(directoryChanged(QString)), this, SLOT(onElementChange(QString)));
    while (!mStop);
}

void PW::TapiocaWaitResults::onElementChange(QString path)
{
    //Watch all subdirs into homol dir:
    QDir homolDir(mHomolPath);
    if (homolDir.exists()){
        mCounter = 0;
        for (int i = 0; i < homolDir.entryList().count(); i++){
            if (homolDir.entryList().at(i) != "." && homolDir.entryList().at(i) != ".."){
                QDir homolChild(mHomolPath + "/" + homolDir.entryList().at(i));
                if (homolChild.entryList().count() >= (mImagesCount - 2))
                        mCounter++;
            }
            //Check if results finished.
            if (mCounter == mImagesCount)
                mStop = true;
        }
    }
}
