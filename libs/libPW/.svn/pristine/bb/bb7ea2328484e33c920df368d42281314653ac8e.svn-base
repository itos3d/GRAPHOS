#ifndef CONVERTPROCESS_H
#define CONVERTPROCESS_H

#include <QFutureWatcher>
#include <QProcess>

#include "Process.h"

namespace PW{
class ConvertProcess2 : public Process
{
public:
    ConvertProcess2(QStringList inputImages);
    static void convert(const QString &imageFileName);

    virtual QByteArray readStdout();
    virtual QByteArray readStderr();

protected:

    void run();

private:
        QStringList mInputImages;
        QFutureWatcher<void> *mImageConverting;

private slots:
        void onResultReadyAt(int i);
        void finished();
};
}


#endif // CONVERTPROCESS_H
