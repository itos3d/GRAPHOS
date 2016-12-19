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
#include <QWaitCondition>
#include <QDebug>
#include <signal.h>

#include <iostream>

#include "ExternalProcess.h"

using namespace PW;

ExternalProcess::ExternalProcess(QString commandPath):
    mRunning(false)
{
//    mCommandPath = "\""+commandPath+"\"";
    mCommandPath = commandPath;
    setSteps(1);
    mProcess = new QProcess();
    mStdOutFile = new QFile();
    mErrOutFile = new QFile();
    mWorkingDir = "";
    mErrorFilePath = "pwErrors.log";
    QFileInfo fileInfo(mErrorFilePath);
    mErrorFileSize = fileInfo.size();
//    mProcess->setStandardErrorFile(mErrorFilePath);
//    mProcess->setStandardOutputFile(mErrorFilePath);

    mErrorWatcher = new QFileSystemWatcher(QStringList() << mErrorFilePath);

    connect(mErrorWatcher, SIGNAL(fileChanged(QString)),this,SLOT(onError(QString)));
    connect(this, SIGNAL(error(QProcess::ProcessError)),this,SLOT(onError(QProcess::ProcessError)));
    connect(mProcess,SIGNAL(readyReadStandardOutput()),this, SIGNAL(readyReadStandardOutput()));
    connect(mProcess,SIGNAL(readyReadStandardError()),this, SIGNAL(readyReadStandardError()));
    connect(mProcess,SIGNAL(readyReadStandardOutput()),this, SLOT(on_newStdData()));
    connect(mProcess,SIGNAL(readyReadStandardError()),this, SLOT(on_newErrorData()));
//    connect(&mTimer,SIGNAL(timeout()),this,SLOT(onTimeout()));
}

ExternalProcess::~ExternalProcess(){
    delete mProcess;
    delete mErrorWatcher;
    delete mStdOutFile;
    delete mErrOutFile;
}

void ExternalProcess::start()
{
    run();
}

void ExternalProcess::setWaitForFinished(bool wait)
{
    mProcess->waitForFinished();
}

bool ExternalProcess::isRunning()
{
    return mRunning;
}

void PW::ExternalProcess::run()
{
    mRunning = true;

    //Open log files:
    mStdOutFile->setFileName(mStdOutputFilePath);
    if(mStdOutFile->exists())
        mStdOutFile->open(QFile::WriteOnly);
    mErrOutFile->setFileName(mStdErrorFilePath);
    if(mErrOutFile->exists())
        mErrOutFile->open(QFile::WriteOnly);

    QDir workingDir(mWorkingDir);
    if (workingDir.exists(mWorkingDir))
        mProcess->setWorkingDirectory(mWorkingDir);
    connect(mProcess,SIGNAL(finished(int)),this, SLOT(on_mProcessFinished(int)));
    emit statusChanged(0,getStartupMessage());
//    std::cout<<"Working dir="<<mWorkingDir.toStdString()<<std::endl;
//    std::cout<<"Command path="<<mCommandPath.toStdString()<<std::endl;
//    std::cout<<"Inputs:"<<std::endl;
//    for(int ni=0;ni<mInputs.size();ni++)
//    {
//        if(ni==1)
//        {
//            QString input=mInputs[ni];
//            input=input.replace("\\","/");
//            input=""""+input+"""";
//            mInputs[ni]=input;
//        }
//        std::cout<<"input["<<QString::number(ni).toStdString()<<"]="<<mInputs[ni].toStdString()<<std::endl;
//    }
    mProcess->start(mCommandPath, mInputs);
}

void PW::ExternalProcess::setWorkingDir(QString workingDir)
{
    mWorkingDir = workingDir;
//    mWorkingDir = "\""+workingDir+"\"";
}

void PW::ExternalProcess::onError(QProcess::ProcessError commandError)
{
    stop();
    emit Process::error(1, mCommandPath);
}

