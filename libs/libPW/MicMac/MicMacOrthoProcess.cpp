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
#include "MicMacOrthoProcess.h"
#include "TaramaProcess.h"
#include "MaltProcess.h"
#include "TawnyProcess.h"
#include "BasculeProcess.h"
#include "Nuage2PlyProcess.h"
#include "AperiCloudProcess.h"

using namespace PW;

MicMacOrthoProcess::MicMacOrthoProcess(QString inputRegExp, QString orientation, bool runBascule)
{
    //setStartupMessage("MicMac Ortophoto...");
    setStartupMessage("Generating ortophoto-type model...");

    QString outputPath = inputRegExp.left(inputRegExp.lastIndexOf(QRegExp("/"))+1);

//    appendProcess(new BasculeProcess());
//    at(0)->addIntputs(QStringList()<<inputRegExp<<"RadialStd"<<"Repere.xml"<<"PostPlan=_Masq");

//    appendProcess(new TaramaProcess());
//    at(1)->addIntputs(QStringList()<<inputRegExp<<"RadialStd"<<"Repere=Repere.xml"<<"Out=TA0");

    if (runBascule){
        appendProcess(new BasculeProcess());
//        at(0)->addIntputs(QStringList()<<inputRegExp<<"PW"<<"Basc"<<"PostPlan=_Masq");
        at(0)->addIntputs(QStringList()<<inputRegExp<< orientation <<"Basc"<<"PostPlan=_Masq");

        AperiCloudProcess *aperiCloud = new AperiCloudProcess();
        aperiCloud->setStartupMessage(tr("Writting reoriented sparse model (.ply)"));
        aperiCloud->addIntputs(QStringList()<<inputRegExp<< "Basc" << "Out=Basc.ply" );
        appendProcess(aperiCloud);

        appendProcess(new MaltProcess());
        at(2)->addIntputs(QStringList()<<"Ortho"<<inputRegExp<<"Basc"<<"SzW=1"<<"AffineLast=false"<<"DefCor=0.0");

        appendProcess(new TawnyProcess());
        at(3)->addIntputs(QStringList()<<outputPath + "Ortho-MEC-Malt/");

        appendProcess(new Nuage2PlyProcess());
        at(4)->addIntputs(QStringList()<<outputPath+"MEC-Malt/NuageImProf_STD-MALT_Etape_7.xml" <<"Attr="+outputPath+"/Ortho-MEC-Malt/Ortho-Eg-Test-Redr.tif");
    }

//    appendProcess(new MaltProcess());
//    at(2)->addIntputs(QStringList()<<"Ortho"<<inputRegExp<<"RadialStd"<<"Repere=Repere.xml"<<"DirTA=TA0"<<"SzW=1 ZoomF=1"<<"Regul=0.05");

//    Malt Ortho  "Abbey.*.jpg" L93 SzW=1 AffineLast=false DefCor=0.0

}
