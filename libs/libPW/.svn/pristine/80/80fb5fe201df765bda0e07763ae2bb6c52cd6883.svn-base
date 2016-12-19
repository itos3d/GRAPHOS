#ifndef MULTIPROCESSCONCURRENT_H
#define MULTIPROCESSCONCURRENT_H

#include <QList>
#include <QFutureWatcher>

#include "Process.h"

namespace PW{
class MultiProcessConcurrent : public Process
{

    Q_OBJECT

public:
    MultiProcessConcurrent();
    MultiProcessConcurrent(bool isSequential);
    ~MultiProcessConcurrent();

    virtual QByteArray readStdout();
    virtual QByteArray readStderr();

    void appendProcess(Process *process);
    void appendProcess(QList<Process*> processList);
    void clearProcessList();
    int count();
    Process * at(int i);

    virtual int getSteps();

public slots:
    static void process(Process *process);
    virtual void stop();

protected:
    void run();

private:
    QList<Process*> mProcessList;
    bool mIsSequential;
    int mCurrentProcess;
    QFutureWatcher<void> *mWatcher;

private slots:
    void onError(int code, QString cause);
    void onResultReadyAt(int i);
    void finished();

};
}

#endif // MULTIPROCESSCONCURRENT_H