void PW::ExternalProcess::onError(QString path)
{
    QFileInfo fileInfo(mErrorFilePath);
    int errorFileSize = fileInfo.size();
    if (errorFileSize > 0 && (errorFileSize - mErrorFileSize) < 0){
        stop();
        emit Process::error(1, mCommandPath);
    }
}

void ExternalProcess::onTimeout()
{
    mProcess->write("\n");
    mTimer.start(5000);
}

void ExternalProcess::on_newStdData()
{
    QByteArray array = readStdout();
    QString out(array);
    emit newStdData(out);
    if(mStdOutFile->exists()){
        mStdOutFile->write(array);
    }
}

void ExternalProcess::on_newErrorData()
{
    QByteArray array = readStderr();
    QString out(array);
    emit newErrorData(out);
    if(mErrOutFile->exists()){
        mErrOutFile->write(array);
    }
}

void ExternalProcess::on_mProcessFinished(int code)
{
    disconnect(mProcess,SIGNAL(finished(int)),this, SLOT(on_mProcessFinished(int)));
    emit statusChanged(1,getStartupMessage());
    mRunning = false;

    //Close log files:
    if(mStdOutFile->exists())
        mStdOutFile->close();
    if(mErrOutFile->exists())
        mErrOutFile->close();

    qDebug() << QString(" ************** Finishing: ") << mCommandPath <<
                QString(" ExitCode: ") << QString::number(code) << QString(" ExitCode: ") << this->objectName();
    emit finished();
}

void PW::ExternalProcess::stop()
{   
    Process::stop();
    cascadeKill(mProcess->pid());
    mProcess->kill();
}

void PW::ExternalProcess::setErroLogFile(QString filePath)
{
    mErrorWatcher->removePath(mErrorFilePath);
    mErrorFilePath = filePath;

    QFileInfo fileInfo(mErrorFilePath);
    mErrorFileSize = fileInfo.size();
//    mProcess->setStandardErrorFile(mErrorFilePath);

    mErrorWatcher->addPath(mErrorFilePath);
}

void PW::ExternalProcess::setStdOutputFilePath(QString filePath)
{
    mStdOutputFilePath = filePath;
//    mProcess->setStandardOutputFile(filePath);
}

void PW::ExternalProcess::setStdErrorFilePath(QString filePath)
{
    mStdErrorFilePath = filePath;
//    mProcess->setStandardErrorFile(filePath);
}

qint64 ExternalProcess::write(const char *data)
{
    return mProcess->write(data);
}

QByteArray ExternalProcess::readStdout()
{
    return mProcess->readAllStandardOutput();
}

QByteArray ExternalProcess::readStderr()
{
    return mProcess->readAllStandardError();
}

void ExternalProcess::insertEnvironmentVar(QString varName, QString value)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert(varName, value);
    mProcess->setProcessEnvironment(env);
}

void ExternalProcess::appendEnvironmentValue(QString varName, QString value, int position)
{
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    QString newValue = env.value(varName);
    QString separator = "";
    if (!newValue.isEmpty())
        separator = ";";
    if (position)
        newValue = newValue + separator + value;
    else
        newValue = value + separator + newValue;
    env.insert(varName, newValue);
    mProcess->setProcessEnvironment(env);
}

int ExternalProcess::error()
{
    return mProcess->error();
}

void ExternalProcess::cascadeKill(Q_PID pid){
#ifdef Q_OS_LINUX
    QProcess killer;
    QStringList params;
    params << "--ppid";
    params << QString::number(pid);
    params << "-o";
    params << "pid";
    params << "--noheaders";
    killer.start("/bin/ps",params,QIODevice::ReadOnly);
    if(killer.waitForStarted(-1))
    {
        if(killer.waitForFinished(-1))
        {
            QByteArray temp=killer.readAllStandardOutput();
            QString str=QString::fromLocal8Bit(temp);
            QStringList list=str.split("\n");

            for(int i=0;i<list.size();i++)
            {
                if(!list.at(i).isEmpty())
//                    ::kill(list.at(i).toInt(),SIGKILL);
                    cascadeKill(list.at(i).toInt());
            }
            ::kill(pid,SIGKILL);
        }
    }
#endif
}
