#include <QtConcurrentMap>

#include "ASIFTkpdConcurrent.h"
#include "libPW.h"

using namespace PW;

bool        ASIFTkpdConcurrent::mResize         = true;
QString     ASIFTkpdConcurrent::mOutputDir      = "";
int         ASIFTkpdConcurrent::mNumTilts       = 7;

ASIFTkpdConcurrent::ASIFTkpdConcurrent(QStringList inputImages, QString outputDir, bool resize, int numTilts):
    mInputImages(inputImages)
{
    mResize = resize;
    mOutputDir = outputDir;
    mNumTilts = numTilts;

    mImageProcessing = new QFutureWatcher<void>(this);
    connect(mImageProcessing, SIGNAL(resultReadyAt(int)), SLOT(onResultReadyAt(int)));
    connect(mImageProcessing, SIGNAL(finished()), SLOT(finished()));
    setStartupMessage("Computing ASIFT keypoints...");
}

void ASIFTkpdConcurrent::process(const QString &imageFileName)
{
    QProcess process;
    QStringList args;
    args << imageFileName;

    if (mOutputDir.isEmpty())
        mOutputDir = imageFileName.left(imageFileName.lastIndexOf(QRegExp("/")));

    QString inputFileName = imageFileName.right(imageFileName.length()-imageFileName.lastIndexOf(QRegExp("/"))-1);
    args.append(mOutputDir + "/" + inputFileName+".keys");
    if(mResize)
        args.append("1");
    else
        args.append("0");
    args.append(QString::number(mNumTilts));

    process.start(LibPW::getAsiftBinPath() + "/" +  ASIFT_KPD_COMMAND, args);
    process.waitForFinished(-1);
}

QByteArray ASIFTkpdConcurrent::readStdout()
{
    return QByteArray("");
}

QByteArray ASIFTkpdConcurrent::readStderr()
{
    return QByteArray("");
}

void ASIFTkpdConcurrent::run()
{
    //imageConverting->setFuture(QtConcurrent::mapped(mInputImages, convert));
    mImageProcessing->setFuture(QtConcurrent::map(mInputImages, process));
    mImageProcessing->waitForFinished();
}

void ASIFTkpdConcurrent::onResultReadyAt(int i)
{
    emit statusChanged(i, getStartupMessage());
}

void ASIFTkpdConcurrent::finished()
{
    emit statusChanged(mInputImages.size(), getStartupMessage());
}
