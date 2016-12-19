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
#ifndef WAITFORRESULTSPROCESS_H
#define WAITFORRESULTSPROCESS_H

#include <QFileSystemWatcher>

#include "Process.h"

namespace PW{

class LIBPWSHARED_EXPORT WaitForResultsProcess : public Process
{
    Q_OBJECT

public:
    virtual void start();
    virtual void setWaitForFinished(bool wait);
    virtual bool isRunning();

    enum WatcherModeFlag {
        Create = 0x0000,
        Change = 0x0001
    };

    WaitForResultsProcess(QStringList pathList, WatcherModeFlag watcherMode);

    virtual QByteArray readStdout();
    virtual QByteArray readStderr();

protected:
    void run();

    QFileSystemWatcher *mFileWatcher;
    QStringList mElementList;
    QStringList mElementChanged;
    long mOffset;
    bool mStop;


public slots:
    virtual void onElementChange(QString path);


};
}

#endif // WAITFORRESULTSPROCESS_H
