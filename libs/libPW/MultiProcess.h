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
#ifndef MULTIPROCESS_H
#define MULTIPROCESS_H

#include <QList>

#include "Process.h"

namespace PW{
class LIBPWSHARED_EXPORT MultiProcess : public Process
{

    Q_OBJECT

public:
    MultiProcess();
    MultiProcess(bool isSequential);
    ~MultiProcess();

    virtual void start();
    virtual void setWaitForFinished(bool wait);
    virtual bool isRunning();

    virtual QByteArray readStdout();
    virtual QByteArray readStderr();

    void appendProcess(Process *process);
    void appendProcess(QList<Process*> processList);
    void clearProcessList();
    int count();
    Process * at(int i);

    virtual int getSteps();

public slots:
    virtual void stop();

protected:
    void run();

private:
    QList<Process*> mProcessList;
    bool mIsSequential;
    int mCurrentProcess;
    int mRunningCount;
    int mIdealThreadCount;
    int mFinishedCount;
    int mCurrentStep;
    bool mConcatenateMessages;
    bool mWaitForFinished;

private slots:
    void onError(int code, QString cause);
    void onAProcessFinished();
    void OnChildStatusChanged(int step, QString childMessage);
    void OnChildStatusChangedNext();
};
}

#endif // MULTIPROCESS_H
