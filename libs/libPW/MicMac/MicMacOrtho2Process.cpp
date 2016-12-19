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
#include "MicMacOrtho2Process.h"
#include "BasculeProcess.h"
#include "MicMacProcess.h"
#include "Nuage2PlyProcess.h"
#include "PortoProcess.h"
#include "AperiCloudProcess.h"


using namespace PW;

MicMacOrtho2Process::MicMacOrtho2Process(QString inputRegExp, QString orientation, QString micmacParamsFile, QString portoParamsFile, bool runBascule, bool expTxt)
{
//    setStartupMessage("MicMac Ortophoto...");
    setStartupMessage("Generating ortophoto-type model...");

    QString outputPath = inputRegExp.left(inputRegExp.lastIndexOf(QRegExp("/"))+1);

    if (runBascule){
        appendProcess(new BasculeProcess());
//        at(0)->addIntputs(QStringList()<<inputRegExp<<"PW"<<"Basc"<<"PostPlan=_Masq");
        QString expTxtStr="ExpTxt=0";
        if(expTxt)
            expTxtStr="ExpTxt=1";
        at(0)->addIntputs(QStringList()<<inputRegExp<< orientation <<"Basc"<<"PostPlan=_Masq"<<expTxtStr);

        AperiCloudProcess *aperiCloud = new AperiCloudProcess();
        aperiCloud->setStartupMessage(tr("Writting reoriented sparse model (.ply)"));
        aperiCloud->addIntputs(QStringList()<<inputRegExp<< "Basc" << "Out=Basc.ply" << expTxtStr);
        appendProcess(aperiCloud);
    }

    MicMacProcess *micmac = new MicMacProcess();
    micmac->addIntputs(QStringList()<< micmacParamsFile);
    appendProcess(micmac);

    PortoProcess *porto = new PortoProcess();
    porto->addIntputs(QStringList()<< portoParamsFile);
    appendProcess(porto);


    Nuage2PlyProcess * nuage2Ply = new Nuage2PlyProcess();
    nuage2Ply->addIntputs(QStringList()<<outputPath+"MM-Ter/NuageImProf_LeChantier_Etape_6.xml" <<"Attr="+outputPath+"ORTHO/Ortho.tif");
    appendProcess(nuage2Ply);
}
