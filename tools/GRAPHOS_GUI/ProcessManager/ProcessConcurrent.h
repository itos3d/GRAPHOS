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
#ifndef PROCESSCONCURRENT_H
#define PROCESSCONCURRENT_H

#include <QFutureWatcher>
#include "Process.h"
#include "opencv/cv.hpp"
class  ProcessConcurrent : public Process
{   
    Q_OBJECT

public:
    ProcessConcurrent();

    virtual void start();
    virtual void setWaitForFinished(bool wait);
    virtual bool isRunning();

    virtual QByteArray readStdout();
    virtual QByteArray readStderr();

public slots:
    virtual void stop();
    void on_mProcessFinished();

protected:
    virtual void run()=0;
    int runLauncher();

private:
    bool mRunning;
    QFutureWatcher<int> *mWatcher;
    bool mWait;

};

//template <class T>
//class ProcessConcurrentList : public Process
//{
//public:

//    ProcessConcurrentList(QVector<T> v);
//    ~ProcessConcurrentList();

//    virtual void ProcessConcurrentList::run();

//protected:
//    //template <class T> virtual int run();
//    QVector<T> mVector;

//private:
//    bool mRunning;
//    QFutureWatcher<int> *mWatcher;
//};


#endif // PROCESSCONCURRENT_H
