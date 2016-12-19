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
#include "MultiProcess.h"
#include <QDebug>



MultiProcess::MultiProcess():
    mIsSequential(true),
    mCurrentProcess(-1),
    mRunningCount(0),
    mWaitForFinished(false)
{
    setSteps(0);
}

MultiProcess::MultiProcess(bool isSequential):
    mIsSequential(isSequential),
    mRunningCount(0),
    mWaitForFinished(false)
{
    setSteps(0);
}

MultiProcess::~MultiProcess(){
    for (int i=0; i<mProcessList.count(); i++)
        delete mProcessList.at(i);
}

void MultiProcess::start()
{
    if (!isRunning())
        run();
}

void MultiProcess::setWaitForFinished(bool wait)
{
    mWaitForFinished = wait;
}

bool MultiProcess::isRunning()
{
    return (mRunningCount > 0);
}

QByteArray MultiProcess::readStdout()
{
    if(mIsSequential && mCurrentProcess >= 0)
        return mProcessList.at(mCurrentProcess)->readStdout();
    else
        return "";
}

QByteArray MultiProcess::readStderr()
{
    if(mIsSequential && mCurrentProcess >= 0)
        return mProcessList.at(mCurrentProcess)->readStderr();
    else
        return "";
}

void MultiProcess::appendProcess(Process *process)
{
    mProcessList.append(process);
    connect(process,SIGNAL(readyReadStandardOutput()),this, SIGNAL(readyReadStandardOutput()));
    connect(process,SIGNAL(readyReadStandardError()),this, SIGNAL(readyReadStandardError()));
    connect(process,SIGNAL(newStdData(QString)),this, SIGNAL(newStdData(QString)));
    connect(process,SIGNAL(newErrorData(QString)),this, SIGNAL(newErrorData(QString)));
    connect(process,SIGNAL(statusChanged(int,QString)),this, SLOT(OnChildStatusChanged(int,QString)));
    connect(process,SIGNAL(statusChangedNext()),this, SLOT(OnChildStatusChangedNext()));
    setSteps(getSteps() + process->getSteps());
}

void MultiProcess::appendProcess(QList<Process*> processList){
    mProcessList.append(processList);
    for(int i=0; i< processList.count();i++){
        connect(processList.at(i),SIGNAL(readyReadStandardOutput()),this, SIGNAL(readyReadStandardOutput()));
        connect(processList.at(i),SIGNAL(readyReadStandardError()),this, SIGNAL(readyReadStandardError()));
        connect(processList.at(i),SIGNAL(newStdData(QString)),this, SIGNAL(newStdData(QString)));
        connect(processList.at(i),SIGNAL(newErrorData(QString)),this, SIGNAL(newErrorData(QString)));
        connect(processList.at(i),SIGNAL(statusChanged(int,QString)),this, SLOT(OnChildStatusChanged(int,QString)));
        connect(processList.at(i),SIGNAL(statusChangedNext()),this, SLOT(OnChildStatusChangedNext()));
        setSteps(getSteps() +processList.at(i)->getSteps());
    }
}

void MultiProcess::clearProcessList()
{
    for(int i=0; i< mProcessList.count();i++){
        disconnect(mProcessList.at(i),SIGNAL(readyReadStandardOutput()),this, SIGNAL(readyReadStandardOutput()));
        disconnect(mProcessList.at(i),SIGNAL(readyReadStandardError()),this, SIGNAL(readyReadStandardError()));
        disconnect(mProcessList.at(i),SIGNAL(newStdData(QString)),this, SIGNAL(newStdData(QString)));
        disconnect(mProcessList.at(i),SIGNAL(newErrorData(QString)),this, SIGNAL(newErrorData(QString)));
        disconnect(mProcessList.at(i),SIGNAL(statusChanged(int,QString)),this, SIGNAL(OnChildStatusChanged(int,QString)));
        disconnect(mProcessList.at(i),SIGNAL(statusChangedNext()),this, SLOT(OnChildStatusChangedNext()));

    }
    mProcessList.clear();
    setSteps(0);
}

