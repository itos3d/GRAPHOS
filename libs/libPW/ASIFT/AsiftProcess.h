#ifndef ASIFTPROCESS_H
#define ASIFTPROCESS_H

#include "MultiProcess.h"
#include "PWImage.h"

namespace PW{

class AsiftProcess : public MultiProcess
{
public:
    AsiftProcess(QList<PWImage *> inputImages, QString outputPath, bool resize, int tilts);

private:
    QList<PWImage *> mInputImages;
};

}

#endif // ASIFTPROCESS_H
