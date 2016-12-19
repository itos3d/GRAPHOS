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
#include "cvDecolorProcess.h"
#include "opencv2/photo.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/core.hpp"
#include <QFileInfo>
using namespace PW;

cvDecolorProcess::cvDecolorProcess(QString inputFile, QString outputDir):mInputFile(inputFile),
    mOtputDir(outputDir)
{
    setStartupMessage("Preprocessing images (decolorization)...");

}

cvDecolorProcess::~cvDecolorProcess()
{

}


void cvDecolorProcess::run(){
    QFileInfo fileInfo(mInputFile);
    QString *stdData = new QString();
    if (fileInfo.isFile()){
        std::string filename = fileInfo.filePath().toLatin1();
        cv::Mat I;
        I = cv::imread(filename,CV_LOAD_IMAGE_UNCHANGED);
        std::string outputFile;
        outputFile.clear();
        outputFile.append(mOtputDir.toUtf8().constData());
        outputFile.append("/");
        outputFile.append(fileInfo.fileName().split(".").first().append(".tif").toUtf8().constData());

        if (I.channels()!=1) {
            stdData->clear();
            stdData->append("Decoloring image ");
            stdData->append(fileInfo.fileName());
            emit newStdData(stdData->toAscii());
            cv::Mat gray = cv::Mat(I.size(),CV_8UC1);
            cv::Mat color_boost = cv::Mat(I.size(),CV_8UC3);
            cv::decolor(I,gray,color_boost);

            cv::imwrite(outputFile, gray );
        }else {
            cv::imwrite(outputFile, I);
        }

        stdData->clear();
        stdData->append("Writing preprocessed image: ");
        stdData->append(fileInfo.fileName());
        emit newStdData(stdData->toAscii());

    }
}
