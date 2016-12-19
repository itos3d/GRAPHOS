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
#include "RadialBasic.h"
#include <QVector>
#include <math.h>

using namespace PW;

RadialBasic::RadialBasic():
    mK1(0.0),
    mK2(0.0)
{
}

int RadialBasic::getID()
{
    return APERO_MODEL_RADIAL_BASIC;
}

double PW::RadialBasic::getK1()
{
    return mK1;
}

double PW::RadialBasic::getK2()
{
    return mK2;
}

void PW::RadialBasic::setK1(double k1)
{
    mK1 = k1;
}

void PW::RadialBasic::setK2(double k2)
{
    mK2 = k2;
}

QString RadialBasic::undistort(QString inputImage, double focal, double xpp, double ypp)
{
    QString outputPath;

    return outputPath;
}

bool RadialBasic::canUnistort()
{
    return false;
}

void RadialBasic::undistort(double xpp, double ypp, double &x, double &y)
{
    double du_pp=x-xpp;
    double dv_pp=y-ypp;
    double xcd=xpp;
    double ycd=ypp;
    double du_cd=x-xcd;
    double dv_cd=y-ycd;
    double rho2_cd=(du_cd*du_cd+dv_cd*dv_cd);
    double cx_dr=0.0;
    double cy_dr=0.0;
    double cx_dr_before=-100000.0;
    double cy_dr_before=-100000.0;
    bool control=true;
    QVector<double> coeffsDist;
    coeffsDist.push_back(mK1);
    coeffsDist.push_back(mK2);
    while(control)
    {
        for(int nCoef=1;nCoef<=coeffsDist.size();nCoef++)
        {
            double coeffDist=coeffsDist[nCoef-1];
            cx_dr=cx_dr+du_cd*(pow(rho2_cd,nCoef))*coeffDist;
            cy_dr=cy_dr+dv_cd*(pow(rho2_cd,nCoef))*coeffDist;
        }
        if(fabs(cx_dr-cx_dr_before)<0.001&&abs(cy_dr-cy_dr_before)<0.001)
            control=false;
        else
        {
            cx_dr_before=cx_dr;
            cy_dr_before=cy_dr;
            du_cd=x-xcd-cx_dr;
            dv_cd=y-ycd-cy_dr;
            rho2_cd=(du_cd*du_cd+dv_cd*dv_cd);
            cx_dr=0.0;
            cy_dr=0.0;
        }
    }
    x=du_pp-cx_dr;
    y=dv_pp-cy_dr;
}

void RadialBasic::distort(double xpp, double ypp, double &x, double &y)
{
    double du_pp=x-xpp;
    double dv_pp=y-ypp;
    double xcd=xpp;
    double ycd=ypp;
    double du_cd=x-xcd;
    double dv_cd=y-ycd;
    double rho2_cd=(du_cd*du_cd+dv_cd*dv_cd);
    double cx_dr=0.0;
    double cy_dr=0.0;
    QVector<double> coeffsDist;
    coeffsDist.push_back(mK1);
    coeffsDist.push_back(mK2);
    for(int nCoef=1;nCoef<=coeffsDist.size();nCoef++)
    {
        double coeffDist=coeffsDist[nCoef-1];
        cx_dr=cx_dr+du_cd*(pow(rho2_cd,nCoef))*coeffDist;
        cy_dr=cy_dr+dv_cd*(pow(rho2_cd,nCoef))*coeffDist;
    }
    x=du_pp+cx_dr;
    y=dv_pp+cy_dr;
}
