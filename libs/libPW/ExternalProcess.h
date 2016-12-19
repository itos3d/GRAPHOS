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
#ifndef EXTERNALPROCESS_H
#define EXTERNALPROCESS_H

#include <QProcess>
#include <QFileSystemWatcher>
#include <QTimer>
#include <QFile>

#include "Process.h"

namespace PW{

class LIBPWSHARED_EXPORT ExternalProcess  : public Process
{
    Q_OBJECT

public:
    ExternalProcess(QString commandPath);
    ~ExternalProcess();

    virtual void start();
    virtual void setWaitForFinished(bool wait);
    virtual bool isRunning();

    void setWorkingDir(QString workingDir);
    void setErroLogFile(QString filePath);
    void setStdOutputFilePath(QString filePath);
    void setStdErrorFilePath(QString filePath);
    qint64 write(const char *data);

    virtual QByteArray readStdout();
    virtual QByteArray readStderr();

    //! Insert a evironment variable in the execution environment of de process overwriting it if existing
    /*!
        \param varName variable name
        \param  value new value
      */
//    virtual void insertEnvironmentVar(QString varName, QString value);
    void insertEnvironmentVar(QString varName, QString value);

    //! Append a value to an environment variable in the execution environment of de process using ";" as separator
    /*!
        \param varName variable name
        \param  value new value
        \param position 0 insert de value before (default). 1 insert value after.
      */
//    virtual void appendEnvironmentValue(QString varName, QString value, int position=0);
    void appendEnvironmentValue(QString varName, QString value, int position=0);

    //! direct call to QProcess::error()
    /*!
        \return Error code
      */
    virtual int error();

public slots:
    virtual void stop();

protected:
    void run();

    QString mCommandPath;
    QString mWorkingDir;

protected slots:
    void onError(QProcess::ProcessError commandError);
    void onError(QString path);
    void onTimeout();

private slots:
    void on_newStdData();
    void on_newErrorData();
    void on_mProcessFinished(int code);

private:
    QProcess *mProcess;
    int mErrorFileSize;
    QString mErrorFilePath;
    QString mStdOutputFilePath;
    QString mStdErrorFilePath;
    QFile *mStdOutFile;
    QFile *mErrOutFile;
    QFileSystemWatcher *mErrorWatcher;
    QTimer mTimer;
    bool mRunning;

    void cascadeKill(Q_PID pid);
};
}
#endif // EXTERNALPROCESS_H
