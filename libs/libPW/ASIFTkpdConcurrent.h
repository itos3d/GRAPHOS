#ifndef ASIFTKPDCONCURRENT_H
#define ASIFTKPDCONCURRENT_H

#include <QFutureWatcher>
#include <QProcess>

#include "Process.h"

namespace PW{
class ASIFTkpdConcurrent : public Process
{
public:
    ASIFTkpdConcurrent(QStringList inputImages, QString outputDir="", bool resize=true, int numTilts=7);

    static void process(const QString &imageFileName);

    virtual QByteArray readStdout();
    virtual QByteArray readStderr();

protected:

    void run();

private:

    static QString mOutputDir;
    static bool mResize;
    static int mNumTilts;

    QStringList mInputImages;
    QFutureWatcher<void> *mImageProcessing;

private slots:
    void onResultReadyAt(int i);
    void finished();
};
}

#endif // ASIFTKPDCONCURRENT_H