void MultiProcess::run()
{
    mFinishedCount=0;
    mCurrentStep=0;
    mStopped = false;
    mIdealThreadCount = QThread::idealThreadCount();
    int initialLaunchs = mIdealThreadCount;
    if (mProcessList.size()<mIdealThreadCount)
        initialLaunchs = mProcessList.size();
    if(!mIsSequential){
        for(int i=0 ; i<initialLaunchs; i++){
            if(!mStopped ){
                connect(mProcessList.at(i),SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
                connect(mProcessList.at(i),SIGNAL(finished()),this,SLOT(onAProcessFinished()));
                mProcessList.at(i)->start();
                if(mWaitForFinished && i==initialLaunchs-1)
                    mProcessList.at(i)->setWaitForFinished(true);
                mRunningCount++;
                mCurrentProcess = i;
            }
        }
    }
    else{
        if(mProcessList.size() > 0){
            mCurrentProcess = 0;
            connect(mProcessList.at(0),SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
            connect(mProcessList.at(0),SIGNAL(finished()),this,SLOT(onAProcessFinished()));
            mProcessList.at(0)->start();
            if(mWaitForFinished && mProcessList.size()==1)
                mProcessList.at(0)->setWaitForFinished(true);
        }
    }
}

//void PW::MultiProcess::run()
//{
//    mFinishedCount=0;
//    mCurrentStep=0;
//    mStopped = false;
//    mIdealThreadCount = QThread::idealThreadCount();
//    for(int i=0 ; i<mProcessList.count(); i++){
//        if(!mStopped){
//            mCurrentProcess = i;
////            emit statusChanged(i,mProcessList.at(i)->getStartupMessage());
//            connect(mProcessList.at(i),SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
//            connect(mProcessList.at(i),SIGNAL(finished()),this,SLOT(onAProcessFinished()));
//            mProcessList.at(i)->start();
//            if(mIsSequential)
//                mProcessList.at(i)->wait();
//            else{
//                mRunningCount++;
//                if(mRunningCount >= mIdealThreadCount || i == (mProcessList.size()-1))
//                    mProcessList.at(i)->wait();
//                mCurrentProcess = -1;
//            }
//        }
//    }
//    while(mFinishedCount<mProcessList.size() && !mStopped);
//}

int MultiProcess::count()
{
    return mProcessList.count();
}

Process *MultiProcess::at(int i)
{
    if(i<mProcessList.count())
        return mProcessList.at(i);
}

int MultiProcess::getSteps()
{
    return Process::getSteps();
}

void MultiProcess::onError(int code, QString cause)
{
    emit error(code, cause);
}

void MultiProcess::onAProcessFinished(){
    if(mStopped)
        return;
    qDebug() << QString("Process Finished - ") <<
                QString("Steps: ") <<
                QString::number(getSteps()) <<
                QString(" - FinishedCount: ") <<
                QString::number(mFinishedCount) <<
                QString(" - CurrentProcess: ") <<
                QString::number(mCurrentProcess);
    mFinishedCount++;
    if(mIsSequential){
        disconnect(mProcessList.at(mCurrentProcess),SIGNAL(finished()),this,SLOT(onAProcessFinished()));
        mCurrentProcess++;
        mRunningCount--;
        if(mCurrentProcess < mProcessList.size()){
            connect(mProcessList.at(mCurrentProcess),SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
            connect(mProcessList.at(mCurrentProcess),SIGNAL(finished()),this,SLOT(onAProcessFinished()));
            mProcessList.at(mCurrentProcess)->start();
            if(mWaitForFinished && mCurrentProcess == mProcessList.size()-1)
                 mProcessList.at(mCurrentProcess)->setWaitForFinished(true);
        }else{
            qDebug() << QString("Finished Sequential ") << getStartupMessage();
            emit finished();
        }
    }else{
        mRunningCount--;
        qDebug() << QString("...........................RunningCount ") << QString::number(mRunningCount);
        if (mRunningCount < mIdealThreadCount && mCurrentProcess < mProcessList.size()-1){
            mCurrentProcess++;
            mRunningCount++;
            connect(mProcessList.at(mCurrentProcess),SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
            connect(mProcessList.at(mCurrentProcess),SIGNAL(finished()),this,SLOT(onAProcessFinished()));
            mProcessList.at(mCurrentProcess)->start();
        }
        else if (mCurrentProcess+1 >= mProcessList.size() && mRunningCount == 0)
        {
            qDebug() << QString("Finished Non Sequential ") << getStartupMessage();
            emit finished();
        }
    }
}

void MultiProcess::OnChildStatusChanged(int step, QString childMessage){

    if(step)
        mCurrentStep++;
    QString message = childMessage;
    if (message.isEmpty())
        message=getStartupMessage();
    emit statusChanged(mCurrentStep,message);
}
void MultiProcess::OnChildStatusChangedNext(){


    emit statusChangedNext();
}

void MultiProcess::stop()
{
    Process::stop();
    for(int i=0 ; i<mProcessList.count(); i++){
        if(mProcessList.at(i)->isRunning())
            mProcessList.at(i)->stop();
    }
}
