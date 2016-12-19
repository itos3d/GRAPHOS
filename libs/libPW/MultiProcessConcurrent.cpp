#include <QtConcurrentMap>
#include <QDebug>

#include "MultiProcessConcurrent.h"

using namespace PW;


MultiProcessConcurrent::MultiProcessConcurrent():
    mIsSequential(true),
    mCurrentProcess(-1)
{
}

MultiProcessConcurrent::MultiProcessConcurrent(bool isSequential):
    mIsSequential(isSequential)
{
    mWatcher = new QFutureWatcher<void>(this);
    connect(mWatcher, SIGNAL(resultReadyAt(int)), SLOT(onResultReadyAt(int)));
    connect(mWatcher, SIGNAL(finished()), SLOT(finished()));
}

MultiProcessConcurrent::~MultiProcessConcurrent(){
    for (int i=0; i<mProcessList.count(); i++)
        delete mProcessList.at(i);
}

QByteArray MultiProcessConcurrent::readStdout()
{
    if(mIsSequential && mCurrentProcess >= 0)
        return mProcessList.at(mCurrentProcess)->readStdout();
    else
        return "";
}

QByteArray MultiProcessConcurrent::readStderr()
{
    if(mIsSequential && mCurrentProcess >= 0)
        return mProcessList.at(mCurrentProcess)->readStderr();
    else
        return "";
}

void PW::MultiProcessConcurrent::appendProcess(PW::Process *process)
{
    mProcessList.append(process);
    connect(process,SIGNAL(readyReadStandardOutput()),this, SIGNAL(readyReadStandardOutput()));
    connect(process,SIGNAL(readyReadStandardError()),this, SIGNAL(readyReadStandardError()));
    connect(process,SIGNAL(newStdData(QString)),this, SIGNAL(newStdData(QString)));
    connect(process,SIGNAL(newErrorData(QString)),this, SIGNAL(newErrorData(QString)));
}

void PW::MultiProcessConcurrent::appendProcess(QList<Process*> processList){
    mProcessList.append(processList);
    for(int i=0; i< processList.count();i++){
        connect(processList.at(i),SIGNAL(readyReadStandardOutput()),this, SIGNAL(readyReadStandardOutput()));
        connect(processList.at(i),SIGNAL(readyReadStandardError()),this, SIGNAL(readyReadStandardError()));
        connect(processList.at(i),SIGNAL(newStdData(QString)),this, SIGNAL(newStdData(QString)));
        connect(processList.at(i),SIGNAL(newErrorData(QString)),this, SIGNAL(newErrorData(QString)));
    }
}

void PW::MultiProcessConcurrent::clearProcessList()
{
    for(int i=0; i< mProcessList.count();i++){
        disconnect(mProcessList.at(i),SIGNAL(readyReadStandardOutput()),this, SIGNAL(readyReadStandardOutput()));
        disconnect(mProcessList.at(i),SIGNAL(readyReadStandardError()),this, SIGNAL(readyReadStandardError()));
        disconnect(mProcessList.at(i),SIGNAL(newStdData(QString)),this, SIGNAL(newStdData(QString)));
        disconnect(mProcessList.at(i),SIGNAL(newErrorData(QString)),this, SIGNAL(newErrorData(QString)));
    }
    mProcessList.clear();
}

void PW::MultiProcessConcurrent::process(Process *process)
{
    process->start();
}

void PW::MultiProcessConcurrent::run()
{
    if(mIsSequential){
        mStopped = false;
        for(int i=0 ; i<mProcessList.count(); i++){
            if(!mStopped){
                mCurrentProcess = i;
                emit statusChanged(i,mProcessList.at(i)->getStartupMessage());
                connect(mProcessList.at(i),SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
                mProcessList.at(i)->start();
                mProcessList.at(i)->wait();
            }
        }
    }else{
        for(int i=0 ; i<mProcessList.count(); i++)
            connect(mProcessList.at(i),SIGNAL(error(int,QString)),this,SLOT(onError(int,QString)));
        mWatcher->setFuture(QtConcurrent::map(mProcessList, process));
        mWatcher->waitForFinished();
    }
}

int PW::MultiProcessConcurrent::count()
{
    return mProcessList.count();
}

Process *MultiProcessConcurrent::at(int i)
{
    if(i<mProcessList.count())
        return mProcessList.at(i);
}

int MultiProcessConcurrent::getSteps()
{
    return mProcessList.count();
}

void PW::MultiProcessConcurrent::onError(int code, QString cause)
{
    emit error(code, cause);
}

void PW::MultiProcessConcurrent::stop()
{
    Process::stop();
    for(int i=0 ; i<mProcessList.count(); i++){
        if(mProcessList.at(i)->isRunning())
            mProcessList.at(i)->stop();
    }
}

void PW::MultiProcessConcurrent::onResultReadyAt(int i)
{
    emit statusChanged(i, getStartupMessage());
}

void PW::MultiProcessConcurrent::finished()
{
    emit statusChanged(mProcessList.size(), getStartupMessage());
}

