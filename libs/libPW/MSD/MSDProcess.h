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
#ifndef MSDPROCESS_H
#define MSDPROCESS_H

#include <QMap>
#include "MultiProcess.h"
#include "ProcessedImageData.h"
#include "MSDMatching.h"

namespace PW {

class LIBPWSHARED_EXPORT MSDProcess : public MultiProcess
{
public:
    MSDProcess(QString projectBasePath, QStringList imagesPathList, QString outputPath,  QMap<QString, QString> MSDParameters,bool affine=true,int affineTilts =0);
    ~MSDProcess();

private:
    MultiProcess *mKPDProcess;
    MSDMatching *mMatchingProcess;
    QString matchesFolder;
    QStringList mImagesPathList;
    QMap<QString, ProcessedImageData*> mImageMetadataMap;
    QMap<QString, QString> mMSDParameters;
    bool removeDir(QString dirName);
    bool mAffine;
    int mAffineTilts;
};
}

#endif // MSDPROCESS_H
