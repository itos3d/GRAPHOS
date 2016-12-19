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
#ifndef PROCESS_H
#define PROCESS_H

#include <QThread>
#include <QStringList>



class Process: public QObject
{
    Q_OBJECT
public:
    Process();

    virtual void        start()=0;
    virtual void        setWaitForFinished(bool wait)=0;
    virtual bool        isRunning()=0;
    virtual QByteArray  readStdout()=0;
    virtual QByteArray  readStderr()=0;

    virtual bool        isStopped();
    virtual int         getSteps();

    void                addIntputs (QStringList inputs);
    QStringList         getOutputs ();
    QString             getStartupMessage();
    void                setStartupMessage(QString message);
    void                setSteps(int steps);

public slots:
    virtual void stop();


signals:
    void statusChanged(int step, QString message);
    void statusChangedNext();
    void finished();
    void error(int errorCode, QString errorMessage);

    //For real-time output reading.
    void readyReadStandardOutput();
    void readyReadStandardError();
    void newStdData(QString data);
    void newErrorData(QString data);


protected:
    QStringList mInputs;
    bool mStopped;

private:
    int mSteps;
    QString mStartupMessage;

};

#endif // PROCESS_H
