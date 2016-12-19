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
#ifndef TAPIOCAWAITRESULTS_H
#define TAPIOCAWAITRESULTS_H

#include <QFileSystemWatcher>
#include <QStringList>
#include <QMap>

#include "Process.h"

namespace PW{

class LIBPWSHARED_EXPORT TapiocaWaitResults : public Process
{
    Q_OBJECT

public:
    TapiocaWaitResults(QString homolPath, int imagesCount = 0);
    ~TapiocaWaitResults();

protected:
    void run();

public slots:
    virtual void onElementChange(QString path);

private:
    int mImagesCount;
    QString mHomolPath;
    QFileSystemWatcher *mFileWatcher;
    QStringList mElementList;
    QStringList mElementChanged;
    long mOffset;
    bool mStop;
    QMap<QString, bool> mCompleted;
    int mCounter;
};
}

#endif // TAPIOCAWAITRESULTS_H
