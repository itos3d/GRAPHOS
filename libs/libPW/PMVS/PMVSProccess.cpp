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
#include "PMVSProccess.h"
#include "libPW.h"

#include <QTextStream>

using namespace PW;


PMVSProccess::PMVSProccess(QString pmvsDir, QString optionsFile, QMap<QString, QString> options):
    ExternalProcess(LibPW::getPMVSBinPath() + "/" + PMVS_PMVS_COMMAND),
    mOptions(options),
    mPMVSDir(pmvsDir)
{
    setStartupMessage("Generating PVMS Dense Model...");

    setStdOutputFilePath(LibPW::getStdErrorPath() + "/PMVS.log");
    setStdErrorFilePath(LibPW::getStdErrorPath() + "/PMVSError.log");

    QString workingDir = mCommandPath.left(mCommandPath.lastIndexOf(QRegExp("/")));
    //    workingDir = workingDir.left(workingDir.lastIndexOf(QRegExp("/"))+1);
    setWorkingDir(workingDir);

    addIntputs(QStringList() << pmvsDir << optionsFile);

}

void PMVSProccess::start()
{
    //****pmvs options: *******************

    QFile pmvsOptionsFile(mPMVSDir +  "/pmvs_options.txt");
    QString optionsString = "";
    QString optionsLine = "";
    if (pmvsOptionsFile.open(QIODevice::ReadOnly)){
        while (!pmvsOptionsFile.atEnd()) {
            optionsLine = QString(pmvsOptionsFile.readLine());
            for(int i=0; i<mOptions.count();i++){                
                if (optionsLine.contains(mOptions.keys().at(i))){
                    optionsLine = mOptions.keys().at(i) + " " + mOptions.values().at(i)+ "\r\n";
                    break;
                }
            }
            optionsString = optionsString + optionsLine;
        }
        pmvsOptionsFile.close();

        if(pmvsOptionsFile.open(QIODevice::WriteOnly)){
            QTextStream outputStream(&pmvsOptionsFile);
            outputStream << optionsString << "\n";

            pmvsOptionsFile.close();
        }
    }

    //*************************************
    ExternalProcess::start();
}
