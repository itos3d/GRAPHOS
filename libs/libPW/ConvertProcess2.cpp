#include <QtConcurrentMap>

#include "ConvertProcess2.h"
#include "libPW.h"

using namespace PW;

void ConvertProcess2::convert(const QString &imageFileName)
{
    QProcess process;
    QString pngFilePath = imageFileName.left(imageFileName.lastIndexOf(".")+1)
            + "png";

    QStringList inputs;
    inputs << imageFileName << pngFilePath;
    process.start(TOOLS_CONVERT_COMMAND, inputs);
    process.waitForFinished(-1);
}

QByteArray ConvertProcess2::readStdout()
{
    return QByteArray("");
}

QByteArray ConvertProcess2::readStderr()
{
    return QByteArray("");
}

ConvertProcess2::ConvertProcess2(QStringList inputImages):
    mInputImages(inputImages)
{
    mImageConverting = new QFutureWatcher<void>(this);
    connect(mImageConverting, SIGNAL(resultReadyAt(int)), SLOT(onResultReadyAt(int)));
    connect(mImageConverting, SIGNAL(finished()), SLOT(finished()));
    setStartupMessage("Converting images to png...");
}

void ConvertProcess2::run()
{
    //imageConverting->setFuture(QtConcurrent::mapped(mInputImages, convert));
    mImageConverting->setFuture(QtConcurrent::map(mInputImages, convert));
    mImageConverting->waitForFinished();
}

void ConvertProcess2::onResultReadyAt(int i)
{
    emit statusChanged(i, getStartupMessage());
}

void ConvertProcess2::finished()
{
    emit statusChanged(mInputImages.size(), getStartupMessage());
}
